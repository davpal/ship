#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "judge.h"

using namespace std;

void menu();

int main(){
  int option, type;
  string name;
  Judge controller;
  while(true){
    menu();
    cin >> option;
    system("cls");
    switch(option){
      case 1:
        // nowa gra
        cout << "1. Gracz vs Gracz\n";
        cout << "2. Gracz vs Komputer\n";
        cin >> type;
        system("cls");
        controller.newGame(type);
	      break;
      case 2:
        // wczytaj grę
        controller.loadGame("last.sav");
        break;
      case 3:
        // statystyki
        controller.stats();
        break;
      case 4: {
          ifstream manual("manual.txt");
          string line;
          while(getline(manual, line)) cout << line << '\n';
          cout << "\n\nNacisnij ENTER, aby kontynuwac...";
          cin.get();
          cin.get();
          system("cls");
        }
        break;
      case 5:
        return 0;
	      break;
      default:
        cout << "Nie ma takiej opcji!\n";
        continue;
    }
  }
  return 0;
}

void menu(){
  cout << " ======== STATKI =======\n";
  cout << "1. Nowa gra\n";
  cout << "2. Wczytaj gre\n";
  cout << "3. Statystyki\n";
  cout << "4. Instrukcja\n";
  cout << "5. Zakoncz\n";
}
