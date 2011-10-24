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
  std::string range = (boost::format("[%f:%f][%f:%f]") % minx % maxx % miny %maxy).str();
  objective_function = pt.get<std::string>("optimization.objective_function");
  parser.SetExpr(objective_function);
  replace_tokens(objective_function, "^", "**");
  swarm_size = pt.get<int>("optimization.swarm_size");
  iterations = pt.get<int>("optimization.iterations");

  algorithm->Initialize();

  /*
  BOOST_FOREACH(ptree::value_type &v,
          pt.get_child("optimization.parameters"))
      m_modules.insert(v.second.data());
  */
  plots.clear();
  plots.reserve(pt.get_child("optimization.plots").size());
  BOOST_FOREACH(ptree::value_type &pl, pt.get_child("optimization.plots")) {
    std::string init_command = pl.second.get_child("init_command").data();
    std::string plot_command = pl.second.get_child("plot_command").data();
    replace_tokens(init_command, range_token, range);
    replace_tokens(init_command, obj_fun_token, objective_function);
    replace_tokens(init_command, swarm_token, swarm_filename);
    replace_tokens(plot_command, range_token, range);
    replace_tokens(plot_command, obj_fun_token, objective_function);
    replace_tokens(plot_command, swarm_token, swarm_filename);
    plots.push_back(pplot(new gnuplot(plot_command)));
    BOOST_FOREACH(ptree::value_type &def, pl.second.get_child("definition")) {
      *plots.back() << def.second.data();
    }
  }
}

void optimization_suite::optimize()
{
  algorithm->Optimize();                                                                                                                     
  std::cout << "Optimized swarm:" << std::endl  << *algorithm << std::endl;                          
}  
  
void optimization_suite::step(int count_)
{
  for (int i = 0; i < count_ && !algorithm->Done(); ++i) algorithm->Step();
  std::cout << "\nSwarm:" << std::endl  << *algorithm;       
  std::ofstream ofs(swarm_filename);
  ofs << *algorithm;
  ofs.flush();
  plots.back()->plot();
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
