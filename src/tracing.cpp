//
// Created by dl11 on 3/12/23.
//

#include "tracing.h"

void tracing::trace(const char *message) {
#if DEBUG
  std::cout << message << std::endl;
#endif
}
