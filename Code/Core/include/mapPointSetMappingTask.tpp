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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapPointSetMappingTask.tpp $
*/


#ifndef __MAP_POINT_MAPPING_TASK_TPP
#define __MAP_POINT_MAPPING_TASK_TPP

#include "mapPointSetMappingTask.h"
#include "mapMissingProviderException.h"

namespace map
{
	namespace core
	{

		template <class TRegistration, class TInputPointSet, class TResultPointSet, template <class> class TLoadPolicy>
		void
		PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy>::
		setInputPointSet(const InputPointSetType *inputPoints)
		{
			if (_spInputPoints != inputPoints)
			{
				_spInputPoints = inputPoints;
				clearResults();
				this->Modified();
			}
		}

		template <class TRegistration, class TInputPointSet, class TResultPointSet, template <class> class TLoadPolicy>
		const typename PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy>::InputPointSetType *
		PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy>::
		getInputPointSet() const
		{
			return _spInputPoints;
		}

		template <class TRegistration, class TInputPointSet, class TResultPointSet, template <class> class TLoadPolicy>
		typename PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy>::ResultPointSetPointer
		PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy>::
		getResultPointSet(void)
		{
			if (_spResultPoints.IsNull())
			{
				this->execute();
			}

			assert(_spResultPoints.IsNotNull());

			return _spResultPoints;
		}

		template <class TRegistration, class TInputPointSet, class TResultPointSet, template <class> class TLoadPolicy>
		PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy>::
		PointSetMappingTask()
		{
			_errorValue = itk::NumericTraits<ErrorPointValueType>::Zero;
			_throwOnMappingError = true;
			_spResultPoints = NULL;
			_spInputPoints = NULL;
		}

		template <class TRegistration, class TInputPointSet, class TResultPointSet, template <class> class TLoadPolicy>
		PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy>::
		~PointSetMappingTask()
		{
		}

		template <class TRegistration, class TInputPointSet, class TResultPointSet, template <class> class TLoadPolicy>
		void
		PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy>::
		doExecution(void) const
		{
			if (_spInputPoints.IsNull())
			{
				mapExceptionMacro(ServiceException, << "Cannot register point set. Input point set is null.");
			}

			PerformerRequestType request(Superclass::_spRegistration, _spInputPoints, _throwOnMappingError, _errorValue);

			mapLogInfoMacro( << "Register pointset. Request: " << request);

			TaskPerformerBaseType *pPerformer = TaskPerformerStackType::getProvider(request);

			if (!pPerformer)
			{
				mapExceptionMacro(MissingProviderException, << "No responsible registration performer available for given request. Request:" << request);
			}

			_spResultPoints = pPerformer->performMapping(request);

			assert(_spResultPoints.IsNotNull());
		}

		template <class TRegistration, class TInputPointSet, class TResultPointSet, template <class> class TLoadPolicy>
		void
		PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy>::
		clearResults(void) const
		{
			_spResultPoints = NULL;
		}

		template <class TRegistration, class TInputPointSet, class TResultPointSet, template <class> class TLoadPolicy>
		void
		PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy>::
		clearInputs(void)
		{
			_spInputPoints = NULL;
		}

		template <class TRegistration, class TInputPointSet, class TResultPointSet, template <class> class TLoadPolicy>
		void
		PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy>::
		setThrowOnMappingError(bool throwOnError)
		{
			if (throwOnError != _throwOnMappingError)
			{
				_throwOnMappingError = throwOnError;
				this->Modified();
			}
		};

		template <class TRegistration, class TInputPointSet, class TResultPointSet, template <class> class TLoadPolicy>
		bool
		PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy>::
		getThrowOnMappingError() const
		{
			return _throwOnMappingError;
		};

		template <class TRegistration, class TInputPointSet, class TResultPointSet, template <class> class TLoadPolicy>
		void
		PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy>::
		setErrorPointValue(const ErrorPointValueType &value)
		{
			if (value != _errorValue)
			{
				_errorValue = value;
				this->Modified();
			}
		};

		template <class TRegistration, class TInputPointSet, class TResultPointSet, template <class> class TLoadPolicy>
		const typename PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy>::ErrorPointValueType &
		PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy>::
		getErrorPointValue() const
		{
			return _errorValue;
		};

		template <class TRegistration, class TInputPointSet, class TResultPointSet, template <class> class TLoadPolicy>
		void
		PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy>::
		PrintSelf(std::ostream &os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);

			os << indent << "InputPoints: " << _spInputPoints.GetPointer() << std::endl;
			os << indent << "ResultPoints: " << _spResultPoints.GetPointer() << std::endl;
			os << indent << "ThrowOnMappingError: " << _throwOnMappingError << std::endl;
			os << indent << "ErrorValue: " << _errorValue << std::endl;
		}

	} // end namespace core
} // end namespace map

#endif
