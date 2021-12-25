#ifndef CT_GRAPH_UTILS_HPP_
#define CT_GRAPH_UTILS_HPP_

class CtGraph;
class CtAdd;
class CtPtAdd;
class CtInput;
class CtPtMul;
class CtRotate;
class CtMul;
class CtOp;

CtInput* ct_input(CtGraph* ct_graph);
CtAdd* ct_add(CtGraph* ct_graph, CtOp* parent0, CtOp* parent1);
CtMul* ct_mul(CtGraph* ct_graph, CtOp* parent0, CtOp* parent1);
CtPtAdd* ct_pt_add(CtGraph* ct_graph, CtOp* parent);
CtPtMul* ct_pt_mul(CtGraph* ct_graph, CtOp* parent);
CtRotate* ct_rotate(CtGraph* ct_graph, CtOp* parent);

#endif  // CT_GRAPH_UTILS_HPP_
