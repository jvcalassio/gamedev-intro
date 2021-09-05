#ifndef __VEC2__
#define __VEC2__

/**
 * Vector 2D class
 * x, y represents the position
 * */
class Vec2 {
    public:
        float x;
        float y;

        Vec2();
        Vec2(float x, float y);

        Vec2 operator+ (const Vec2& point);
        Vec2 operator- (const Vec2& point);
        friend Vec2 operator* (float value, const Vec2& point);
        friend Vec2 operator* (const Vec2& point, float value);
        bool operator== (const Vec2& point);
        bool operator!= (const Vec2& point);
        float magnitude();
        Vec2 normalized();
        int normalize();
        float distance(const Vec2& to);
        float angle();
        float angle(const Vec2& to);
        Vec2 rotated(float angle);
        void rotate(float angle);
        float dot(const Vec2& point);
};

#endif