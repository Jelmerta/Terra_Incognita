#ifndef GAMEEVENT_H
#define GAMEEVENT_H
#include <string>

class GameEvent {
public:
  GameEvent(std::string name) { this->name = name; }

  std::string getName() { return name; }

private:
  std::string name;
};

#endif