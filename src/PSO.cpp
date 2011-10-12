#include "PSO.hpp"
#include "Particle.hpp"
#include "random.hpp"

using namespace psolib;

PSO::PSO(const Particle& particle_, size_t size_, MinMax mm_)
  : Algorithm(particle_, size_, mm_),
    inertia(0.4),
    particle_learn(2),
    swarm_learn(2)
{
  RegisterParameters();
}

PSO::~PSO()
{
}

void PSO::Move(Particle& particle_)
{
  std::auto_ptr<Velocity> pldiff(particle_.SubPos(particle_.GetBestPosition(), particle_.GetPosition()));
  std::auto_ptr<Velocity> pgdiff(particle_.SubPos(swarm.GetBest().GetPosition(), particle_.GetPosition()));

  Velocity& local_diff = *pldiff.get();
  local_diff *= particle_learn;
  local_diff *= RandomReal();

  Velocity& global_diff = *pgdiff.get();
  global_diff *= swarm_learn;
  global_diff *= RandomReal();

  particle_.GetVelocity() *= inertia;
  particle_.GetVelocity() += local_diff;
  particle_.GetVelocity() += global_diff;

  particle_.GetPosition() += particle_.GetVelocity();
  particle_.UpdateBest();
}

void PSO::RegisterParameters()
{
  Algorithm::RegisterParameters();
  params.Add<double>("inertia", inertia);
  params.Add<double>("particle_learn", particle_learn);
  params.Add<double>("particle_learn", swarm_learn);
}

void PSO::UpdateParameters()
{
  Algorithm::UpdateParameters();
  inertia        = params.Get<double>("inertia");
  particle_learn = params.Get<double>("particle_learn");
  swarm_learn    = params.Get<double>("particle_learn");
}

