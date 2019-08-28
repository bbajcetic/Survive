#include "Vec2D.h"

Vec2D::Vec2D () {
    this->x = 0;
    this->y = 0;
}
Vec2D::Vec2D (float x, float y) {
    this->x = x;
    this->y = y;
}
float Vec2D::getLength() {
    return sqrt( pow(x, 2) + pow(y, 2) );
}
void Vec2D::print() {
    printf("(%f,%f)\n", x, y);
}
Vec2D Vec2D::operator - (Vec2D const &obj) {
    Vec2D result(x - obj.x, y - obj.y);
    return result;
}
Vec2D Vec2D::operator + (Vec2D const &obj) {
    Vec2D result(x + obj.x, y + obj.y);
    return result;
}
float Vec2D::operator * (Vec2D const &obj) {
    return x * obj.x + y * obj.y;
}
Vec2D Vec2D::operator * (float const &obj) {
    Vec2D result(x * obj, y * obj);
    return result;
}
Vec2D vecProject(Vec2D a, Vec2D b) {
    float top = a * b;
    float bottom = pow( b.getLength(), 2 );
    Vec2D result = b * (top/bottom);
    return result;
}

