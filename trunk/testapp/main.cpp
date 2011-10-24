#include <iostream>
#include <iomanip>
#include "optsuite.h"
#include <PSO.hpp>
#include "plot.h"

#include <windows.h>

using namespace std;

int main(int argc, char* argv[])
{
  optimization_suite& opti = optimization_suite::getInstance();
  opti.create_algorithm<psolib::PSO>();  
  //opti.init(-19, 19, -19, 19, "(x*x+y-11)^2+(x+y*y-7)^2");
  //opti.init(-6, 6, -6, 6, "(1-x)^2+100*(y-x^2)^2", 10);
  opti.load_from_file("test2.xml");

  std::cin.get();
  while (!opti.done()) {
    opti.step(1);
    //std::cin.get();
    ::Sleep(1000);
  }
  std::cin.get();
  return 0;
  /**/
}

