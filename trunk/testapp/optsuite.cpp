#include "optsuite.h"
#include <random.hpp>  
#include <iostream>
#include <fstream>
#include "gnuplot.h"

#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

const char* obj_fun_token  = "%OBJECTIVE_FUNCTION%";
const char* swarm_token    = "%SWARM%";
const char* range_token    = "%RANGE%";
const char* swarm_filename = "swarm.dat";

optimization_suite::optimization_suite() 
  : particle(2, Evaluator), algorithm(0)
{
  particle.Initializer(Initializer);
  parser.DefineVar("x", &x);
  parser.DefineVar("y", &y);
}

optimization_suite::~optimization_suite() 
{ 
  if (algorithm) delete algorithm; 
}

void optimization_suite::load_from_file(const std::string& filename_)
{
  using boost::property_tree::ptree;
  ptree pt;
  read_xml(filename_, pt);
  minx = pt.get<double>("optimization.range.minx");
  maxx = pt.get<double>("optimization.range.maxx");
  miny = pt.get<double>("optimization.range.miny");
  maxy = pt.get<double>("optimization.range.maxy");
  dump = pt.get<bool>("optimization.options.dump");
  dump_file = pt.get<std::string>("optimization.options.dump_file");
  std::string range = (boost::format("[%f:%f][%f:%f]") % minx % maxx % miny %maxy).str();
  objective_function = pt.get<std::string>("optimization.objective_function");
  parser.SetExpr(objective_function);
  replace_tokens(objective_function, "^", "**");
  swarm_size = pt.get<int>("optimization.swarm_size");
  iterations = pt.get<int>("optimization.iterations");

  BOOST_FOREACH(ptree::value_type &v, pt.get_child("optimization.parameters")) {
    algorithm->SetParameter(v.first.data(), v.second.data());    
  }
  algorithm->UpdateParameters();
  algorithm->Initialize();

  init_command = pt.get<std::string>("optimization.plot.init_command");
  plot_command = pt.get<std::string>("optimization.plot.plot_command");
  replace_tokens(init_command, range_token, range);
  replace_tokens(init_command, obj_fun_token, objective_function);
  replace_tokens(init_command, swarm_token, swarm_filename);
  replace_tokens(plot_command, range_token, range);
  replace_tokens(plot_command, obj_fun_token, objective_function);
  replace_tokens(plot_command, swarm_token, swarm_filename);
  BOOST_FOREACH(ptree::value_type &def, pt.get_child("optimization.plot.definition")) {
    plot << def.second.data();
  }
}

void optimization_suite::optimize()
{
  algorithm->Optimize();                                                                                                                     
}  
  
void optimization_suite::step(int count_, bool silent_)
{
  for (int i = 0; i < count_ && !algorithm->Done(); ++i) algorithm->Step();
  if (!silent_) std::cout << "\nIteration " << algorithm->Iteration() << " swarm:" << std::endl  << *algorithm << std::endl;
  std::ofstream ofs(swarm_filename);
  ofs << *algorithm;
  ofs.flush();
  plot << plot_command;
  if (dump) {
    std::ofstream ofs((boost::format(dump_file) % algorithm->Iteration()).str().c_str());
    ofs << *algorithm;
    ofs.flush();
  }
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
  return algorithm != 0; 
}
  
optimization_suite& optimization_suite::getInstance()
{
  static optimization_suite instance;
  return instance;
}

void optimization_suite::replace_tokens(std::string& cmd_, const std::string& token_, const std::string& value_)
{
  int x = 0;
  while(x = cmd_.find(token_), x != std::string::npos) {
    cmd_.erase(x, token_.length());
		cmd_.insert(x, value_);
  }
}

void optimization_suite::show_result() const
{
  std::cout << "Number of iterations: " << algorithm->Iteration() << std::endl;
  std::cout << "Optimized swarm: " << std::endl << *algorithm << std::endl;
}
