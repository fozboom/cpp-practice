#ifndef GEOMETRY_INCLUDE_POINT_POINT_HPP_
#define GEOMETRY_INCLUDE_POINT_POINT_HPP_
#include <cstdint>
#include "IShape.hpp"

class Point: public IShape{
 public:
  Point(std::int64_t x, std::int64_t y);
  Point() = default;
  Point(const Point& other) = default;
  Point& operator=(const Point& other) = default;
  std::int64_t GetX() const;
  std::int64_t GetY() const;
  ~Point() override = default;
 private:
  std::int64_t x_;
  std::int64_t y_;
};

#endif  // GEOMETRY_INCLUDE_POINT_POINT_HPP_
