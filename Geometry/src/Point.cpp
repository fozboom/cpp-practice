#include "Point.hpp"

Point::Point(std::int64_t x, std::int64_t y) : x_(x), y_(y) {
}

std::int64_t Point::GetX() const {
  return x_;
}

std::int64_t Point::GetY() const {
  return y_;
}
