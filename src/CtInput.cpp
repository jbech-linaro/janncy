#include "include/CtInput.hpp"

#include "include/CtGraphVisitor.hpp"

void CtInput::visit(CtGraphVisitor* visitor) { return visitor->visit(this); }
