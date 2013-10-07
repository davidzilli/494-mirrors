//
//  Light_Beam.cpp
//  game
//
//  Created by David Zilli on 9/29/13.
//
//

#include "Light_Beam.h"

//For each time step, grows the beam in its direction of travel
void Light_Beam::project_forward(const float &move) {
    if (!m_reflected) {
        float temp_theta = m_theta;
        m_theta = 0.0f;
        m_size = Vector2f(m_size.x + move, m_size.y);
        m_theta = temp_theta;
    }
}

//The beam of light is responsible for finding the target it will hit when it is created.
//Find the center of the start of the beam and project a line in the direction of its theta.
//That line can be used to test all map objects for intersection. The point of intersection
//return true when an intersect is found and sets the target to the point
bool Light_Beam::get_target_intersect(Game_Object &rhs) {
    Point2f A1, A2, B1, B2;
    
    //A is the Beam
    A1 = Point2f(get_position().x, get_position().y);
    A2 = Point2f(cos(get_theta()) * (get_position().x + 2000), //x
                 sin(get_theta()) * (get_position().x + 2000)); //y
    
    //B is a game object being tested for collision
    B1 = rhs.get_position();
    B2 = Point2f(rhs.get_position().x,
                 sin(rhs.get_theta()) * rhs.get_size().x + rhs.get_position().y);
    
    float denom = ((B2.y - B1.y) * (A2.x - A1.x)) - ((B2.x - B1.x) * (A2.y - A1.y));
    float Ua = ((B2.x - B1.x) * (A1.y - B1.y) - (B2.y - B1.y) * (A1.x - B1.x)) / denom;
    float Ub = ((A2.x - A1.x) * (A1.y - B1.y) - (A2.y - A1.y) * (A1.x - B1.x)) / denom;
    
    if (denom == 0) {
        return false;
    }
    
    if ((Ua < 0 || Ua > 1) || (Ub < 0 || Ub > 1)) {
        return false;
    }
    
    target_intersect = new Point2f(B1 + Ub * (B2 - B1));
    return true;
}

//If the beam has been reflected, it's flag is set to true
bool Light_Beam::get_is_reflected() {
    return m_reflected;
}

void Light_Beam::set_is_reflected(bool is_reflected) {
    m_reflected = is_reflected;
}

bool Light_Beam::can_reflect(Game_Object* rhs) {
    return false;
}

//This is the Game_Object source of the beam, typically the cannon or a mirror
void Light_Beam::set_source(Game_Object* source) {
    m_source = source;
}

Game_Object* Light_Beam::get_source() {
    return m_source;
}

bool Light_Beam::collide(Game_Object &rhs) {
    return false;
}