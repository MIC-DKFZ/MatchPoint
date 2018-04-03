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


#ifndef __MAP_POINT_MAPPING_TASK_H
#define __MAP_POINT_MAPPING_TASK_H

#include "mapStaticServiceStack.h"
#include "mapMappingTaskBase.h"
#include "mapMappingPerformerBase.h"
#include "mapPointSetMappingPerformerLoadPolicy.h"
#include "mapPointSetMappingPerformerRequest.h"

#include "itkObject.h"

namespace map
{

	namespace core
	{
		/*! @class PointSetMappingTask
		* @brief Class realizes tasks, that map point set data.
		*
		* @ingroup MappingTask
		* @ingroup Registration
		* @tparam TRegistration the registration class, that should be used to perform the task.
		* @tparam TInputPointSet Type of the point set in the input space.
		* @tparam TResultPointSet Type of the point set in the target space.
		* @tparam TLoadPolicy the load policy that should be used for the provider stack of the point set task.
		*/
		template <class TRegistration, class TInputPointSet, class TResultPointSet, template <class> class TLoadPolicy = PointSetMappingPerformerLoadPolicy>
		class PointSetMappingTask: public MappingTaskBase<TRegistration>
		{
		public:
			/*! Standard class typedefs. */
			typedef PointSetMappingTask<TRegistration, TInputPointSet, TResultPointSet, TLoadPolicy >  Self;
			typedef MappingTaskBase<TRegistration>                            Superclass;
			typedef itk::SmartPointer<Self>        Pointer;
			typedef itk::SmartPointer<const Self>  ConstPointer;

			typedef typename MappingTaskBase<TRegistration>::RegistrationType  RegistrationType;
			typedef TInputPointSet                                                  InputPointSetType;
			typedef typename InputPointSetType::ConstPointer                        InputPointSetConstPointer;
			typedef TResultPointSet                                                 ResultPointSetType;
			typedef typename ResultPointSetType::Pointer                            ResultPointSetPointer;
			typedef typename ResultPointSetType::PixelType                          ErrorPointValueType;

			typedef PointSetMappingPerformerRequest<RegistrationType, InputPointSetType, ResultPointSetType>
			PerformerRequestType;

			typedef MappingPerformerBase<PerformerRequestType> TaskPerformerBaseType;

			itkTypeMacro(PointSetMappingTask, MappingTaskBase);
			itkNewMacro(Self);

#ifdef ITK_USE_CONCEPT_CHECKING
			/** Begin concept checking */
			itkConceptMacro(InputPointSetFitsRegistrationCheck,
							(itk::Concept::SameDimension<InputPointSetType::PointDimension, RegistrationType::MovingDimensions>));
			itkConceptMacro(ResultPointSetFitsRegistrationCheck,
							(itk::Concept::SameDimension<ResultPointSetType::PointDimension, RegistrationType::TargetDimensions>));
			/** End concept checking */
#endif

		protected:
			typedef TLoadPolicy<TaskPerformerBaseType> LoadPolicyType;

			typedef services::ServiceStack<TaskPerformerBaseType, LoadPolicyType >
			ConcreteTaskPerformerStackType;

		public:
			typedef services::StaticServiceStack<ConcreteTaskPerformerStackType>  TaskPerformerStackType;

			/*! Sets _spInputPoints to inputPoints and sets _spResultPoints to null.
			 * @param [in] inputPoints The pointer to the input points*/
			void setInputPointSet(const InputPointSetType* inputPoints);
			const InputPointSetType* getInputPointSet() const;

			/*! Returns _spResultPoints. If the smart pointer is null the method will call execute() to
			 * register the input data.
			 * @post _spResultPoints is set.
			 * @pre _spInputPoints and _spRegistration are not null.*/
			ResultPointSetPointer getResultPointSet(void);

			void setThrowOnMappingError(bool throwOnError);
			bool getThrowOnMappingError() const;

			void setErrorPointValue(const ErrorPointValueType& value);
			const ErrorPointValueType& getErrorPointValue() const;

		protected:
			PointSetMappingTask();
			virtual ~PointSetMappingTask();

			InputPointSetConstPointer _spInputPoints;
			mutable ResultPointSetPointer     _spResultPoints;

			/*! Indicates the error handling strategie if the kernel is not sufficient to map a point in the point set (e.g. point is not inside
			 * the deformation field of a field based kernel). True: an exception will be thrown; false: point will be copied into the result list
			 * and marked as incorrect via _errorValue.*/
			bool _throwOnMappingError;
			/*! Value used to label points in the result set that could not be mapped because of an mapping error.
			 * This is only relevant, if _throwOnMappingError is true.*/
			ErrorPointValueType _errorValue;

			/*! Performs the mapping of the input point set.
			 * @eguarantee strong
			 * @pre _inputPoints must have been set.
			 * @post _resultPoints are set.
			 */
			virtual void doExecution(void) const;

			virtual void clearResults(void) const;

			/*! clears all input datas of the task used to execute().
			 * @eguarantee strong
			 */
			virtual void clearInputs(void);

			/*! Methods invoked by itk::LightObject::Print().  */
			virtual void PrintSelf(std::ostream& os, itk::Indent indent) const;

		private:
			PointSetMappingTask(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapPointSetMappingTask.tpp"
#endif

#endif
