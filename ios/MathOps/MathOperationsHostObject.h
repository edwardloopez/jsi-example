#ifndef MathOperationsHostObject_h
#define MathOperationsHostObject_h

#include <jsi/jsi.h>

namespace facebook {
namespace jsi {
class Runtime;
} // namespace jsi
} // namespace facebook

void installMathOperations(facebook::jsi::Runtime& runtime);

#endif /* MathOperationsHostObject_h */
