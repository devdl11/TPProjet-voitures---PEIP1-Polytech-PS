//
// Created by dl11 on 3/12/23.
//

#ifndef MAINDIR_SRC_TRACING_H_
#define MAINDIR_SRC_TRACING_H_

#define DEBUG true

#include <iostream>

namespace tracing {
  void trace(const char *message);
  void error(const char *message);
  void warning(const char *message);
}

#endif //MAINDIR_SRC_TRACING_H_
