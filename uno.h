#ifndef UNO_H
#define UNO_H

#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"

// Prototypes:
int check_card(std::vector<Player> &v, int cur, Deck &deck, Deck &discard, Card &c);
int reverse_order(std::vector<Player> &v, std::string name);
int start_game(int num_plyrs);
void create_players(std::vector<Player> &players, int num_plyrs, Deck &deck);
void make_discard(Deck &deck, Deck &discard, Card &dropped_c);

// Friend functions:
void print_hand(const Player &p);
bool can_drop(Player &p, Deck &discard);
bool check_uno(const Player &p);
bool check_win(const Player &p);

#endif