#include <random>

#include "include/FlowNode.hpp"

namespace janncy {

double get_uniform_random() {
    static std::uniform_real_distribution<double> unif(0, 1);
    static std::default_random_engine re;
    return unif(re);
}

}  // namespace janncy
