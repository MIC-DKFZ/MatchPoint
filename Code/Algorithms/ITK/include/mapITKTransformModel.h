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




#ifndef __ITK_TRANSFORM_MODEL_H
#define __ITK_TRANSFORM_MODEL_H

namespace map
{
	namespace algorithm
	{
		namespace itk
		{

			/*! @struct ITKTransformModel
			This struct is the master copy for the template specialization.
			It is a dummy and not for practical use. For every itk transform that should be usable with the MatchPoint tranform policies,
			should have a proper specialization of this struct and determining the proper TransformModel that should be used for this special
			class/case.
			To define a model for a special transform use template specialization
			(e.g. template<unsigned int TDim> class ITKTransformModel<itk::MySpecialTransform <TDim> >).
			See also existing specialized ITKTransformModels (e.g. mapITKTranslationTransform.h) for more
			information.
			@template TConcreteITKTranform type of the concrete itk transform controlled by the class
			@ingroup ITK
			@ingroup ITKTranformModel
			*/
			template<class TConcreteITKTranform>
			class ITKTransformModel;
		}
	}
}

#endif
