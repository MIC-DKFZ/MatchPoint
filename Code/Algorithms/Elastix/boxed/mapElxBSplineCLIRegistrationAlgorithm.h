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




#ifndef __MAP_ELX_BSPLINE_CLI_REGISTRATION_ALGORITHM_H
#define __MAP_ELX_BSPLINE_CLI_REGISTRATION_ALGORITHM_H

//MatchPoint
#include "mapContinuous.h"

#include "mapElxCLIRegistrationAlgorithmBase.h"
#include "mapClassMacros.h"

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{

			/*! @class ElxBSplineCLIRegistrationAlgorithm
						@brief The class is a boxed elastix BSpline registration algorithm (using CLI).
						The algorithm has two stages (1. rigid registration, 2. BSpline registration). It uses elastix via CLI and uses auto
						generated parameter files.
			    @ingroup Algorithms
						@ingroup Elastix
						@ingroup Boxed
			 */
			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			class ElxBSplineCLIRegistrationAlgorithm : public
				elastix::CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>
			{
			public:
				typedef ElxBSplineCLIRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy> Self;
				typedef elastix::CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>
				Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;
				itkTypeMacro(ElxBSplineCLIRegistrationAlgorithm, CLIRegistrationAlgorithmBase);
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

			protected:
				ElxBSplineCLIRegistrationAlgorithm();
				virtual ~ElxBSplineCLIRegistrationAlgorithm();

				/*! @reimplemented */
				virtual void prepParameterMaps();
			private:

				ElxBSplineCLIRegistrationAlgorithm(const Self& source);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapElxBSplineCLIRegistrationAlgorithm.tpp"
#endif

#endif
