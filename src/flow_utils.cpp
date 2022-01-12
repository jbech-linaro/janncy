#include "include/flow_utils.hpp"

#include <cmath>
#include <numeric>
#include <vector>

#include "include/Flow.hpp"
#include "include/Panic.hpp"
#include "include/utils.hpp"

#include "include/Add.hpp"
#include "include/AveragePool.hpp"
#include "include/BatchNormalization.hpp"
#include "include/ConvLayer.hpp"
#include "include/Flatten.hpp"
#include "include/FullyConnected.hpp"
#include "include/Input.hpp"
#include "include/MaxPool.hpp"
#include "include/ReLU.hpp"

namespace janncy {

Add* add(Flow* flow, std::vector<FlowNode*> parents) {
    if (parents.size() < 2) {
        panic("An add object expects at least two parents!");
    }
    if (!parents[0]) {
        panic("nullptr parent!");
    }
    for (auto parent : parents) {
        if (parents[0]->shape() != parent->shape()) {
            panic("Parents of Add layer do not all have the same shape!",
                  parents[0]->shape(), parent->shape());
        }
    }
    auto shape = parents[0]->shape();
    auto n_add = new Add(shape);
    flow->add_node(n_add, parents);
    return n_add;
}

AveragePool* average_pool(Flow* flow, FlowNode* parent,
                          const std::vector<int>& kernel_shape,
                          const std::vector<int>& stride,
                          const std::vector<int>& padding) {
    if (!parent) {
        panic("nullptr parent!");
    }
    auto input_shape = parent->shape();
    auto shape =
        get_shape_average_pool(input_shape, kernel_shape, stride, padding);
    auto n_average_pool = new AveragePool(shape, kernel_shape, stride, padding);
    flow->add_node(n_average_pool, std::vector<FlowNode*>{parent});
    return n_average_pool;
}

BatchNormalization* batch_normalization(Flow* flow, FlowNode* parent) {
    if (!parent) {
        panic("nullptr parent!");
    }
    auto shape = parent->shape();
    auto n_batch_normalization = new BatchNormalization(shape);
    flow->add_node(n_batch_normalization, {parent});
    return n_batch_normalization;
}

ConvLayer* conv_layer(Flow* flow, FlowNode* parent,
                      const std::vector<int>& kernel_shape,
                      const std::vector<int>& stride,
                      const std::vector<int>& padding) {
    if (!parent) {
        panic("nullptr parent!");
    }
    auto input_shape = parent->shape();
    auto shape =
        get_shape_conv_layer(input_shape, kernel_shape, stride, padding);
    auto n_conv_layer = new ConvLayer(shape, kernel_shape, stride, padding);
    flow->add_node(n_conv_layer, {parent});
    return n_conv_layer;
}

Flatten* flatten(Flow* flow, FlowNode* parent, int axis) {
    if (!parent) {
        panic("nullptr parent!");
    }
    auto input_shape = parent->shape();
    auto shape = get_shape_flatten(input_shape, axis);
    auto n_flatten = new Flatten(shape);
    flow->add_node(n_flatten, {parent});
    return n_flatten;
}

FullyConnected* fully_connected(Flow* flow, FlowNode* parent,
                                const std::vector<int>& kernel_shape) {
    if (kernel_shape.size() != 2) {
        panic("FullyConnected layer expects a two-dimensional kernel!",
              kernel_shape);
    }
    auto input_shape = parent->shape();
    auto shape = get_shape_fully_connected(input_shape, kernel_shape);
    auto n_fully_connected = new FullyConnected(shape);
    flow->add_node(n_fully_connected, {parent});
    return n_fully_connected;
}

Input* input(Flow* flow, const std::vector<int>& shape) {
    auto n_input = new Input(shape);
    flow->add_node(n_input, std::vector<FlowNode*>{});
    return n_input;
}

MaxPool* max_pool(Flow* flow, FlowNode* parent,
                  const std::vector<int>& kernel_shape,
                  const std::vector<int>& stride,
                  const std::vector<int>& padding) {
    if (!parent) {
        panic("nullptr parent!");
    }
    auto input_shape = parent->shape();
    auto shape = get_shape_max_pool(input_shape, kernel_shape, stride, padding);
    auto n_max_pool = new MaxPool(shape, kernel_shape, stride, padding);
    flow->add_node(n_max_pool, {parent});
    return n_max_pool;
}

ReLU* relu(Flow* flow, FlowNode* parent) {
    if (!parent) {
        panic("nullptr parent!");
    }
    auto shape = parent->shape();
    auto n_relu = new ReLU(shape);
    flow->add_node(n_relu, {parent});
    return n_relu;
}

std::vector<int> get_shape_average_pool(const std::vector<int>& input_shape,
                                        const std::vector<int>& kernel_shape,
                                        const std::vector<int>& stride,
                                        const std::vector<int>& padding) {
    std::cout << "input shape: " << input_shape << "\n";
    std::cout << "kernel shape: " << kernel_shape << "\n";
    std::cout << "stride (not a shape!): " << stride << "\n";
    std::cout << "padding (not a shape!): " << padding << "\n";

    int channels = input_shape[0];
    auto effective_kernel_shape = std::vector<int>{channels, channels};
    effective_kernel_shape.insert(effective_kernel_shape.end(),
                                  kernel_shape.begin(), kernel_shape.end());

    auto shape = get_shape_conv_layer(input_shape, effective_kernel_shape,
                                      stride, padding);
    std::cout << "output shape: " << shape << "\n";
    std::cout << std::endl;
    return shape;
}

std::vector<int> get_shape_conv_layer(const std::vector<int>& input_shape,
                                      const std::vector<int>& kernel_shape,
                                      const std::vector<int>& stride,
                                      const std::vector<int>& padding) {
    std::cout << "conv layer" << std::endl;
    std::cout << "input shape: " << input_shape << "\n";
    std::cout << "kernel shape: " << kernel_shape << "\n";
    std::cout << "stride (not a shape!): " << stride << "\n";
    std::cout << "padding (not a shape!): " << padding << "\n";

    // TODO we're assuming symetric padding on both sides of each

    std::vector<int> output_shape(input_shape.size());
    output_shape[0] = kernel_shape[0];  // number of output channels

    // Actual dimensions
    for (unsigned i = 0; i + 1 < input_shape.size(); ++i) {
        // From https://pytorch.org/docs/1.10.1/generated/torch.nn.Conv2d.html
        output_shape[i + 1] =
            (input_shape[i + 1] + 2 * padding[i] - kernel_shape[i + 2]) /
                stride[i] +
            1;
    }
    std::cout << "output shape: " << output_shape << "\n";
    std::cout << std::endl;
    return output_shape;
}

std::vector<int> get_shape_max_pool(const std::vector<int>& input_shape,
                                    const std::vector<int>& kernel_shape,
                                    const std::vector<int>& stride,
                                    const std::vector<int>& padding) {
    std::cout << "MaxPool actually!" << std::endl;
    return get_shape_average_pool(input_shape, kernel_shape, stride, padding);
}

std::vector<int> get_shape_flatten(const std::vector<int>& input_shape,
                                   int axis) {
    assert(axis < input_shape.size());
    auto first_dim =
        std::accumulate(input_shape.begin(), input_shape.begin() + axis - 1, 1,
                        std::multiplies<int>{});
    auto second_dim =
        std::accumulate(input_shape.begin() + axis - 1, input_shape.end(), 1,
                        std::multiplies<int>{});
    std::cout << "flatten shape: " << first_dim << ", " << second_dim
              << std::endl;
    if (first_dim > 1) {
        return std::vector<int>{first_dim, second_dim};
    } else {
        return std::vector<int>{second_dim};
    }
}

std::vector<int> get_shape_fully_connected(
    const std::vector<int>& input_shape, const std::vector<int>& kernel_shape) {
    std::cout << "fully connected kernel: ";
    for (auto dim : kernel_shape) {
        std::cout << dim << ", ";
    }
    std::cout << std::endl;
    if (input_shape.size() != 1) {
        panic("Input to FullyConnected must be one-dimensional!");
    }
    if (kernel_shape.size() != 2) {
        panic("The kernel of FullyConnected must be two-dimensional!");
    }
    return std::vector<int>{kernel_shape[0]};
}

}  // namespace janncy
