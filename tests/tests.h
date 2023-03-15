//
// Created by dl11 on 3/12/23.
//

#ifndef MAINDIR_SRC_TESTS_H_
#define MAINDIR_SRC_TESTS_H_

#include <vector>
#include <iostream>
#include "../src/nasch.h"

namespace testing {

static std::string debugOutput;
void debug(const std::stringstream &s);

class TestEnvironment {
 public:
  TestEnvironment() = default;
  std::string runLine(const std::string &line);


 private:
  std::vector<NaSch::Route> routes;
  long currentRoute = -1;
};

class TestFramework {
 public:
    TestFramework() = default;

    void loadTestFiles(const std::string &path);
    void runTests();

 protected:
    static void runTest(const std::string &path);

 private:
  std::vector<std::string> filesPaths;
};

static TestFramework testFramework = TestFramework();

void test1();
void test1Bis();
void test1Ter();

} // testing

#endif //MAINDIR_SRC_TESTS_H_
