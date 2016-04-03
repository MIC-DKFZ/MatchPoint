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

#ifndef __COMBINED_REGISTRATION_KERNEL_TPP
#define __COMBINED_REGISTRATION_KERNEL_TPP

#include "mapExceptionObjectMacros.h"

namespace map
{
    namespace core
    {

        template<unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
        CombinedRegistrationKernel<VInputDimensions, VInterimDimensions, VOutputDimensions>::
            CombinedRegistrationKernel()
        {
        };

        template<unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
        CombinedRegistrationKernel<VInputDimensions, VInterimDimensions, VOutputDimensions>::
            ~CombinedRegistrationKernel()
        {
        };

        template<unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
        bool
            CombinedRegistrationKernel<VInputDimensions, VInterimDimensions, VOutputDimensions>::
            doMapPoint(const InputPointType& inPoint, OutputPointType& outPoint) const
        {
            bool result = false;

            if (this->transformExists())
            {
                //use default implementation
                result = Superclass::doMapPoint(inPoint, outPoint);
            }
            else
            {
                //field is yet not generated, thus use the source kernels to avoid field generation.
                typedef typename SourceKernel1BaseType::OutputPointType InterimPointType;

                InterimPointType interimPoint;

                result = _pCombinationInterface->get1stSourceKernelBase()->mapPoint(inPoint, interimPoint);

                if (result)
                {
                    result = _pCombinationInterface->get2ndSourceKernelBase()->mapPoint(interimPoint, outPoint);
                }
            }

            return result;
        };

        template<unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
        void
            CombinedRegistrationKernel<VInputDimensions, VInterimDimensions, VOutputDimensions>::
            setTransformFunctor(const TransformGenerationFunctorType* functor)
        {
            const CombinationFunctorInterfaceType* pInterface =
                dynamic_cast<const CombinationFunctorInterfaceType*>(functor);
            assert(pInterface);

            _pCombinationInterface = pInterface;

            Superclass::setTransformFunctor(functor);
        };

        template<unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions>
        void
            CombinedRegistrationKernel<VInputDimensions, VInterimDimensions, VOutputDimensions>::
            PrintSelf(std::ostream& os, itk::Indent indent) const
        {
            Superclass::PrintSelf(os, indent);
        };

    } // end namespace core
} // end namespace map

#endif
