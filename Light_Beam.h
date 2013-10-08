//
//  Light_Beam.h
//  game
//
//  Created by David Zilli on 9/29/13.
//
//

#ifndef __game__Light_Beam__
#define __game__Light_Beam__

#include <iostream>
#include "Game_Object.h"
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Light_Beam : public Game_Object {
public:
    Light_Beam(const Point2f &position_,
           const Vector2f &size_,
           const float &theta_)
    : Game_Object(position_, size_, theta_),
    m_reflected(false),
    m_source(NULL),
    target_intersect(NULL)
    {
    }
    
    void render() const {
        Game_Object::render("light_beam", 0.0f, 0.5f);
    }
    
    void project_forward(const float &move);
    bool get_is_reflected();
    void set_is_reflected(bool is_reflected);
    bool can_reflect(Game_Object* rhs);
    void set_source(Game_Object* source);
    Game_Object* get_source();
    bool get_target_intersect(Game_Object &rhs);
    bool collide(Game_Object &rhs);
    bool can_rotate();
    void move(Vector2f dir);
    bool selectable();

private:
    bool m_reflected;
    Game_Object *m_source;
    Point2f* target_intersect;
};

#endif /* defined(__game__Light_Beam__) */
