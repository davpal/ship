#ifndef GAME_H_
#define GAME_H_

#include "observer.h"
#include "player.h"

// Reprezentacja gry 
class Game : public Observable {
private:
  Player * current, * enemy; // wskazniki na graczy obecnych w grze
  int type; // typ gry
  string state; // stan, wiadomosc dla obserwatorow
public:
  Game(const char *); // konstruktor ladujacy gre z pliku
  Game(int); // nowa gra o zadanym typie
  ~Game();
  void loop(); // glowna petla gry
  void next(); // przelacz na nastepnego gracza
  
  // zwroc ref. do zwyciezcy
  // uruchamiana tylko po zakonczeniu gry!
  Player & winner() const {
    return *current;
  }
  
  // zwroc ref. do przegranego
  // uruchamiana tylko po zakonczeniu gry!
  Player & looser() const {
    return *enemy;
  }
  
  // zwroc stan
  string getState() const {
    return state;
  }
  
  // funkcje do operacji na strumieniach
  friend ostream & operator<<(ostream & os, const Game & g);
  friend istream & operator>>(istream & is, Game & g);
};

#endif
