#ifndef OBJECT_H
#define OBJECT_H

#include "game.h"

class Object {
   private:
    Game* curGame;
   
   protected:
    int HP;
    int power;
    int defense;
    float xPos;
    float yPos;
    wpicture body;

   public:
    Object() = default;
    Object(wpicture Body, int hp, int Power, int Defense);

    bool move(float x, float y);
    inline void bindGame(Game* game);
    inline void setPos(SHORT x, SHORT y);
    inline void draw();
};

Object::Object(wpicture Body, int hp, int Power, int Defense) {
    HP = hp;
    body = Body;
    power = Power;
    defense = Defense;
}

void Object::bindGame(Game* game) {
    curGame = game;
}

inline bool Object::move(float x, float y) {
    if (!curGame->getGameState())
        return false;
    if (curGame->isMapObj(body, xPos+x, yPos+y))
        return false;
    xPos += x;
    yPos += y;
    return true;
}

void Object::setPos(SHORT x, SHORT y) {
    xPos = x;
    yPos = y;
}

void Object::draw() {
    curGame->draw(body, xPos, yPos);
}

#endif