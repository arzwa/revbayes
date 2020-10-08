#ifndef ContinuousEventScaleProposal_H
#define ContinuousEventScaleProposal_H

#include <stddef.h>
#include <string>
#include <iosfwd>

#include "Proposal.h"

namespace RevBayesCore {
class CharacterEventContinuous;
class ConditionedBirthDeathShiftProcessContinuous;
class DagNode;
class Tree;
template <class variableType> class StochasticNode;
    
    /**
     * The birth-death proposal for events along a tree.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team
     * @since 2009-09-08, version 1.0
     *
     */
    class ContinuousEventScaleProposal : public Proposal {
        
    public:
        ContinuousEventScaleProposal( StochasticNode<Tree> *n, double l );                                                                //!<  constructor
        
        // Basic utility functions
        void                                            cleanProposal(void);                                                                //!< Clean up proposal
        ContinuousEventScaleProposal*                   clone(void) const;                                                                  //!< Clone object
        double                                          doProposal(void);                                                                   //!< Perform proposal
        const std::string&                              getProposalName(void) const;                                                        //!< Get the name of the proposal for summary printing
        double                                          getProposalTuningParameter(void) const;
        void                                            printParameterSummary(std::ostream &o, bool name_only) const;                                       //!< Print the parameter summary
        void                                            prepareProposal(void);                                                              //!< Prepare the proposal
        void                                            setProposalTuningParameter(double tp);
        void                                            tune(double r);                                                                     //!< Tune the proposal to achieve a better acceptance/rejection ratio
        void                                            undoProposal(void);                                                                 //!< Reject the proposal
        
    protected:
        
        void                                            swapNodeInternal(DagNode *oldN, DagNode *newN);                                     //!< Swap the DAG nodes on which the Proposal is working on
        
    private:
        // parameters
        
        StochasticNode<Tree>*                           variable;                                                                           //!< The variable the Proposal is working on
        ConditionedBirthDeathShiftProcessContinuous*    distribution;

        double                                          lambda;
        
        CharacterEventContinuous*                       stored_value;                                                                        //!< The stored value of the Proposal used for rejections.
        double                                          stored_rate;                                                                              //!< The value we propose.
        size_t                                          stored_index;                                                                              //!< The value we propose.
        bool                                            failed;

};
    
}

#endif


