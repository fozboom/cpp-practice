#ifndef GEOMETRY_INCLUDE_VECTOR_HPP_
#define GEOMETRY_INCLUDE_VECTOR_HPP_
#include <algorithm>
#include <cstdint>

class Vector {
 public:
  Vector() = default;
  Vector(std::int64_t x, std::int64_t y);
  Vector& operator=(const Vector& other) = default;
  Vector(const Vector& other) = default;

  std::int64_t GetX() const;
  std::int64_t GetY() const;

  Vector& operator+=(const Vector& other);
  Vector& operator-=(const Vector& other);

 private:
  std::int64_t x_;
  std::int64_t y_;
};

Vector operator+(const Vector& a, const Vector& b);
Vector operator-(const Vector& a, const Vector& b);

#endif  // GEOMETRY_INCLUDE_VECTOR_HPP_
