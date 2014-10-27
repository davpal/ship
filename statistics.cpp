#include "statistics.h"
#include "game.h"

#include <fstream>
#include <string>
#include <algorithm>

// Konstruktor ładuje statystyki z pliku
Statistics::Statistics(const char * f):statfile(f){
  ifstream fin(f);
  Score s;
  while(fin >> s){
    results.push_back(s); // wczytuj rekordy i dodawaj do zbioru
  }
}

// destruktor zapisuje wszystkie rekordy do pliku statystyk
Statistics::~Statistics(){
  ofstream fout(statfile.c_str());
  for(int i = 0; i < results.size(); ++i)
    fout << results[i] << '\n';
}

// W przpadku zakonczenia rozgrywki
void Statistics::update(Observable * o){
  Game * g = dynamic_cast<Game*>(o); // rzutuj na obiekt gry
  if(g->getState() != "") return; //
  Player & w = g->winner(); // pobierz zwyciezce
  Player & l = g->looser(); // pobierz przegranego
  int i;
  // szukaj zwyciezcy w rankingu
  for(i = 0; i < results.size(); ++i){
    if(w.getName() == results[i].getName()){ // gry jest
      results[i].win(); // aktualizuj liczbe wygranych
      break;
    }
  }
  if(i == results.size()) // gdy go nie ma
    results.push_back(Score(w.getName(), 1, 0)); // utworz dla niego rekord

  // szukaj przegranego w rankingu
  for(i = 0; i < results.size(); ++i){
    if(l.getName() == results[i].getName()){ // gry jest
      results[i].lose(); // aktualizuj liczbe przegranych
      break;
    }
  }
  if(i == results.size()) // gdy go nie ma
    results.push_back(Score(l.getName(), 0, 1)); // utworz dla niego rekord

  sort(results.begin(), results.end()); // sortuj wg liczby wygranych
}

// metoda porownujaca rekordy
bool Score::operator<(const Score & s) const {
  return wins != s.wins ? wins > s.wins : loses < s.loses;
}

// funkcja zapisujaca rekord do strumienia
ostream & operator<<(ostream & os, const Score & s){
  os << s.name << ' ' <<  s.wins << ' ' << s.loses;
  return os;
}

// funkcja odczytujaca rekord ze strumienia
istream & operator>>(istream & is, Score & s){
  is >> s.name >> s.wins >> s.loses;
  return is;
}

// funkcja zapisujaca statystyki do strumienia
ostream & operator<<(ostream & os, const Statistics & s){
  for(int i = 0; i < s.results.size(); ++i)
    os << i+1 << ". " << s.results[i] << '\n';
  return os;
}
