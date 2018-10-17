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


#ifndef __JOM_PLM_BSPLINE_CLI_REGISTRATION_ALGORITHM_H
#define __JOM_PLM_BSPLINE_CLI_REGISTRATION_ALGORITHM_H

//MatchPoint
#include "mapContinuous.h"

#include "mapPlmCLIRegistrationAlgorithmBase.h"
#include "mapClassMacros.h"

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			/*! @class JOMPlmBSplineCLIRegistrationAlgorithm
						@brief The class is a boxed plastimatch BSpline registration algorithm (using CLI, in many aspects similar to the SLICER PLastimatch BSpline plugin).
						The algorithm has three stages (1. rigid registration, 2./3. BSpline registration). It uses plastimatch via CLI and uses auto
						generated parameter files.
			    @ingroup Algorithms
						@ingroup Plastimatch
						@ingroup Boxed
			 */
      template<class TMovingImage, class TTargetImage, class TMovingPointSet, class TTargetPointSet, class TIdentificationPolicy>
      class JOMPlmBSplineCLIRegistrationAlgorithm : public
        plastimatch::CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>
			{
			public:
        typedef JOMPlmBSplineCLIRegistrationAlgorithm<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy> Self;
        typedef plastimatch::CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TMovingPointSet, TTargetPointSet, TIdentificationPolicy>
				Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;
				itkTypeMacro(JOMPlmBSplineCLIRegistrationAlgorithm, CLIRegistrationAlgorithmBase);
				mapNewAlgorithmMacro(Self);

				typedef typename Superclass::UIDType UIDType;
				typedef typename Superclass::UIDPointer UIDPointer;

				typedef typename Superclass::TargetImageType TargetImageType;
				typedef typename Superclass::MovingImageType MovingImageType;
				typedef typename Superclass::MovingRepresentationDescriptorType MovingRepresentationDescriptorType;
				typedef typename Superclass::TargetRepresentationDescriptorType TargetRepresentationDescriptorType;

				typedef typename Superclass::RegistrationPointer RegistrationPointer;
				typedef typename Superclass::RegistrationType RegistrationType;
				typedef typename Superclass::FieldRepRequirement FieldRepRequirement;

        typedef typename Superclass::MetaPropertyType MetaPropertyType;
        typedef typename Superclass::MetaPropertyPointer MetaPropertyPointer;
        typedef typename Superclass::MetaPropertyNameType MetaPropertyNameType;
        typedef typename Superclass::MetaPropertyVectorType MetaPropertyVectorType;

			protected:
				JOMPlmBSplineCLIRegistrationAlgorithm();
				virtual ~JOMPlmBSplineCLIRegistrationAlgorithm();

				/*! @reimplemented*/
				virtual void configureAlgorithm();

        /*! @reimplemented */
				virtual void prepConfigurationPLM();

				// MetaPropertyAlgorithmBase
				/*! @reimplemented*/
				virtual void compileInfos(MetaPropertyVectorType& infos) const;

				/*! @reimplemented*/
				virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType& name) const;

				/*! @reimplemented*/
				virtual void doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty);

        bool _alignCenter;
        unsigned int _s1_maxIterations;
        ::map::core::String _s1_subsampling;
        unsigned int _s2_maxIterations;
        ::map::core::String _s2_subsampling;
        ::map::core::String _s2_gridSpacing;
        double _s2_regularization;
        bool _doStage3;
        unsigned int _s3_maxIterations;
        ::map::core::String _s3_subsampling;
        ::map::core::String _s3_gridSpacing;
        double _s3_regularization;

			private:

				JOMPlmBSplineCLIRegistrationAlgorithm(const Self& source);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapJOMPlmBSplineCLIRegistrationAlgorithm.tpp"
#endif

#endif
