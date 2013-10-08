//
//  Target.h
//  game
//
//  Created by David Zilli on 10/7/13.
//
//

#ifndef __game__Target__
#define __game__Target__

#include <iostream>
#include "Game_Object.h"
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Target : public Game_Object {
public:
    Target(const Point2f &position_,
         const Vector2f &size_,
         const float &theta_,
         bool m_reflective_)
    : Game_Object(position_, size_, theta_, m_reflective_),
    m_target(NULL),
    m_target_is_selected(false),
    m_texture("target")
    {
    }
    
    void render() const {
        Game_Object::render(m_texture, 0.5f, 0.5f);
    }
    
    bool can_reflect(Game_Object* rhs);
    bool collide(Game_Object &rhs);
    void move(Vector2f dir);
    void set_target(Game_Object* target);
    Game_Object* get_target();
    bool can_rotate();
    bool get_target_is_selected();
    void set_target_is_selected(bool flag);
    bool selectable();
    void set_position(Point2f pos);
    
private:
    Game_Object* m_target;
    bool m_target_is_selected;
    String m_texture;
    
};

#endif /* defined(__game__Target__) */
