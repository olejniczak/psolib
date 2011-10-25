#include "Algorithm.hpp"
#include "Particle.hpp"
#include "Swarm.hpp"

#include <algorithm>
#include <numeric>

using namespace psolib;

class Comparator
{
  public:
    Comparator(MinMax mm_) : mm(mm_) {}
    void MiniMaxi(MinMax mm_) { mm = mm_; }
    bool operator() (PParticle a, PParticle b)
    { 
      return mm == Minimize ? 
              a->Score() < b->Score() : 
              a->Score() > b->Score(); 
    }
  private:
    MinMax mm;
};

Swarm::Swarm(const Particle& particle_, size_t size_, const MinMax& mm_)
  : particle(&particle_), minmax(mm_)
{
  for (size_t i = 0; i < size_; ++i) {
    particles.push_back(PParticle(particle->Clone()));
  }
}

Swarm::Swarm(const Swarm& other_)
  : minmax(other_.minmax)
{
  particles.clear();
  for (size_t i = 0; i < other_.size(); ++i) {
    particles.push_back(PParticle(other_.particles[i]->Clone()));
  }
}

Swarm& Swarm::operator=(const Swarm& other_)
{
  if (&other_ != this) {
    minmax = other_.minmax;
    particles.clear();
    for (size_t i = 0; i < other_.size(); ++i) {
      particles.push_back(PParticle(other_.particles[i]->Clone()));
    }
  }
  return *this;
}

Swarm::~Swarm()
{
}

size_t Swarm::size() const
{
  return particles.size();
}

Particle& Swarm::operator[](size_t i_)
{
  return *particles[i_];
}

const Particle& Swarm::operator[](size_t i_) const
{
  return *particles[i_];
}

const Particle& Swarm::GetBest() const
{
  return *particles.front().get();
}

const Particle& Swarm::GetWorst() const
{
  return *particles.back().get();
}

const Particle& Swarm::Sort()
{
  std::sort(particles.begin(), particles.end(), Comparator(minmax));
  return GetBest();
}

void Swarm::Initialize()
{
  for (size_t i = 0; i < size(); ++i) {
    particles[i]->Initialize();
  }
  Evaluate();
}

void Swarm::Evaluate(bool flag_)
{
  for (size_t i = 0; i < size(); ++i) {
    particles[i]->Evaluate(flag_);
  }
  Sort();
}

