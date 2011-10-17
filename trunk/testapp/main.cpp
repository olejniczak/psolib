#include <iostream>
#include <iomanip>
#include "optsuite.h"

using namespace std;

int main(int argc, char* argv[])
{
  optimization_suite& opti = optimization_suite::getInstance();
  opti.init(-5, 5, -5, 5, "(x*x+y-11)^2+(x+y*y-7)^2", 20);
  //opti.init(-6, 6, -6, 6, "(1-x)^2+100*(y-x^2)^2", 10);
  while (!opti.done()) {
    opti.step(10);
    std::cin.get();
  }
  std::cin.get();
  return 0;
}

