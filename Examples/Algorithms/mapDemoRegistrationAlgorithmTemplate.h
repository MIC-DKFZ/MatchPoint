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

//----------------------------------------------------------
// !!!EXPERIMENTAL CODE!!!
//
// This code may not be used for release.
// Add #define SIDT_ENFORCE_MATURE_CODE to any release module
// to ensure this policy.
//----------------------------------------------------------

/***********************************************************
* Demo: demoRegistrationAlgorithm
* Topics:
* - "reboxing" of an algorithm?
* - special initial parameters?
*
* Algorithms in MatchPoint can normally be configured via
* policies. This allows to choose between arbitrary dynamic
* settings of algorithms in run time and the fixed
* initialization while compile time.
* For example itk based registration algorithms have a
* policy for each component to control the access to the
* component.\n
* Initial values are set at compile time via reimplementing
* the member configureAlgorithm() or via user interaction
* (e.g. public setter or MetaPropertyAlgorithmInterface).
***********************************************************/

#ifdef SIDT_ENFORCE_MATURE_CODE
#error "This code is marked as experimental code. It must not be used because this build enforces mature code."
#endif
#ifndef SIDT_CONTAINS_EXPERIMENTAL_CODE
#define SIDT_CONTAINS_EXPERIMENTAL_CODE 1
#endif

#ifndef __MAP_DEMO_REGISTRATION_ALGORITHM_TEMPLATE_H
#define __MAP_DEMO_REGISTRATION_ALGORITHM_TEMPLATE_H


#include "mapTransMSRegistrationAlgorithmTemplate.h"

namespace
{
	const char* const DemoRegistrationAlgorithm_profile =
		"<Profile><Description>A simple Mattes MI based image registration algorithm just supporting translation.</Description><Contact>Ralf Floca; sbr@dkfz-heidelberg.de</Contact><Characteristics><DataType>Image</DataType><TransformModel>translation</TransformModel><TransformDomain>global</TransformDomain><Metric>Mean square difference</Metric><Optimization>Regular Step Gradient Descent</Optimization></Characteristics><Keywords><Keyword>basic</Keyword></Keywords></Profile>";
	mapGenerateAlgorithmUIDPolicyMacro(DemoRegistrationAlgorithmUIDPolicy, "de.dkfz.matchpoint.test",
									   "DemoRegistrationAlgorithm", "1.0.0", DemoRegistrationAlgorithm_profile);
}

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{
			/*! @class DemoRegistrationAlgorithm
			* Boxed registration algorithm used in the MatchPoint examples and an example for "reboxing"
			* In this case we take the RigidMSRegistrationAlgorithm, because it perfectly fits our needs
			* and just adapt the initialization of the optimizer component in the constructor in our new
			* Algorithm class. All other components stay untouched. In Addition the
			* UID policy is changed, because the reboxed algorithm should have its own unique identifier.
			*/
			template <class TMovingImage, class TTargetImage = TMovingImage, typename TUIDPolicy = DemoRegistrationAlgorithmUIDPolicy>
			class DemoRegistrationAlgorithm: public
				map::algorithm::boxed::TransMSRegistrationAlgorithmTemplate<TMovingImage, TTargetImage, TUIDPolicy>::Type
			{
			public:
				typedef DemoRegistrationAlgorithm Self;

				typedef typename
				map::algorithm::boxed::TransMSRegistrationAlgorithmTemplate<TMovingImage, TTargetImage, TUIDPolicy>::Type
				Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;

				itkTypeMacro(DemoRegistrationAlgorithm, TransMSRegistrationAlgorithmTemplate);
				mapNewAlgorithmMacro(Self);

			protected:
				DemoRegistrationAlgorithm()
				{
				};

				virtual void configureAlgorithm()
				{
					Superclass::configureAlgorithm();
					this->getConcreteITKOptimizer()->SetMaximumStepLength(4.00);
					this->getConcreteITKOptimizer()->SetMinimumStepLength(0.01);
					this->getConcreteITKOptimizer()->SetNumberOfIterations(200);
				}

				virtual ~DemoRegistrationAlgorithm()
				{
				};

			private:

				DemoRegistrationAlgorithm(const Self& source);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented

			};

		}
	}
}


#endif
