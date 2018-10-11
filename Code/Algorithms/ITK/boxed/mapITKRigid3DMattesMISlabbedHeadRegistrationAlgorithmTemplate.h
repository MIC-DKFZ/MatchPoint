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


#ifndef __MAP_ITK_RIGID_MMI_SLABBED_HEAD_REGISTRATION_ALGORITHM_H
#define __MAP_ITK_RIGID_MMI_SLABBED_HEAD_REGISTRATION_ALGORITHM_H

#include "mapITKEuler3DMattesMIMultiResRegistrationAlgorithmTemplate.h"

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{
				/** \class MultiModalRigidSlabbedHeadRegistrationAlgorithm
				* \ingroup Data_image MetaProperty Model_rigid Det_comp_iterative Det_stochastic Det_res_multi Dim_3D_3D Mod_multi PreInit_Geo
				* Algorithm is used to solve a special case of head registration problems.
				* It is configured to register the slabbed MRI head data (thus date where only a part of the head is visible) onto whole Head images
				* (e.g.CT planning data).
				* Uses 3 Resolution levels. By default initializes via image centers
				*/
      template <class TImageType,
        class TIdentificationPolicy,
        class TInterpolatorPolicy = SealedFixedInterpolatorPolicyMacro< ::itk::LinearInterpolateImageFunction<TImageType, map::core::continuous::ScalarType> >,
        class TPyramideInitializationPolicy = algorithm::itk::NoComponentInitializationPolicy>
				class MultiModalRigidSlabbedHeadRegistrationAlgorithm :
					public map::algorithm::boxed::ITKEuler3DMattesMIMultiResRegistrationAlgorithm<TImageType, TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>
				{
				public:
					typedef MultiModalRigidSlabbedHeadRegistrationAlgorithm Self;

					typedef typename ITKEuler3DMattesMIMultiResRegistrationAlgorithm<TImageType, TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>
					Superclass;

					typedef ::itk::SmartPointer<Self>                                     Pointer;
					typedef ::itk::SmartPointer<const Self>                               ConstPointer;

					itkTypeMacro(MultiModalRigidSlabbedHeadRegistrationAlgorithm,
								 ITKEuler3DMattesMIMultiResRegistrationAlgorithm);
					mapNewAlgorithmMacro(Self);

				protected:
          MultiModalRigidSlabbedHeadRegistrationAlgorithm();
					virtual ~MultiModalRigidSlabbedHeadRegistrationAlgorithm();
          
          void configureAlgorithm();
          void doInterLevelSetup();

				private:

          MultiModalRigidSlabbedHeadRegistrationAlgorithm(const Self& source);  //purposely not implemented
					void operator=(const Self&); //purposely not implemented
				};
		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKRigid3DMattesMISlabbedHeadRegistrationAlgorithmTemplate.tpp"
#endif

#endif
