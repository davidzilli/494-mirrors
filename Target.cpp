//
//  Target.cpp
//  game
//
//  Created by David Zilli on 10/7/13.
//
//

#include "Target.h"

bool Target::can_reflect(Game_Object* rhs) {
    return false;
}

bool Target::collide(Game_Object &rhs) {
    return false;
}

void Target::move(Vector2f dir) {
    m_position += dir * m_size.x;
    
    if (m_target && m_target_is_selected) {
        cout << "Moving the target's target" << endl;
        m_target->move(dir);
    }
}

void Target::set_target(Game_Object* target) {
    m_target = target;
}

Game_Object* Target::get_target() {
    return m_target;
}

bool Target::can_rotate() {
    return false;
}

bool Target::get_target_is_selected() {
    return m_target_is_selected;
}

void Target::set_target_is_selected(bool flag) {
    m_target_is_selected = flag;
    if (flag) {
        m_texture = "target_sel";
    } else {
        m_texture = "target";
    }
}

bool Target::selectable() {
    return false;
}

void Target::set_position(Point2f pos) {
    m_position = pos;
}
