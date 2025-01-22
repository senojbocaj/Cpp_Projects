#include "Game.h"

#include <iostream>

using std::string, std::vector, std::cout, std::cin, std::endl;

Game::Game() : players({}), suits({}), ranks({}), deck({}), drawPile({}), discardPile({}) {}

void Game::loadDeckFromFile(std::string filename) {

    std::ifstream ifs(filename); // Opens file for input.

    if(!ifs.is_open()) { // Ensures the file is opened successfully.
        throw std::invalid_argument(filename + " could not be opened.");
    }

    string suitList, rankList; // Creates string vars for reading lines.
    getline(ifs, suitList); // Gets suit line.
    getline(ifs, rankList); // Gets rank line.

    std::stringstream sl(suitList); // Creates stringstream for suits.
    std::stringstream rl(rankList); // Creates stringstream for ranks.

    string s, r; // Creates temp string vars.

    while (getline(sl, s, ' ')) { // Splits stringtream by spaces and adds to temp string var which is pushed onto the vector.
      suits.push_back(s);
    }

    while (getline(rl, r, ' ')) { // Splits stringtream by spaces and adds to temp string var which is pushed onto the vector.
      ranks.push_back(r);
    }

    string card; // Creates string var for card line.
    while (std::getline(ifs, card)) {
        std::istringstream iss(card);
        string rank, suit;
        bool validRank = false; // Creates bool for rank validity.
        bool validSuit = false;// Creates bool for suit validity.
        if (!(iss >> rank >> suit)) { // Checks if there's not enough values, if so throw error.
            ifs.close();
            throw std::runtime_error("Invalid format in file.");
        }

        string extraVal;
        if (iss >> extraVal) { // Checks if there's too many values, if so throw error.
            ifs.close();
            throw std::runtime_error("Invalid format in file.");
        }
        
        for (size_t i = 0; i < ranks.size(); i++) { // Checks all known rank values to current ranl value, if found, set bool var to true.
          if (ranks.at(i) == rank) {
            validRank = true;
          }
        }

        for (size_t i = 0; i < suits.size(); i++) { // Checks all known suit values to current suit value, if found, set bool var to true.
          if (suits.at(i) == suit) {
            validSuit = true;
          }
        }

        if (validRank == false || validSuit == false) { // If either of the tests came back false, throw error.
            ifs.close();
            throw std::runtime_error("Invalid rank or suit in file.");
        }

        try { // Creates new card, adds new card to deck, inserts new card to draw pile. Catches errors thrown and throws the correct one.
            Card* newCard = new Card(rank, suit);
            deck.push_back(newCard);
            drawPile.insert(drawPile.begin(), newCard);
        } catch (const std::invalid_argument& e) {
              ifs.close();
              throw std::runtime_error("Invalid card" + string(e.what()));
        }
    }
}

void Game::addPlayer(bool isAI) {
  Player* newPlayer = new Player(isAI);
  players.push_back(newPlayer);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::drawCard(Player* p) {
    if (!drawPile.empty()) { // If draw pile is not empty
        Card* topCard = drawPile.back(); // Get the top card of the draw pile
        p->addToHand(topCard); // Add the top card to the player's hand
        drawPile.pop_back(); // Remove the top card from the draw pile
    } else if (!discardPile.empty()) { // If draw pile is empty but discard pile is not empty
        cout << "Draw pile, empty, flipping the discard pile." << endl; // Print the message
        // Move all cards from discard pile to draw pile (flipping)
        while (!discardPile.empty()) {
            Card* card = discardPile.back();
            drawPile.push_back(card);
            discardPile.pop_back();
        }
        // Now draw the top card of the new draw pile
        if (!drawPile.empty()) {
            Card* topCard = drawPile.back();
            p->addToHand(topCard);
            drawPile.pop_back();
        }
    } else { // If both draw pile and discard pile are empty
        throw std::runtime_error("Both draw pile and discard pile are empty.");
    }
}

Card* Game::deal(int numCards) {
    // Form a starting discard pile by discarding the top card of the draw pile
    if (!drawPile.empty()) {
        Card* initialDiscardedCard = drawPile.back();
        discardPile.push_back(initialDiscardedCard);
        drawPile.pop_back();
    } else {
        throw std::runtime_error("Unable to deal cards: draw pile is empty.");
    }

    // Deal cards to players' hands
    int numPlayers = players.size();
    int currentPlayerIndex = 0; // Index of the current player to deal cards to

    for (int i = 0; i < numCards; ++i) {
        // Deal one card to the current player
        Player* currentPlayer = players[currentPlayerIndex];
        drawCard(currentPlayer);

        // Move to the next player in turn order
        currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
    }

    return discardPile.back(); // Return the initially discarded card
}

string Game::mostPlayedSuit() {
  
  return nullptr;
}

int Game::runGame() {
  return 7;
}



// Destructor--Deallocates all the dynamic memory we allocated
Game::~Game() {
  for (unsigned int i = 0; i < deck.size(); i++) {
    delete deck.at(i);
  }
  for (unsigned int i = 0; i < players.size(); i++) {
    delete players.at(i);
  }
}