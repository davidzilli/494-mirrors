//
//  Mirror.h
//  game
//
//  Created by David Zilli on 9/30/13.
//
//

#ifndef __game__Mirror__
#define __game__Mirror__

#include <iostream>
#include "Game_Object.h"
#include "Light_Beam.h"
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Mirror : public Game_Object {
public:
    Mirror(const Point2f &position_,
           const Vector2f &size_,
           const float &theta_,
           bool m_reflective_)
    : Game_Object(position_, size_, theta_, m_reflective_)
    {
    }
    
    static const float beam_speed = 400.0f;
    
    void render() const {
        Game_Object::render("mirror", 0.5f, 0.5f);
    }
    
    Light_Beam * reflect(Light_Beam *light_beam);
    bool can_reflect(Game_Object* rhs);
    bool collide(Game_Object &rhs);
    Point2f get_collision_point(Game_Object &rhs);
    
private:
    
};

#endif /* defined(__game__Mirror__) */
