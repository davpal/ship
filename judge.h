#ifndef JUDGE_H_
#define JUDGE_H_

#include "game.h"
#include "statistics.h"
#include <string>

// Reprezentacja kontrolera gry - Arbiter
class Judge : public Observer {
private:
  Game * game; // obiekt bierzacej gry
  Statistics * stat; // obiekt rejestrujacy statystyki
public:
  Judge(); 
  ~Judge();
  void newGame(int); // nowa gra
  void loadGame(const char *); // wczytaj gre
  bool saveGame(const char *); // zapisz gre
  void stats() const; // pokaz statystyki
  virtual void update(Observable *); // wywolana podczas zmiany stanu gry
};

#endif
