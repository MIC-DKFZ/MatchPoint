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


#ifndef __REGISTRATION_KERNEL_BASE_TPP
#define __REGISTRATION_KERNEL_BASE_TPP

namespace map
{
	namespace core
	{

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		RegistrationKernelBase<VInputDimensions, VOutputDimensions> ::
		hasLimitedRepresentation() const
		{
			return this->getLargestPossibleRepresentation().IsNotNull();
		};


		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		RegistrationKernelBase<VInputDimensions, VOutputDimensions> ::
        RegistrationKernelBase()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		RegistrationKernelBase<VInputDimensions, VOutputDimensions> ::
		~RegistrationKernelBase()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		RegistrationKernelBase<VInputDimensions, VOutputDimensions> ::
		mapPoint(const InputPointType& inPoint, OutputPointType& outPoint) const
		{
			bool result = true;

			if (!doMapPoint(inPoint, outPoint))
			{
				//need to handle outPoint explicit, because it was not mapped
				outPoint.Fill(0);
				result = false;
			}

			return result;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		RegistrationKernelBase<VInputDimensions, VOutputDimensions>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);
			os << indent << "Largest possible field representation: ";
			RepresentationDescriptorConstPointer spRep = getLargestPossibleRepresentation();

			if (spRep.IsNull())
			{
				os << "none" << std::endl;
			}
			else
			{
				os << std::endl;
				spRep->Print(os);
				os << std::endl;
			}
		};

	} // end namespace core
} // end namespace map

#endif
