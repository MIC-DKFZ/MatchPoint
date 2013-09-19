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


#include "vnl/vnl_det.h"
#include "vnl/vnl_inverse.h"

#include "mapFSLHelper.h"

namespace map
{
	namespace algorithm
	{
		namespace fsl
		{
			MatrixConverter<3>::MatrixType
			MatrixConverter<3>::
			convertFSLToRAS(const MatrixType& fslMatrix, const DescriptorType* targetDesc,
							const DescriptorType* movingDesc)
			{
				MatrixType tSpacing, mSpacing, tSwap, mSwap, tRSAMatrix, mRSAMatrix, result;

				// Set the target/mov matrices
				tRSAMatrix = convertVoxelSpaceToRASPhysicalSpaceMatrix(targetDesc).GetVnlMatrix();
				mRSAMatrix = convertVoxelSpaceToRASPhysicalSpaceMatrix(movingDesc).GetVnlMatrix();

				// Set the swap matrices
				tSwap.set_identity(); //swap for target space

				if (vnl_det(tRSAMatrix) > 0)
				{
					tSwap(0, 0) = -1.0;
					tSwap(0, 3) = targetDesc->getSize()[0];
				}

				mSwap.set_identity(); //swap for moving space

				if (vnl_det(mRSAMatrix) > 0)
				{
					mSwap(0, 0) = -1.0;
					mSwap(0, 3) = movingDesc->getSize()[0];
				}

				// Set the spacing matrices
				tSpacing.set_identity();
				mSpacing.set_identity();

				for (size_t i = 0; i < 3; i++)
				{
					tSpacing(i, i) = targetDesc->getSpacing()[i];
					mSpacing(i, i) = movingDesc->getSpacing()[i];
				}

				result =
					mRSAMatrix * vnl_inverse(mSpacing) * mSwap *
					vnl_inverse(fslMatrix) *
					tSwap * tSpacing * vnl_inverse(tRSAMatrix);

				return result;
			}

			MatrixConverter<3>::MatrixType
			MatrixConverter<3>::
			convertRASToITKTrans(const MatrixType& rsaMatrix)
			{
				// Get the current matrix
				MatrixType result = rsaMatrix;

				// Flip the entries that must be flipped
				result(2, 0) *= -1;
				result(2, 1) *= -1;
				result(0, 2) *= -1;
				result(1, 2) *= -1;
				result(0, 3) *= -1;
				result(1, 3) *= -1;


				return result;
			};

			MatrixConverter<2>::MatrixType
			MatrixConverter<2>::
			convertFSLToRAS(const MatrixType& fslMatrix, const DescriptorType* targetDesc,
							const DescriptorType* movingDesc)
			{
				MatrixType tSpacing, mSpacing, tSwap, mSwap, tRSAMatrix, mRSAMatrix, result;

				// Set the target/mov matrices
				tRSAMatrix = convertVoxelSpaceToRASPhysicalSpaceMatrix(targetDesc).GetVnlMatrix();
				mRSAMatrix = convertVoxelSpaceToRASPhysicalSpaceMatrix(movingDesc).GetVnlMatrix();

				// Set the swap matrices
				tSwap.set_identity(); //swap for target space

				if (vnl_det(tRSAMatrix) > 0)
				{
					tSwap(0, 0) = -1.0;
				}

				mSwap.set_identity(); //swap for moving space

				if (vnl_det(mRSAMatrix) > 0)
				{
					mSwap(0, 0) = -1.0;
				}

				// Set the spacing matrices
				tSpacing.set_identity();
				mSpacing.set_identity();

				for (size_t i = 0; i < 2; i++)
				{
					tSpacing(i, i) = targetDesc->getSpacing()[i];
					mSpacing(i, i) = movingDesc->getSpacing()[i];
				}

				result =
					mRSAMatrix * vnl_inverse(mSpacing) * mSwap *
					vnl_inverse(fslMatrix) *
					tSwap * tSpacing * vnl_inverse(tRSAMatrix);

				return result;
			}

			MatrixConverter<2>::MatrixType
			MatrixConverter<2>::
			convertRASToITKTrans(const MatrixType& rsaMatrix)
			{
				// Get the current matrix
				MatrixType result = rsaMatrix;

				// Flip the entries that must be flipped
				result(0, 2) *= -1;
				result(1, 2) *= -1;


				return result;
			};

		} // end namespace fsl
	} // end namespace algorithm
} // end namespace map
