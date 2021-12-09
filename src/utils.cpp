#include <random>

#include "include/FlowNode.hpp"
#include "include/Tensor.hpp"

int get_output_width(FlowNode* parent, Tensor filter, int stride, bool padded) {
    int result;
    if (!padded) {
        result =
            (parent->output_tensor().shape()[1] - 2 * (filter.shape()[1] / 2)) /
            stride;
    } else {
        result = parent->output_tensor().shape()[1] / stride;
    }
    if (result == 0) {
        result = 1;
    }
    return result;
}

int get_output_height(FlowNode* parent, Tensor filter, int stride,
                      bool padded) {
    int result;
    if (!padded) {
        result =
            (parent->output_tensor().shape()[2] - 2 * (filter.shape()[2] / 2)) /
            stride;
    } else {
        result = parent->output_tensor().shape()[2] / stride;
    }
    if (result == 0) {
        result = 1;
    }
    return result;
}

double get_uniform_random() {
    static std::uniform_real_distribution<double> unif(0, 1);
    static std::default_random_engine re;
    return unif(re);
}
