#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "player.h"
#include "observer.h"
#include <iostream>

using namespace std;

// Reprezentacja jednego rekordu w statystykach
class Score {
private:
  string name; // nazwa gracza
  int wins, loses; // wygranych, przegranych
public:
  // Konstruktor tworzy rekord wypelniony danymi
  Score(string n, int w, int l):name(n), wins(w), loses(l){
  }
  
  // Tworzy pusty rekord
  Score(){}
  
  //pobierz nazwe gracza
  string getName() const {
    return name;
  }
  
  // metoda porownojaca, dla funkcji std::sort
  bool operator<(const Score &) const;
  
  // dodaj wygrana
  void win(){
    ++wins;
  }
  
  // dodaj przegrana
  void lose(){
    ++loses;
  }
  
  // funkcje do operacji na strumieniach
  friend ostream & operator<<(ostream & os, const Score & s);
  friend istream & operator>>(istream &, Score &);
};

// Statystyki
class Statistics : public Observer {
private:
  vector<Score> results; // zbior rekordow
  string statfile; // plik statystyk
public:
  Statistics(const char *); // konstruktor laduje statystyki z pliku
  ~Statistics(); 
  void update(Observable * o); // w przypadku zmiany stanu gry
  
  // funkcja do operacji na strumieniu
  friend ostream & operator<<(ostream &, const Statistics &);
};


#endif
