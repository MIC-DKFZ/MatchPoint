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


#ifndef __MAP_RIGID_3D_CLOSED_FORM_REGISTRATION_ALGORITHM_H
#define __MAP_RIGID_3D_CLOSED_FORM_REGISTRATION_ALGORITHM_H

#include "mapITKClosedFormRegistrationAlgorithm.h"

#include "itkVersorRigid3DTransform.h"


namespace map
{
	namespace algorithm
	{

		namespace boxed
		{
			const char* const DefaultITKRigid3DClosedForm_profile =
				"<Profile><Description>Simple 3D rigid (translation and euler angles) registration algorithm using point sets pairs and a closed form solution. It assumes that both given point sets are sorted by pair index.</Description><Contact>Ralf Floca; sbr@dkfz-heidelberg.de</Contact><Characteristics><DataType>Points</DataType><ComputationStyle>analytic</ComputationStyle><Deterministic/><DimMoving>3</DimMoving><DimTarget>3</DimTarget><TransformModel>rigid</TransformModel><TransformDomain>global</TransformDomain></Characteristics><Keywords><Keyword>basic</Keyword></Keywords></Profile>";
			mapGenerateAlgorithmUIDPolicyMacro(DefaultITKRigid3DClosedFormRegistrationAlgorithmUIDPolicy,
											   "de.dkfz.matchpoint", "ITKRigid3DClosedFormRegistrationAlgorithm.default", "1.0.0",
											   DefaultITKRigid3DClosedForm_profile);

			/** @brief Boxing of a closed form 3D rigid registration algorithm
			 @ingroup Boxed
			*/
			template < class TPointSet = core::continuous::Elements<3>::InternalPointSetType,
					 class TIdentificationPolicy = DefaultITKRigid3DClosedFormRegistrationAlgorithmUIDPolicy >
			struct ITKRigid3DClosedFormRegistrationAlgorithmTemplate
			{
public:
				//optional
				typedef ::itk::VersorRigid3DTransform< map::core::continuous::ScalarType> TransformType;

				//default typdefs
				typedef map::algorithm::itk::ITKClosedFormRegistrationAlgorithm<TPointSet, TPointSet, TransformType, TIdentificationPolicy>
				Type;
				typedef typename Type::Pointer Pointer;
			};
		}
	}
}


#endif
