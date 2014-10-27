#include "player.h"

#include <cstdlib>
#include <ctime>

// zapisywanie danych gracza do strumienia
ostream & operator<<(ostream & os, const Player & p){
  os << p.name << ' ' << p.moves <<  ' ' <<
    p.hits << ' ' << p.misses << ' ' << p.ships << '\n';
  os << p.my << p.enemy;
  return os;
}

// wczytywanie danych gracza ze strumienia
istream & operator>>(istream & is, Player & p){
  is >> p.name >> p.moves >> p.hits >> p.misses >> p.ships;
  is >> p.my >> p.enemy;
  return is;
}

// ruch czlowieka
int HumanPlayer::move(){
  int x, y;
  // pokaaz info gracza
  cout << "Ruch gracza " + name << '\n';
  cout << "Trafien: " << hits << ", straty = " << 20 - ships << "\n\n";
  cout << "Twoje statki:\n\n";
  cout << my << '\n';
  cout << "\n\nTwoje posuniecia:\n\n";
  cout << enemy << '\n';
  // pytaj o wspolrzedne pola
  do {
    cout << "Podaj wspolrzedne(x y): ";
    if(!(cin >> x >> y)){ // podano inny znak niz cyfre
      cin.clear(); // czyscimy strumien
      cin.ignore(); // ignorujemy reszte znakow
      return -1; // informacja o przerwaniu gry
    }
    // powtarzaj dotad az gracz wprowadzi poprawne pole
  } while(!(x < 10 && x >= 0 && y < 10 && y >=0)
    || enemy.get(x * 10 + y) == '0' || enemy.get(x * 10 + y) == 'X');
  ++moves; // zwieksz liczbe ruchow
  cout << '\n';
  return x * 10 + y; // zwracamy numer pola
}

// ruch gracza komputerowego
int ComputerPlayer::move(){
  srand(time(0)); // nowe ziarno losowosci
  int x;
  std::cout << enemy << '\n';
  do {
    x = rand() % 100;
    // losuj az trafi na niesprawdzone pole
  } while(enemy.get(x) == '0' || enemy.get(x) == 'X');

  ++moves; // zwieksz liczbe ruchow
  return x; // zwroc numer pola
}

// sprawdzanie pola przeciwnika
bool Player::check(int t) {
  if(my.get(t) == '#'){ // jesli trafiono statek
    my.set(t, 'X'); // oznaczamy 'trafienie'
    --ships; // zmniejsz liczbe statkow
    return true; // true - trafiony
  } else {
    my.set(t, '0'); // oznaczamy 'pudlo'
  }
  return false; // false - pudlo
}
