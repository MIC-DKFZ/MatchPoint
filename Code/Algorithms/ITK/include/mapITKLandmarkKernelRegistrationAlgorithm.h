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




#ifndef __ITK_LANDMARK_KERNEL_REGISTRATION_ALGORITHM_H
#define __ITK_LANDMARK_KERNEL_REGISTRATION_ALGORITHM_H

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

			/*! @class ITKLandmarkKernelRegistrationAlgorithm
			@brief The class implements a "registration" algorithm that initializes its transformation model.
			This algorithm is a analytic approach that assumes that the transform model in conjunction with the
			a moving and a target landmark set is sufficient to establish a registration.
			@remark this algorithm can only be used with transforms that derive from itk::KernelTransform (e.g. ElasticBodySplineKernelTransform).
			@ingroup Algorithms
			*/
			template < class TPointSet, class TITKTransform,
					 class TIdentificationPolicy >
			class ITKLandmarkKernelRegistrationAlgorithm : public
				RegistrationAlgorithm<TPointSet::PointDimension, TPointSet::PointDimension>,
			public PointSetRegistrationAlgorithmBase<TPointSet, TPointSet>,
			public TIdentificationPolicy,
			public facet::AnalyticAlgorithmInterface
			{
			public:
				typedef ITKLandmarkKernelRegistrationAlgorithm<TPointSet, TITKTransform, TIdentificationPolicy>
				Self;
				typedef RegistrationAlgorithm<TPointSet::PointDimension, TPointSet::PointDimension>  Superclass;
				typedef TIdentificationPolicy IdentificationPolicyType;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;
				itkTypeMacro(ITKLandmarkKernelRegistrationAlgorithm, RegistrationAlgorithm);
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

				/** Stiffness of the spline.  A stiffness of zero results in the
				* standard interpolating spline.  A non-zero stiffness allows the
				* spline to approximate rather than interpolate the landmarks.
				* Stiffness values are usually rather small, typically in the range
				* of 0.001 to 0.1. The approximating spline formulation is based on
				* the short paper by R. Sprengel, K. Rohr, H. Stiehl. "Thin-Plate
				* Spline Approximation for Image Registration". In 18th
				* International Conference of the IEEE Engineering in Medicine and
				* Biology Society. 1996.
				*/
				itkSetClampMacro(Stiffness, double, 0.0, ::itk::NumericTraits<double>::max());
				itkGetConstMacro(Stiffness, double);

				/** Set if the transformation kernel of the result should be stored as the transform
				* or as a vector field*/
				itkSetMacro(GenerateField, bool);
				itkGetConstMacro(GenerateField, bool);
				itkBooleanMacro(GenerateField);

				virtual typename FieldRepRequirement::Type isMovingRepresentationRequired() const;

				virtual typename FieldRepRequirement::Type isTargetRepresentationRequired() const;

				/*! @reimplemented */
				virtual bool isReusable() const;

			protected:
				ITKLandmarkKernelRegistrationAlgorithm();
				virtual ~ITKLandmarkKernelRegistrationAlgorithm();

				double m_Stiffness;
				bool m_GenerateField;

				/*! @reimplemented*
				This default implementation does nothing.
				*/
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

				void finalizeAlgorithm();

				/*! Returns if the registration should be computed. The registration is outdated if doGetRegistration returns null
				* or the modification times of at least one policy is newer then the modification time of the registration.
				@eguarantee strong
				@return true if the registration should be (re)computed. False if the registration is uptodate.
				*/
				virtual bool registrationIsOutdated() const;

				/*! Methods invoked by derivated classes.  */
				virtual void PrintSelf(std::ostream& os, ::itk::Indent indent) const;

				static void convertPointSetToKernelPointSet(const TPointSet* ps,
						typename TITKTransform::PointSetPointer& kernelPS);

			private:
				/*! Smartpointer to the finalized registration. Will be set by finalizeAlgorithm()*/
				typename RegistrationType::Pointer _spFinalizedRegistration;
				typename TransformModelType::Pointer _spTransform;

				ITKLandmarkKernelRegistrationAlgorithm(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKLandmarkKernelRegistrationAlgorithm.tpp"
#endif

#endif
