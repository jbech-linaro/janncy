#ifndef CTOP_HPP_
#define CTOP_HPP_

#include "Node.hpp"

#include <string>
#include <vector>

class CtOp : public Node<CtOp> {
  public:
    CtOp(std::vector<CtOp*> parents) : Node(parents){};
    virtual std::string type_str() const = 0;
    std::string str() const;
};

#endif  // CTOP_HPP_
