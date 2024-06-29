#ifndef GEOMETRY_INCLUDE_SEGMENT_SEGMENT_HPP_
#define GEOMETRY_INCLUDE_SEGMENT_SEGMENT_HPP_
#include "IShape.hpp"
#include "Point.hpp"
class Segment : public IShape {
 public:
  Segment() = default;
  Segment(const Point& a, const Point& b);
  Segment(const Segment& other) = default;
  Segment& operator=(const Segment& other) = default;
  Point GetA() const;
  Point GetB() const;
  ~Segment() override = default;
 private:
  Point a_;
  Point b_;
};

#endif  // GEOMETRY_INCLUDE_SEGMENT_SEGMENT_HPP_
