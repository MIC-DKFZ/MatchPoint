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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapTestKernelBase.h $
*/

#ifndef __MAP_TEST_KERNEL_BASE_H
#define __MAP_TEST_KERNEL_BASE_H

#include "mapRegistrationKernelBase.h"

namespace map
{
	namespace testing
	{

		/*!@brief Dummy Kernel used if a simple testing kernel is needed that does nothing.*/
		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class TestKernelBase: public core::RegistrationKernelBase<VInputDimensions, VOutputDimensions>
		{
		public:
			/*! Standard class typedefs. */
			typedef TestKernelBase<VInputDimensions, VOutputDimensions>  Self;
			typedef core::RegistrationKernelBase<VInputDimensions, VOutputDimensions> Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			itkTypeMacro(TestKernelBase, core::RegistrationKernelBase);
			itkNewMacro(Self);

			typename Superclass::RepresentationDescriptorConstPointer getLargestPossibleRepresentation() const
			{
				typename Superclass::RepresentationDescriptorConstPointer spTemp = NULL;
				return spTemp;
			}

			void precomputeKernel()
			{
				// do nothing
			}

			bool doMapPoint(const typename Superclass::InputPointType &inPoint, typename Superclass::OutputPointType &outPoint) const
			{
				return false;
			}

		};



	} // end namespace testing
} // end namespace map

#endif
