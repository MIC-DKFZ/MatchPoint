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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapLazyFieldPolicy.tpp $
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
		LazyFieldPolicy<VInputDimensions, VOutputDimensions>::
		setFieldFunctor(const FieldGenerationFunctorType &functor)
		{
			_spGenerationFunctor = &functor;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		const typename LazyFieldPolicy<VInputDimensions, VOutputDimensions>::FieldGenerationFunctorType *
		LazyFieldPolicy<VInputDimensions, VOutputDimensions>::
		getFieldFunctor() const
		{
			return _spGenerationFunctor;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		LazyFieldPolicy<VInputDimensions, VOutputDimensions>::
		LazyFieldPolicy() : _spGenerationFunctor(NULL)
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		LazyFieldPolicy<VInputDimensions, VOutputDimensions>::
		~LazyFieldPolicy()
		{
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		LazyFieldPolicy<VInputDimensions, VOutputDimensions>::
		fieldExists() const
		{
			return _spField.IsNotNull();
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		LazyFieldPolicy<VInputDimensions, VOutputDimensions>::
		checkAndPrepareField() const
		{
			::itk::MutexLockHolder<MutexType> mutexHolder(_checkMutex);

			if (_spField.IsNull())
			{
				//create field
				mapLogInfoObjMacro( << "Lazy field kernel needs to generate the field");
				generateField();
			}

			return true;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		typename LazyFieldPolicy<VInputDimensions, VOutputDimensions>::RepresentationDescriptorConstPointer
		LazyFieldPolicy<VInputDimensions, VOutputDimensions>::
		getRepresentationDescriptor() const
		{
			assert(_spGenerationFunctor.IsNotNull());
			RepresentationDescriptorConstPointer spRep = _spGenerationFunctor->getInFieldRepresentation();
			return spRep;
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		LazyFieldPolicy<VInputDimensions, VOutputDimensions>::
		PrintSelf(std::ostream &os, itk::Indent indent) const
		{
			if (_spGenerationFunctor.IsNotNull())
			{
				os << indent << "Generation functor : " << std::endl << _spGenerationFunctor << std::endl;
			}
			else
			{
				os << indent << "Generation functor : NULL" << std::endl;
			}

			if (_spField.IsNotNull())
			{
				os << indent << "Field : " << std::endl << _spField << std::endl;
			}
			else
			{
				os << indent << "Field : NULL" << std::endl;
			}
		};

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		void
		LazyFieldPolicy<VInputDimensions, VOutputDimensions>::
		generateField() const
		{
			::itk::MutexLockHolder<MutexType> mutexHolder(_generateMutex);

			assert(_spGenerationFunctor.IsNotNull());
			_spField = _spGenerationFunctor->generateField();
			mapLogInfoObjMacro( << "Lazy field kernel has generated the field");
		};


	} // end namespace core
} // end namespace map

#endif
