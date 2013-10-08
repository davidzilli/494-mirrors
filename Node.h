//
//  Node.h
//  game
//
//  Created by David Zilli on 10/8/13.
//
//

#ifndef __game__Node__
#define __game__Node__

#include <iostream>
#include "Game_Object.h"
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Node : public Game_Object {
public:
    Node(const Point2f &position_,
           const Vector2f &size_,
           const float &theta_,
           bool m_reflective_)
    : Game_Object(position_, size_, theta_, m_reflective_),
    m_texture("node_inactive"),
    m_is_active(false)
    {
    }
    
    void render() const {
        Game_Object::render(m_texture, 0.5f, 0.5f);
    }
    
    bool collide(Game_Object &rhs);
    bool can_rotate();
    void move(Vector2f dir);
    bool selectable();
    bool get_is_active();
    void set_is_active(bool flag);
    
private:
    bool m_is_active;
    String m_texture;
};

#endif /* defined(__game__Node__) */
