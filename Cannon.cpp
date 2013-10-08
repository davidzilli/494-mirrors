//
//  Cannon.cpp
//  game
//
//  Created by David Zilli on 9/28/13.
//
//

#include "Cannon.h"
#include "Game_Object.h"
#include "Light_Beam.h"
#include <zenilib.h>

using namespace std;
using namespace Zeni;

Light_Beam * Cannon::fire() const {
    const float radius = 1.0f * get_radius();
    const Vector2f bullet_size(8.0f, 8.0f);
    
//    const Point2f position(get_position() +                                         // the Tank's upper-left coordinate
//                           0.5f * get_size() +                      // shift to center of the Tank
//                           radius * Vector2f(cos(get_theta()), -sin(get_theta()))); // then shift in front of the Tank
    
    const Point2f position(get_position() +                                         // the Tank's upper-left coordinate
                           0.5f * (get_size() - bullet_size)); // then shift in front of the Tank
    
    Light_Beam* new_beam = new Light_Beam(position, bullet_size, get_theta());
    new_beam->set_source((Game_Object*)this);
    cout << "Beam Theta: " << new_beam->get_theta() << endl;
    return new_beam;
}

bool Cannon::can_reflect(Game_Object* rhs) {
    return false;
}

bool Cannon::collide(Game_Object &rhs) {
    return Game_Object::collide(rhs);
}

bool Cannon::can_rotate() {
    return true;
}

void Cannon::move(Vector2f dir) {
    return;
}

bool Cannon::selectable() {
    return false;
}