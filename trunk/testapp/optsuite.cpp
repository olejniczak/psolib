#include "optsuite.h"
#include <random.hpp>  
#include <iostream>
#include <fstream>
#include <boost/format.hpp>
#include "gnuplot.h"

optimization_suite::optimization_suite() 
  : real_particle(2, Evaluator), pso(0)
{
  real_particle.Initializer(Initializer);
  parser.DefineVar("x", &x);
  parser.DefineVar("y", &y);
}

optimization_suite::~optimization_suite() 
{ 
  if (pso) delete pso; 
}

void optimization_suite::init(double minx_, double maxx_, double miny_, double maxy_, const std::string obj_fun_, int count_)
{
  minx = minx_;
  maxx = maxx_;
  miny = miny_;
  maxy = maxy_;
  if (pso) delete pso;
  pso = new psolib::PSO(real_particle, count_);
  parser.SetExpr(obj_fun_);  
  pso->Initialize();                                                                                                                   
  std::cout << "Initial swarm:" << std::endl << *pso;
  plot << "set logscale z 10"
       << "set isosamples 50, 50"
       << "set contour base"
       << "unset clabel"
       << "set xlabel \"x\" "
       << "set ylabel \"y\""
       << "!mkdir frames"
       << "!cd frames"
       //<< "counter = 0"
       << "set term jpeg size 1280,720 font 'Verdana,12'";

  std::ofstream ofs("swarm");
  ofs << *pso;
  ofs.flush();
  plot << "set output 'frames\\frame_000.jpg'"
       << "splot [-19:19] [-19:19] (x**2+y-11)**2 + (x+y**2-7)**2, 'swarm' using 1:2:6 with points";
  plot.flush();
}
  
void optimization_suite::optimize()
{
  pso->Optimize();                                                                                                                     
  std::cout << "Optimized swarm:" << std::endl  << *pso << std::endl;                          
}  
  
void optimization_suite::step(int count_)
{
  for (int i = 0; i < count_ && !pso->Done(); ++i) pso->Step();
  std::cout << "\nSwarm:" << std::endl  << *pso;       
  std::ofstream ofs("swarm");
  ofs << *pso;
  ofs.flush();

  static int counter = 1;

  plot << (boost::format("set output 'frames\\frame_%03d.jpg'") % counter++).str()
       << "splot [-19:19] [-19:19] (x**2+y-11)**2 + (x+y**2-7)**2, 'swarm' with vectors";
  plot.flush();
}
  
void optimization_suite::Initializer(psolib::Particle& particle_)                                                                                
{                                                                                                                                   
  optimization_suite& opt = optimization_suite::getInstance();
  psolib::RealParticle& part = *dynamic_cast<psolib::RealParticle*>(&particle_);                                                    
  part.GetPos()[0] = psolib::RandomReal(opt.minx, opt.maxx);                                                                                
  part.GetPos()[1] = psolib::RandomReal(opt.miny, opt.maxy);                                                                                  
  part.GetVel()[0] = 0;                                                                                                             
  part.GetVel()[1] = 0;                                                                                                             
};               

double optimization_suite::Evaluator(psolib::Position& position_)
{
  psolib::RealPosition& pos = *dynamic_cast<psolib::RealPosition*>(&position_);
  optimization_suite& opt = optimization_suite::getInstance();
  opt.x = pos[0];
  opt.y = pos[1];
  return opt.parser.Eval();
}     
  
bool optimization_suite::ready() 
{ 
  return pso != 0; 
}
  
optimization_suite& optimization_suite::getInstance()
{
  static optimization_suite instance;
  return instance;
}

