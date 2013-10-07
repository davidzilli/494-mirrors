//
//  Wall.cpp
//  game
//
//  Created by David Zilli on 10/2/13.
//
//

#include "Wall.h"

bool Wall::can_reflect(Game_Object* rhs) {
    return false;
}

bool Wall::collide(Game_Object &rhs) {

    return Game_Object::collide(rhs);
//    Point2f A1, A2, B1, B2;
//    A1 = Point2f(rhs.get_position().x, //x
//                 rhs.get_position().y); //y
//    A2 = rhs.get_position() + rhs.get_size().x * Vector2f(cos(rhs.get_theta()), -sin(rhs.get_theta())); //y
//    
//    B1 = get_position();
//    B2 = Point2f(get_position().x + get_size().x,
//                 get_position().y + get_size().y);
//    
//    float denom = ((B2.y - B1.y) * (A2.x - A1.x)) - ((B2.x - B1.x) * (A2.y - A1.y));
//    float Ua = ((B2.x - B1.x) * (A1.y - B1.y) - (B2.y - B1.y) * (A1.x - B1.x)) / denom;
//    float Ub = ((A2.x - A1.x) * (A1.y - B1.y) - (A2.y - A1.y) * (A1.x - B1.x)) / denom;
//    
//    if (denom == 0) {
//        return false;
//    }
//    
//    if ((Ua < 0 || Ua > 1) || (Ub < 0 || Ub > 1)) {
//        return false;
//    }
//    
//    return true;
}
