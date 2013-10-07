//
//  Cannon.h
//  game
//
//  Created by David Zilli on 9/28/13.
//
//

#ifndef __game__Cannon__
#define __game__Cannon__

#include <iostream>
#include "Game_Object.h"
#include "Light_Beam.h"
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Cannon : public Game_Object {
public:
    Cannon(const Point2f &position_,
           const Vector2f &size_,
           const float &theta_)
    : Game_Object(position_, size_, theta_)
    {
    }
    
    static const float beam_speed = 1000.0f;
    
    void render() const {
        Game_Object::render("cannon", 0.5f, 0.5f);
    }
    
    Light_Beam * fire() const;
    bool can_reflect(Game_Object *rhs);
    bool collide(Game_Object &rhs);

};

#endif /* defined(__game__Cannon__) */
