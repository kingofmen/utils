#include "geometry.h"

namespace utils {
namespace geometry {

const doublet doublet::zero(0, 0);
const triplet triplet::zero(0, 0, 0);

double degToRad(double degrees) { return degrees * 3.14159265 / 180; }
double radToDeg(double radians) { return radians * 180 / 3.14159265; }

triplet triplet::cross(const triplet &other) const {
  triplet ret;
  ret.x() = this->y() * other.z() - this->z() * other.y();
  ret.y() = this->z() * other.x() - this->x() * other.z();
  ret.z() = this->x() * other.y() - this->y() * other.x();
  return ret;
}

double triplet::dot(const triplet &other) const {
  double ret = this->x() * other.x();
  ret += this->y() * other.y();
  ret += this->z() * other.z();
  return ret;
}

double triplet::angle(const triplet &other) const {
  double ret = this->dot(other);
  ret /= this->norm();
  ret /= other.norm();
  return acos(ret);
}

void triplet::normalise() { (*this) /= this->norm(); }

void triplet::rotatexy(double degrees, const triplet &around) {
  (*this) -= around;
  double newx =
      this->x() * cos(degToRad(degrees)) - this->y() * sin(degToRad(degrees));
  double newy =
      this->x() * sin(degToRad(degrees)) + this->y() * cos(degToRad(degrees));
  this->x() = newx;
  this->y() = newy;
  (*this) += around;
}

void triplet::operator-=(const triplet &other) {
  this->x() -= other.x();
  this->y() -= other.y();
  this->z() -= other.z();
}
void triplet::operator+=(const triplet &other) {
  this->x() += other.x();
  this->y() += other.y();
  this->z() += other.z();
}
void triplet::operator/=(double scale) {
  this->x() /= scale;
  this->y() /= scale;
  this->z() /= scale;
}
void triplet::operator*=(double scale) {
  this->x() *= scale;
  this->y() *= scale;
  this->z() *= scale;
}

triplet operator-(triplet one, triplet two) {
  triplet ret = one;
  ret -= two;
  return ret;
}

triplet operator+(triplet one, triplet two) {
  triplet ret = one;
  ret += two;
  return ret;
}

triplet operator*(triplet one, double scale) {
  triplet ret = one;
  ret *= scale;
  return ret;
}

triplet operator/(triplet one, double scale) {
  triplet ret = one;
  ret /= scale;
  return ret;
}

double doublet::dot(const doublet &other) const {
  double ret = this->x() * other.x();
  ret += this->y() * other.y();
  return ret;
}

double doublet::angle(const doublet &other) const {
  double ret = this->dot(other);
  ret /= this->norm();
  ret /= other.norm();
  return acos(ret);
}

void doublet::normalise() { (*this) /= this->norm(); }

void doublet::operator-=(const doublet &other) {
  this->x() -= other.x();
  this->y() -= other.y();
}
void doublet::operator+=(const doublet &other) {
  this->x() += other.x();
  this->y() += other.y();
}

void doublet::operator/=(double scale) {
  this->x() /= scale;
  this->y() /= scale;
}
void doublet::operator*=(double scale) {
  this->x() *= scale;
  this->y() *= scale;
}

doublet &doublet::operator=(const boost::tuple<double, double, double> &rhs) {
  this->x() = boost::get<0>(rhs);
  this->y() = boost::get<1>(rhs);
  return *this;
}

void doublet::rotate(double degrees, const doublet &around) {
  (*this) -= around;
  double newx =
      this->x() * cos(degToRad(degrees)) - this->y() * sin(degToRad(degrees));
  double newy =
      this->x() * sin(degToRad(degrees)) + this->y() * cos(degToRad(degrees));
  this->x() = newx;
  this->y() = newy;
  (*this) += around;
}

bool intersect(double line1x1, double line1y1, double line1x2, double line1y2,
               double line2x1, double line2y1, double line2x2, double line2y2,
               double tol) {
  double line1A = line1y2 - line1y1;
  double line1B = line1x1 - line1x2;
  double line1C = line1A * line1x1 + line1B * line1y1;

  double line2A = line2y2 - line2y1;
  double line2B = line2x1 - line2x2;
  double line2C = line2A * line2x1 + line2B * line2y1;

  double det = line1A * line2B - line1B * line2A;
  if (fabs(det) < 0.00001)
    return false; // Parallel lines

  double xinter = (line2B * line1C - line1B * line2C) / det;
  // Small tolerance accounts for roundoff error.
  if (xinter < std::min(line1x1, line1x2) - tol)
    return false;
  if (xinter > std::max(line1x1, line1x2) + tol)
    return false;
  if (xinter < std::min(line2x1, line2x2) - tol)
    return false;
  if (xinter > std::max(line2x1, line2x2) + tol)
    return false;
  double yinter = (line1A * line2C - line2A * line1C) / det;
  if (yinter < std::min(line1y1, line1y2) - tol)
    return false;
  if (yinter > std::max(line1y1, line1y2) + tol)
    return false;
  if (yinter < std::min(line2y1, line2y2) - tol)
    return false;
  if (yinter > std::max(line2y1, line2y2) + tol)
    return false;

  return true;
}

bool intersect(doublet line1p1, doublet line1p2, doublet line2p1,
               doublet line2p2, double tol) {
  return intersect(line1p1.x(), line1p1.y(), line1p2.x(), line1p2.y(),
                   line2p1.x(), line1p1.y(), line2p2.x(), line2p2.y(), tol);
}

} // namespace geometry
} // namespace utils
