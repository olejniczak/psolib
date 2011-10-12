
#include "random.hpp"

#include <ctime>
#include <boost/random.hpp>

namespace psolib {

  namespace {
  
    boost::mt19937 seed(static_cast<unsigned int>(std::time(0)));

    template<class T>
    struct randgen {
        typedef T type;
        randgen(typename T::input_type const & min_,
                typename T::input_type const & max_)
          : gm(min_, max_),
            vg(seed, gm) 
        {}
        typename T::result_type operator()() 
        { 
          return vg();	
        }
      private:
        T gm;
        boost::variate_generator<boost::mt19937&, T> vg;
    };

  }

  int RandomInt(int min_, int max_)
  {
    randgen<boost::uniform_int<> > rg(min_, max_);
    return rg();
  }

  double RandomReal(double min_, double max_)
  {
    randgen<boost::uniform_real<> > rg(min_, max_);
    double r = rg();
    return r;
  }

  void Seed(int seed_)
  {
    seed.seed(seed_);
  }
}