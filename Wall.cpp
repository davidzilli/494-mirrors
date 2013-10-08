//
//  Wall.cpp
//  game
//
//  Created by David Zilli on 10/2/13.
//
//

#include "Wall.h"

bool Wall::can_reflect(Game_Object* rhs) {
    return false;
}

bool Wall::collide(Game_Object &rhs) {

    return Game_Object::collide(rhs);

}

bool Wall::can_rotate() {
    return false;
}

void Wall::move(Vector2f dir) {
    return;
}

bool Wall::selectable() {
    return false;
}