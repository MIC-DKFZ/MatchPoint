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




#ifndef __NULL_REGISTRATION_KERNEL_BASE_H
#define __NULL_REGISTRATION_KERNEL_BASE_H

#include "mapRegistrationKernelBase.h"

namespace map
{
	namespace core
	{

		/*! @class NullRegistrationKernel
		    This class defines null kernels. This type of kernel should be used by registration algorithms,
		    if there is no valid registration kernel (yet) for a mapping direction. Thus it is the "official"
		    and explicit way to define, that a mapping direction (and its kernel) is undefined and not valid.
		    (It is analog to the meaning of NULL pointer). Any attempt to use this kernel for mapping purposes will
		    fail. The precompution of the kernel will raise an exception. Combination of a NullRegistrationKernel with a
		    kernel of any other type will result in NullRegistrationKernel. The inversion of a NullRegistrationKernel is
		    a NullRegistrationKernel
				@ingroup RegKernel
		 */
		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class NullRegistrationKernel : public RegistrationKernelBase<VInputDimensions, VOutputDimensions>
		{
		public:
			typedef NullRegistrationKernel<VInputDimensions, VOutputDimensions> Self;
			typedef RegistrationKernelBase<VInputDimensions, VOutputDimensions> Superclass;
			typedef itk::SmartPointer<Self> Pointer;
			typedef itk::SmartPointer<const Self> ConstPointer;

			itkTypeMacro(NullRegistrationKernel, RegistrationKernelBase);
			itkNewMacro(Self);

			typedef typename Superclass::InputPointType InputPointType;
			typedef typename Superclass::OutputPointType OutputPointType;
			typedef typename Superclass::RepresentationDescriptorConstPointer
			RepresentationDescriptorConstPointer;


			/*! @brief gets the largest possible representation descriptor. The descriptor defines
			 * the space the kernel guarantees to map.
			 * @return Smart pointer to the descriptor (may be generated dynamicaly)
			 * @retval NULL there is no descriptor. If hasLimitedRepresentation returns false, the kernel
			 * has no mapping limitations and covers the total input space.
			  @eguarantee strong
			 */
			virtual RepresentationDescriptorConstPointer getLargestPossibleRepresentation() const;

			/*! @brief forces kernel to precompute, even if it is a LazyFieldKernel
			  @eguarantee strong
			 */
			virtual void precomputeKernel() const override;

		protected:

			/*! Methods invoked by itk::LightObject::Print().  */
			virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

			/*! Maps the point from input to output space. Is used by mapPoint()
			 * It will always return false because a NullRegistrationKernel cannot map
			 * any points
			 * @eguarantee strong
			 */
			virtual bool doMapPoint(const InputPointType& inPoint, OutputPointType& outPoint) const;

			NullRegistrationKernel();
			virtual ~NullRegistrationKernel();

      /** @reimplementation
      Reimplementation of the itk::LightObject::InternalClone*/
      virtual ::itk::LightObject::Pointer	InternalClone()	const;

		private:
			//No copy constructor allowed
			NullRegistrationKernel(const Self& source);
			void operator=(const Self&);  //purposely not implemented

		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		std::ostream& operator<< (std::ostream& os,
								  const NullRegistrationKernel<VInputDimensions, VOutputDimensions>& p)
		{
			p.Print(os);
			return os;
		}

	}
}


#ifndef MatchPoint_MANUAL_TPP
#include "mapNullRegistrationKernel.tpp"
#endif

#endif
