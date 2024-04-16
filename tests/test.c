#include <assert.h>
#include <string.h>
#include "../src/deck.c"

void test_new_card() {
    char *card1 = new_card('K','S');
    char *card2 = "K-S";
    assert(strcmp(card1,card2)==0);
}

void test_new_deck() {
    deck_t deck;
    char *lastcard = "A-D";
    char *firstcard = "2-S";
    fill_deck(&deck);
    assert(strcmp(deck.cards[deck.numcards-1],lastcard)==0);
    assert(strcmp(deck.cards[0],firstcard)==0);
    assert(deck.numcards==52);
}

void test_card_swap() {
    deck_t deck;
    char *firstcard = "2-S";
    fill_deck(&deck);
    assert(strcmp(deck.cards[0],firstcard)==0);
    card_swap(&deck.cards[0],&deck.cards[1]);
    assert(strcmp(deck.cards[1],firstcard)==0);
}

void test_draw_card() {
    deck_t deck;
    deck_t player={{},0,0};
    char *lastcard = "A-D";
    fill_deck(&deck);
    draw_card(&deck,&player);
    assert(strcmp(player.cards[0],lastcard)==0);
}

int main(int argc, char **argv) {
    test_new_card();
    test_new_deck();
    test_card_swap();
    test_draw_card();
    printf("\u2705 tests passed\n");
}