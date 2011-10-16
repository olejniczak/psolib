#include "gnuplot.h"

#ifdef _WIN32 || _WIN64
  #define popen _popen
  #define pclose _pclose
#endif

gnuplot::gnuplot(const std::string& path_)
{
    pipe = popen((path_ + " -persist").c_str(), "w");
}

gnuplot::~gnuplot()
{
    command("exit");
    pclose(pipe);
}

void gnuplot::command(const std::string& cmd_)
{
    fprintf(pipe, (cmd_ + "\n").c_str());
}

gnuplot& gnuplot::operator << (const std::string& cmd_)
{
    command(cmd_);
    return *this;
}
