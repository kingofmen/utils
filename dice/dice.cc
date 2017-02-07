#include "dice.h"

#include <cstdlib>

namespace utils {
namespace dice {

DieRoll::DieRoll(int d, int f) : dice(d), faces(f), next(0) {
  if (dice > 1)
    next = new DieRoll(dice - 1, f);
}

double DieRoll::probability(int target, int mods, RollType t) const {
  if (1 == dice)
    return baseProb(target, mods, t);
  target -= mods;
  double ret = 0;
  for (int i = 1; i <= faces; ++i) {
    ret += next->probability(target - i, 0, t);
  }
  ret /= faces;
  return ret;
}

int DieRoll::roll() const {
  int ret = dice;
  for (int i = 0; i < dice; ++i) {
    ret += (rand() % faces);
  }
  return ret;
}

double DieRoll::baseProb(int target, int mods, RollType t) const {
  // Returns probability of roll <operator> target on one die.

  target -= mods;
  double numTargets = 1.0;
  switch (t) {
  case Equal:
    if (target < 1)
      return 0;
    if (target > faces)
      return 0;
    return (numTargets / faces);

  case GtEqual:
    if (target <= 1)
      return 1;
    if (target > faces)
      return 0;
    numTargets = 1 + faces - target;
    return numTargets / faces;

  case LtEqual:
    if (target >= faces)
      return 1;
    if (target <= 0)
      return 0;
    numTargets = target;
    return numTargets / faces;

  case Greater:
    if (target < 1)
      return 1;
    if (target >= faces)
      return 0;
    numTargets = faces - target;
    return numTargets / faces;

  case Less:
    if (target > faces)
      return 1;
    if (target < 1)
      return 0;
    numTargets = target - 1;
    return numTargets / faces;

  default:
    break;
  }
  return 0;
}

} // namespace dice
} // namespace utils
