#include <stdio.h>
#include "poker.c"
#include "args.c"

#define DEFAULT_PLAYERS 5
#define DEFAULT_HANDS 1
#define DEFAULT_SEED time(NULL)
#define INITIAL_ARR_SIZE 1
#define DEFAULT_COMMAND 0 // sim
#define DEFAULT_VERBOSE 0

typedef struct {
    int won;
    int lost;
    int tied;
}stats_t;

void sort();
void simulation(int num_players, int hands,int seed, char *table_arg, char *hand_arg, int verbose);

int main(int argc, char **argv) {
    args program_args = {DEFAULT_COMMAND, DEFAULT_PLAYERS, DEFAULT_HANDS, DEFAULT_SEED, DEFAULT_VERBOSE, NULL, NULL};
    parse_args(argc, argv, &program_args);
    if (program_args.sort) {
        sort();
    } else {
        simulation(program_args.players, program_args.hands, program_args.seed, program_args.table, program_args.hand, program_args.verbose);
    }
    return 0;
}

void simulation(int num_players, int hands,int seed, char *table_arg, char *hand_arg, int verbose) {
    deck_t deck;
    deck_t players[10]={{{},0,0}};
    deck_t table;
    stats_t stats = {0,0,0};
    int i;
    srand(seed);
    if (verbose) printf("seed: %d\n",seed);
    fill_deck(&deck);
    for (i=0;i<hands;i++) {
        reset_game(&deck,&table,players,num_players);
        shuffle_deck(&deck);
        add_cards(&deck,&players[0],hand_arg);
        add_cards(&deck,&table,table_arg);
        play_game(&deck,&table,players,num_players);
        sort_hands(&table,players,num_players);
        if (verbose) print_game(i+1,&table,players,num_players);
        if (players[0].id == 0) {
            if (compare_hand(&table,&players[0],&players[1])==0) {
                stats.tied++;
            }
            stats.won++;
        } else {
            stats.lost++;
        }
    }
    printf("win,lost,tied\n%.3f,%.3f,%.3f\n",stats.won/(float)hands,stats.lost/(float)hands,stats.tied/(float)hands);

   return;
}

void sort() {
    int i;
    char *line=NULL;
    size_t len;
    deck_t *players = (deck_t*)malloc(INITIAL_ARR_SIZE*sizeof(deck_t));
    int arr_size=INITIAL_ARR_SIZE;
    int num_players=0;
    int num_cards = 0;
    while (getline(&line,&len,stdin) != -1) {
        if (num_cards == 0) {
            num_cards = check_cards(line);
            if (num_cards==0) {
                printf("Enter Cards\n");
                continue; 
            }
        }
        if (check_cards(line) == num_cards) {
            if (arr_size == num_players) {
                players = (deck_t*)realloc(players,2*arr_size*sizeof(deck_t));
                arr_size *= 2;
            }
            add_new_cards(&players[num_players],line);
            num_players++;
        } else if (check_cards(line) == 0){
            break;     
        } else {
            fprintf(stderr,"Error: %s num cards must be consistent\n use --help for card formatting help\n",line);
            exit(1);  
        } 
    }
    sort_hands(NULL,players,num_players);
    for (i=0;i<num_players;i++) {
        if (i!=0) printf("\n");
        print_deck(&players[i]);
    }
}