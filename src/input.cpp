#include <cctype>
#include <input.h>
#include <vector>
#include <ncurses.h>

using namespace std;

bool Event::shift() {
  return keycode != lowercase;
} 

int Event::axis(int lowkey, int highKey) {
  return -(keycode == lowkey) + (keycode == highKey);
}

int Event::axisl(int lowkey, int highKey) {
  return -(lowercase == lowkey) + (lowercase == highKey);
}


bool Event::propagate(vector<InputReceiver*> receivers, bool allowInvalid) {
  if (!isValidKey && !allowInvalid) return false;

  for (auto r : receivers) 
    if (r->accept(*this)) return true;
  
  return false;
}

bool FnReceiver::accept(Event evt) {
  return handler(evt);
}

Event InputManager::get() {
  int key = getch();

  return Event { 
    .keycode = key, 
    .lowercase = tolower(key),
    .isValidKey = (key != ERR)
  };
}
