#ifndef OccurrenceBirthDeathProcess_H
#define OccurrenceBirthDeathProcess_H

#include <stddef.h>
#include <iosfwd>
#include <string>
#include <vector>

#include "AbstractBirthDeathProcess.h"
#include "RbException.h"

namespace RevBayesCore {

class Taxon;
class DagNode;
class Tree;
class Clade;

template <class valueType> class TypedDagNode;
template <class valueType> class RbVector;

  /**
     * @file This file contains the declaration of the random variable class for occurrence birth-death process, see Manceau & al. 2020 algorithm (http://dx.doi.org/10.1101/755561).
     *
     * @brief Declaration of the occurrence Birth-Death process class.
     * @return The joint density of trees + population sizes
     */

    class OccurrenceBirthDeathProcess : public AbstractBirthDeathProcess {

    public:
      OccurrenceBirthDeathProcess(                        const TypedDagNode<double> *sa,
                                                          const TypedDagNode<double> *l,
                                                          const TypedDagNode<double> *m,
                                                          const TypedDagNode<double> *p,
                                                          const TypedDagNode<double> *o,
                                                          const TypedDagNode<double> *rho,
                                                          const TypedDagNode<double> *r,
                                                          const TypedDagNode<long> *n,

                                                          const std::string& cdt,
                                                          const std::vector<Taxon> &tn,
                                                          const TypedDagNode< RevBayesCore::RbVector<double> > *O,
                                                          // const std::vector<double> &O,
                                                          bool uo,
                                                          bool mt,
                                                          bool vb,
                                                          TypedDagNode<Tree> *tr);


    virtual                                                     ~OccurrenceBirthDeathProcess(void);
      // Public member functions
      OccurrenceBirthDeathProcess*                        clone(void) const;
      void                                                poolTimes(void) const;


    protected:
      double                                              computeLnProbabilityDivergenceTimes(void) const;                                //!< Compute the log-transformed probability of the current value.
      // Parameter management functions
      void                                                swapParameterInternal(const DagNode *oldP, const DagNode *newP);                //!< Swap a parameter

      // Helper functions
      double                                              computeLnProbabilityTimes(void) const;                                          //!< Compute the log-transformed probability of the current value.
      double                                              lnProbNumTaxa(size_t n, double start, double end, bool MRCA) const { throw RbException("Cannot compute P(nTaxa)."); }
      double                                              lnProbTreeShape(void) const;
      double                                              simulateDivergenceTime(double origin, double present) const;                    //!< Simulate a speciation event.
      double                                              pSurvival(double start, double end) const;                                      //!< Compute the probability of survival of the process (without incomplete taxon sampling).
      double                                              pZero(double t, double c1, double c2) const;
      double                                              lnQ(double t, double c1, double c2) const;
      double                                              pHatZero(double t) const;
      double                                              functionP(double t, double z) const;
      double                                              functionU(double t, double z) const;

      // Members
      const TypedDagNode< double > *                        start_age;                             //!< Start age of the process.
      const TypedDagNode< double > *                        lambda;                                //!< The speciation rate.
      const TypedDagNode< double > *                        mu;                                    //!< The extinction rate.
      const TypedDagNode< double > *                        psi;                                   //!< The sampling probability of a just extinct species.
      const TypedDagNode< double > *                        omega;                                 //!< The occurrence sampling rate.
      const TypedDagNode< double > *                        rho;                                   //!< The sampling probability of extant taxa.
      const TypedDagNode< double > *                        removalPr;                             //!< The removal probability after sampling.
      const TypedDagNode< long > *                          maxHiddenLin;                          //!< The maximal number of hidden lineages.
      const std::string &                                   cond;                                  //!< Condition of the process ("time" or "survival")
      const std::vector<Taxon> &                            taxa;                                  //!< Extinct and extant taxa
      // const std::vector<double> &                           occurrence_ages;                       //!< Vector of occurrence times
      const TypedDagNode< RevBayesCore::RbVector<double> > *occurrence_ages;                       //!< Vector of occurrence times
      const bool                                            useOrigin;                             //!< Start the process at the origin (otherwise root)
      const bool                                            useMt;                                 //!< Forward traversal Mt algorithm (otherwise backward Lt)
      const bool                                            verbose;                               //!< Display warnings and information messages

    };


}

#endif /* defined(OccurrenceBirthDeathProcess_H) */