#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
using namespace std;

class Board {
  private:
    char fields[100];
  public:
    Board();
    void set(int, char);
    char get(int) const;
    void random();
    void clear();
    friend ostream & operator<<(ostream &, const Board &);
    friend istream & operator>>(istream &, Board &);
};

#endif