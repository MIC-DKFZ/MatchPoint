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
// @version $Revision: 1285 $ (last changed revision)
// @date    $Date: 2016-03-30 17:47:52 +0200 (Mi, 30 Mrz 2016) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/branches/Issue-1505/Code/Core/include/mapLazyRegistrationKernelInterface.h $
*/


#ifndef __LAZY_REGISTRATION_KERNEL_INTERFACE_H
#define __LAZY_REGISTRATION_KERNEL_INTERFACE_H

#include "mapRegistrationTopology.h"
#include "mapTransformGenerationFunctor.h"


namespace map
{
	namespace core
	{

		/*! @class LazyRegistrationKernelInterface
		    @brief class for LazyRegistrationKernelInterface.

		    This class is the class for the LazyRegistrationKernelInterface.
		 */
		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class LazyRegistrationKernelInterface
		{
		public:
			typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectTransformType
			TransformType;
      typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectMappingVectorType
          MappingVectorType;

			typedef functors::TransformGenerationFunctor<VInputDimensions, VOutputDimensions>
			TransformGenerationFunctorType;
			typedef typename TransformGenerationFunctorType::ConstPointer TransformGenerationFunctorConstPointer;

			/*! sets the field's functor
			  @eguarantee no fail
			  @param functor Pointer to the functor that is responsible for generating the field
        @pre functor must point to a valid instance.
			*/
			virtual void setTransformFunctor(const TransformGenerationFunctorType* functor) = 0;

			/*! gets the field's functor
			  @eguarantee no fail
			  @return Pointer to the field functor that is used to generate the field on demand.
			*/
			virtual const TransformGenerationFunctorType*  getTransformFunctor() const = 0;

		protected:
        LazyRegistrationKernelInterface() {};
        ~LazyRegistrationKernelInterface() {};

		private:
			//No copy constructor allowed
			LazyRegistrationKernelInterface(const LazyRegistrationKernelInterface&);
			void operator=(const LazyRegistrationKernelInterface&);  //purposely not implemented

		};

	}
}

#endif
