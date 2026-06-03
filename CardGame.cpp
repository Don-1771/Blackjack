#include <iostream>
#include <array>
#include <algorithm>
#include <random>
//-----------------------------------------------------------------------------
struct Card
{
   enum Rank
   {
      rank_ace,
      rank_2,
      rank_3,
      rank_4,
      rank_5,
      rank_6,
      rank_7,
      rank_8,
      rank_9,
      rank_10,
      rank_jack,
      rank_queen,
      rank_king,

      max_rank,
   };

   enum Suit
   {
      suit_clubs,
      suit_diamonds,
      suit_hearts,
      suit_spades,

      max_suit,
   };  
   static constexpr std::array<Rank, Rank::max_rank> allRanks{
      rank_ace,
      rank_2,
      rank_3,
      rank_4,
      rank_5,
      rank_6,
      rank_7,
      rank_8,
      rank_9,
      rank_10,
      rank_jack,
      rank_queen,
      rank_king};
   static constexpr std::array<Suit, Suit::max_suit> allSuits{      
      suit_clubs,
      suit_diamonds,
      suit_hearts,
      suit_spades};

   friend std::ostream& operator<<(std::ostream& out, const Card &card)
   {
      static constexpr std::array<char, Rank::max_rank> ranks{'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
      static constexpr std::array<char, Suit::max_suit> suits{'C', 'D', 'H', 'S'};
      out << ranks[static_cast<Rank>(card.rank)] << suits[static_cast<Suit>(card.suit)];
      return out;
   }

   int value()
   {
      static constexpr std::array<int, Rank::max_rank> valueRanks{11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
      return valueRanks[rank];
   }

   Rank rank{};
   Suit suit{};
};
//-----------------------------------------------------------------------------
class Deck
{
private:
   std::array<Card, Card::max_rank* Card::max_suit> Cards{};

public:
   Deck()
   {
      int i = 0;
      for (auto suit : Card::allSuits)
         for (auto rank : Card::allRanks)
            Cards[i++] =  Card { rank, suit };
   }

   Card dealCard();
   void shuffle();
};

Card Deck::dealCard()
{
   static int i = 0;
   return Cards[i++];
}

void Deck::shuffle()
{
   std::random_device rd;
   std::mt19937 g(rd());

   std::shuffle(Cards.begin(), Cards.end(), g);
}
//-----------------------------------------------------------------------------
struct Player
{
   int score{};
   int countAce{};
};
//-----------------------------------------------------------------------------
namespace Settings
{
   static const int Bust{ 21 };
   static const int dealerStopsAt{ 17 };
}
//-----------------------------------------------------------------------------

void ChangeAce(Player& player)
{
   while (player.score > Settings::Bust && player.countAce > 0)
   {
      --player.countAce;
      player.score -= 10;
   }
}

void CheckCardAce(Card& card, Player& player)
{
   if (card.rank == Card::rank_ace)
      ++player.countAce;
}

void startGame(Deck& deck, Player& player, Player& dealer)
{
   Card card{deck.dealCard()};

   dealer.score += card.value();
   CheckCardAce(card, dealer);
   std::cout << "The dealer is showing " << card << " (" << dealer.score << ")\n";

   card = deck.dealCard();
   player.score += card.value();
   CheckCardAce(card, player);
   std::cout << "You are showing " << card << " ";
      
   card = deck.dealCard();
   player.score += card.value(); 
   CheckCardAce(card, player);
   ChangeAce(player);
   std::cout << card << " (" << player.score << ")\n";
}

void dealerGame(Deck& deck, Player& dealer)
{
   Card card{};
   
   while(dealer.score < Settings::dealerStopsAt)
   {
      card = deck.dealCard();
      dealer.score += card.value();
      CheckCardAce(card, dealer);
      ChangeAce(dealer);
      std::cout << "The dealer flips a " << card << ".They now have : " << dealer.score << '\n';
   }

   if (dealer.score > Settings::Bust)
      std::cout << "The dealer went bust!\n";
}

void playerGame(Deck& deck, Player& player)
{
   Card card{};
   char ch{ 'h' };
   while(ch == 'h')
   {
      std::cout << "(h) to hit, or (s) to stand: ";
      std::cin >> ch;
      if (!std::cin )
      {
         std::cin.clear();
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         continue;
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      if (ch == 'h')
      {
         card = deck.dealCard();
         player.score += card.value();
         CheckCardAce(card, player);
         ChangeAce(player);
         std::cout << "You were dealt " << card << ".  "
                  << "You now have : " << player.score << '\n';
      }

      if (player.score > Settings::Bust)
      {
         std::cout << "You went bust!\n";
         ch = 's';
      }
   }
}

void resultGame(Player& player, Player& dealer)
{
   if (player.score <= Settings::Bust && (dealer.score > Settings::Bust || dealer.score < player.score))
      std::cout << "You win!\n";
   else if (dealer.score == player.score)
      std::cout << "The result is a tie)\n";
   else
      std::cout << "You lose!\n";
}
//-----------------------------------------------------------------------------
int main()
{
   Deck deck;
   deck.shuffle();

   Player dealer;
   Player player;

   startGame(deck, player, dealer);   
   playerGame(deck, player);
   if (player.score <= Settings::Bust)
      dealerGame(deck, dealer);
   resultGame(player, dealer);

   return 0;
}
//-----------------------------------------------------------------------------
