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




#ifndef __AFFINE_MATRIX_DECOMPOSER_H
#define __AFFINE_MATRIX_DECOMPOSER_H

#include "mapRegistrationKernelBase.h"

namespace map
{
	namespace core
	{

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		struct AffineMatrixDecomposer
		{
		public:

			typedef RegistrationKernelBase<VInputDimensions, VOutputDimensions> KernelType;
      typedef typename KernelType::TransformType TransformType;
			typedef typename TransformType::MatrixType MatrixType;
			typedef typename TransformType::OutputVectorType OffsetType;


			/*! Convinient function that tries to get the internals of the kernel as a affine matrix
			 * decomposition. The function checks if the passed kernel is a ModelBasedKernel. If thats
			 * true it checks if it can retrieve a decompostion.
			 * The decomposistion seperates the transform model into an affine matrix and an offset.
			 * It is indecated by the return value if the actual model can be decomposed.\n
			 * Usage of the return values: Point_trans = Matrix*Point + Offset
			 *
			 * @eguarantee strong
			 * @pre pKernel musst point to a valid instance.
			 * @param [in] Pointer to the kernel that should be decomposed.
			 * @param [out] matrix Referenz to the matrix that define the affine non-translation part (e.g. rotation and scaling).
			 * @param [out] offset Referenz to a vector that defines the translation offset.
			 * @return Indicates if the transform model can be decomposed in a affine transformation matrix plus offset. If it returns false, it cannot be decomposed
			 * and the referenced output parameters are invalid.*/
			static bool decomposeKernel(const KernelType* pKernel, MatrixType& matrix, OffsetType& offset);
		};

	}
}

#ifndef MatchPoint_MANUAL_TPP
# include "mapAffineMatrixDecomposer.tpp"
#endif

#endif
