/**
 * Test application for PSOlib programming library
 *
 * See <WEBSITE> for documentation.
 *
 * @author Copyright &copy 2011 Przemys³aw Olejniczak.
 * @version <VERSION>
 * @date <DATE>
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 */
#include <iostream>
#include <iomanip>
#include "optsuite.h"
#include <PSO.hpp>

using namespace std;

template <class T>
bool read_value(T& value_, const std::string& prompt_)
{
  std::cout << prompt_ << " (" << value_ << ") : ";
  std::string line;
  std::getline(cin, line);
  if (line.empty()) return false;
  if (line == "q" || line == "Q") return true;
  try {
    value_ = boost::lexical_cast<T>(line);
  }
  catch (...) {}
  return false;
}

int main(int argc, char* argv[])
{
  std::string filename;
  if (argc == 2) {
    filename = argv[1];
  }
  else {
    std::cout << "Type configuration file name for optimization:";
    std::cin >> filename;
    std::cin.ignore(256, '\n');
  }

  optimization_suite& opti = optimization_suite::getInstance();
  opti.create_algorithm<psolib::PSO>();  
  opti.load_from_file(filename);

  while (!opti.done()) {
    static int step_count = 1;
    if (read_value<int>(step_count, "Get steps count")) break;;
    opti.step(step_count);
  }
  opti.show_result();
  std::cout << "Press any key to exit." << std::endl;
  std::cin.get();
  return 0;
}

