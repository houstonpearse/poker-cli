#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include "deck.c"

#define MAX_PLAYERS 10

typedef struct {
    int sort;
    int players;
    int hands;
    int seed;
    char *table;
    char *hand;
} args;

const struct option long_opts[] = {
    {"help",no_argument,NULL,'h'},
    {"players", required_argument, NULL, 'p'},
    {"hands", required_argument, NULL, 'n'},
    {"seed", required_argument, NULL, 's'},
    {"table", required_argument, NULL, 't'},
    {"hand", required_argument,NULL, 'a'},
    {NULL, 0, NULL, 0}
};

const char *short_opts = "h:p:n:s:t:a:";

void print_help() {
    printf("Usage:\n");
    printf("\t./poker-cli\n");
    printf("\t./poker-cli [--players <int> --hands <int> --seed <int> ]\n");
    printf("\t./poker-cli [--players <int> --hands <int>  --hand [<card>]'A-S,A-C' --table [<card]'A-H,A-D']\n");
    printf("\tcat hands.txt | ./poker-cli sort\n");
    printf("\nOption Values:\n");
    printf("\tplayers<int> must be between 1 and 10\n");
    printf("\thands<int> must be greater than 0\n");
    printf("\tseed<int> must be greater than 0\n");
    printf("\thand[<card>] must be a list of 1 or 2 cards separated by ',' or ' '\n");
    printf("\ttable[<card>] must be a list of 1 to 5 cards separated by ',' or ' '\n");
    printf("\nOption types:\n");
    printf("\t<card> must be in the format '<value>-<suit>' where value \n");
    printf("\t<value> must be one of the following: A 1 2 3 4 5 6 7 8 9 T J Q K\n");
    printf("\t<suit> must be one of the following: H D C S\n");
}

void parse_args(int argc, char **argv, args *program_args) {
    int num=0,index;
    char c;
    while ((c = getopt_long(argc,argv,short_opts,long_opts,&index)) != -1) {
        switch (c) {
            case 'h':
                print_help();
                exit(0);
            case 'p':
                if ((atoi(optarg) <= MAX_PLAYERS) && (atoi(optarg) >= 1)) {
                    program_args->players = atoi(optarg);
                } else {
                    fprintf(stderr,"players must be an integer between 1 and 10 inclusive\n");
                    exit(1);
                }
                break;
            case 'n':
                if (atoi(optarg)>0) {
                    program_args->hands = atoi(optarg);
                } else {
                    fprintf(stderr,"hands must be an integer > 0\n");
                    exit(1);
                }
                break;
            case 's':
                if (atoi(optarg)>0) {
                    program_args->seed = atoi(optarg);
                } else {
                    fprintf(stderr,"seed must be an integer > 0");
                    exit(1);
                }
                break;
            case 't':
                num = check_cards(optarg);
                if ( num==0 || num>5 ) {
                    fprintf(stderr,"Error: %s \nTable option must contain between 1 and 5 table cards\n",optarg);
                    fprintf(stderr,"e.g --table 'A-S,A-C'\n");
                    print_help();
                    exit(1);
                }
                program_args->table = (char*)malloc((strlen(optarg)+1)*sizeof(char));
                strcpy(program_args->table,optarg);
                break;
            case 'a':
                num = check_cards(optarg);
                if ( num==0 || num>2 ) {
                    fprintf(stderr,"Error: %s \nHand option must contain either 1 or 2 cards\n",optarg);
                    fprintf(stderr,"e.g --hand 'A-S,A-C'\n");
                    print_help();
                    exit(1);
                }
                program_args->hand = (char*)malloc((strlen(optarg)+1)*sizeof(char));
                strcpy(program_args->hand,optarg);
                break;
        }
    }
    int i;
    for (i = optind; i < argc; i++) {
        if (strcmp(argv[i],"sort")==0) {
            program_args->sort = 1;
        } else {
            fprintf(stderr,"Unknown argument: %s\n",argv[i]);
            print_help();
            exit(1);
        }
    }  
}

