#include <cstdlib>
#include <random>

namespace janncy {

double GetUniformRandom() {
  static std::uniform_real_distribution<double> unif(0, 1);
  static std::default_random_engine re;
  return unif(re);
}

}  // namespace janncy
