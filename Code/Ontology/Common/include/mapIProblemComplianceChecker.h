// -----------------------------------------------------------------------
// MatchPoint - DKFZ translational registration framework
//
// Copyright c German Cancer Research Center DKFZ,
// Software development for Integrated Diagnostics and Therapy SIDT.
// ALL RIGHTS RESERVED.
// See mapCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/MatchPoint/copyright.html
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the above copyright notices for more information.
//
//------------------------------------------------------------------------





#ifndef __MAP_I_PROBLEM_COMPLIANCE_CHECKER_H
#define __MAP_I_PROBLEM_COMPLIANCE_CHECKER_H

#include "mapIProblemComplianceDefinition.h"

namespace iro
{
		/** This interface is realized by any class that offer the possibility
    * to be checked if it complies with a certain problem compliance definition
    * (e.g. if a registration path is valid within a certain problem model
    * or only contains transformations of a certain problem statement.*/
    template <typename TProblemStatementTraits>
		class IProblemComplianceChecker
		{
		public:
      typedef IProblemComplianceDefinition<typename TProblemStatementTraits::Type>  ProblemComplianceInterface;

			/** Checks if the instance that implements this interface is in compliance eith the passed problem compliance definition.
       * @return True: the instance complies with the passed definition. False: the instance is not in compliance (e.g. defined
       * for an other problem statement or valid within an other problem model).
       * @pre pProblemCompliance must point to a valid instance.
       * @exception ::iro::exceptions::InvalidArgument: pProblemCompliance is not valid*/
			bool checkProblemCompliance(const ProblemComplianceInterface* pProblemCompliance) const
      {
        if (!pProblemCompliance) throw ::iro::exceptions::InvalidArgument("Cannot check compliance. Invalid proplem compliance pointer");
        return doCheckProblemCompliance(pProblemCompliance);
      };

		protected:

			virtual bool doCheckProblemCompliance(const ProblemComplianceInterface* pProblemCompliance) const = 0;

      virtual ~IProblemComplianceChecker() {};
      IProblemComplianceChecker() {};
		private:
			IProblemComplianceChecker(const IProblemComplianceChecker&); //not implemented by purpose
			IProblemComplianceChecker& operator=(const IProblemComplianceChecker&); //not implemented by purpose
		};
} // end namespace iro

#endif
