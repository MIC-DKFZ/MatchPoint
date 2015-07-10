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


#ifndef __MAP_IMAGE_MAPPING_TASK_TPP
#define __MAP_IMAGE_MAPPING_TASK_TPP

#include "mapImageMappingTask.h"
#include "mapMissingProviderException.h"

#include "itkLinearInterpolateImageFunction.h"

namespace map
{
	namespace core
	{
		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		void
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		setInputImage(const InputImageType* inputImage)
		{
			if (_spInputImage != inputImage)
			{
				_spInputImage = inputImage;
				clearResults();
				this->Modified();
			}
		}

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		const typename
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy>::InputImageType*
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		getInputImage() const
		{
			return _spInputImage;
		}

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		typename ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::ResultImagePointer
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		getResultImage(void)
		{
			if (_spResultImage.IsNull())
			{
				this->execute();
			}

			assert(_spResultImage.IsNotNull());

			return _spResultImage;
		}

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		void
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		setResultImageDescriptor(const ResultImageDescriptorType* pDescriptor)
		{
			if (_spResultDescriptor != pDescriptor)
			{
				_spResultDescriptor = pDescriptor;
				clearResults();
				this->Modified();
			}
		}

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		const typename
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::ResultImageDescriptorType*

		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		getResultImageDescriptor(void) const
		{
			return _spResultDescriptor;
		}

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		void
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		setImageInterpolator(InterpolateBaseType* pInterpolator)
		{
			if (_spInterpolator != pInterpolator)
			{
				_spInterpolator = pInterpolator;
				clearResults();
				this->Modified();
			}
		}

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		const typename
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::InterpolateBaseType*
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		getImageInterpolator(void) const
		{
			return _spInterpolator;
		}

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		void
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		setThrowOnMappingError(bool throwOnError)
		{
			if (throwOnError != _throwOnMappingError)
			{
				_throwOnMappingError = throwOnError;
				this->Modified();
			}
		};

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		bool
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		getThrowOnMappingError() const
		{
			return _throwOnMappingError;
		};

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		void
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		setErrorValue(const ErrorValueType& value)
		{
			if (value != _errorValue)
			{
				_errorValue = value;
				this->Modified();
			}
		};

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		const typename
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::ErrorValueType&
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		getErrorValue() const
		{
			return _errorValue;
		};

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		void
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		setThrowOnPaddingError(bool throwOnError)
		{
			if (throwOnError != _throwOnPaddingError)
			{
				_throwOnPaddingError = throwOnError;
				this->Modified();
			}
		};

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		bool
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		getThrowOnPaddingError() const
		{
			return _throwOnPaddingError;
		};

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		void
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		setPaddingValue(const PaddingValueType& value)
		{
			if (value != _paddingValue)
			{
				_paddingValue = value;
				this->Modified();
			}
		};

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		const typename
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::PaddingValueType&
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		getPaddingValue() const
		{
			return _paddingValue;
		};

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		ImageMappingTask()
		{
			_errorValue = itk::NumericTraits<ErrorValueType>::Zero;
			_paddingValue = itk::NumericTraits<PaddingValueType>::Zero;
			_throwOnMappingError = true;
			_throwOnPaddingError = false;
			_spResultImage = NULL;
			_spInputImage = NULL;
			_spResultDescriptor = NULL;
			_spInterpolator = DefaultInterpolatorType::New();
		}

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		~ImageMappingTask()
		{
		}

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		void
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		doExecution(void) const
		{
			if (_spInputImage.IsNull())
			{
				mapExceptionMacro(ServiceException, << "Cannot register input image. Input image is null.");
			}

			if (_spInterpolator.IsNull())
			{
				mapExceptionMacro(ServiceException, << "Cannot register input image. Interpolator is null.");
			}

			typename ResultImageDescriptorType::ConstPointer spCurrentDescriptor = _spResultDescriptor;

			if (spCurrentDescriptor.IsNull())
			{
				//generate default discriptor by using input image
				spCurrentDescriptor = createFieldRepresentation(*_spInputImage);
			}

			PerformerRequestType request(Superclass::_spRegistration, _spInputImage, spCurrentDescriptor,
			                             _spInterpolator, _throwOnMappingError, _errorValue, _throwOnPaddingError, _paddingValue);

			mapLogInfoMacro( << "Register image. Request: " << request);

			TaskPerformerBaseType* pPerformer = TaskPerformerStackType::getProvider(request);

			if (!pPerformer)
			{
				mapExceptionMacro(MissingProviderException,
				                  << "No responsible registration performer available for given request. Request:" << request);
			}

			_spResultImage = pPerformer->performMapping(request);

			assert(_spResultImage.IsNotNull());
		}

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		void
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		clearResults(void) const
		{
			_spResultImage = NULL;
		}

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		void
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		clearInputs(void)
		{
			_spInputImage = NULL;
		}

		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy>
		void
		ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >::
		PrintSelf(std::ostream& os, itk::Indent indent) const
		{
			Superclass::PrintSelf(os, indent);

			os << indent << "InputImage: " << _spInputImage.GetPointer() << std::endl;
			os << indent << "ResultImage: " << _spResultImage.GetPointer() << std::endl;
			os << indent << "ResultDescriptor: " << _spResultDescriptor.GetPointer() << std::endl;
			os << indent << "Interpolator: " << _spInterpolator.GetPointer() << std::endl;
			os << indent << "ThrowOnMappingError: " << _throwOnMappingError << std::endl;
			os << indent << "ErrorValue: " << _errorValue << std::endl;
			os << indent << "ThrowOnPaddingError: " << _throwOnPaddingError << std::endl;
			os << indent << "PaddingValue: " << _paddingValue << std::endl;
		}


	} // end namespace core
} // end namespace map

#endif
