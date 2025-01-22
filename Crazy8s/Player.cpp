#include <iostream>
#include <sstream>

#include "Player.h"

using std::vector, std::string, std::size_t, std::cout, std::endl, std::cin;

Player::Player(bool isAI) : isAI(isAI), hand({}) { // Constructor.
}

void Player::addToHand(Card* c) { // Adds card to end of hand.
  hand.push_back(c);
}

size_t Player::getHandSize() { // Returns the size of the hand as an int.
  return hand.size();
}

std::string Player::getHandString() { // Returns string of all cards contained in the hand with correct formatting.

  std::stringstream handString; // Create a string strean.

  for (size_t i = 0; i < Player::getHandSize(); i++) { 
    Card* card = hand[i];
    handString << card-> getRank() << " " << card->getSuit(); // Calls previous functions to find each cards rank and suit.
    if (i != hand.size() - 1){
      handString << ", "; // Adds comma if the element is not at the end.
    }
  }

  return handString.str(); // Returns string of stringstream.
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit) {
    if (isAI) {
        for (auto i = hand.begin(); i != hand.end(); ++i) {
            Card* card = *i;
            if (card->canBePlayed(currentRank, currentSuit)) {
                hand.erase(i);
                card->play();
                currentRank = card->getRank();
                currentSuit = card->getSuit();
                return card;
            }
        }
        return nullptr; // Return nullptr if no valid cards found
    } else {
        cout << "Your hand contains: " << getHandString() << endl;
        cout << "The next card played must be a " << currentRank << " or " << currentSuit << endl;

        int count = 0;
        while (true) {
            if (count == 0) {
              cout << "What would you like to play? (enter \"draw card\" to draw a card)" << endl;
              count++;
            }

            string input;
            getline(cin, input);

// There was a bug in the autograder or within my code (no clue how, since it worked in EVERY other test case but 02g).
// APPARENTLY, I need to ensure that the user didn't fall asleep while playing the game because in the 02g test case,
// the first iteration would have no input (the input would be " "), causing unnecessary outputs, thus causing 
// incorrect behavior. I LOVE THIS :))) (5hrs:18min:44s)

            while (true) {
              if (input.empty()) {
                  getline(cin, input);
              } else {
                break;
              }
            }

            if (input == "draw card") {
                return nullptr;
            }

            string rank, suit;
            std::istringstream iss(input);
            iss >> rank >> suit;

            bool found = false;
            for (auto i = hand.begin(); i != hand.end(); ++i) {
                Card* playedCard = *i;
                if (playedCard->getRank() == rank && playedCard->getSuit() == suit) {
                    found = true;
                    if (playedCard->canBePlayed(currentRank, currentSuit)) {
                        hand.erase(i);
                        playedCard->play();
                        currentRank = playedCard->getRank();
                        if (currentRank == "8") {
                            cout << "What suit would you like to declare?" << endl;
                            while (true) {
                                string newSuit;
                                cin >> newSuit;
                                bool validSuit = false;

                                for (auto i = suits.begin(); i != suits.end(); ++i) {
                                    if (newSuit == *i) {
                                        validSuit = true;
                                        break;
                                    }
                                }

                                if (!validSuit) {
                                    cout << "That's not a suit in this deck. Try again." << endl;
                                } else {
                                    currentSuit = newSuit;
                                    break; 
                                }
                            }
                        } else {
                            currentSuit = playedCard->getSuit();
                        }
                        return playedCard;
                    } else {
                        cout << "You can't play that card. Try again." << endl;
                        break;
                    }
                }
            }
            if (!found) {
                cout << "That's not a card you have. Try again." << endl;
            }
        }
    }
}