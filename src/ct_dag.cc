#include "include/ct_dag.h"

#include <memory>
#include <vector>

#include "include/add_cc.h"
#include "include/add_cp.h"
#include "include/add_cs.h"
#include "include/ct_input.h"
#include "include/mul_cc.h"
#include "include/mul_cp.h"
#include "include/mul_cs.h"
#include "include/rotate_c.h"

namespace janncy {

namespace ct_dag {

const CtOp& CreateInput(CtDag& ct_dag) {
  return ct_dag.AddNode(std::make_unique<CtInput>(), {});
}

const CtOp& CreateAddCC(CtDag& ct_dag, const CtOp& parent_1,
                        const CtOp& parent_2) {
  return ct_dag.AddNode(std::make_unique<AddCC>(), {&parent_1, &parent_2});
}

const CtOp& CreateAddCP(CtDag& ct_dag, const CtOp& parent) {
  return ct_dag.AddNode(std::make_unique<AddCP>(), {&parent});
}

const CtOp& CreateAddCS(CtDag& ct_dag, const CtOp& parent) {
  return ct_dag.AddNode(std::make_unique<AddCS>(), {&parent});
}

const CtOp& CreateMulCC(CtDag& ct_dag, const CtOp& parent_1,
                        const CtOp& parent_2) {
  return ct_dag.AddNode(std::make_unique<MulCC>(), {&parent_1, &parent_2});
}

const CtOp& CreateMulCP(CtDag& ct_dag, const CtOp& parent) {
  return ct_dag.AddNode(std::make_unique<MulCP>(), {&parent});
}

const CtOp& CreateMulCS(CtDag& ct_dag, const CtOp& parent) {
  return ct_dag.AddNode(std::make_unique<MulCS>(), {&parent});
}

const CtOp& CreateRotateC(CtDag& ct_dag, const CtOp& parent) {
  return ct_dag.AddNode(std::make_unique<RotateC>(), {&parent});
}

}  // namespace ct_dag

}  // namespace janncy
