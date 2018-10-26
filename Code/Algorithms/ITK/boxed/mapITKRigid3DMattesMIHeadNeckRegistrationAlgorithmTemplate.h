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


#ifndef __MAP_ITK_RIGID_MMI_HEADNECK_REGISTRATION_ALGORITHM_H
#define __MAP_ITK_RIGID_MMI_HEADNECK_REGISTRATION_ALGORITHM_H

#include "mapITKEuler3DMattesMIMultiResRegistrationAlgorithmTemplate.h"

namespace map
{
	namespace algorithm
	{
		namespace boxed
		{
				/** \class MultiModalRigidHeadNeckRegistrationAlgorithm
				* \ingroup Data_image MetaProperty Model_rigid Det_comp_iterative Det_stochastic Det_res_multi Dim_3D_3D Mod_multi PreInit_Geo
				* Algorithm is used for special cases where a head image should be registered onto a head/neck image (target image). It skips the lower part of
					* the target image if a preinitialization (via geometric center or centroid) is used, to establish a better initialization. By default initializes via geometric centers.
				*/
      template <class TImageType, 
        class TIdentificationPolicy, 
        class TInterpolatorPolicy =
        SealedFixedInterpolatorPolicyMacro< ::itk::LinearInterpolateImageFunction<TImageType, map::core::continuous::ScalarType> >,
        class TPyramideInitializationPolicy = algorithm::itk::NoComponentInitializationPolicy>
				class MultiModalRigidHeadNeckRegistrationAlgorithm :
					public map::algorithm::boxed::ITKEuler3DMattesMIMultiResRegistrationAlgorithm<TImageType, TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>
				{
				public:
					typedef MultiModalRigidHeadNeckRegistrationAlgorithm Self;

                    typedef ITKEuler3DMattesMIMultiResRegistrationAlgorithm<TImageType, TImageType, TIdentificationPolicy, TInterpolatorPolicy, TPyramideInitializationPolicy>
					Superclass;

					typedef ::itk::SmartPointer<Self>                                     Pointer;
					typedef ::itk::SmartPointer<const Self>                               ConstPointer;

					itkTypeMacro(MultiModalRigidHeadNeckRegistrationAlgorithm,
								 ITKEuler3DMattesMIMultiResRegistrationAlgorithm);
					mapNewAlgorithmMacro(Self);

				protected:
					MultiModalRigidHeadNeckRegistrationAlgorithm();
					virtual ~MultiModalRigidHeadNeckRegistrationAlgorithm();

          void configureAlgorithm();
					void doInterLevelSetup();
          void prepInitializeTransformation();

				private:

					MultiModalRigidHeadNeckRegistrationAlgorithm(const Self& source);  //purposely not implemented
					void operator=(const Self&); //purposely not implemented
				};
		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapITKRigid3DMattesMIHeadNeckRegistrationAlgorithmTemplate.tpp"
#endif


#endif
