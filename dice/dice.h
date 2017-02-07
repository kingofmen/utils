// Functions for simulating die rolls and calculating probabilities.

namespace utils {
namespace dice {

enum RollType { Equal = 0, GtEqual, LtEqual, Greater, Less };

struct DieRoll {
  DieRoll(int d, int f);
  double probability(int target, int mods, RollType t) const;
  int roll() const;

private:
  double baseProb(int target, int mods, RollType t) const;

  int dice;
  int faces;
  DieRoll *next;
};

} // namespace dice
} // namespace utils
