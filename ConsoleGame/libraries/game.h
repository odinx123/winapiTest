#ifndef GAME_H
#define GAME_H 1

#include "map.h"

class Game : public Map {
   private:
    bool game;

   public:
    Game() = default;
    Game(SHORT Width, SHORT Height);
    void setGameState(bool state) { game = state; }
    bool getGameState() const { return game; }
};

Game::Game(SHORT Width, SHORT Height): Map(Width, Height) {
    game = true;
}

#endif