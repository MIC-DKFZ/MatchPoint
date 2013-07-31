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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Common/boxed/mapDummyImageRegistrationAlgorithm.h $
*/




#ifndef __DUMMY_IMAGE_REGISTRATION_ALGORITHM_H
#define __DUMMY_IMAGE_REGISTRATION_ALGORITHM_H

#include "mapContinuous.h"

#include "mapAnalyticAlgorithmInterface.h"
#include "mapImageRegistrationAlgorithmBase.h"
#include "mapRegistrationAlgorithm.h"

/*! @namespace map The namespace map is used throughout the MatchPoint project to
    mark code as components of this project
 */
namespace map
{
	namespace algorithm
	{

		mapGenerateAlgorithmUIDPolicyMacro(DummyImageRegistrationUIDPolicy, "de.dkfz.matchpoint", "Dummy", "1.0.0");

		/*! @class DummyImageRegistrationAlgorithm
		    @brief This is a simple image registration algorithm that does nothing.
		    The algorithm determines a registration that has an identity transform no
		    matter what image you pass to him. This class can be used for testing purposes
		    or if you want to check in a evaluation what the outcome is if nothing is changed.
		    @ingroup Boxed
		 */
		template < class TMovingImage, class TTargetImage,
		         class TIdentificationPolicy = DummyImageRegistrationUIDPolicy >
		class DummyImageRegistrationAlgorithm : public facet::AnalyticAlgorithmInterface,
			public ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>,
			public RegistrationAlgorithm<TMovingImage::ImageDimension, TTargetImage::ImageDimension>
		{
		public:
			typedef DummyImageRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy> Self;
			typedef RegistrationAlgorithm<TMovingImage::ImageDimension, TTargetImage::ImageDimension> Superclass;

			typedef ::itk::SmartPointer<Self>                                     Pointer;
			typedef ::itk::SmartPointer<const Self>                               ConstPointer;
			itkTypeMacro(DummyImageRegistrationAlgorithm, RegistrationAlgorithm);
			mapNewAlgorithmMacro(Self);

			typedef TIdentificationPolicy IdentificationPolicyType;
			typedef typename Superclass::FieldRepRequirement FieldRepRequirement;
			typedef typename Superclass::UIDPointer UIDPointer;
			typedef typename Superclass::AlgorithmType AlgorithmType;
			typedef typename Superclass::RegistrationType RegistrationType;
			typedef typename Superclass::RegistrationPointer RegistrationPointer;

			static UIDPointer UID();

			virtual UIDPointer getUID() const;

			/*! @brief Returns the algorithm type for this registration algorithm
			  @eguarantee strong
			  @return The algorithm type
			 */
			virtual AlgorithmType getAlgorithmType() const;

			virtual typename FieldRepRequirement::Type isMovingRepresentationRequired() const;

			virtual typename FieldRepRequirement::Type isTargetRepresentationRequired() const;

			virtual bool isReusable() const;

		protected:
			DummyImageRegistrationAlgorithm();
			virtual ~DummyImageRegistrationAlgorithm();

			virtual void configureAlgorithm();

			/*! @brief starts the computation of the registration
			  @eguarantee strong
			  @return Indicates of the registration was successfully determined (e.g. could be
			  false if an iterative algorithm was stopped prematurely by the user).
			 */
			virtual bool doDetermineRegistration();

			/*!
			 * Returns the final registration
			  @eguarantee strong
			 */
			virtual RegistrationPointer doGetRegistration() const;

			/*! Returns if the registration should be computed. The registration is outdated if doGetRegistration returns null
			 * or the modification times of at least one policy is newer then the modification time of the registration.
			  @eguarantee strong
			  @return true if the registration should be (re)computed. False if the registration is uptodate.
			 */
			virtual bool registrationIsOutdated() const;

			/*! Methods invoked by derivated classes.  */
			virtual void PrintSelf(std::ostream &os, ::itk::Indent indent) const;

		private:

			RegistrationPointer _spFinalizedRegistration;

			DummyImageRegistrationAlgorithm(const Self &source);
			void operator=(const Self &); //purposely not implemented
		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapDummyImageRegistrationAlgorithm.tpp"
#endif

#endif
