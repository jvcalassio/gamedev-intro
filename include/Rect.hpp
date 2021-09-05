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
        Vec2 center() const;
        float distance_to(const Rect& to);
        bool contains(const Vec2& point);
};

#endif