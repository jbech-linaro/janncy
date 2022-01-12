#include "include/ct_graph_utils.hpp"

#include "include/CtAdd.hpp"
#include "include/CtGraph.hpp"
#include "include/CtInput.hpp"
#include "include/CtMul.hpp"
#include "include/CtOp.hpp"
#include "include/CtPtAdd.hpp"
#include "include/CtPtMul.hpp"
#include "include/CtRotate.hpp"

namespace janncy {

CtInput* ct_input(CtGraph* ct_graph) {
    auto node = new CtInput();
    ct_graph->add_node(node, {});
    return node;
}

CtAdd* ct_add(CtGraph* ct_graph, CtOp* parent0, CtOp* parent1) {
    auto result = new CtAdd();
    ct_graph->add_node(result, {parent0, parent1});
    return result;
}

CtMul* ct_mul(CtGraph* ct_graph, CtOp* parent0, CtOp* parent1) {
    auto result = new CtMul();
    ct_graph->add_node(result, {parent0, parent1});
    return result;
}

CtPtAdd* ct_pt_add(CtGraph* ct_graph, CtOp* parent) {
    auto result = new CtPtAdd();
    ct_graph->add_node(result, {parent});
    return result;
}

CtPtMul* ct_pt_mul(CtGraph* ct_graph, CtOp* parent) {
    auto result = new CtPtMul();
    ct_graph->add_node(result, {parent});
    return result;
}

CtRotate* ct_rotate(CtGraph* ct_graph, CtOp* parent) {
    auto result = new CtRotate();
    ct_graph->add_node(result, {parent});
    return result;
}

}  // namespace janncy
