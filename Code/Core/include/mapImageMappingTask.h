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


#ifndef __MAP_IMAGE_MAPPING_TASK_H
#define __MAP_IMAGE_MAPPING_TASK_H

#include "mapStaticServiceStack.h"
#include "mapMappingTaskBase.h"
#include "mapImageMappingPerformerBase.h"
#include "mapImageMappingPerformerLoadPolicy.h"

#include "itkObject.h"

namespace map
{

	namespace core
	{
		/*! @class ImageMappingTask
		* @brief Class realizes tasks, that map image data.
		*
		* You may set a descriptor for the result image (specifying spacing, image size and origin).
		* If no external descriptor has been defined, the task will generate one using the input image
		* as template.
		* @ingroup MappingTask
		* @ingroup Registration
		* @tparam TRegistration the registration class, that should be used to perform the task.
		* @tparam TInputImage Type of the image in the input space.
		* @tparam TResultImage Type of the image in the target space.
		* @tparam TLoadPolicy the load policy that should be used for the provider stack of the point set task.
		*/
		template <class TRegistration, class TInputImage, class TResultImage, template <class> class TLoadPolicy = ImageMappingPerformerLoadPolicy>
		class ImageMappingTask: public MappingTaskBase<TRegistration>
		{
		public:
			/*! Standard class typedefs. */
			typedef ImageMappingTask<TRegistration, TInputImage, TResultImage, TLoadPolicy >  Self;
			using Superclass = MappingTaskBase<TRegistration>;
			using Pointer = itk::SmartPointer<Self>;
			using ConstPointer = itk::SmartPointer<const Self>;

			using RegistrationType = typename MappingTaskBase<TRegistration>::RegistrationType;
			using InputImageType = TInputImage;
			using InputImageConstPointer = typename InputImageType::ConstPointer;
			using ResultImageType = TResultImage;
			using ResultImagePointer = typename ResultImageType::Pointer;

			typedef ImageMappingPerformerBase<RegistrationType, InputImageType, ResultImageType>
			TaskPerformerBaseType;
			using PerformerRequestType = typename TaskPerformerBaseType::RequestType;

			using ErrorValueType = typename PerformerRequestType::ErrorValueType;
			using PaddingValueType = typename PerformerRequestType::PaddingValueType;
			using ResultImageDescriptorType = typename PerformerRequestType::ResultImageDescriptorType;
			using InterpolateBaseType = typename PerformerRequestType::InterpolateBaseType;

			itkTypeMacro(ImageMappingTask, MappingTaskBase);
			itkNewMacro(Self);

#ifdef ITK_USE_CONCEPT_CHECKING
			/** Begin concept checking */
			itkConceptMacro(InputImageFitsRegistrationCheck,
							(itk::Concept::SameDimension<InputImageType::ImageDimension, RegistrationType::MovingDimensions>));
			itkConceptMacro(ResultImageFitsRegistrationCheck,
							(itk::Concept::SameDimension<ResultImageType::ImageDimension, RegistrationType::TargetDimensions>));
			/** End concept checking */
#endif

		protected:
			using LoadPolicyType = TLoadPolicy<TaskPerformerBaseType>;

			typedef services::ServiceStack<TaskPerformerBaseType, LoadPolicyType >
			ConcreteTaskPerformerStackType;

		public:
			using TaskPerformerStackType = services::StaticServiceStack<ConcreteTaskPerformerStackType>;

			/*! Sets _spInputImage to inputPoints and sets _spResultImage to null.
			 * @param [in] inputPoints The pointer to the input image*/
			void setInputImage(const InputImageType* inputImage);
			const InputImageType* getInputImage() const;

			/*! Returns _spResultImage. If the smart pointer is null the method will call execute() to
			 * register the input data.
			 * @post _spResultImage is set.
			 * @pre _spInputImage and _spRegistration are not null.*/
			ResultImagePointer getResultImage();

			/*! Sets the result image descriptor.
			 * @param [in] pDescriptor Pointer to the descriptor. If set to NULL the task will generate one
			 * by using the input image as template.*/
			void setResultImageDescriptor(const ResultImageDescriptorType* pDescriptor);
			const ResultImageDescriptorType* getResultImageDescriptor() const;

			void setThrowOnMappingError(bool throwOnError);
			bool getThrowOnMappingError() const;

			void setErrorValue(const ErrorValueType& value);
			const ErrorValueType& getErrorValue() const;

			void setThrowOnPaddingError(bool throwOnError);
			bool getThrowOnPaddingError() const;

			void setPaddingValue(const PaddingValueType& value);
			const PaddingValueType& getPaddingValue() const;

			void setImageInterpolator(InterpolateBaseType* pInterpolator);
			const InterpolateBaseType* getImageInterpolator() const;

		protected:
			ImageMappingTask();
			~ImageMappingTask() override;

			/*! Smart pointer to the input image*/
			InputImageConstPointer  _spInputImage;

			/*! Smart pointer to the result image. Only points to a result
			 * after the task execution (till clearResults)*/
			mutable ResultImagePointer _spResultImage;

			typedef itk::LinearInterpolateImageFunction<InputImageType, continuous::ScalarType>
			DefaultInterpolatorType;
			using InterpolateBasePointer = typename PerformerRequestType::InterpolateBasePointer;
			/*! Smart pointer to the interpolator instance that should be used to generate the result image*/
			InterpolateBasePointer _spInterpolator;

			using ResultImageDescriptorConstPointer = typename ResultImageDescriptorType::ConstPointer;
			/*! Smart pointer to the result image descriptor. If it points to NULL when the task is executed
			 * a descriptor will be created by using the input image as template.*/
			ResultImageDescriptorConstPointer _spResultDescriptor;

			/*! Indicates the error handling strategie if the kernel is not sufficient to map a pixel in the image (e.g. point is not inside
			 * the deformation field of a field based kernel). True: an exception will be thrown; false: the pixel marked as incorrect via
			 * setting to _errorValue.*/
			bool _throwOnMappingError;
			/*! Value used to label pixels in the result image that could not be mapped because of an mapping error.
			 * This is only relevant, if _throwOnMappingError is true.*/
			ErrorValueType _errorValue;

			/*! Indicates the error handling strategie if the input image is not sufficient to generate the result image (e.g. parts of the result image
			 * are mapped outside of the input image). True: an exception will be thrown; false: the pixels are marked as incorrect via
			 * setting to _paddingValue.*/
			bool _throwOnPaddingError;
			/*! Value used to label pixels in the result image that could not be set, because they were mapped outside the input image.
			 * This is only relevant, if _throwOnPaddingError is true.*/
			PaddingValueType _paddingValue;


			/*! Performs the mapping of the input image.
			 * If _spResultDescriptor is NULL, it will be generated using the input image.
			 * @eguarantee strong
			 * @pre _inputPoints must have been set.
			 * @post _resultPoints are set.
			 */
			void doExecution() const override;

			/*! Sets _spResultImage to NULL.
			 * @eguarantee strong
			 * @post _resultPoints is NULL.
			 */
			void clearResults() const override;

			/*! clears all input datas of the task used to execute().
			 * Must be defined for any concrete data performer.
			 * @eguarantee strong
			 */
			void clearInputs() override;

			/*! Methods invoked by itk::LightObject::Print().  */
			void PrintSelf(std::ostream& os, itk::Indent indent) const override;

		private:
			ImageMappingTask(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapImageMappingTask.tpp"
#endif

#endif
