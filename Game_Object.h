//
//  GameObject.h
//  game
//
//  Created by David Zilli on 9/28/13.
//
//

#ifndef __game__GameObject__
#define __game__GameObject__

#include <iostream>
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Game_Object {
public:
    Game_Object(const Point2f &position_,
                const Vector2f &size_,
                const float &theta_ = 0.0f,
                const float &speed_ = 0.0f,
                const bool &reflective_ = false)
    : m_position(position_),
    m_size(size_),
    m_theta(theta_),
    m_speed(speed_),
    m_reflective(reflective_)
    {
    }
    
    // If you might delete base class pointers, you need a virtual destructor.
    virtual ~Game_Object() {}
    virtual void render() const = 0;
    bool is_reflective();
    const float get_radius() const;
    const Point2f & get_position() const;
    const Vector2f & get_size() const;
    const float & get_theta() const;
    void turn_left(const float &theta_);
    virtual bool collide(Game_Object &rhs);
    Point2f get_collision_point(Game_Object &rhs);
    const Point2f get_center();
    virtual bool can_reflect(Game_Object *rhs);
    virtual bool can_rotate() = 0;
    virtual bool selectable() = 0;
    virtual void move(Vector2f dir) = 0;


protected:
    Point2f m_position; // Upper left corner
    Vector2f m_size; // (width, height)
    float m_theta;
    float m_speed;
    bool m_reflective;
    
    void render(const String &texture, float x_offset, float y_offset, const Color &filter = Color()) const {
        // Use a helper defined in Zeni/EZ2D.h
        render_image(
                     texture, // which texture to use
                     m_position, // upper-left corner
                     m_position + m_size, // lower-right corner
                     m_theta, // rotation in radians
                     1.0f, // scaling factor
                     m_position + Point2f(x_offset * m_size.x, y_offset * m_size.y), // point to rotate & scale about
                     false, // whether or not to horizontally flip the texture
                     filter); // what Color to "paint" the texture
    }
    
    
private:
    
};

#endif /* defined(__game__GameObject__) */
