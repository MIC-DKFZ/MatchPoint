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
// @version $Revision: 4912 $ (last changed revision)
// @date    $Date: 2013-07-31 10:04:21 +0200 (Mi, 31 Jul 2013) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapDefaultSLStaticPolicy.h $
*/


#ifndef __MAP_DEFAULT_SL_STATIC_POLICY_H
#define __MAP_DEFAULT_SL_STATIC_POLICY_H

namespace map
{
	namespace core
	{
		namespace services
		{
			/*! @class NoneStaticLoadPolicy
			* @brief Default loading policy for static service stacks.
			*
			* This policy does nothing, therefore a repository using this policy has no static loading operations.
			*
			* @ingroup LoadPolicies
			* @tparam TConcreteServiceStack The service stack class that is wrapped by the policy owner.
			*/
			template <class TConcreteServiceStack>
			class DefaultSLStaticPolicy
			{
			protected:
				/*! Standard class typedefs. */
				typedef TConcreteServiceStack ConcreteServiceStackType;

				/*! Will be called after registering the concrete stack to allow the policy to do final operations on
				 * the concrete stack.
				 * @eguarantee basic
				 * @param [in] pStack Pointer to the stack. Pointer must point to a valid stack instance.
				 */
				static void finalizeStaticLoading(ConcreteServiceStackType *pStack);

				/*! Registers the concrete stack that should be handled by the policy. Function will be called directly after the
				 * stack was created.
				 * @eguarantee strong
				 * @param [in] pStack Pointer to the stack. Pointer must point to a valid stack instance.
				 * @pre pStack must not be NULL
				 */
				static void registerConcreteStack(ConcreteServiceStackType *pStack);

				DefaultSLStaticPolicy();
				~DefaultSLStaticPolicy();

			private:
				typedef DefaultSLStaticPolicy<TConcreteServiceStack> Self;
				DefaultSLStaticPolicy(const Self &); //purposely not implemented
				void operator=(const Self &); //purposely not implemented
			};

		} // end namespace services
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapDefaultSLStaticPolicy.tpp"
#endif

#endif
