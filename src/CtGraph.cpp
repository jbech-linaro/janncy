#include "include/CtGraph.hpp"

#include <vector>

#include "include/CleartextEvaluator.hpp"
#include "include/CtAdd.hpp"
#include "include/CtInput.hpp"
#include "include/CtMul.hpp"
#include "include/CtPtAdd.hpp"
#include "include/CtPtMul.hpp"
#include "include/CtRotate.hpp"

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
