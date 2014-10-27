#include "game.h"

#include <fstream>

// wczytaj gre z pliku
Game::Game(const char * f){
  ifstream save(f);
  if(!save.is_open()) return; // nie udalo sie wczytac, powrot
  save >> type; // wczytaj typ gry
  current = new HumanPlayer(""); // pierwszy gracz to czlowiek
  if(type == 2)
    enemy = new ComputerPlayer(); // drugi to komputer w przypadku tego trybu
  else
    enemy = new HumanPlayer(""); // w innym wypadku drugi gracz to tez człowiek

  save >> *current >> *enemy; // wczytaj dane obydwu graczy
}

Game::~Game(){
}

// nowa gra o zadanym typie
Game::Game(int t):type(t){
  string name;
  std::cout << "Gracz pierwszy: ";
  std::cin >> name; // wczytaj imie gracza
  current = new HumanPlayer(name); // nowy gracz-czlowiek
  if(type == 2)
    enemy = new ComputerPlayer(); // nowy gracz-komputer
  else {
    std::cout << "Gracz drugi: ";
    std::cin >> name;
    enemy = new HumanPlayer(name); // drugi gracz-czlowiek
  }
}

// glowna petla gry
void Game::loop(){
  do {
    int t = current->move(); // pobierz numer pola od gracza
    if(t == -1){ // jesli gracz przerwal gre
      ofstream save("last.sav"); // zapisujemy do pliku
      save << *this; // obiekt bierzacej gry
      state = "Gra zapisana!\n"; // informujemy obserwatorw
      notifyAll(); // i zmianie stanu
      return; // powrot
    }
    if(enemy->check(t)){ // sprawdz zadane pole
      state = "Gracz " + current->getName() + ": trafienie!\n\n";
      notifyAll(); // informuj o trafieniu
      current->hit(t); // aktualizuj dane
    } else {
      state = "Gracz " + current->getName() + ": pudlo!\n\n";
      notifyAll(); // informuj o chybieniu
      current->miss(t); // aktualizuj dane
    }
    // gdy przeciwnik przegrywa
    if(enemy->lost()){
      state = ""; // bez zadnych informacji
      notifyAll(); // zmiana stanu
      return; // powrot
    }
    next(); // przelacz tugracza
  } while(true); // powtarzaj do konca rozgrywki lub jej przerwania
}

// przelacza gracza na nastepnego
void Game::next(){
  Player * t = current;
  current = enemy;
  enemy = t;
}

// zapisuje na strumien dane gry
ostream & operator<<(ostream & os, const Game & g){
  os << g.type << '\n' << *g.current << *g.enemy;
  return os;
}

// odczytuje ze strumienia dane gry
istream & operator>>(istream & is, Game & g){
  is >> *g.current >> *g.enemy;
  return is;
}
