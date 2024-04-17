#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.c"

#define PLAYER_HAND_SIZE 2
#define TABLE_SIZE 5

/* deal cards to players and table*/
void play_game(deck_t *deck, deck_t *table, deck_t players[],int player_count) {
    int i,j;
    for (i=0;i<TABLE_SIZE;i++) {
        if (table->numcards<TABLE_SIZE) {
            draw_card(deck,table);
        }
    }
    for (i=0;i<player_count;i++) {
        for (j=0;j<PLAYER_HAND_SIZE;j++) {
            if (players[i].numcards<PLAYER_HAND_SIZE) {
                draw_card(deck,&players[i]);
            }
        }
        players[i].id=i;
    }
}

void reset_game(deck_t *deck,deck_t *table, deck_t players[],int player_count) {
    int i;
    table->numcards = 0;
    for (i=0;i<player_count;i++) {
        players[i].numcards = 0;
    }
    deck->numcards = DECKSIZE;
}

/* must have equal sized hands */
int compare_hands(const void *a, const void *b) {
    deck_t *player1 = (deck_t*)a, *player2 = (deck_t*)b;
    int i,j,k; 
    int p1[NUMVALS][NUMSUITS]={{0}},p2[NUMVALS][NUMSUITS]={{0}};
    for (i=0;i<player1->numcards;i++) {
        for (j=0;j<NUMVALS;j++) {
            for (k=0;k<NUMSUITS;k++) {
                if ((player1->cards[i][0] == values[j]) &&
                    (player1->cards[i][2] == suits[k])) {
                    p1[j][k]++;
                }
                if ((player2->cards[i][0] == values[j]) &&
                    (player2->cards[i][2] == suits[k])) {
                    p2[j][k]++;
                }
            }
        }
    }
    
    // straight flush + royal flush -- no kicker
    int p1len,p2len;
    for (j=0;j<NUMSUITS;j++) {
        p1len=p2len=0;
        for (i=NUMVALS-1;i>=0;i--) {
            if (p1[i][j]){
                p1len++;
            } else {
                p1len=0;
            }
            if (p2[i][j]){
                p2len++;
            } else {
                p2len=0;
            }
            if (p1len==5 && p2len==5){
                return 0;
            } else if (p1len == 5) {
                return -1;
            } else if (p2len == 5) {
                return 1;
            }
        }
        if (p1[NUMVALS-1][j]) p1len++; // check ace card
        if (p2[NUMVALS-1][j]) p2len++; // check ace card
        if (p1len==5 && p2len==5){
            return 0;
        } else if (p1len == 5) {
            return -1;
        } else if (p2len == 5) {
            return 1;
        }
    } 

    // quads - single kicker
    int p1kicker=-1,p2kicker=-1;
    int tied=0;
    p1len=p2len=0;
    for (i=NUMVALS-1;i>=0;i--) {
        p1len=p2len=0;
        for (j=0;j<NUMSUITS;j++) {
            p1len+=p1[i][j];
            p2len+=p2[i][j];
        }
        if (tied) {
            // kicker is lower than quads
            if (p1len>0 && p2len>0) return 0;
            if (p1len>0) return -1;
            if (p2len>0) return 1;
        }
        if (p1len==4 && p2len==4) {
            //tied quads
            if (p1kicker!=-1 && p2kicker!=-1) {
                return p2kicker-p1kicker;
            }
            tied=1;
        } else if (p1len == 4) {
            return -1;
        } else if (p2len == 4) {
            return 1;
        } else if (p1len>0){
            p1kicker=i;
        } else if (p2len>0) {
            p2kicker=i;
        }
    }

    // fullhouse
    int p1two=-1,p2two=-1,p1three=-1,p2three=-1;
    for (i=NUMVALS-1;i>=0;i--) {
        p1len=p2len=0;
        for (j=0;j<NUMSUITS;j++) {
            p1len+=p1[i][j];
            p2len+=p2[i][j]; 
        }
        if (p1len==3 && p1three==-1) {
            p1three=i;
        } else if (p1len>=2 && p1two==-1) {
            p1two=i;
        }
        if (p2len==3 && p2three==-1) {
            p2three=i;
        } else if (p2len>=2 && p2two==-1){
            p2two=i; 
        } 
        if (p2two!=-1 && p2three!=-1 && p1two!=-1 && p1three!=-1) {
            if (p1three==p2three){
                return p2two-p1two;
            }
            return p2three-p1three;
        }
        
    }

    // flush
    int p1flush=0,p2flush=0;
    for (j=0;j<NUMSUITS;j++) {
        p1len=p2len=0;
        for (i=NUMVALS-1;i>=0;i--) {
            if (p1[i][j]) p1len++;
            if (p2[i][j]) p2len++;
        }
        if (p1len>=5) p1flush=1;
        if (p2len>=5) p2flush=1;
    } 
    if (p1flush && p2flush){
        // tiebreak flush
        p1len=p2len=0;
        for (i=NUMVALS-1;i>=0;i--) {
            for(j=0;j<NUMSUITS;j++) {
                if (p1[i][j]) p1len++;
                if (p2[i][j]) p2len++;
            }
            if (p1len != p2len) {
                return p2len-p1len;
            }
        }
        if (p1len==p2len) return 0;
    } else if (p1flush) {
        return -1;
    } else if (p2flush) {
        return 1;
    }

    // straight
    p1len=p2len=0;
    int p1val,p2val;
    int p1ace=1,p2ace=1;
    for (i=NUMVALS-1;i>=0;i--) {
        p1val=p2val=0;
        for (j=0;j<NUMSUITS;j++) {
            if (p1[i][j]) p1val++;
            if (p2[i][j]) p2val++;
        }
        if (p1val) {
            if (i==NUMVALS-1) p1ace=1;
            p1len++;
        } else {
            p1len=0;
        }
        if (p2val) {
            if (i==NUMVALS-1) p2ace=1;
            p2len++;
        } else {
            p2len=0;
        }
        if (p1len==5&&p2len==5) return 0;
        if (p1len==5) return -1;
        if (p2len==5) return 1;
    }
    if (p1ace) p1len++;
    if (p2ace) p2len++;
    if (p1len==5&&p2len==5) return 0;
    if (p1len==5) return -1;
    if (p2len==5) return 1;

    // triple -- two kickers
    int p1kicker1=-1;
    int p2kicker1=-1;
    int p1kicker2=-1;
    int p2kicker2=-1;
    p1three=-1;
    p2three=-1;
    for (i=NUMVALS-1;i>=0;i--) {
        p1len=p2len=0;
        for (j=0;j<NUMSUITS;j++) {
            p1len+=p1[i][j];
            p2len+=p2[i][j]; 
        }
        if (p1len==1 && p1kicker1!=-1 && p1kicker2==-1) p1kicker2=i; // set second kicker
        if (p2len==1 && p2kicker1!=-1 && p2kicker2==-1) p2kicker2=i;
        if (p1len==1 && p1kicker1==-1) p1kicker1=i; // set first kicker
        if (p2len==1 && p2kicker1==-1) p2kicker1=i;
        if (p1len==3 && p1three==-1) p1three=i; // set three of a kind
        if (p2len==3 && p2three==-1) p2three=i;
        if (p1three!=-1 && p2three!=-1) {
            // tie break triple with 2 kickers
            if (p1kicker1!=p2kicker1) return p2kicker1-p1kicker1; // kicker 1 are not tied
            if (p1kicker2!=p2kicker2) return p2kicker2-p1kicker2; // kicker 2 are not tied
            if (p1kicker2!=-1) return 0; // kicker 1 and 2 are tied
            // kickers are either tied or have no vals
        } else if (p1three!=-1) {
            return -1;
        } else if (p2three!=-1) {
            return 1;
        }
    }

    // two pair
    // pair
    // high card
    int p1first=-1,p2first=-1,p1second=-1,p2second=-1;
    p1kicker=-1,p2kicker=-1;
    int equalkickernum=0;
    for (i=NUMVALS-1;i>=0;i--) {
        p1len=p2len=0;
        for (j=0;j<NUMSUITS;j++) {
            p1len+=p1[i][j];
            p2len+=p2[i][j]; 
        }
        if (p1len==2 && p1second!=-1 && p1kicker==-1) p1kicker=i; // three pairs
        if (p2len==2 && p2second!=-1 && p2kicker==-1) p2kicker=i; // three pairs
        if (p1len==2 && p1first!=-1 && p1second==-1) p1second=i;
        if (p2len==2 && p2first!=-1 && p2second==-1) p2second=i;
        if (p1len==2 && p1first==-1) p1first=i;
        if (p2len==2 && p2first==-1) p2first=i;
        if (p1len==1 && p1kicker==-1) p1kicker=i;
        if (p2len==1 && p2kicker==-1) p2kicker=i;
        if (p1kicker!=-1 && p1kicker==p2kicker) {
            p1kicker=-1;
            p2kicker=-1;
            equalkickernum+=1;
        }
    }
    // printf("%d %d %d\n",p1first,p1second,p1kicker);
    // printf("%d %d %d\n",p2first,p2second,p2kicker);
    // printf("%d\n",equalkickernum);
    if (p1first!=-1 && p2first!=-1) { // both have at least 1 pair
        if (p1second!=-1 && p2second !=-1) { // both have 2 pairs
            if (p1first==p2first) {
                if (p1second==p2second) {
                    if (equalkickernum<1) {
                        return p2kicker-p1kicker;
                    }
                    return 0;
                }
                return p2second-p1second;
            }
            return p2first-p1first;
        }
        if (p1second!=p2second) return p2second-p1second; // two pair and one pair
        if (p1first==p2first) { // both have 1 pair of equal rank
            if (equalkickernum<3) {
                return p2kicker-p1kicker;
            }
            return 0;
        }
        return p2first-p1first; 
    }
    if (p1first!=p2first){ // only 1 has a pair
        return p2first-p1first;
    }
    if (equalkickernum<5) { // both no pairs
        return p2kicker-p1kicker;
    }
    return 0;
}

void sort_hands(deck_t *table, deck_t players[], int player_count) {
    int i,j;
    if (table != NULL) {
        for (i=0; i<player_count;i++) {
            for (j=0; j<table->numcards;j++){
                add_card_reference(&players[i],table->cards[j]);
            }
        }
    }
    qsort(players,player_count,sizeof(deck_t),compare_hands);
    if (table != NULL) {
        for (i=0; i<player_count;i++) {
            players[i].numcards -= table->numcards;
        }
    }
}

void print_hands(deck_t players[],int num_players) {
    int i;
    for (i=0;i<num_players;i++) {
        if (i!=0) printf("\n");
        printf("player%d: ",players[i].id);
        print_deck(&players[i]);
    }
}

void print_game(int id, deck_t *table, deck_t players[],int num_players) {
    printf("game %d\n",id);
    printf("table: ");
    print_deck(table);
    printf("\n");
    print_hands(players,num_players);
    printf("\n");
}