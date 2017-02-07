// Utility functions and classes for 2d and 3d geometry.

#include "boost/tuple/tuple.hpp"

namespace utils {
namespace geometry {

// Conversions.
double degToRad(double degrees);
double radToDeg(double radians);

// Two-d and three-d vectors with convenience functions.
struct doublet : public boost::tuple<double, double> {
  doublet(double x, double y) : boost::tuple<double, double>(x, y) {}
  doublet() : boost::tuple<double, double>(0, 0) {}

  double &x() { return boost::get<0>(*this); }
  double &y() { return boost::get<1>(*this); }

  double x() const { return boost::get<0>(*this); }
  double y() const { return boost::get<1>(*this); }

  double angle(const doublet &other) const;
  double dot(const doublet &other) const;
  double norm() const { return sqrt(pow(this->x(), 2) + pow(this->y(), 2)); }
  void normalise();
  void rotate(double degrees, const doublet &around = zero);
  double distance(const doublet &other) const {
    return sqrt(pow(x() - other.x(), 2) + pow(y() - other.y(), 2));
  }

  doublet &operator=(const boost::tuple<double, double, double> &rhs);
  void operator/=(double scale);
  void operator*=(double scale);
  void operator-=(const doublet &other);
  void operator+=(const doublet &other);

private:
  static const doublet zero;
};

struct triplet : public boost::tuple<double, double, double> {
  triplet(double x, double y, double z)
      : boost::tuple<double, double, double>(x, y, z) {}
  triplet(double x, double y) : boost::tuple<double, double, double>(x, y, 0) {}
  triplet(double x) : boost::tuple<double, double, double>(x, 0, 0) {}
  triplet() : boost::tuple<double, double, double>(0, 0, 0) {}

  double &x() { return boost::get<0>(*this); }
  double &y() { return boost::get<1>(*this); }
  double &z() { return boost::get<2>(*this); }

  double x() const { return boost::get<0>(*this); }
  double y() const { return boost::get<1>(*this); }
  double z() const { return boost::get<2>(*this); }

  double angle(const triplet &other) const;
  triplet cross(const triplet &other) const;
  double dot(const triplet &other) const;
  double norm() const {
    return sqrt(pow(this->x(), 2) + pow(this->y(), 2) + pow(this->z(), 2));
  }
  void normalise();

  void operator/=(double scale);
  void operator*=(double scale);
  void operator-=(const triplet &other);
  void operator+=(const triplet &other);

  void rotatexy(
      double degrees,
      const triplet &around = zero); // Special for rotating the xy projection.

private:
  static const triplet zero;
};

triplet operator-(triplet one, triplet two);
triplet operator+(triplet one, triplet two);
triplet operator*(triplet one, double scale);
triplet operator/(triplet one, double scale);

// Returns true if the lines defined by (x1, y1, x2, y2) intersect.
bool intersect(double line1x1, double line1y1, double line1x2, double line1y2,
               double line2x1, double line2y1, double line2x2, double line2y2,
               double tol = 0.0001);

bool intersect(doublet line1p1, doublet line1p2, doublet line2p1,
               doublet line2p2, double tol = 0.0001);

} // namespace geometry
} // namespace utils
