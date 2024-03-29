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
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/branches/Issue-1505/Code/Core/include/mapLazyRegistrationKernel.tpp $
*/

#ifndef __LAZY_REGISTRATION_KERNEL_TPP
#define __LAZY_REGISTRATION_KERNEL_TPP

#include "mapExceptionObjectMacros.h"
#include "mapPointVectorCombinationPolicy.h"

#include <mutex>

namespace map
{
    namespace core
    {

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        void
            LazyRegistrationKernel<VInputDimensions, VOutputDimensions>::
            setTransformFunctor(const TransformGenerationFunctorType* functor)
        {
            assert(functor);
            if (!functor)
            {
                mapDefaultExceptionMacro(<< "Error. Cannot set functor. Functor points to NULL.");
            }

            std::lock_guard<std::mutex> mutexHolder(_generateMutex);
            _spGenerationFunctor = functor;
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        const typename LazyRegistrationKernel<VInputDimensions, VOutputDimensions>::TransformGenerationFunctorType*
            LazyRegistrationKernel<VInputDimensions, VOutputDimensions>::
            getTransformFunctor() const
        {
            return _spGenerationFunctor;
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        bool
            LazyRegistrationKernel<VInputDimensions, VOutputDimensions>::
            transformExists() const
        {
            return _spTransform.IsNotNull();
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
        typename LazyRegistrationKernel<VInputDimensions, VOutputDimensions>::RepresentationDescriptorConstPointer
            LazyRegistrationKernel<VInputDimensions, VOutputDimensions>::
            getLargestPossibleRepresentation() const
        {
            RepresentationDescriptorConstPointer spRep;
            if (_spGenerationFunctor.IsNotNull())
            {
                spRep = _spGenerationFunctor->getInFieldRepresentation();
            }
            return spRep;
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
        const typename
            LazyRegistrationKernel<VInputDimensions, VOutputDimensions>::TransformType*
            LazyRegistrationKernel<VInputDimensions, VOutputDimensions>::
            getTransformModel() const
        {
            if (!this->checkAndPrepareTransform())
            {
                mapDefaultExceptionMacro(<< "Error. Cannot return field. checkAndPrepareField() failed.");
            }

            return _spTransform;
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        bool
            LazyRegistrationKernel<VInputDimensions, VOutputDimensions>::
            checkAndPrepareTransform() const
        {
            std::lock_guard<std::mutex> mutexHolder(_checkMutex);

            if (_spTransform.IsNull())
            {
                //create field
                mapLogInfoObjMacro(<< "Lazy field kernel needs to generate the field");

                std::lock_guard<std::mutex> mutexHolder(_generateMutex);

                assert(_spGenerationFunctor.IsNotNull());
                _spTransform = _spGenerationFunctor->generateTransform();
                mapLogInfoObjMacro(<< "Lazy field kernel has generated the field");
            }

            return true;
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
        LazyRegistrationKernel<VInputDimensions, VOutputDimensions>::
            LazyRegistrationKernel()
        {
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
        LazyRegistrationKernel<VInputDimensions, VOutputDimensions>::
            ~LazyRegistrationKernel()
        {
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        const typename LazyRegistrationKernel<VInputDimensions, VOutputDimensions>::OutputPointType
            LazyRegistrationKernel<VInputDimensions, VOutputDimensions>::
            getNullPoint() const
        {
            OutputPointType result;
            if (_spGenerationFunctor.IsNotNull())
            {
                result = _spGenerationFunctor->getNullPoint();
            }

            return result;
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        bool
            LazyRegistrationKernel<VInputDimensions, VOutputDimensions>::
            usesNullPoint() const
        {
            bool result = false;
            if (_spGenerationFunctor.IsNotNull())
            {
                result = _spGenerationFunctor->getNullPointUsage();
            }

            return result;
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        ::itk::LightObject::Pointer
          LazyRegistrationKernel<VInputDimensions, VOutputDimensions>::
          InternalClone() const
        {
          Pointer clone = Self::New();
          clone->_spTransform = this->_spTransform;
          clone->_spGenerationFunctor = this->_spGenerationFunctor;

          return clone.GetPointer();
        };

        template<unsigned int VInputDimensions, unsigned int VOutputDimensions >
        void
            LazyRegistrationKernel<VInputDimensions, VOutputDimensions>::
            PrintSelf(std::ostream& os, itk::Indent indent) const
        {
            Superclass::PrintSelf(os, indent);
            if (_spGenerationFunctor.IsNotNull())
            {
                os << indent << "Generation functor : " << std::endl << _spGenerationFunctor << std::endl;
            }
            else
            {
                os << indent << "Generation functor : NULL" << std::endl;
            }

            if (_spTransform.IsNotNull())
            {
                os << indent << "Transform : " << std::endl << _spTransform << std::endl;
            }
            else
            {
                os << indent << "Transform : NULL" << std::endl;
            }

            os << indent << "Use null vector: " << this->usesNullPoint() << std::endl;
            os << indent << "Null vector: " << this->getNullPoint() << std::endl;
        };

    } // end namespace core
} // end namespace map

#endif
