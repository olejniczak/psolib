/**
 * The following code declares class RealParticle,
 * with its members RealPosition and RealVelocity
 *
 * See <WEBSITE> for documentation.
 *
 * @author Copyright &copy 2011 Przemys³aw Olejniczak.
 * @version <VERSION>
 * @date <DATE>
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 */
#ifndef PSOLIB_REALPARTICLE_HPP
#define PSOLIB_REALPARTICLE_HPP

#include "Particle.hpp"

namespace psolib {

  //namespace { // anonymous
    class PositionImpl;
    class VelocityImpl;
  //}

  /**
   * @class RealVelocity
   * 
   */
  class RealVelocity : public Velocity
  {
    public:
      explicit RealVelocity(size_t size_ = 0);
      RealVelocity(const RealVelocity&);
      RealVelocity(const Position&, const Position&);
      ~RealVelocity();
      RealVelocity* Clone() const;
      void Copy(const Velocity&);
      void Resize(size_t);
    public:
      const double& operator[](size_t) const;
      double& operator[](size_t);
    public:
      RealVelocity& operator*=(double);
      RealVelocity& operator+=(const Velocity&);
    private:
      VelocityImpl* impl;

      friend class RealPosition;
  };

  /**
   * @class RealPosition
   *
   */
  class RealPosition : public Position
  {
    public:
      explicit RealPosition(size_t size_ = 0);
      RealPosition(const RealPosition&);
      ~RealPosition();
      RealPosition* Clone() const;
      void Copy(const Position&);
      void Resize(size_t);
    public:
      const double& operator[](size_t) const;
      double& operator[](size_t);
    public:
      RealPosition& operator+=(const Velocity&);
    private:
      PositionImpl* impl;

      friend class RealVelocity;
  };

  /**
   * @class RealParticle
   * 
   */
  class RealParticle : public Particle
  {
    public:
      RealParticle(const RealParticle&);
      RealParticle(size_t size_, Particle::Evaluator_t f_ = 0);
      Particle* Clone() const;
      void Copy(const Particle&);
    public:
      RealPosition* CreatePosition();
      RealVelocity* CreateVelocity();
      RealVelocity* SubPos(const Position&, const Position&);
    public:
      RealPosition& GetPos() { return *dynamic_cast<RealPosition*>(position); }
      RealVelocity& GetVel() { return *dynamic_cast<RealVelocity*>(velocity); }
      const RealPosition& GetPos() const { return *dynamic_cast<RealPosition*>(position); }
      const RealVelocity& GetVel() const { return *dynamic_cast<RealVelocity*>(velocity); }
      std::string ToString() const;
  };

} /* namespace psolib */

#endif /* PSOLIB_REALPARTICLE_HPP */
