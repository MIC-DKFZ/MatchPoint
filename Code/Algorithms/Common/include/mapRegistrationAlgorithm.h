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




#ifndef __REGISTRATION_ALGORITHM_H
#define __REGISTRATION_ALGORITHM_H

#include "mapRegistrationAlgorithmBase.h"
#include "mapRegistrationAlgorithmInterface.h"

#include "itkSimpleFastMutexLock.h"


namespace map
{
	namespace algorithm
	{

		/*! @class RegistrationAlgorithm
		    @brief Template class for registration algorithms. Has input and
		    output dimensions.

		    This class is the abstract class for generating registration algorithms,
		    inherited from RegistrationAlgorithmBase and extended with InputDimensions
		    and OutputDimensions. The different concrete RegistrationAlgorithm
		    implementations inherit from this.
		    @ingroup Algorithms
		 */
		template<unsigned int VMovingDimensions, unsigned int VTargetDimensions>
		class RegistrationAlgorithm: public RegistrationAlgorithmBase,
			public facet::RegistrationAlgorithmInterface<VMovingDimensions, VTargetDimensions>
		{
		public:
			typedef RegistrationAlgorithm<VMovingDimensions, VTargetDimensions> Self;
			typedef RegistrationAlgorithmBase      Superclass;
			typedef ::itk::SmartPointer<Self>        Pointer;
			typedef ::itk::SmartPointer<const Self>  ConstPointer;
			itkTypeMacro(RegistrationAlgorithm, RegistrationAlgorithmBase);

			/** Dimension of the algorithm */
			itkStaticConstMacro(MovingDimensions, unsigned int, VMovingDimensions);
			itkStaticConstMacro(TargetDimensions, unsigned int, VTargetDimensions);

			typedef facet::RegistrationAlgorithmInterface<VMovingDimensions, VTargetDimensions>
			RegistrationAlgorithmInterfaceType;
			typedef typename RegistrationAlgorithmInterfaceType::RegistrationType          RegistrationType;
			typedef typename RegistrationAlgorithmInterfaceType::RegistrationPointer       RegistrationPointer;
			typedef typename RegistrationAlgorithmInterfaceType::ConstRegistrationPointer
			ConstRegistrationPointer;

			/*! @brief Gets the number of moving dimensions for this registration algorithm
			  @eguarantee strong
			  @return The number of moving dimensions
			  @sa getTargetDimensions()
			 */
			unsigned int getMovingDimensions() const;

			/*! @brief Gets the number of target dimensions for this registration algorithm
			  @eguarantee strong
			  @return The number of target dimensions
			  @sa getMovingDimensions()
			 */
			unsigned int getTargetDimensions() const;

			/*! Checks if the registration is uptodate. If not the registration becomes (re)computed
			 * the valid registration will be returned.
			  @eguarantee strong
			  @return Smart pointer to the registration instance. May be null if no registration could be
			  computed (determineRegistration returned false).
			  @retval an ITK smart pointer on a specific RegistrationType object
			 */
			RegistrationPointer getRegistration();

			typedef core::FieldRepresentationDescriptor<VMovingDimensions> MovingRepresentationDescriptorType;
			typedef core::FieldRepresentationDescriptor<VTargetDimensions> TargetRepresentationDescriptorType;

			const MovingRepresentationDescriptorType* getMovingRepresentation() const;
			void setMovingRepresentation(const MovingRepresentationDescriptorType* pDescriptor);

			const TargetRepresentationDescriptorType* getTargetRepresentation() const;
			void setTargetRepresentation(const TargetRepresentationDescriptorType* pDescriptor);

		protected:

			/*! @brief returns if the registration should be computed. This default implementation returns true
			 * if the doGetRegistration() returns a null pointer.
			  @eguarantee strong
			  @return true if the registration should be (re)computed. False if the registration is uptodate.
			 */
			virtual bool registrationIsOutdated() const;

			/*! @brief internal virtual method that gets the precomputed registration
			  @remark This method does not compute a registration, the computation is done by doDetermineRegistration()
			  @eguarantee strong
			  @return the registration
			  @retval an ITK smart pointer on a specific RegistrationType object
			 */
			virtual RegistrationPointer doGetRegistration() const = 0;

			/*! Indicates the support region in the moving space required by the algorithm user.
			   Thus, every object covered by the representation descriptor should be mapable by the direct kernel.
			   If set to null, the support region should not be limited.*/
			typename MovingRepresentationDescriptorType::ConstPointer _spMovingRepresentation;
			/*! Indicates the support region in the target space required by the algorithm user.
			   Thus, every object covered by the representation descriptor should be mapable by the inverse kernel.
			   If set to null, the support region should not be limited.*/
			typename TargetRepresentationDescriptorType::ConstPointer _spTargetRepresentation;

			/*! This method is called by setMovingRepresentation() before the new representation is set.
			 * This default implementation does nothing.
			 * @param [in] pMovingRepresentation Pointer to the new representation.*/
			virtual void doBeforeSetMovingRepresentation(const MovingRepresentationDescriptorType*
					pMovingRepresentation);
			/*! This method is called by setMovingRepresentation() after the new representation is set.
			 * This default implementation does nothing.*/
			virtual void doAfterSetMovingRepresentation();

			/*! This method is called by setTargetRepresentation() before the new representation is set.
			 * This default implementation does nothing.
			 * @param [in] pTargetRepresentation Pointer to the new representation.*/
			virtual void doBeforeSetTargetRepresentation(const TargetRepresentationDescriptorType*
					pTargetRepresentation);
			/*! This method is called by setTargetRepresentation() after the new representation is set.
			 * This default implementation does nothing.*/
			virtual void doAfterSetTargetRepresentation();

			/*! This method is called by getMovingRepresentation() before the representation is returned.
			 * This default implementation does nothing.*/
			virtual void doBeforeGetMovingRepresentation() const;
			/*! This method is called by getTargetRepresentation() after the representation is returned.
			 * This default implementation does nothing.*/
			virtual void doBeforeGetTargetRepresentation() const;

			/*! The lock is used to manage the access to determination of a registration
			 * and write acces to all members that are relevant for determination of a registration
			 */
			mutable ::itk::SimpleFastMutexLock _determinationLock;

			RegistrationAlgorithm();
			virtual ~RegistrationAlgorithm();

		private:
			RegistrationAlgorithm(const Self& source);  //purposely not implemented
			void operator=(const Self&);  //purposely not implemented

		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapRegistrationAlgorithm.tpp"
#endif

#endif
