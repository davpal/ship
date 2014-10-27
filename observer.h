#ifndef OBSERVER_H_
#define OBSERVER_H_

/*
 * Implementacja wzorca obserwator
 *
 */

#include <vector>
#include <string>

using namespace std;

class Observable;

// interfejs obserwatorów
class Observer {
public:
  virtual ~Observer() = 0;
  virtual void update(Observable *) = 0; // metoda czysto wirtualna(abstrakcyjna)
};

// klasa abstrakcyjna dla obiektów obserwowanych
class Observable {
private:
  vector<Observer *> o; // zbiór obserwatorów
public:
  virtual ~Observable() {} // przynajmniej jedna metoda wirtualna
  // metoda dodająca obserwatora
  void addObserver(Observer * _o){
    o.push_back(_o);
  }
  void notifyAll(); // metoda informująca o zmianie stanu obiektu obserwowanego
};

#endif
