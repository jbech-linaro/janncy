#include "include/Input.hpp"

Input::Input(Tensor input_tensor)
    : FlowNode({nullptr}, input_tensor) {}

