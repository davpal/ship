#ifndef PLAYER_H_
#define PLAYER_H_

#include "board.h"

// klasa abstrakcyjna reprezentujaca gracza
class Player {
protected:
  Board my, enemy; // plansza wlasna i pomocnicza
  int moves, hits, misses, ships; // ruchy, trafienia, chybienia, liczba pozostalych statkow
  string name; // nazwa gracza

  public:
    // konstruktor tworzy gracz o podanej nazwie
    Player(const string & n):moves(0), hits(0), misses(0), ships(20), name(n){
      enemy.clear(); // czysc plansze pomocnicza
    }
    virtual int move() = 0; // metoda abstrakcyjna, zwraca numer pola wybranego przez gracza

    // funkcje do operacji strumieniowych
    friend ostream & operator<<(ostream &, const Player &);
    friend istream & operator>>(istream &, Player &);

    bool check(int t); // metoda sprawdzajaca podany ruch

    // chybienie
    void miss(int t){
      enemy.set(t, '0'); // oznacz nietrafione pole
      ++misses;
    }

    // trafienie
    void hit(int t){
      enemy.set(t, 'X'); // oznacz trafione pole
      ++hits;
    }

    // metoda zwraca informacje czy gracz przegral,
    // tj. stracil wszystkie statki
    bool lost() const {
      return !ships;
    }

    // zwroc imie
    string getName() const {
      return name;
    }

    // zwroc liczbe ruchow
    int getMoves() const {
      return moves;
    }
};

// reprezentacja gracza-człowieka
class HumanPlayer : public Player {
public:
  // konstruktor tworzy gracza o podanym imieniu z klawiatury
  HumanPlayer(const string & name):Player(name){}
  int move(); // pyta o wspolrzedne pola
};

// reprezentacja gracza-komputera
class ComputerPlayer : public Player {
public:
  // nadajemy mu nazwe computer
  ComputerPlayer(): Player("Computer"){}
  int move(); // algorytm sztucznej inteligencji wybiera pole
};

#endif
