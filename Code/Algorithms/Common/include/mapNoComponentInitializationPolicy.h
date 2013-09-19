// -----------------------------------------------------------------------
// MatchPoint - DKFZ translational registration framework
//
// Copyright (c) German Cancer Research Center (DKFZ),
// Software development for Integrated Diagnostics and Therapy (SIDT).
// ALL RIGHTS RESERVED.
// See mapCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/MatchPoint/copyright.html
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the above copyright notices for more information.
//
//------------------------------------------------------------------------
/*!
// @file
// @version $Revision$ (last changed revision)
// @date    $Date$ (last change date)
// @author  $Author$ (last changed by)
// Subversion HeadURL: $HeadURL$
*/




#ifndef __NO_COMPONENT_INITIALIZATION_POLICY_H
#define __NO_COMPONENT_INITIALIZATION_POLICY_H

namespace map
{
	namespace algorithm
	{
		namespace itk
		{
			/*! @struct NoComponentInitializationPolicy
			 * @brief Policy that defines the initialization of a component.
			 *
			 * In this case it doesn't initialize the
			 * passed component at all. This policy is for example used in conjunction
			 * with FixedPolicy and SealedPolicy to define the default values of a
			 * component used in an registration algorithm.
			 * @ingroup ITKPolicies
			*/
			struct NoComponentInitializationPolicy
			{
			public:
				/*! @remark Elipsis are normaly considered bad practice, but in this case
				 * the use is adequat in order to ease the use of the no component policy.
				 * By using the elipsis the interface requirements for component initialisation
				 * policies are met for any component, thus we can use one NoComponentInitializationPolicy.
				 * for any component. Disadvantages of elipsis like loss of type information
				 * don't matter in this case because the method is a dummy function and has no
				 * real implementation. Normal initialization policies should have a reference to
				 * the component as parameter.
				 */
				static void initialize(...) {};
			};

		}
	}
}

#endif
