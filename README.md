# Blackjack (Console Game in C++)

## Project Overview

This project is a simple console-based implementation of the Blackjack card game written in C++. The player competes against a dealer with standard rules, aiming to reach a score as close to 21 as possible without exceeding it.

The project was created for educational purposes to practice object-oriented programming, STL usage, and basic game logic design in C++.

---

## Features

- Full deck of 52 cards
- Card shuffling using `<random>`
- Dealer AI with fixed rules (stops at 17)
- Ace handling logic (dynamic value adjustment)
- Turn-based player interaction
- Win/lose/tie outcome evaluation

---

## Game Rules

- The goal is to reach a hand value as close to 21 as possible without going over.
- Number cards are worth their face value.
- Face cards (J, Q, K) are worth 10 points.
- Ace is worth 11 or 1 (adjusted automatically if player/dealer busts).
- Dealer must draw until reaching at least 17.

---

## Architecture

### Card
Represents a single playing card:
- Rank (Ace to King)
- Suit (Clubs, Diamonds, Hearts, Spades)
- Value calculation based on rank
- Output formatting via `operator<<`

---

### Deck
Represents a full deck of 52 cards:
- Automatically generated on initialization
- Supports shuffling using `std::shuffle`
- Card dealing via sequential access

---

### Player
Represents both player and dealer:
- Tracks current score
- Tracks number of Aces for dynamic adjustment

---

### Settings
Game configuration constants:
- Bust limit: 21
- Dealer stop threshold: 17

---

## Game Flow

1. Deck is created and shuffled
2. Initial cards are dealt:
   - Dealer shows one card
   - Player receives two cards
3. Player turn:
   - Choose to hit or stand
   - Can draw multiple cards
4. Dealer turn:
   - Draws until reaching at least 17
5. Final result is calculated

---

## Ace Handling Logic

Aces are treated dynamically:
- Initially counted as 11 points
- If total score exceeds 21:
  - Ace value is reduced from 11 to 1 (subtracting 10 from score)
- This adjustment repeats if multiple Aces exist

---

## Build and Run

### Requirements
- C++17 or higher
- Standard compliant compiler (GCC, Clang, MSVC)

### Compilation
```bash
g++ main.cpp -o blackjack
