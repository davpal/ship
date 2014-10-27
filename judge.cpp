#include "judge.h"

#include <fstream>
#include <cstdlib>

// W konstruktrze wczytujemy statystyki z pliku jesli istnieja
Judge::Judge():game(NULL){
  stat = new Statistics("stats.dat");
}

// niszczymy obiekt gry i statystyk w destruktorze
Judge::~Judge(){
  if(game != NULL) delete game;
  delete stat;
}

// nowa gra o zadanym typie
void Judge::newGame(int type){
  game = new Game(type); // nowy obiekt gry
  game->addObserver(this); // arbiter bedzie obserwowal gre
  game->addObserver(stat); // statystyki beda rejestrowane po zakonczeniu rozgrywki
  game->loop(); // glowna petla gry
}

// wczytaj gre z podanego pliku
void Judge::loadGame(const char * s){
  game = new Game(s); // nowy obiekt gry ladowany z pliku
  if(game != NULL){
    // dodawanie obserwatorow
    game->addObserver(this);
    game->addObserver(stat);
    game->loop(); // glowna petla gry
  }
}

// zapisz gre do podanego pliku
bool Judge::saveGame(const char * s){
  ofstream fout(s); // strumien wyjsciowy
  if(fout.is_open()){ // jesli udalo sie otworzyc
    fout << *game; // zapisujemy obiekt gry(serializacja)
    fout.close(); // zamknij plik
    return true; // sukces!
  }

  return false; // niepowodzenie!
}

// wyswietl statystyki
void Judge::stats() const {
  std::cout << "====== RANKING =======\n";
  std::cout << *stat; // pokaz obiekt statystyk
}

// zmiana stanu gry
void Judge::update(Observable * o){
  Game * g = dynamic_cast<Game*>(o); // rzutuj na obiekt gry
  // brak wiadomosci w obiekcie oznacza koniec rozgrywki
  if(g->getState() == "")
    // pobierz nazwe zwyciezcy i pokaz na ekranie
    std::cout << "Gracz " + dynamic_cast<Game*>(o)->winner().getName() << " wygrywa!\n";
  else {
    system("cls");
    // w innym przypadku pokaz zmiane stanu na ekranie
    std::cout << g->getState();
  }
}

