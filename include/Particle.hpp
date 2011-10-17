/**
 * The following code declares class Particle,
 * which has some Position and Velocity in the
 * search space.
 * Instances of Position and Velocity have to
 * define operations:
 *  1° substraction(Position, Position) -> Velocity
 *  2° multiplication(double, Velocity) -> Velocity
 *  3° addition(Velocity, Velocity)     -> Velocity
 *  4° addition(Position, Velocity)     -> Position (move Particle)
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
#ifndef PSOLIB_PARTICLE_HPP
#define PSOLIB_PARTICLE_HPP

#include <string>

namespace psolib {

  class Velocity
  {
    public:
      virtual ~Velocity() = 0;
      Velocity& operator=(const Velocity&);
      virtual Velocity* Clone() const = 0;
      virtual void Copy(const Velocity&) = 0;
      virtual void Initialize() {}
    public:
      /**
       * this metod defines operation °2 described above
       * which is a multiplication of Velocity by a real number
       *
       * @param double multiplier
       * @return Velocity (reference) multiplied
       */
      virtual Velocity& operator*=(double) = 0;
      /**
       * this metod defines operation °3 described above
       * which is a addiction of two Velocities
       *
       * @param Velocity (const reference)
       * @return Velocity (reference)
       */
       virtual Velocity& operator+=(const Velocity&) = 0;
  };

  class Position
  {
    public:
      virtual ~Position() = 0;
      Position& operator=(const Position&);
      virtual Position* Clone() const = 0;
      virtual void Copy(const Position&) = 0;
      virtual void Initialize() {}
    public:
      /**
       * this metod defines operation °4 described above
       * which is a move of the position by a Velocity
       * in search space
       *
       * @param Velocity (const reference)
       * @return Position (reference) moved
       */
      virtual Position& operator+=(const Velocity&) = 0;
  };

  class Algorithm;
  class Particle
  {
    public:
      typedef void (*Initializer_t)(Particle&);
      typedef double (*Evaluator_t)(Position&);
    protected:
      Particle() {}
    public:
      //virtual ~Particle() = 0;
      Particle(Position*, Velocity*);

      Particle(const Particle&);
      Particle& operator=(const Particle&);
      virtual void Copy(const Particle&);
      virtual Particle* Clone() const = 0;
      /**
       * creates concrete Position
       * pure virtual
       * @note returned pointer have to be deleted!
       * @return Position (pointer)
       */
      virtual Position* CreatePosition() = 0;
      /**
       * creates concrete Velocity
       * pure virtual
       * @note returned pointer have to be deleted!
       * @return Velocity (pointer)
       */
      virtual Velocity* CreateVelocity() = 0;
    public:
      /**
       * this metod defines operation °1 described above
       * which is a substraction of two Volocities
       * 
       * @note returned pointer have to be deleted!
       *
       * @param Position (const reference)
       * @param Position (const reference)
       * @return Velocity (pointer)
       */
      virtual Velocity* SubPos(const Position&, const Position&) = 0;

      const Position& GetPosition() const { return *position; }
      Position& GetPosition() { return *position; }

      void SetPosition(const Position& position_) { *position = position_; }
      const Position& GetBestPosition() const { return *best; }

      Velocity& GetVelocity() { return *velocity; }
    public:
      double Evaluate(bool flag_ = false);
      Evaluator_t Evaluator() const { return eval; }
      Evaluator_t Evaluator(Evaluator_t f_) { evaluated = false; return(eval=f_); }

      void Initialize() { evaluated = false; neval = 0; (*init)(*this); delete best; best = position->Clone(); }
      Initializer_t Initializer() const { return init; }
      Initializer_t Initializer(Initializer_t f_) { return (init = f_); } 

      int Nevals() const { return neval; }
      double Score() const { return score; }
      double Score() { Evaluate(); return score; }
      double Score(double s_) { evaluated = true; last_score = score;  score = s_; }
      virtual const Particle& UpdateBest();
      virtual std::string ToString() const { return ""; }
    protected:
      Position* position;
      Position* best;
      Velocity* velocity;

      Initializer_t init;
      Evaluator_t   eval;

      double score;			    //!< value returned by the objective function
      double last_score;
      bool evaluated;		    //!< has this particle been evaluated?
      size_t neval;		      //!< how many evaluations since initialization?

      friend std::ostream& operator<<(std::ostream&, const Particle&);
  };
  
  std::ostream& operator<<(std::ostream& os_, const Particle& p_);

} /* namespace psolib */

#endif /*PSO_PARTICLE_HPP */
