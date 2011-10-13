#include "Particle.hpp"

#include <memory>
#include <iostream>

using namespace psolib;

std::ostream& operator<<(std::ostream& os_, const Particle& p_)
{
  os_ << p_.ToString() << std::endl;
  return os_;
}

Velocity::~Velocity() {} // virtual destructor

Velocity& Velocity::operator=(const Velocity& other_)
{
  if (&other_ != this) Copy(other_);
  return *this;
}

Position::~Position() {} // virtual destructor

Position& Position::operator=(const Position& other_)
{
  if (&other_ != this) Copy(other_);
  return *this;
}


Particle::Particle(const Particle& other_)
{
  Copy(other_);
}

Particle& Particle::operator=(const Particle& other_)
{
  if (&other_ != this) Copy(other_);
  return *this;
}

void Particle::Copy(const Particle& orig_)
{
  if (&orig_ == this) return;

  position = orig_.position->Clone();
  best = orig_.best->Clone();
  velocity = orig_.velocity->Clone();
  
  init = orig_.init;
  eval = orig_.eval;

  score = orig_.score;
  evaluated = orig_.evaluated;
  neval = orig_.neval;
}

Particle::Particle(Position* position_, Velocity* velocity_)
  : position(position_),
    velocity(velocity_)
{
}

const Particle& Particle::UpdateBest()
{
  if (Score() < (*eval)(*best)) *best = *position;
  return *this;
}

Particle::~Particle() {} // virtual destructor

double Particle::Evaluate(bool flag_)
{
  if(!evaluated || flag_){
    if(eval) { 
      neval++; 
      score = (*eval)(*position); 
    }
    evaluated = true;
  }
  return score; 
}

