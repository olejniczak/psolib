#include "Algorithm.hpp"
#include "Particle.hpp"

using namespace psolib;

std::ostream& psolib::operator<<(std::ostream& os_, const Algorithm& a_)
{
  for (size_t i = 0; i < a_.swarm.size(); ++i) os_ << a_.swarm[i];
  return os_;
}

bool Algorithm::TerminateUponGeneration(Algorithm& algorithm)
{
  return algorithm.Iteration() >= algorithm.IterationsCount();
}

bool Algorithm::TerminateUponConvergence(Algorithm& algorithm)
{
  if (algorithm.curr_iter < algorithm.conv_count) return false;
  return algorithm.Convergence() < algorithm.conv_diff;
}

Algorithm::Algorithm(const Particle& particle_, size_t size_, MinMax mm_)
  : minimaxi(mm_), swarm_size(size_), swarm(particle_, size_, mm_),
    iter_count(500), curr_iter(0), conv_count(10), conv_diff(0.0001), 
    bests(conv_count, 0), convergence(0),
    terminator(&TerminateUponConvergence)
{
  RegisterParameters();
}

Algorithm::~Algorithm()
{
}

void Algorithm::Initialize()
{
  swarm.Initialize();
  curr_iter = 0;
}

void Algorithm::Optimize()
{
  while(!Done()) Step();
}

void Algorithm::Step()
{
  if (params.Dirty()) UpdateParameters();
  for (size_t i = 0; i < swarm.size(); ++i) {
    Move(swarm[i]);
  }
  swarm.Evaluate(true);
  bests.push_back(swarm.GetBest().Score());
  convergence = std::fabs(bests.front() - bests.back());
  ++curr_iter;
}

void Algorithm::RegisterParameters()
{
  params.Add<int>("swarm_size", iter_count);
  params.Add<int>("iter_count", iter_count);
  params.Add<double>("conv_diff", conv_diff);
  params.Add<int>("conv_count", conv_count);
}

void Algorithm::UpdateParameters()
{
  iter_count = params.Get<int>("iter_count");
  conv_diff  = params.Get<double>("conv_diff");
  conv_count = params.Get<int>("conv_count");
}

bool Algorithm::Done()
{
  return terminator(*this);
}