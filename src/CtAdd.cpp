#include "include/CtAdd.hpp"

#include "include/CtGraphVisitor.hpp"

void CtAdd::visit(CtGraphVisitor* visitor) { return visitor->visit(this); }
