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


#ifndef __LAZY_FIELD_POLICY_TPP
#define __LAZY_FIELD_POLICY_TPP

#include "mapLogbookMacros.h"

#include "itkMutexLockHolder.h"

namespace map
{
	namespace core
	{

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		LazyTransformPolicy<VInputDimensions, VOutputDimensions>::
		setTransformFunctor(const TransformGenerationFunctorType& functor)
		{
			_spGenerationFunctor = &functor;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		const typename LazyTransformPolicy<VInputDimensions, VOutputDimensions>::TransformGenerationFunctorType*
		LazyTransformPolicy<VInputDimensions, VOutputDimensions>::
		getTransformFunctor() const
		{
			return _spGenerationFunctor;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		LazyTransformPolicy<VInputDimensions, VOutputDimensions>::
		LazyTransformPolicy() : _spGenerationFunctor(NULL)
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		LazyTransformPolicy<VInputDimensions, VOutputDimensions>::
		~LazyTransformPolicy()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		LazyTransformPolicy<VInputDimensions, VOutputDimensions>::
    transformExists() const
		{
			return _spTransform.IsNotNull();
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		LazyTransformPolicy<VInputDimensions, VOutputDimensions>::
		checkAndPrepareTransform() const
		{
			::itk::MutexLockHolder<MutexType> mutexHolder(_checkMutex);

			if (_spTransform.IsNull())
			{
				//create field
				mapLogInfoObjMacro( << "Lazy field kernel needs to generate the field");
				generateTransform();
			}

			return true;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename LazyTransformPolicy<VInputDimensions, VOutputDimensions>::RepresentationDescriptorConstPointer
		LazyTransformPolicy<VInputDimensions, VOutputDimensions>::
		getRepresentationDescriptor() const
		{
			assert(_spGenerationFunctor.IsNotNull());
			RepresentationDescriptorConstPointer spRep = _spGenerationFunctor->getInFieldRepresentation();
			return spRep;
		};

    template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
    const typename LazyTransformPolicy<VInputDimensions, VOutputDimensions>::MappingVectorType&
        LazyTransformPolicy<VInputDimensions, VOutputDimensions>::
        doGetNullVector() const
    {
        return _nullVector;
    };

    template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
    bool
        LazyTransformPolicy<VInputDimensions, VOutputDimensions>::
        doUsesNullVector() const
    {
        return _useNullVector;
    };

    template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
    void
        LazyTransformPolicy<VInputDimensions, VOutputDimensions>::
        setNullVector(const MappingVectorType& nullVector)
    {
        _nullVector = nullVector;
    };

    template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
    void
        LazyTransformPolicy<VInputDimensions, VOutputDimensions>::
        setNullVectorUsage(bool use)
    {
        _useNullVector = use;
    };

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		LazyTransformPolicy<VInputDimensions, VOutputDimensions>::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
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

      os << indent << "Use null vector: " << _useNullVector << std::endl;
      os << indent << "Null vector: " << this->_nullVector << std::endl;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		LazyTransformPolicy<VInputDimensions, VOutputDimensions>::
		generateTransform() const
		{
			::itk::MutexLockHolder<MutexType> mutexHolder(_generateMutex);

			assert(_spGenerationFunctor.IsNotNull());
			_spTransform = _spGenerationFunctor->generateTransform();
			mapLogInfoObjMacro( << "Lazy field kernel has generated the field");
		};


	} // end namespace core
} // end namespace map

#endif
