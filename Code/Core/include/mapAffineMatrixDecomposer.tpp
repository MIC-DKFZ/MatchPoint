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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapAffineMatrixDecomposer.tpp $
*/




#ifndef __AFFINE_MATRIX_DECOMPOSER_TPP
#define __AFFINE_MATRIX_DECOMPOSER_TPP

#include "mapAffineMatrixDecomposer.h"

namespace map
{
	namespace core
	{

		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		bool
		AffineMatrixDecomposer<VInputDimensions, VOutputDimensions>::
		decomposeKernel(const KernelType *pKernel, MatrixType &matrix, OffsetType &offset)
		{
			bool result = false;

			if (!pKernel)
			{
				mapDefaultExceptionStaticMacro( << "Error decomposing affine matrix of kernel. Passed kernel pointer is NULL.");
			};

			const ModelKernelType *pModelKernel = dynamic_cast<const ModelKernelType *>(pKernel);

			if (pModelKernel)
			{
				const TransformType *pTransform = pModelKernel->getTransformModel();
				result = pTransform->getAffineMatrixDecomposition(matrix, offset);
			};

			return result;
		};

	}
}

#endif
