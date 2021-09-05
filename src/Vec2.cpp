#include <cmath>
#include "../include/Vec2.hpp"
#ifndef M_PI 
#define M_PI		3.14159265358979323846
#endif

Vec2::Vec2() {
    this->x = 0.0f;
    this->y = 0.0f;
}

Vec2::Vec2(float x, float y) {
    this->x = x;
    this->y = y;
}

/**
 * Sum between vectors
 * */
Vec2 Vec2::operator+ (const Vec2& point) {
    return Vec2(
        x + point.x,
        y + point.y
    );
}

/**
 * Subtraction between vectors
 * */
Vec2 Vec2::operator- (const Vec2& point) {
    return Vec2(
        x - point.x,
        y - point.y
    );
}

/**
 * Product by scalar
 * */
Vec2 operator* (float value, const Vec2& point) {
    return Vec2(
        point.x * value,
        point.y * value
    );
}

/**
 * Product by scalar
 * */
Vec2 operator* (const Vec2& point, float value) {
    return Vec2(
        point.x * value,
        point.y * value
    );
}

/**
 * Comparison between vectors (equal)
 * */
bool Vec2::operator== (const Vec2& point) {
    return (x == point.x && y == point.y);
}

/**
 * Comparison between vectors (not equal)
 * */
bool Vec2::operator!= (const Vec2& point) {
    return !(x == point.x && y == point.y);
}

/**
 * Returns this vector's length (from (0,0))
 * */
float Vec2::magnitude() {
    return sqrt( (x*x) + (y*y) );
}

/**
 * Returns a new vector with same direction as this vector,
 * but with length = 1
 * */
Vec2 Vec2::normalized() {
    float mag = this->magnitude();
    if(mag != 0) {
        Vec2 res(x / mag, y / mag);
        return res;
    }
    return Vec2();
}

/**
 * Normalize this vector
 * Returns 1 if successful, returns 0 if the vector is too small to be normalized
 * */
int Vec2::normalize() {
    float mag = this->magnitude();
    if(mag != 0) {
        x = x / mag;
        y = y / mag;
        return 1;
    }
    return 0;
}

/**
 * Distance between two vectors
 * Same as magnitude of ( v1 - v2 )
 * */
float Vec2::distance(const Vec2& to) {
    Vec2 res(to.x - x, to.y - y);
    return res.magnitude();
}

/**
 * Angle between this vector and the X axis
 * */
float Vec2::angle() {
    return atan2(y, x);
}

/**
 * Angle between the line formed by (to - this vector)
 * and the X axis
 * Same as (to - this).angle()
 * */
float Vec2::angle(const Vec2& to) {
    // o comentado seria angulo entre a linha de (0,0 ate to) e (0,0 ate this)
    //return acos( ((x * to.x) + (y * to.y)) / (this->magnitude() * to.magnitude()) );
    return atan2( to.y - y, to.x - x );
}

/**
 * Rotates this vector by {angle} radians
 * It considers that Y grows downwards (so the angle is multiplied by -1)
 * */
Vec2 Vec2::rotated(float angle) {
    //double angle_rad = (angle * M_PI * -1) / 180.0;
    float newx = (x * cos(angle)) - (y * sin(angle));
    float newy = (y * cos(angle)) + (x * sin(angle));
    return Vec2(newx, newy);
}

/**
 * Rotates this vector by {angle} radians
 * It considers that Y grows downwards (so the angle is multiplied by -1)
 * */
void Vec2::rotate(float angle) {
    //double angle_rad = (angle * M_PI * -1) / 180.0;
    float newx = (x * cos(angle)) - (y * sin(angle));
    float newy = (y * cos(angle)) + (x * sin(angle));
    x = newx;
    y = newy;
}

/**
 * Dot product between two vectors
 * */
float Vec2::dot(const Vec2& point) {
    return (x * point.x) + (y * point.y);
}