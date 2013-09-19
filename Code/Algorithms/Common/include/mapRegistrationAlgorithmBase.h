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




#ifndef __REGISTRATION_ALGORITHM_BASE_H
#define __REGISTRATION_ALGORITHM_BASE_H

#include "itkObject.h"

#include "itkSimpleFastMutexLock.h"
#include "itkMutexLockHolder.h"

#include "mapAlgorithmIdentificationInterface.h"
#include "mapMacros.h"
#include "mapMAPAlgorithmsExports.h"


#define mapNewAlgorithmMacro(classname) \
	static Pointer New() \
	{ \
		Pointer smartPtr = new classname (); \
		smartPtr->UnRegister(); \
		smartPtr->configureAlgorithm();\
		smartPtr->doneFirstConfiguration();\
		return smartPtr; \
	}

namespace map
{
	namespace algorithm
	{

		/*! @class RegistrationAlgorithmBase
		    @brief Base class for registration algorithms. Does not have input and
		    output dimensions.

		    This class is the base class for generating registration algorithms. Only
		    RegistrationAlgorithm inherits from this.
		    @ingroup Algorithms
		 */
		class MAPAlgorithms_EXPORT RegistrationAlgorithmBase: public ::itk::Object,
			public facet::AlgorithmIdentificationInterface
		{
		public:
			typedef RegistrationAlgorithmBase Self;
			typedef ::itk::Object               Superclass;
			typedef ::itk::SmartPointer<Self>        Pointer;
			typedef ::itk::SmartPointer<const Self>  ConstPointer;
			itkTypeMacro(RegistrationAlgorithmBase, ::itk::Object);

			/*! @brief There are two algorithm types, analytic and iterative ones, which
			    differ from the approach of obtaining the registration.
			 */
			enum AlgorithmType
			{
				ATAnalytic      /*!< analytic algorithm type */,
				ATIterative     /*!< iterative algorithm type */
			};

			/*! @brief Defines the state the algorithm is in
			*/
			struct AlgorithmState
			{
				enum Type
				{
					Pending      /*!< the algorithm has been instanziated and is waiting. */,
					Initializing /*!< the algorithm is about to be initialized, but not yet started*/,
					Running      /*!< the algorithm has been started and is running */,
					Stopping     /*!< the algorithm is ordered to stop */,
					Stopped      /*!< the algorithm has been stopped or is done with its processing */,
					Finalizing   /*!< the algorithm has been is done with its processing and and about to generate the results*/,
					Finalized    /*!< the algorithm has been is done with its processing and has a result*/,
				};
			};

			/*! @brief gets the algorithm's current state
			@eguarantee no fail
			@return returns the state of the algorithm
			*/
			virtual AlgorithmState::Type getCurrentState() const;

			/*! @brief Gets the number of moving dimensions for this registration algorithm
			  @eguarantee no fail
			  @return The number of moving dimensions
			  @sa getTargetDimensions()
			*/
			virtual unsigned int getMovingDimensions() const = 0;

			/*! @brief Gets the number of target dimensions for this registration algorithm
			  @eguarantee no fail
			  @return The number of target dimensions
			  @sa getMovingDimensions()
			*/
			virtual unsigned int getTargetDimensions() const = 0;

			/*! @brief Returns the algorithm type for this registration algorithm
			  @eguarantee no fail
			  @return The algorithm type
			  @sa AlgorithmType
			*/
			virtual AlgorithmType getAlgorithmType() const = 0;

			/*! @brief Enforces the (re)computation of the registration and starts it.
			  @return Indicates of the registration was successfully determined (e.g. could be
			  false if an iterative algorithm was stopped prematurely by the user).
			  @eguarantee strong
			  @post If algorithm is indicated as reusable he is configured identically to its
			   state before this function is called.
			 */
			bool determineRegistration();

			/*! @brief Indicates if the algorithm is designed to be reused. Thus if
			 * it is possible to use one instance to determine several registrations
			 * with the same settings.
			 @eguarantee no fail
			 @retval true An instance can be used several times to determine registrations
			  with the same algorithmic settings.
			 @retval false The algorithm does not guarentee that in the case of several
			  executions the algorithm is correctly initialized for later executions except the first.
			  In this case it is normally necessary to generate an algorithm instance per registration
			  task. Or reset the settings of the algorithm manually.*/
			virtual bool isReusable() const = 0;

		protected:
			/*! @brief sets the algorithm's current state
			and calls onStateChange before;
			@eguarantee strong
			*/
			virtual void setCurrentState(const AlgorithmState::Type& state);

			/*! Method is called when state is going to be changed via setAlgorithmState().
			  Overwrite this method to create special algorithmic behavior. The default implementation
			  does nothing.
			  @eguarantee strong
			  @return returns the success of stopping
			  @retval true if algorithm has been successfully stopped
			  @retval false otherwise
			 */
			virtual void onStateChange(AlgorithmState::Type oldState, AlgorithmState::Type newState) const;

			/*! @brief starts the computation of the registration
			  @eguarantee strong
			  @return Indicates of the registration was successfully determined (e.g. could be
			  false if an iterative algorithm was stopped prematurely by the user).
			 */
			virtual bool doDetermineRegistration() = 0;

			/*! This member is used to implement the basic setup of the algorithm or
			 * of its. properties (e.g. step size, resolution schedule).
			 * @remark this function is called by mapNewAlgorithmMacro() to configure the
			 * basic settings of an algorithm after instance creation.
			 * @remark If an implemented algorithm is specified as reusable, this function
			 * should also ensure the reusability of an algorithm. Thus it is called after algorithm
			* usage to ensure reasonable settings (default or set by user) for the next execution.
			 * @eguarantee strong
			 * @post Algorithm is configured with default settings or the user settings, if provided (and
			 * he is reusable).
			 * @sa mapNewAlgorithmMacro*/
			virtual void configureAlgorithm() = 0;

			/*! Method returns the current value of _firstConfiguration. It is true within the call of mapNewAlgorithmMacro.*/
			bool isFirstConfiguration() const;

			/*! Internal helper function (used by mapNewAlgorithmMacro) to set _firstConfiguration to false.*/
			void doneFirstConfiguration();

			RegistrationAlgorithmBase();
			virtual ~RegistrationAlgorithmBase();

			/*! Methods invoked by ::itk::LightObject::Print().  */
			virtual void PrintSelf(std::ostream& os, ::itk::Indent indent) const;

			/*! mutex used to secure all state changes.
			 */
			::itk::SimpleFastMutexLock _stateLock;

			typedef ::itk::MutexLockHolder< ::itk::SimpleFastMutexLock > StateLockHolderType;

		private:
			/*! the current state of the algorithm (initialized, pausing, ...)
			 */
			AlgorithmState::Type _currentState;

			/*! This member is used to indicate if a algorithm instance is configured the first time.
			 * it is set by mapNewAlgorithmMacro()*/
			bool _firstConfiguration;

			//No copy constructor allowed
			RegistrationAlgorithmBase(const Self& source);
			void operator=(const Self&);  //purposely not implemented
		};

	}
}

#endif
