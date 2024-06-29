#include "Vector.hpp"

Vector::Vector(std::int64_t x, std::int64_t y) : x_(x), y_(y) {
}

std::int64_t Vector::GetX() const {
  return x_;
}

std::int64_t Vector::GetY() const {
  return y_;
}

Vector& Vector::operator+=(const Vector& other) {
  x_ += other.x_;
  y_ += other.y_;
  return *this;
}

Vector& Vector::operator-=(const Vector& other) {
  x_ -= other.x_;
  y_ -= other.y_;
  return *this;
}

Vector operator+(const Vector& a, const Vector& b) {
  Vector result = a;
  result += b;
  return result;
}

Vector operator-(const Vector& a, const Vector& b) {
  Vector result = a;
  result -= b;
  return result;
}
