//
//  Wall.h
//  game
//
//  Created by David Zilli on 10/2/13.
//
//

#ifndef __game__Wall__
#define __game__Wall__

#include <iostream>
#include "Game_Object.h"
#include "Light_Beam.h"
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Wall : public Game_Object {
public:
    Wall(const Point2f &position_,
           const Vector2f &size_,
           const float &theta_,
         bool m_reflective_)
    : Game_Object(position_, size_, theta_, m_reflective_)
    {
    }
    
    void render() const {
        Game_Object::render("wall", 0.5f, 0.5f);
    }
    
    bool can_reflect(Game_Object* rhs);
    bool collide(Game_Object &rhs);

    
private:
    
};


#endif /* defined(__game__Wall__) */
