/**
 * The following code declares class OptiSuite
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
#ifndef PSOLIB_OPTISUITE_HPP
#define PSOLIB_OPTISUITE_HPP


namespace psolib {
  /*
  template <class Alg, class Part, class InitF, class ObjF, int N>
  class OptiSuite
  {
    public:
      OptiSuite()
        : particle(2, Objective),
          algorithm(particle, N)
      {
        particle.Initializer(Initializer);
      }
    private:
      static void Initializer(psolib::Particle& particle_)
      {
        InitF(*dynamic_cast<P*>(&particle_));
      };
      static void Objective(psolib::Particle& particle_)
      {
        ObjF(*dynamic_cast<P*>(&particle_));
      };
    private:
      Alg  algorithm;
      Part particle;
  };
  */
}

#endif // PSOLIB_OPTISUITE_HPP
