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




#ifndef __DIMENSIONLESS_REGISTRATION_KERNEL_INTERFACE_H
#define __DIMENSIONLESS_REGISTRATION_KERNEL_INTERFACE_H

#include "itkObject.h"
#include "mapMAPCoreExports.h"

namespace map
{
	namespace core
	{

		/*! @class DimensionlessRegistrationKernelBase
		    This class is the dimensionless (thus abstract) base class for registration kernels.
				@ingroup RegKernel
		 */
		class MAPCore_EXPORT DimensionlessRegistrationKernelBase : public itk::Object
		{
		public:
			typedef DimensionlessRegistrationKernelBase Self;
			typedef itk::Object Superclass;
			typedef itk::SmartPointer<Self> Pointer;
			typedef itk::SmartPointer<const Self> ConstPointer;

			itkTypeMacro(DimensionlessRegistrationKernelBase, itk::Object);

			/*! @brief determines if there is a limit in the data representation of the kernel
			  @eguarantee strong
			  @return if the registration kernel has limited representation
			  @retval true if the data representation is limited
			  @retval false if the data representation is not limited
			 */
			virtual bool hasLimitedRepresentation() const = 0;

			/*! @brief forces kernel to precompute, even if it is a LazyFieldKernel
			  @eguarantee strong
			 */
			virtual void precomputeKernel() = 0;

			/*! @brief Gets the number of input dimensions
			@eguarantee no fail
			*/
			virtual unsigned int getInputDimensions() const = 0;

			/*! @brief Gets the number of output dimensions
			@eguarantee no fail
			*/
			virtual unsigned int getOutputDimensions() const = 0;

		protected:

			/*! Methods invoked by itk::LightObject::Print().  */
			virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

			DimensionlessRegistrationKernelBase();
			virtual ~DimensionlessRegistrationKernelBase();

		private:
			//No copy constructor allowed
			DimensionlessRegistrationKernelBase(const Self& source);
			void operator=(const Self&);  //purposely not implemented

		};

		std::ostream& operator<< (std::ostream& os,
								  const DimensionlessRegistrationKernelBase& p);

	}
}

#endif
