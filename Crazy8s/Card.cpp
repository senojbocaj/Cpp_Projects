#include <iostream>

#include "Card.h"

using std::string;

Card::Card(string rank, string suit) : rank(rank), suit(suit), timesPlayed(0) { // Constructor.

  // Checks if rank is non-alphanumeric.
  for (char c : rank) {
    if (!std::isalnum(c)) {
      throw std::invalid_argument("Rank must contain only letters and numbers.");
    }
  }

  // Checks if suit is non-alphanumeric.
  for (char c : suit) {
    if (!std::isalnum(c)) {
      throw std::invalid_argument("Suit must contain only letters and numbers.");
    }
  }

  // Check if rank or suit is empty.
  if (rank.empty() || suit.empty()) {
    throw std::invalid_argument("Rank and suit cannot be empty.");
  }

  this->rank = rank;
  this->suit = suit;
}


string Card::getRank() { // Getter.
  return rank;
}

string Card::getSuit() { // Getter.
  return suit;
}

int Card::getTimesPlayed() { // Getter.
  return timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit) { // Checks if card matches last played rank or suit, or if the card being played is a "8", else card cannot be played.
  if (Card::getRank() == "8") {
    return true;
  } else if (currentRank == Card::getRank() || currentSuit == Card::getSuit()) {
      return true;
  } else {
      return false;
  }
}

void Card::play() { // Counts the number of times a card has been played.
  timesPlayed++;
}
