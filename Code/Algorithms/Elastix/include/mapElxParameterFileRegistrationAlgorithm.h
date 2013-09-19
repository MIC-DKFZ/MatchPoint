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




#ifndef __MAP_ELX_PARAMETERFILE_REGISTRATION_ALGORITHM_H
#define __MAP_ELX_PARAMETERFILE_REGISTRATION_ALGORITHM_H

//MatchPoint
#include "mapContinuous.h"

#include "mapElxCLIRegistrationAlgorithmBase.h"
#include "mapClassMacros.h"

namespace map
{
	namespace algorithm
	{
		namespace elastix
		{

			/*! @class ParameterFileRegistrationAlgorithm
						@brief The class is an algorithm that serves as a wrapper for the registration tool "elastix".
						The algorithm uses user specified parameter files to configure elastix. The user can specify the location
						of the parameter files before starting the registration algorithm.
			    @ingroup Algorithms
						@ingroup Elastix
			 */
			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			class ParameterFileRegistrationAlgorithm : public
				CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>
			{
			public:
				typedef ParameterFileRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy> Self;
				typedef CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy>  Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;
				itkTypeMacro(ParameterFileRegistrationAlgorithm, CLIRegistrationAlgorithmBase);
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

				mapGetMetaMacro(ParameterFilePath, core::String);
				mapSetMetaMacro(ParameterFilePath, core::String);

			protected:
				ParameterFileRegistrationAlgorithm();
				virtual ~ParameterFileRegistrationAlgorithm();

				/*! @reimplemented*/
				virtual void compileInfos(MetaPropertyVectorType& infos) const;

				/*! @reimplemented*/
				virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType& name) const;

				/*! @reimplemented*/
				virtual void doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty);

				/* @reimplemented*/
				virtual void configureAlgorithm();

				/*! This method is the slot for the generation of the parameter maps that should be passed to elastix. The base class assumes that
				 after calling this methods the member _parameterMaps contains all parameters for all stages.
				 @eguarantee strong
				*/
				virtual void prepParameterMaps();

				core::String _parameterFilePath;

			private:

				ParameterFileRegistrationAlgorithm(const Self& source);  //purposely not implemented
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapElxParameterFileRegistrationAlgorithm.tpp"
#endif

#endif
