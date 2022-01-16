#include "include/ct_graph.h"

#include <vector>

#include "include/cleartext_evaluator.h"
#include "include/ct_add.h"
#include "include/ct_input.h"
#include "include/ct_mul.h"
#include "include/ct_pt_add.h"
#include "include/ct_pt_mul.h"
#include "include/ct_rotate.h"

namespace janncy {

CtOp* CtGraph::create_input() { return add_node(new CtInput(), {}); }
CtOp* CtGraph::create_add(const CtOp* parent_1, const CtOp* parent_2) {
  return add_node(new CtAdd(), {parent_1, parent_2});
}
CtOp* CtGraph::create_mul(const CtOp* parent_1, const CtOp* parent_2) {
  return add_node(new CtMul(), {parent_1, parent_2});
}
CtOp* CtGraph::create_pt_add(const CtOp* parent) {
  return add_node(new CtPtAdd(), {parent});
}
CtOp* CtGraph::create_pt_mul(const CtOp* parent) {
  return add_node(new CtPtMul(), {parent});
}
CtOp* CtGraph::create_rotate(const CtOp* parent) {
  return add_node(new CtRotate(), {parent});
}

}  // namespace janncy
