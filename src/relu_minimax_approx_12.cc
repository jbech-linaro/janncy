#include <vector>

#include "include/ct_dag.h"

namespace janncy {

namespace {

using Coefficient = double;

std::vector<std::string> poly0 = {"relu_minimax_approx_12/poly0/coeff00",
                                  "relu_minimax_approx_12/poly0/coeff01",
                                  "relu_minimax_approx_12/poly0/coeff02",
                                  "relu_minimax_approx_12/poly0/coeff03",
                                  "relu_minimax_approx_12/poly0/coeff04",
                                  "relu_minimax_approx_12/poly0/coeff05",
                                  "relu_minimax_approx_12/poly0/coeff06",
                                  "relu_minimax_approx_12/poly0/coeff07"};

std::vector<std::string> poly1 = {"relu_minimax_approx_12/poly1/coeff00",
                                  "relu_minimax_approx_12/poly1/coeff01",
                                  "relu_minimax_approx_12/poly1/coeff02",
                                  "relu_minimax_approx_12/poly1/coeff03",
                                  "relu_minimax_approx_12/poly1/coeff04",
                                  "relu_minimax_approx_12/poly1/coeff05",
                                  "relu_minimax_approx_12/poly1/coeff07",
                                  "relu_minimax_approx_12/poly1/coeff08",
                                  "relu_minimax_approx_12/poly1/coeff09",
                                  "relu_minimax_approx_12/poly1/coeff10",
                                  "relu_minimax_approx_12/poly1/coeff11",
                                  "relu_minimax_approx_12/poly1/coeff12",
                                  "relu_minimax_approx_12/poly1/coeff13",
                                  "relu_minimax_approx_12/poly1/coeff14",
                                  "relu_minimax_approx_12/poly1/coeff15"};

std::vector<std::string> poly2 = {"relu_minimax_approx_12/poly2/coeff00",
                                  "relu_minimax_approx_12/poly2/coeff01",
                                  "relu_minimax_approx_12/poly2/coeff02",
                                  "relu_minimax_approx_12/poly2/coeff03",
                                  "relu_minimax_approx_12/poly2/coeff04",
                                  "relu_minimax_approx_12/poly2/coeff05",
                                  "relu_minimax_approx_12/poly2/coeff06",
                                  "relu_minimax_approx_12/poly2/coeff07",
                                  "relu_minimax_approx_12/poly2/coeff08",
                                  "relu_minimax_approx_12/poly2/coeff09",
                                  "relu_minimax_approx_12/poly2/coeff10",
                                  "relu_minimax_approx_12/poly2/coeff11",
                                  "relu_minimax_approx_12/poly2/coeff12",
                                  "relu_minimax_approx_12/poly2/coeff13",
                                  "relu_minimax_approx_12/poly2/coeff14",
                                  "relu_minimax_approx_12/poly2/coeff15",
                                  "relu_minimax_approx_12/poly2/coeff16",
                                  "relu_minimax_approx_12/poly2/coeff17",
                                  "relu_minimax_approx_12/poly2/coeff18",
                                  "relu_minimax_approx_12/poly2/coeff19",
                                  "relu_minimax_approx_12/poly2/coeff20",
                                  "relu_minimax_approx_12/poly2/coeff21",
                                  "relu_minimax_approx_12/poly2/coeff22",
                                  "relu_minimax_approx_12/poly2/coeff23",
                                  "relu_minimax_approx_12/poly2/coeff24",
                                  "relu_minimax_approx_12/poly2/coeff25",
                                  "relu_minimax_approx_12/poly2/coeff26",
                                  "relu_minimax_approx_12/poly2/coeff27"};

}  // namespace

class ReluMinimaxApprox12 {
 public:
  ReluMinimaxApprox12(){};
  CtDag& ct_dag() const;

 private:
  CtDag ct_dag_;
};

}  // namespace janncy
