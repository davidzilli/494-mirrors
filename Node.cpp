//
//  Node.cpp
//  game
//
//  Created by David Zilli on 10/8/13.
//
//

#include "Node.h"

bool Node::collide(Game_Object &rhs) {
    return Game_Object::collide(rhs);
}

bool Node::can_rotate() {
    return false;
}

void Node::move(Vector2f dir) {
    return;
}

bool Node::selectable() {
    return false;
}

bool Node::get_is_active() {
    return m_is_active;
}

void Node::set_is_active(bool flag) {
    m_is_active = flag;
    
    if (flag) {
        m_texture = "node_active";
    } else {
        m_texture = "node_inactive";
    }
}