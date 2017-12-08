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





#ifndef __MAP_I_PROBLEM_COMPLIANCE_DEFINITION_H
#define __MAP_I_PROBLEM_COMPLIANCE_DEFINITION_H

#include "mapOntologyExceptions.h"

namespace iro
{
		/** This interface is realized by any class that defines a
    * problem compliance and offer the possibility to check a statement
    * if it is compliant to this definition.*/
    template <typename TProblemStatement>
		class IProblemComplianceDefinition
		{
		public:
      typedef TProblemStatement  ProblemStatementType;

			/** Checks if the passed problem statement is compliant.
       * @pre pProblem must point to a valid instance.
       * @exception ::iro::exceptions::InvalidArgument: pProblem is not valid*/
			bool checkComplianceOfStatement(const ProblemStatementType* pProblem) const
      {
        if (!pProblem) throw ::iro::exceptions::InvalidArgument("Cannot check compliance. Invalid proplem statement pointer");
        return doCheckComplianceOfStatement(pProblem);
      };

		protected:
			virtual bool doCheckComplianceOfStatement(const ProblemStatementType* pProblem) const = 0;

      virtual ~IProblemComplianceDefinition() {};
      IProblemComplianceDefinition() {};
		private:
			IProblemComplianceDefinition(const IProblemComplianceDefinition&); //not implemented by purpose
			IProblemComplianceDefinition& operator=(const IProblemComplianceDefinition&); //not implemented by purpose
		};
} // end namespace iro

#endif
