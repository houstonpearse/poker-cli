#ifndef _DECK_
#define _DECK_

#include <stdlib.h>
#include <stdio.h>

#define CARD_STR_LEN 3
#define CARD_SEPERATOR '-'
#define DECKSIZE 52
#define NUMSUITS 4
#define NUMVALS 13

typedef struct{
    char *cards[DECKSIZE];
    int numcards;
    int id;
} deck_t;

const char suits[] = {'S','C','H','D'};
const char values[] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};

/* create a new card */
char *new_card(char val, char suit) {
    char sep=CARD_SEPERATOR;
    char *card = (char*)malloc((CARD_STR_LEN+1)*sizeof(char));
    card = strncpy(card,&val,1);
    card = strncat(card,&sep,1);
    card = strncat(card,&suit,1); 
    return card;
}

/* adds all cards to a deck */
void fill_deck(deck_t *deck) {
    int i,j,k=0;
    deck->numcards = DECKSIZE; 
    for (i=0;i<NUMVALS;i++) {
        for (j=0;j<NUMSUITS;j++) {
            deck->cards[k] = new_card(values[i],suits[j]);
            k++;
        }
    }
    deck->id = 0;
}

void card_swap(char **s1,char **s2) {
    char *temp;
    temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

/* shuffles deck by performaing a fisher-yates shuffle 
see: https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle 
*/
void shuffle_deck(deck_t *deck) {
    int i;
    for (i=deck->numcards-1;i>0;i--) {
        card_swap(&deck->cards[i],&deck->cards[rand()%(i+1)]);
    }
}

void draw_card(deck_t *deck,deck_t *player) {
    if (deck->numcards == 0){
        return;
    }
    player->cards[player->numcards]=deck->cards[deck->numcards-1];
    player->numcards += 1;
    deck->numcards -=1;
}

/* add card reference to players hand */
void add_card_reference(deck_t *player, char *card) {
    player->cards[player->numcards] = card;
    player->numcards++;
}

/* adds specific card from the deck to the playes hand */
int add_card(deck_t *deck, deck_t *player, char *card) {
    int i;
    for (i=0;i<deck->numcards;i++) {
        if (strncmp(deck->cards[i],card,CARD_STR_LEN) == 0) {
            add_card_reference(player,deck->cards[i]);
            card_swap(&deck->cards[i],&deck->cards[deck->numcards-1]);
            deck->numcards--;
            return 1;
        }
    }
    printf("Warning Failed to add card: %s. This card is not vaild",card);
    return 0;
}

/* add_cards*/
int add_cards(deck_t *deck, deck_t *player, char *cards) {
    if (cards == NULL) return 0;
    while (strlen(cards) >= CARD_STR_LEN) {
        if (cards[0] == ' ' || cards[0] == ',') {
            cards += sizeof(char);
        } else if (add_card(deck,player,cards)) {
            cards += CARD_STR_LEN*(sizeof(char));
        } else {
            return 0;
        }
    }
    return 1;
}

/* add a new card from outside the deck to the players hand 
    returns 1 on success 0 on failure
*/
int add_new_card(deck_t *player, char *card) {
    int i;
    int suit=0,val=0;
    if (card[1] != CARD_SEPERATOR) return 0;
    for (i=0;i<NUMVALS;i++) {
        if (card[0] == values[i]) val = 1;
    }
    for (i=0;i<NUMSUITS;i++) {
        if (card[2] == suits[i]) suit = 1;
    }
    if (val && suit) {
        add_card_reference(player, new_card(card[0],card[2]));
    } else {
        return 0;
    }
    return 1;
}

/* add cards to players hand */
int add_new_cards(deck_t *player, char *cards) {
    while (strlen(cards) >= CARD_STR_LEN) {
        if (cards[0] == ' ' || cards[0] == ',') {
            cards += sizeof(char);
        } else if (add_new_card(player,cards)) {
            cards += CARD_STR_LEN*(sizeof(char));
        } else {
            return 0;
        }
    }
    return 1;
}

int check_card(char *card) {
    if (strlen(card) < CARD_STR_LEN) return 0;
    if (card[1] != CARD_SEPERATOR) return 0;
    int i,val=0,suit=0;
    for (i=0;i<NUMVALS;i++) {
        if (card[0] == values[i]) {
            val=1;
        }
    }
    for (i=0;i<NUMSUITS;i++) {
        if (card[2] == suits[i]) {
           suit=1;
        }
    }
    if (suit && val) return 1;
    return 0;
}

int check_cards(char *cards) {
    int n=0;
    while (strlen(cards) >= CARD_STR_LEN) {
        if (cards[0] == ' ' || cards[0] == ',') {
            cards += sizeof(char);
        } else if (check_card(cards)) {
            cards += CARD_STR_LEN*(sizeof(char));
            n++;
        } else {
            return 0;
        }
    }
    return n;
}

void print_deck(deck_t *deck) {
    int i;
    for (i=0;i<deck->numcards;i++) {
        printf("%s",deck->cards[i]);
        if (i!=deck->numcards-1) {
            printf(",");
        }
    }
}

#endif