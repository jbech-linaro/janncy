#include "include/CtGraph.hpp"

#include "include/CtInput.hpp"

CtInput* CtGraph::input() {
    auto in_node = new CtInput();
    add_node(in_node);
    return in_node;
}
