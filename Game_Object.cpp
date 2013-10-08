//
//  GameObject.cpp
//  game
//
//  Created by David Zilli on 9/28/13.
//
//

#include "Game_Object.h"
#include "Light_Beam.h"
#include <zenilib.h>

using namespace std;
using namespace Zeni;

const Point2f & Game_Object::get_position() const {return m_position;}
const Vector2f & Game_Object::get_size() const {return m_size;}
const float & Game_Object::get_theta() const {return m_theta;}
const float Game_Object::get_radius() const {return 0.5f * m_size.magnitude();}
bool Game_Object::is_reflective() {return m_reflective;} //whether absorbs or reflects beams

void Game_Object::turn_left(const float &dir_) {
    
    if (dir_ < 0) {
        m_theta += Global::pi / 12 * 23;
    } else if (dir_ > 0) {
        m_theta += Global::pi / 12;
    } else {
        return;
    }
    
    m_theta = fmod(m_theta, Global::pi * 2.0l);
    
}

bool Game_Object::collide(Game_Object &rhs) {
    
    if (dynamic_cast<Light_Beam*>(&rhs)->get_source() == this) {
        return false;
    }
    
    // Find the line segment of the light beam
    Point2f A1, A2;
    A1 = Point2f(rhs.get_position().x, //x
                 rhs.get_position().y); //y
    
    A2 = rhs.get_position() + rhs.get_size().x * Vector2f(cos(rhs.get_theta()), -sin(rhs.get_theta()));
    
    //Find the 3 points of the triangle and the center of the square
    Point2f B1, B2, Bcenter, B3, B4;
    float theta1, theta2;
    
    theta1 = fmodf(get_theta() + Global::pi * 3 / 4, Global::pi * 2);
    theta2 = fmodf(theta1 + Global::pi / 2, Global::pi * 2);
    
    Bcenter = m_position + 0.5f * m_size;
    
    B1 = Point2f(Bcenter.x + cos(theta1) * m_size.magnitude() / 2,
                 Bcenter.y - sin(theta1) * m_size.magnitude() / 2);
    
    B2 = Point2f(Bcenter.x - cos(theta1) * m_size.magnitude() / 2,
                 Bcenter.y + sin(theta1) * m_size.magnitude() / 2);
    
    B3 = Bcenter + m_size.magnitude() / 2 * Vector2f(cos(theta2), -sin(theta2));
    
    B4 = Bcenter - m_size.magnitude() / 2 * Vector2f(cos(theta2), -sin(theta2));

    //Bottom
    
    float denom = ((B2.y - B3.y) * (A2.x - A1.x)) - ((B2.x - B3.x) * (A2.y - A1.y));
    float Ua = ((B2.x - B3.x) * (A1.y - B3.y) - (B2.y - B3.y) * (A1.x - B3.x)) / denom;
    float Ub = ((A2.x - A1.x) * (A1.y - B3.y) - (A2.y - A1.y) * (A1.x - B3.x)) / denom;

    if (denom != 0 && (Ua > 0 && Ua < 1) && (Ub > 00 && Ub < 1)) {
        return true;
    }

    //Left
    denom = ((B3.y - B1.y) * (A2.x - A1.x)) - ((B3.x - B1.x) * (A2.y - A1.y));
    Ua = ((B3.x - B1.x) * (A1.y - B1.y) - (B3.y - B1.y) * (A1.x - B1.x)) / denom;
    Ub = ((A2.x - A1.x) * (A1.y - B1.y) - (A2.y - A1.y) * (A1.x - B1.x)) / denom;

    if (denom != 0 && (Ua > 0 && Ua < 1) && (Ub > 00 && Ub < 1)) {
        return true;
    }
    
    //Top
    denom = ((B4.y - B1.y) * (A2.x - A1.x)) - ((B4.x - B1.x) * (A2.y - A1.y));
    Ua = ((B4.x - B1.x) * (A1.y - B1.y) - (B4.y - B1.y) * (A1.x - B1.x)) / denom;
    Ub = ((A2.x - A1.x) * (A1.y - B1.y) - (A2.y - A1.y) * (A1.x - B1.x)) / denom;
    
    if (denom != 0 && (Ua > 0 && Ua < 1) && (Ub > 00 && Ub < 1)) {
        return true;
    }
    
    //Right
    denom = ((B2.y - B4.y) * (A2.x - A1.x)) - ((B2.x - B4.x) * (A2.y - A1.y));
    Ua = ((B2.x - B4.x) * (A1.y - B4.y) - (B2.y - B4.y) * (A1.x - B4.x)) / denom;
    Ub = ((A2.x - A1.x) * (A1.y - B4.y) - (A2.y - A1.y) * (A1.x - B4.x)) / denom;
    
    if (denom != 0 && (Ua > 0 && Ua < 1) && (Ub > 00 && Ub < 1)) {
        return true;
    }

    return false;
}

Point2f Game_Object::get_collision_point(Game_Object &rhs) {
    Point2f A1, A2, B1, B2;
    A1 = Point2f(rhs.get_position().x, //x
                 rhs.get_position().y); //y
    A2 = rhs.get_position() + rhs.get_size().x * Vector2f(cos(rhs.get_theta()), -sin(rhs.get_theta())); //y
    
    //Top
    B1 = get_position();
    B2 = Point2f(get_position().x + get_size().x,
                 get_position().y);
    
    float denom = ((B2.y - B1.y) * (A2.x - A1.x)) - ((B2.x - B1.x) * (A2.y - A1.y));
    float Ua = ((B2.x - B1.x) * (A1.y - B1.y) - (B2.y - B1.y) * (A1.x - B1.x)) / denom;
    float Ub = ((A2.x - A1.x) * (A1.y - B1.y) - (A2.y - A1.y) * (A1.x - B1.x)) / denom;
    
    if (denom != 0 && (Ua > 0 && Ua < 1) && (Ub > 00 && Ub < 1)) {
        return Point2f(A1 + Ua * (A2 - A1));
    }
    
    //Bottom
    B1 = Point2f(get_position().x, get_position().y + get_size().y);
    B2 = Point2f(get_position().x + get_size().x,
                 get_position().y + get_size().y);
    
    denom = ((B2.y - B1.y) * (A2.x - A1.x)) - ((B2.x - B1.x) * (A2.y - A1.y));
    Ua = ((B2.x - B1.x) * (A1.y - B1.y) - (B2.y - B1.y) * (A1.x - B1.x)) / denom;
    Ub = ((A2.x - A1.x) * (A1.y - B1.y) - (A2.y - A1.y) * (A1.x - B1.x)) / denom;
    
    if (denom != 0 && (Ua > 0 && Ua < 1) && (Ub > 00 && Ub < 1)) {
        return Point2f(A1 + Ua * (A2 - A1));
    }
    
    
    //Right
    B1 = get_position();
    B2 = Point2f(get_position().x + get_size().x,
                 get_position().y + get_size().y);
    
    denom = ((B2.y - B1.y) * (A2.x - A1.x)) - ((B2.x - B1.x) * (A2.y - A1.y));
    Ua = ((B2.x - B1.x) * (A1.y - B1.y) - (B2.y - B1.y) * (A1.x - B1.x)) / denom;
    Ub = ((A2.x - A1.x) * (A1.y - B1.y) - (A2.y - A1.y) * (A1.x - B1.x)) / denom;
    
    if (denom != 0 && (Ua > 0 && Ua < 1) && (Ub > 00 && Ub < 1)) {
        return Point2f(A1 + Ua * (A2 - A1));
    }
    
    //Left
    B1 = get_position();
    B2 = Point2f(get_position().x,
                 get_position().y + get_size().y);
    
    denom = ((B2.y - B1.y) * (A2.x - A1.x)) - ((B2.x - B1.x) * (A2.y - A1.y));
    Ua = ((B2.x - B1.x) * (A1.y - B1.y) - (B2.y - B1.y) * (A1.x - B1.x)) / denom;
    Ub = ((A2.x - A1.x) * (A1.y - B1.y) - (A2.y - A1.y) * (A1.x - B1.x)) / denom;
    
    if (denom != 0 && (Ua > 0 && Ua < 1) && (Ub > 00 && Ub < 1)) {
        return Point2f(A1 + Ua * (A2 - A1));
    }
    
    return Point2f();
}

const Point2f Game_Object::get_center() {
    float temp_theta = m_theta;
    m_theta = 0.0f;
    Point2f center = get_position() + 0.5f * get_size();
    m_theta = temp_theta;
    return center;
}

bool Game_Object::can_reflect(Game_Object *light_beam) {
    
    if(is_reflective() && Game_Object::collide(*light_beam)) {
        //mirror has been hit by a light beam
        //incoming beam's angle has to be within +/- pi/2 of the mirror's angle
        float norm_angle = light_beam->get_theta() - (get_theta() + Global::pi / 4.0f);
        if (norm_angle < 0) {
            norm_angle += Global::pi * 2;
        }
        
        if (norm_angle > Global::pi && norm_angle < Global::pi * 2) {
            return true;
        }
    }
    return false;
}