#include "board.h"

#include <cstdlib>
#include <ctime>
#include <iostream>


using namespace std;

// konstruktor domyslny, tworzy plansze
// z losowym rozmieszczeniem statkow
Board::Board(){
   int i, r, x, y;
  srand(time(0));
  for(i = 0; i < 100; ++i) fields[i] = '_';

  i = 0;
    while(i < 20) {
      r = rand() % 100;
      x = r / 10;
      y = r % 10;
      // gdy pole juz zajete
      if(fields[r] == '#') continue;
      // lewy gorny rog
      else if((x == 0 && y == 0) &&
         (fields[(x+1)*10 + y] == '#' ||
         fields[x*10 + y + 1] == '#' ||
         fields[(x+1)*10 + y + 1] == '#'))
         continue;
      // gorna krawedz
      else if((x == 0 && y > 0 && y < 9) &&
         (fields[(x+1)*10 + y] == '#' ||
         fields[x*10 + y - 1] == '#' ||
         fields[x*10 + y + 1] == '#' ||
         fields[(x+1)*10 + y - 1] == '#' ||
         fields[(x+1)*10 + y + 1] == '#')
      ) continue;
      // prawy gorny rog
      else if((x == 0 && y == 9) &&
         (fields[(x+1)*10 + y - 1] == '#' ||
         fields[(x+1)*10 + y] == '#' ||
         fields[(x)*10 + y - 1] == '#')
      ) continue;
      // prawa krawedz
      else if((x > 0 && x < 9 && y == 9) &&
         (fields[(x+1)*10 + y] == '#' ||
         fields[(x-1)*10 + y] == '#' ||
         fields[x*10 + y - 1] == '#' ||
         fields[(x-1)*10 + y - 1] == '#' ||
         fields[(x+1)*10 + y - 1] == '#')
      ) continue;
      // prawy dolny rog
      else if((x == 9 && y == 9) &&
         (fields[x*10 + y - 1] == '#' ||
         fields[(x-1)*10 + y] == '#' ||
         fields[(x-1)*10 + y - 1] == '#')
      ) continue;
      // dolna krawedz
      else if((x == 9 && y > 0 && y < 9) &&
         (fields[(x-1)*10 + y - 1] == '#' ||
         fields[(x-1)*10 + y + 1] == '#' ||
         fields[(x-1)*10 + y] == '#' ||
         fields[x*10 + y - 1] == '#' ||
         fields[x*10 + y + 1] == '#')
      ) continue;
      // lewy dolny rog
      else if((x == 9 && y == 0) &&
         (fields[(x-1)*10 + y] == '#' ||
         fields[(x-1)*10 + y + 1] == '#' ||
         fields[x*10 + y + 1] == '#')
      ) continue;
      // lewa krawedz
      else if((x > 0 && x < 9 && y == 0) &&
         (fields[(x+1)*10 + y + 1] == '#' ||
         fields[(x-1)*10 + y + 1] == '#' ||
         fields[(x-1)*10 + y] == '#' ||
         fields[(x+1)*10] == '#' ||
         fields[x*10 + y + 1] == '#')
      ) continue;
      // srodek planszy
      else if((x > 0 && x < 9 && y > 0 && y < 9) &&
         (fields[(x-1)*10 + y - 1] == '#' ||
         fields[x*10 + y - 1] == '#' ||
         fields[(x-1)*10 + y + 1] == '#' ||
         fields[x*10 + y + 1] == '#' ||
         fields[(x+1)*10 + y + 1] == '#' ||
         fields[(x+1)*10 + y] == '#' ||
         fields[(x+1)*10 + y - 1] == '#' ||
         fields[(x-1)*10 + y] == '#')
      ) continue;

      fields[r] = '#';
      ++i;
    }
}

// wyczysc plansze
void Board::clear(){
  for(int i = 0; i < 100; ++i) fields[i] = '_';
}

// ustaw pole
void Board::set(int x, char v){
  fields[x] = v;
}

// pobierz pole
char Board::get(int x) const {
  return fields[x];
}

// zapisz plansze do strumienia
ostream & operator<<(ostream & os, const Board & b){
  os << "  ";
  for(int i = 0; i < 10; ++i) os << i << ' ';
  os.put('\n');
  for(int i = 0; i < 10; i++){
    os << i << ' ';
    for(int j = 0; j < 10; ++j){
      os << b.fields[i * 10 + j] << ' ';
    }
    os.put('\n');
  }
  os.put('\n');
  return os;
}

// wczytaj plansze ze strumienia
istream & operator>>(istream & is, Board & b){
  int x;
  char c;
  is.get();
  while(is.get(c) && c != '\n');
  for(int i = 0; i < 10; i++){
    is >> x;
    is.get();
    for(int j = 0; j < 10; ++j){
      is >> b.fields[i * 10 + j];
      is.get();
    }
    while(is.get() != '\n');
  }
  return is;
}
