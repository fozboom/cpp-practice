#include "Segment.hpp"

Point Segment::GetA() const {
  return a_;
}

Point Segment::GetB() const {
  return b_;
}

Segment::Segment(const Point& a, const Point& b) : a_(a), b_(b) {
}
