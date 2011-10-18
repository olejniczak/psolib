
#include "RealParticle.hpp"

#include <vector>
#include <cassert>

#include <boost/format.hpp>

namespace psolib {

  //namespace { // anonymous
    // implementation

    template <class T=double, class C=std::vector<T> >
    class Vector
    {
      public:
        explicit Vector(size_t size_)
          : elements(size_)
        {}
      public:
        C elements;
    };

    class PositionImpl : public Vector<>
    {
      public:
        PositionImpl(size_t size_) : Vector(size_) {}
    };

    class VelocityImpl : public Vector<>
    {
      public:
        VelocityImpl(size_t size_) : Vector(size_) {}
    };

  //} // anonymous namespace
  
} // namespace psolib

using namespace psolib;

/**
 * @class RealVelocity
 */
RealVelocity::RealVelocity(size_t size_)
  : impl(new VelocityImpl(size_))
{          
}

RealVelocity::RealVelocity(const RealVelocity& other_)
  : impl(0)
{ 
  Copy(other_);
}

RealVelocity::RealVelocity(const Position& pos1_, const Position& pos2_)
  : impl(new VelocityImpl(dynamic_cast<const RealPosition*>(&pos1_)->impl->elements.size()))
{
  const RealPosition* pos1 = dynamic_cast<const RealPosition*>(&pos1_);
  const RealPosition* pos2 = dynamic_cast<const RealPosition*>(&pos2_);
  assert(pos1->impl->elements.size() == pos2->impl->elements.size());
  for (size_t i = 0; i < pos1->impl->elements.size(); ++i) {
    impl->elements[i] = pos1->impl->elements[i] - pos2->impl->elements[i];
  }
}

RealVelocity::~RealVelocity()
{  
  delete impl;
}
        
RealVelocity* RealVelocity::Clone() const
{
  return new RealVelocity(*this);
}

void RealVelocity::Copy(const Velocity& other_)
{
  if (&other_ == this) return;
  if (impl) delete impl;
  impl = new VelocityImpl(*dynamic_cast<const RealVelocity*>(&other_)->impl);
}
        
void RealVelocity::Resize(size_t size_)
{
  impl->elements.resize(size_);
}

const double& RealVelocity::operator[](size_t i_) const
{
  return impl->elements[i_];
}

double& RealVelocity::operator[](size_t i_)
{
  return impl->elements[i_];
}

RealVelocity& RealVelocity::operator*=(double factor_)
{
  for (size_t i = 0; i < impl->elements.size(); ++i)
    impl->elements[i] *= factor_;
  return *this;
}
        
RealVelocity& RealVelocity::operator+=(const Velocity& velocity_)
{
  const RealVelocity& velocity = *dynamic_cast<const RealVelocity*>(&velocity_);
  for (size_t i = 0; i < impl->elements.size(); ++i)
    impl->elements[i] += velocity.impl->elements[i];
  return *this;
}

/**
 * @class RealPosition
 */
RealPosition::RealPosition(size_t size_)
  : impl(new PositionImpl(size_))
{          
}

RealPosition::RealPosition(const RealPosition& other_)
  : impl(0)
{ 
  Copy(other_);
}

RealPosition::~RealPosition()
{
  delete impl;   
}

RealPosition* RealPosition::Clone() const
{
  return new RealPosition(*this);
}

void RealPosition::Copy(const Position& other_)
{
  if (&other_ == this) return;
  if (impl) delete impl;
  impl = new PositionImpl(*dynamic_cast<const RealPosition*>(&other_)->impl);
}
        
void RealPosition::Resize(size_t size_)
{
  impl->elements.resize(size_);
}

const double& RealPosition::operator[](size_t i_) const
{
  return impl->elements[i_];
}

double& RealPosition::operator[](size_t i_)
{
  return impl->elements[i_];
}

RealPosition& RealPosition::operator+=(const Velocity& velocity_)
{
  const RealVelocity& velocity = *dynamic_cast<const RealVelocity*>(&velocity_);
  for (size_t i = 0; i < impl->elements.size(); ++i)
    impl->elements[i] += velocity.impl->elements[i];
  return *this;
}

/**
 * @class RealParticle
 */
RealParticle::RealParticle(size_t size_, Particle::Evaluator_t f_)
  : Particle(CreatePosition(), CreateVelocity())    
{
  dynamic_cast<RealPosition*>(position)->Resize(size_);
  dynamic_cast<RealVelocity*>(velocity)->Resize(size_);
  best = position->Clone();
  Evaluator(f_);
}

RealParticle::RealParticle(const RealParticle& other_)
  : Particle()    
{
  RealParticle::Copy(other_);
}

Particle* RealParticle::Clone() const
{
  return new RealParticle(*this);
}

void RealParticle::Copy(const Particle& other_)
{
  Particle::Copy(other_);
}

RealPosition* RealParticle::CreatePosition()
{
  return new RealPosition();
}
      
RealVelocity* RealParticle::CreateVelocity()
{
  return new RealVelocity();
}

RealVelocity* RealParticle::SubPos(const Position& pos1_, const Position& pos2_)
{
  return new RealVelocity(pos1_, pos2_);
}

std::string RealParticle::ToString() const
{
  return (boost::format("%5.3f\t%5.3f\t%5.3f\t%5.3f\t%5.3f\t%5.3f")
                        % (GetPos()[0] - GetVel()[0]) 
                        % (GetPos()[1] - GetVel()[1]) 
                        % (last_score)

                        % GetVel()[0] 
                        % GetVel()[1] 
                        % (Score()-last_score)
                       ).str();
}