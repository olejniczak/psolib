#include <iostream>
#include "optsuite.h"

int main(int argc, char* argv[])
{
  optimization_suite& opti = optimization_suite::getInstance();
  //opti.init(-6, 6, -6, 6, "(x*x+y-11)^2+(x+y*y-7)^2", 20);
  opti.init(-6, 6, -6, 6, "(1-x)^2+100*(y-x^2)^2", 20);
  opti.optimize();
  std::cin.get();
  return 0;
}

