#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <stdexcept>

#include "Card.h"
#include "Player.h"

class Game {
 private:
  std::vector<Player*> players;
  std::vector<std::string> suits;
  std::vector<std::string> ranks;
  std::vector<Card*> deck;
  std::vector<Card*> drawPile;
  std::vector<Card*> discardPile;

 public:
  Game();
  void loadDeckFromFile(std::string filename);
  void addPlayer(bool isAI);
  void drawCard(Player* p);
  Card* deal(int numCards);
  std::string mostPlayedSuit();
  int runGame();
  ~Game();
};

#endif
