#include "observer.h"

Observer::~Observer(){}

void Observable::notifyAll(){
  for(int i = 0; i < o.size(); ++i) // dla wszystkich obserwatorow
    o[i]->update(this); // aktualizacja stanu
}
