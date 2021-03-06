#ifndef __RECT__
#define __RECT__
#include "Vec2.hpp"

/**
 * Rectangle class
 * x, y represents the rectangle position at top left corner
 * w, h represents width and height of the rectanglee
 * */
class Rect {
    public:
        float x;
        float y;
        float w;
        float h;

        Rect();
        Rect(float x, float y, float w, float h);
        friend Rect operator+ (const Rect& rec, const Vec2& point);
        friend Rect operator+ (const Vec2& point, const Rect& rec);
        friend Rect operator- (const Rect& rec, const Vec2& point);
        void operator+= (const Vec2& rec);
        void operator-= (const Vec2& rec);
        Vec2 center() const;
        void set_center(const Vec2& point);
        float distance_to(const Rect& to);
        bool contains(const Vec2& point);
};

#endif