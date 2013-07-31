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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Examples/Algorithms/mapDemoPropertiedAlgorithm.h $
*/

//----------------------------------------------------------
// !!!EXPERIMENTAL CODE!!!
//
// This code may not be used for release.
// Add #define SIDT_ENFORCE_MATURE_CODE to any release module
// to ensure this policy.
//----------------------------------------------------------

/***********************************************************
* Demo: demoProperitedAlgorithm
* Topics:
* - "Advanced reboxing" of an algorithm
* - Generic access to properties of an algorithm
* - Implementing a MetaProperty interface for an algorithm
* - Regarding MAP_SEAL_ALGORITHMS in context of
* properties
*
* The reboxing of algorithm by simply defining a policy,
* and reimplementing members has been shown in
* demoRegistrationAlgorithmTemplate.
* This example shows how to perform greater refinements
* on an algorithm.\n\n
* The MetaProperty interface will be "activated".
* in the demoRegistrationAlgorithm. The used superclass
* already defined the interface (MetaPropertyAlgorithmInterface)
* but has not defined any properties. In this example several
* properties will be defined that can be accessed via the
* MetaPropertyAlgorithmInterface.
* The example also shows how to restrict the access to
* properties depending on the fact that the algorithm is
* sealed or not. The defined properties
* in this example class will only be accessible via the
* interface as long as MAP_SEAL_ALGORITHMS is not defined,
* thus as long the algorithms are not built sealed.
***********************************************************/

#ifdef SIDT_ENFORCE_MATURE_CODE
#error "This code is marked as experimental code. It must not be used because this build enforces mature code."
#endif
#ifndef SIDT_CONTAINS_EXPERIMENTAL_CODE
#define SIDT_CONTAINS_EXPERIMENTAL_CODE 1
#endif

#ifndef __MAP_DEMO_PROPERTIED_ALGORITHM_TEMPLATE_H
#define __MAP_DEMO_PROPERTIED_ALGORITHM_TEMPLATE_H


#include "mapDemoRegistrationAlgorithmTemplate.h"

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{
			mapGenerateAlgorithmUIDPolicyMacro(DemoPropertiedAlgorithmUIDPolicy, "MatchPoint::Test", "DemoPropertiedAlgorithm.default", "1.0.0");

			template <class TMovingImage, class TTargetImage = TMovingImage, typename TUIDPolicy = DemoRegistrationAlgorithmUIDPolicy>
			class DemoPropertiedAlgorithm : public DemoRegistrationAlgorithm<TMovingImage, TTargetImage, TUIDPolicy>
			{
			public:
				typedef DemoPropertiedAlgorithm<TMovingImage, TTargetImage, TUIDPolicy> Self;
				typedef DemoRegistrationAlgorithm<TMovingImage, TTargetImage, TUIDPolicy>  Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;

				itkTypeMacro(DemoPropertiedAlgorithm, DemoRegistrationAlgorithm);
				mapNewAlgorithmMacro(Self);

				typedef ::itk::Array<double> ParametersType;

				typedef typename Superclass::MetaPropertyType MetaPropertyType;
				typedef typename Superclass::MetaPropertyPointer MetaPropertyPointer;
				typedef typename Superclass::MetaPropertyNameType MetaPropertyNameType;
				typedef typename Superclass::MetaPropertyVectorType MetaPropertyVectorType;

			protected:
				DemoPropertiedAlgorithm();
				virtual ~DemoPropertiedAlgorithm();

				virtual void compileInfos(MetaPropertyVectorType &infos) const;

				virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType &name) const;

				virtual void doSetProperty(const MetaPropertyNameType &name, const MetaPropertyType *pProperty);

			private:

				DemoPropertiedAlgorithm(const Self &source);  //purposely not implemented
				void operator=(const Self &); //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapDemoPropertiedAlgorithm.tpp"
#endif

#endif
