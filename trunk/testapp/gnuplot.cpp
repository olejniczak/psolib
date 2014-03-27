#include "gnuplot.h"

#if defined(_WIN32) || defined(_WIN64)
  #define popen _popen
  #define pclose _pclose
#endif

gnuplot::gnuplot()
{
#if defined(_WIN32) || defined(_WIN64)
  pipe = popen("gnuplot -p > NULL 2>&1", "w");
#else
  pipe = popen("gnuplot -p", "w");
  command("set term x11");
#endif
}

gnuplot::~gnuplot()
{
  command("exit");
  pclose(pipe);
}

void gnuplot::command(const std::string& cmd_)
{
  fprintf(pipe, (cmd_ + "\n").c_str());
  fflush(pipe);
}

gnuplot& gnuplot::operator << (const std::string& cmd_)
{
  command(cmd_);
  return *this;
}
