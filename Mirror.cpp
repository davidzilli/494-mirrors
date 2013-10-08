//
//  Mirror.cpp
//  game
//
//  Created by David Zilli on 9/30/13.
//
//

#include "Mirror.h"

Light_Beam * Mirror::reflect (Light_Beam *light_beam) {
    const Vector2f bullet_size(8.0f, 8.0f); 
    
    //Point of reflection is the point of intersection
    Point2f intersection = get_collision_point(*light_beam);
    
    //Reflected theta:
    //The angle of the mirror plane is get_theta()
    //find the min angle between mirror plane and incoming beam
    //add that angle to the mirror plane and that's the new beam's theta
    /*MOVE THIS TO IT'S OWN FUNCTION*/
    float mirror_plane_theta = fmodf(get_theta() + Global::pi * 3 / 4, Global::pi * 2);
    float normalized_beam_theta = light_beam->get_theta() - mirror_plane_theta;
    if (normalized_beam_theta < 0) {
        normalized_beam_theta += Global::pi * 2;
    }
    
    float reflected_theta = 0;
    
    if (normalized_beam_theta < Global::pi / 2) {
        float incident_angle = min(normalized_beam_theta, Global::pi - normalized_beam_theta);
        reflected_theta = fmodf(mirror_plane_theta - incident_angle, Global::pi * 2);
        if (reflected_theta < 0) {
            reflected_theta += Global::pi * 2;
        }
    } else {
        float incident_angle = min(normalized_beam_theta, Global::pi - normalized_beam_theta);
        reflected_theta = fmodf(mirror_plane_theta + Global::pi + incident_angle, Global::pi * 2);
        if (reflected_theta < 0) {
            reflected_theta += Global::pi * 2;
        }
    }

    Light_Beam* new_beam = new Light_Beam(intersection, bullet_size, reflected_theta);
    new_beam->set_source((Game_Object*)this);
    cout << "NEW Beam Theta: " << new_beam->get_theta() * 180.0f / Global::pi << endl;
    return new_beam;
}

bool Mirror::can_reflect(Game_Object* rhs) {

    if(!dynamic_cast<Light_Beam *>(rhs)->get_is_reflected() && dynamic_cast<Light_Beam *>(rhs)->get_source() != this) {
        //mirror has been hit by a light beam
        float mirror_surface_theta = get_theta() + Global::pi * 3 / 4;
        float norm_angle = fmod(dynamic_cast<Light_Beam *>(rhs)->get_theta() - mirror_surface_theta, Global::pi * 2);
        if (norm_angle < 0) {
            norm_angle += Global::pi * 2;
        }
        
        if (norm_angle > 0 && norm_angle < Global::pi) {
            return true;
        }
    }
    return false;
}

bool Mirror::collide(Game_Object &rhs) {
    
    if (dynamic_cast<Light_Beam*>(&rhs)->get_source() == this) {
        return false;
    }
    
    // Find the line segment of the light beam
    Point2f A1, A2;
    A1 = Point2f(rhs.get_position().x, //x
                 rhs.get_position().y); //y
    
    A2 = rhs.get_position() + rhs.get_size().x * Vector2f(cos(rhs.get_theta()), -sin(rhs.get_theta()));
    
    //Find the 3 points of the triangle and the center of the square
    Point2f B1, B2, Bcenter, Bcorner;
    float theta1, theta2;
    
    theta1 = fmodf(get_theta() + Global::pi * 3 / 4, Global::pi * 2);
    theta2 = fmodf(theta1 + Global::pi / 2, Global::pi * 2);
    
    Bcenter = m_position + 0.5f * m_size;
    
    B1 = Point2f(Bcenter.x + cos(theta1) * m_size.magnitude() / 2,
                 Bcenter.y - sin(theta1) * m_size.magnitude() / 2);
    
    B2 = Point2f(Bcenter.x - cos(theta1) * m_size.magnitude() / 2,
                 Bcenter.y + sin(theta1) * m_size.magnitude() / 2);
    
    Bcorner = Bcenter + m_size.magnitude() / 2 * Vector2f(cos(theta2), -sin(theta2));
    
    //Test each line segment for collision
    
    //Diag
    float denom = ((B2.y - B1.y) * (A2.x - A1.x)) - ((B2.x - B1.x) * (A2.y - A1.y));
    float Ua = ((B2.x - B1.x) * (A1.y - B1.y) - (B2.y - B1.y) * (A1.x - B1.x)) / denom;
    float Ub = ((A2.x - A1.x) * (A1.y - B1.y) - (A2.y - A1.y) * (A1.x - B1.x)) / denom;
    
    if (denom != 0 && (Ua > 0 && Ua < 1) && (Ub > 00 && Ub < 1)) {
        return true;
    }

    //Bottom
    
//    denom = ((B2.y - Bcorner.y) * (A2.x - A1.x)) - ((B2.x - Bcorner.x) * (A2.y - A1.y));
//    Ua = ((B2.x - Bcorner.x) * (A1.y - Bcorner.y) - (B2.y - Bcorner.y) * (A1.x - Bcorner.x)) / denom;
//    Ub = ((A2.x - A1.x) * (A1.y - Bcorner.y) - (A2.y - A1.y) * (A1.x - Bcorner.x)) / denom;
//    
//    if (denom != 0 && (Ua > 0 && Ua < 1) && (Ub > 00 && Ub < 1)) {
//        return true;
//    }
//
//    //Left
//    denom = ((Bcorner.y - B1.y) * (A2.x - A1.x)) - ((Bcorner.x - B1.x) * (A2.y - A1.y));
//    Ua = ((Bcorner.x - B1.x) * (A1.y - B1.y) - (Bcorner.y - B1.y) * (A1.x - B1.x)) / denom;
//    Ub = ((A2.x - A1.x) * (A1.y - B1.y) - (A2.y - A1.y) * (A1.x - B1.x)) / denom;
//    
//    if (denom != 0 && (Ua > 0 && Ua < 1) && (Ub > 00 && Ub < 1)) {
//        return true;
//    }

    return false;
}

Point2f Mirror::get_collision_point(Game_Object &rhs) {
    
    // Find the line segment of the light beam
    Point2f A1, A2;
    A1 = Point2f(rhs.get_position().x, //x
                 rhs.get_position().y); //y
    
    A2 = rhs.get_position() + rhs.get_size().x * Vector2f(cos(rhs.get_theta()), -sin(rhs.get_theta()));
    
    //Find the 3 points of the triangle and the center of the square
    Point2f B1, B2, Bcenter, Bcorner;
    float theta1, theta2;
    
    theta1 = fmodf(get_theta() + Global::pi * 3 / 4, Global::pi * 2);
    theta2 = fmodf(theta1 + Global::pi / 2, Global::pi * 2);
    
    Bcenter = m_position + 0.5f * m_size;
    
    B1 = Point2f(Bcenter.x + cos(theta1) * m_size.magnitude() / 2,
                 Bcenter.y - sin(theta1) * m_size.magnitude() / 2);
    
    B2 = Point2f(Bcenter.x - cos(theta1) * m_size.magnitude() / 2,
                 Bcenter.y + sin(theta1) * m_size.magnitude() / 2);
    
    Bcorner = Bcenter + m_size.magnitude() / 2 * Vector2f(cos(theta2), -sin(theta2));
    
    //Test each line segment for collision
    
    //Diag
    float denom = ((B2.y - B1.y) * (A2.x - A1.x)) - ((B2.x - B1.x) * (A2.y - A1.y));
    float Ua = ((B2.x - B1.x) * (A1.y - B1.y) - (B2.y - B1.y) * (A1.x - B1.x)) / denom;
    float Ub = ((A2.x - A1.x) * (A1.y - B1.y) - (A2.y - A1.y) * (A1.x - B1.x)) / denom;
    
    if (denom != 0 && (Ua > 0 && Ua < 1) && (Ub > 00 && Ub < 1)) {
        return Point2f(A1 + Ua * (A2 - A1));
    }
    
    //Bottom
    
//    denom = ((B2.y - Bcorner.y) * (A2.x - A1.x)) - ((B2.x - Bcorner.x) * (A2.y - A1.y));
//    Ua = ((B2.x - Bcorner.x) * (A1.y - Bcorner.y) - (B2.y - Bcorner.y) * (A1.x - Bcorner.x)) / denom;
//    Ub = ((A2.x - A1.x) * (A1.y - Bcorner.y) - (A2.y - A1.y) * (A1.x - Bcorner.x)) / denom;
//    
//    if (denom != 0 && (Ua > 0 && Ua < 1) && (Ub > 00 && Ub < 1)) {
//        return Point2f(A1 + Ua * (A2 - A1));    }
//    
//    //Left
//    denom = ((Bcorner.y - B1.y) * (A2.x - A1.x)) - ((Bcorner.x - B1.x) * (A2.y - A1.y));
//    Ua = ((Bcorner.x - B1.x) * (A1.y - B1.y) - (Bcorner.y - B1.y) * (A1.x - B1.x)) / denom;
//    Ub = ((A2.x - A1.x) * (A1.y - B1.y) - (A2.y - A1.y) * (A1.x - B1.x)) / denom;
//    
//    if (denom != 0 && (Ua > 0 && Ua < 1) && (Ub > 00 && Ub < 1)) {
//        return Point2f(A1 + Ua * (A2 - A1));
//    }
    
    return Point2f();

    
}

bool Mirror::can_rotate() {
    return true;
}

void Mirror::move(Vector2f dir) {
    m_position += dir * m_size.x;
}

bool Mirror::selectable() {
    return true;
}