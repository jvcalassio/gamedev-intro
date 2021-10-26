#include "../include/Rect.hpp"

Rect::Rect() {
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

Rect::Rect(float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

/**
 * Adds {point} positions to Rect
 * */
Rect operator+ (const Rect& rec, const Vec2& point) {
    return Rect(
        rec.x + point.x,
        rec.y + point.y,
        rec.w,
        rec.h
    );
}

/**
 * Adds {point} positions to Rect
 * */
Rect operator+ (const Vec2& point, const Rect& rec) {
    return Rect(
        rec.x + point.x,
        rec.y + point.y,
        rec.w,
        rec.h
    );
}

/**
 * Subtracts {point} positions to Rect
 * */
Rect operator- (const Rect& rec, const Vec2& point) {
    return Rect(
        rec.x - point.x,
        rec.y - point.y,
        rec.w,
        rec.h
    );
}

/**
 * Adds {point} positions to this Rect
 * */
void Rect::operator+= (const Vec2& point) {
    x += point.x;
    y += point.y;
}

/**
 * Subtracts {point} positions to this Rect
 * */
void Rect::operator-= (const Vec2& point) {
    x -= point.x;
    y -= point.y;
}

/**
 * Returns the center point of this rectangle
 * */
Vec2 Rect::center() const {
    return Vec2(
        x + (w / 2),
        y + (h / 2)
    );
}

/**
 * Sets the center point of this rectangle
 * */
void Rect::set_center(const Vec2& point) {
    x = point.x - (w/2);
    y = point.y - (h/2);
}

/**
 * Distance between the center of this and {to} rectangle
 * */
float Rect::distance_to(const Rect& to) {
    return this->center().distance(to.center());
}

/**
 * Returns whether {point} is inside this rectangle
 * */
bool Rect::contains(const Vec2& point) {
    return (point.x >= x) && (point.y >= y)
        && (point.x <= x + w) && (point.y <= y + h);
}