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

Vector& Vector::operator*=(std::int64_t number) {
  x_ *= number;
  y_ *= number;
  return *this;
}

Vector Vector::operator-() const {
  Vector result(-x_, -y_);
  return result;
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

std::int64_t operator*(const Vector& a, const Vector& b) {
  return a.GetX() * b.GetX() + a.GetY() * b.GetY();
}

std::int64_t operator^(const Vector& a, const Vector& b) {
  return a.GetX() * b.GetY() - a.GetY() * b.GetX();
}

Vector operator*(const Vector& a, std::int64_t number) {
  Vector result(a.GetX() * number, a.GetY() * number);
  return result;
}

Vector operator*(std::int16_t number, const Vector& b) {
  return b * number;
}
