//
// Created by dl11 on 3/12/23.
//

#include "tracing.h"

void tracing::trace(const char *message) {
#if DEBUG
  std::cout << message << std::endl;
#endif
}

void tracing::debug(const char *message) {
#if DEBUG
  std::cout << "[DEBUG] ";
  trace(message);
#endif
}

void tracing::error(const char *message) {
#if DEBUG
  std::cout << "[ERROR] ";
  trace(message);
#endif
}

void tracing::warning(const char *message) {
#if DEBUG
  std::cout << "[WARNING] ";
  trace(message);
#endif
}
