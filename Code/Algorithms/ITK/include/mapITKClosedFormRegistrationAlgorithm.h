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




#ifndef __ITK_CLOSED_FORM_REGISTRATION_ALGORITHM_H
#define __ITK_CLOSED_FORM_REGISTRATION_ALGORITHM_H

#include "itkLandmarkBasedTransformInitializer.h"

#include "mapContinuous.h"

#include "mapArbitraryTransformPolicy.h"
#include "mapPointSetRegistrationAlgorithmBase.h"
#include "mapObserverSentinel.h"
#include "mapRegistrationAlgorithm.h"
#include "mapAnalyticAlgorithmInterface.h"


/*! @namespace map The namespace map is used throughout the MatchPoint project to
mark code as components of this project
*/
namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @class ITKClosedFormRegistrationAlgorithm
			@brief The class implements the possibility of point set registration by a closed form solution
			The algorithm allows to perform the determination of a point set registration via closed form solution.
			The solution is based on Berthold K. P. Horn (1987), "Closed-form solution of absolute orientation using unit quaternions,"
			http://people.csail.mit.edu/bkph/papers/Absolute_Orientation.pdf.
			@ingroup Algorithms
			*/
			template < class TMovingPointSet, class TTargetPointSet, class TITKTransform,
					 class TIdentificationPolicy >
			class ITKClosedFormRegistrationAlgorithm : public
				RegistrationAlgorithm<TMovingPointSet::PointDimension, TTargetPointSet::PointDimension>,
			public PointSetRegistrationAlgorithmBase<TMovingPointSet, TTargetPointSet>,
			public facet::AnalyticAlgorithmInterface,
			public TIdentificationPolicy
			{
			public:
				typedef ITKClosedFormRegistrationAlgorithm<TMovingPointSet, TTargetPointSet, TITKTransform, TIdentificationPolicy>
				Self;
				typedef RegistrationAlgorithm<TMovingPointSet::PointDimension, TTargetPointSet::PointDimension>
				Superclass;
				typedef TIdentificationPolicy IdentificationPolicyType;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;
				itkTypeMacro(ITKClosedFormRegistrationAlgorithm, RegistrationAlgorithm);
				mapNewAlgorithmMacro(Self);

				typedef TITKTransform TransformModelType;

				typedef typename Superclass::UIDType UIDType;
				typedef typename Superclass::UIDPointer UIDPointer;
				typedef typename RegistrationAlgorithmBase::AlgorithmType AlgorithmType;
				typedef typename Superclass::MovingRepresentationDescriptorType MovingRepresentationDescriptorType;
				typedef typename Superclass::TargetRepresentationDescriptorType TargetRepresentationDescriptorType;
				typedef typename Superclass::RegistrationPointer RegistrationPointer;
				typedef typename Superclass::RegistrationType RegistrationType;
				typedef typename Superclass::FieldRepRequirement FieldRepRequirement;

				mapDefineAlgorithmIdentificationByPolicyMacro;

				/*! @brief Returns the algorithm type for this registration algorithm
				@eguarantee strong
				@return The algorithm type
				*/
				virtual AlgorithmType getAlgorithmType() const;

				virtual typename FieldRepRequirement::Type isMovingRepresentationRequired() const;

				virtual typename FieldRepRequirement::Type isTargetRepresentationRequired() const;

				/*! @reimplemented */
				virtual bool isReusable() const;

			protected:
				ITKClosedFormRegistrationAlgorithm();
				virtual ~ITKClosedFormRegistrationAlgorithm();

                typedef ::itk::LandmarkBasedTransformInitializer < TransformModelType,
						typename core::discrete::Elements<TTargetPointSet::PointDimension>::InternalImageType,
						typename core::discrete::Elements<TMovingPointSet::PointDimension>::InternalImageType >
						InternalSolverMethodType;

				/* @reimplemented*/
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

				template <typename TPointSet, typename TLandmarks>
				static void convertPointSetToLandmarks(const TPointSet* pointSet, TLandmarks& lms)
				{
					lms.clear();

					typename TPointSet::PointsContainerConstIterator pointIter = pointSet->GetPoints()->Begin();
					typename TPointSet::PointsContainerConstIterator pointEnd = pointSet->GetPoints()->End();

					while (pointIter != pointEnd)
					{
						typename TPointSet::PointType currentPoint = pointIter.Value();
						lms.push_back(currentPoint);

						++pointIter;
					}
				};

				void finalizeAlgorithm();

				/*! Returns if the registration should be computed. The registration is outdated if doGetRegistration returns null
				* or the modification times of at least one policy is newer then the modification time of the registration.
				@eguarantee strong
				@return true if the registration should be (re)computed. False if the registration is uptodate.
				*/
				virtual bool registrationIsOutdated() const;

				/*! Methods invoked by derivated classes.  */
				virtual void PrintSelf(std::ostream& os, ::itk::Indent indent) const;

			private:
				typename InternalSolverMethodType::Pointer _internalSolver;

				/*! Smartpointer to the finalized registration. Will be set by finalizeAlgorithm()*/
				typename RegistrationType::Pointer _spFinalizedRegistration;
				typename TransformModelType::Pointer _spTransform;

				ITKClosedFormRegistrationAlgorithm(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKClosedFormRegistrationAlgorithm.tpp"
#endif

#endif
