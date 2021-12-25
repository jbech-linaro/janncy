#include "include/Flow.hpp"

#include "include/Cipherfier.hpp"
#include "include/FlowNode.hpp"

#include <vector>

CtGraph* Flow::cipherfy() {
    Cipherfier cfv;
    for (auto& node : nodes()) {
        std::cout << "Visiting: " << node->str() << std::endl;
        node->visit(this, &cfv);
    }
    return cfv.ct_graph();
}

