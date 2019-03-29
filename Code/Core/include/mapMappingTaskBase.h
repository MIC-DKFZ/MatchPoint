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


#ifndef __MAP_MAPPING_TASK_BASE_H
#define __MAP_MAPPING_TASK_BASE_H


#include "mapRegistrationException.h"

#include "itkObject.h"

namespace map
{

	namespace core
	{
		/*! @class MappingTaskBase
		* @brief Base class for any mapping tasks.
		*
		* This class is the base class for any mapping task meant to use a registration to map data between to
		* information spaces.\n
		* To perform the mapping the class uses a static service stack populated with
		* MappingPerformers.\n
		*
		* @ingroup RegTask
		* @tparam TRegistration the registration class, that should be used to perform the task.
		*/
		template <class TRegistration>
		class MappingTaskBase: public itk::Object
		{
		public:
			/*! Standard class typedefs. */
			using Self = MappingTaskBase<TRegistration>;
			using Superclass = itk::Object;
			using Pointer = itk::SmartPointer<Self>;
			using ConstPointer = itk::SmartPointer<const Self>;

			itkTypeMacro(MappingTaskBase, itk::Object);

			using RegistrationType = TRegistration;
			using RegistrationPointer = typename RegistrationType::Pointer;
			using RegistrationConstPointer = typename RegistrationType::ConstPointer;

			itkStaticConstMacro(MovingDimensions, unsigned int, RegistrationType::MovingDimensions);
			itkStaticConstMacro(TargetDimensions, unsigned int, RegistrationType::TargetDimensions);

			/*! Performs the registration of the given data by calling doExecution().
				 * Checks if the registration has been set, clear results and logs the beginning of the task.
				 * @eguarantee strong
				 * @result Returns if the input data was successfully registered.
				 * @retval false If _isExceptionNeutral is false, it indecates that an exception occured. The the stored exception copy
				 * for more information (getRegistrationException).
				 * @pre Registration must have been set.
				 */
			bool execute() const;

			/*! Sets the pointer to the registration that should be used. Calls clearResults().
				 */
			void setRegistration(const RegistrationType* pRegistration);
			const RegistrationType* getRegistration() const;

			/*! Returns the pointer to the exception, if any has occured while registering the data.
			 * @result Pointer to the exception.
			 * @retval NULL No exception has occured yet.*/
			const ExceptionObject* getRegistrationException() const;

			void setIsExceptionNeutral(bool neutral);
			bool getIsExceptionNeutral() const;

			/*! Clears the results, inputs and any stored exception.
			 * @remark Registration pointer will not be changed.*/
			void reset();

		protected:
			/*! Performs the registration of the given data and sets/replaces the results.
				 * Must be defined for any concrete data performer.
				 * @eguarantee strong
				 */
			virtual void doExecution() const = 0;

			/*! clears all result values of the task computed by former execute() calls.
			 * Must be defined for any concrete data performer.
			 * @eguarantee strong
			 */
			virtual void clearResults() const = 0;

			/*! clears all input datas of the task used to execute().
			 * Must be defined for any concrete data performer.
			 * @eguarantee strong
			 */
			virtual void clearInputs() = 0;

			/*! Sets the pointer to the exception object to NULL after deleting the old instance, if one is referenced.
					 * @eguarantee strong
					 */
			void clearException() const;

			RegistrationConstPointer _spRegistration;

			MappingTaskBase();
			~MappingTaskBase() override;

			/*! Methods invoked by itk::LightObject::Print().  */
			void PrintSelf(std::ostream& os, itk::Indent indent) const override;

		private:
			/*! Indicates if the task should act exception-neutral (thus passing all exceptions
			 * directly through to the task user) or just catch the exception, store a copy of the exception
			 * for later examinations and return false as the result of excute().*/
			bool _isExceptionNeutral{true};

			/*! Pointer to the cloned excpetion if any exception occurred.*/
			mutable ExceptionObject* _pException{nullptr};

			MappingTaskBase(const Self&);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented
		};
	} // end namespace core
} // end namespace map

#ifndef MatchPoint_MANUAL_TPP
# include "mapMappingTaskBase.tpp"
#endif

#endif
