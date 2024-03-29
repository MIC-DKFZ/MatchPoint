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


#ifndef __MASKED_REGISTRATION_ALGORITHM_BASE_TPP
#define __MASKED_REGISTRATION_ALGORITHM_BASE_TPP

namespace map
{
	namespace algorithm
	{

		// **** public methods ****
		// ************************
		template<unsigned int VMovingDimension, unsigned int VTargetDimension>
		typename MaskedRegistrationAlgorithmBase<VMovingDimension, VTargetDimension>::MovingMaskBaseConstPointer
		MaskedRegistrationAlgorithmBase<VMovingDimension, VTargetDimension>::
		getMovingMask() const
		{
			return _spMovingMask;
		}

		template<unsigned int VMovingDimension, unsigned int VTargetDimension>
		typename MaskedRegistrationAlgorithmBase<VMovingDimension, VTargetDimension>::TargetMaskBaseConstPointer
		MaskedRegistrationAlgorithmBase<VMovingDimension, VTargetDimension>::
		getTargetMask() const
		{
			return _spTargetMask;
		}


		template<unsigned int VMovingDimension, unsigned int VTargetDimension>
		void
		MaskedRegistrationAlgorithmBase<VMovingDimension, VTargetDimension>::
		setMovingMask(const MovingMaskBaseType* pMovingMask)
		{
			_spMovingMask = pMovingMask;
			_movingMaskMTime.setWatchedObject(pMovingMask);
		}

		template<unsigned int VMovingDimension, unsigned int VTargetDimension>
		void
		MaskedRegistrationAlgorithmBase<VMovingDimension, VTargetDimension>::
		setTargetMask(const TargetMaskBaseType* pTargetMask)
		{
			_spTargetMask = pTargetMask;
			_targetMaskMTime.setWatchedObject(pTargetMask);
		}


		// **** protected methods ****
		// ***************************

		template<unsigned int VMovingDimension, unsigned int VTargetDimension>
		MaskedRegistrationAlgorithmBase<VMovingDimension, VTargetDimension>::
		~MaskedRegistrationAlgorithmBase() {}

		template<unsigned int VMovingDimension, unsigned int VTargetDimension>
		MaskedRegistrationAlgorithmBase<VMovingDimension, VTargetDimension>::
		MaskedRegistrationAlgorithmBase()
		{
		}

		template<unsigned int VMovingDimension, unsigned int VTargetDimension>
		void
		MaskedRegistrationAlgorithmBase<VMovingDimension, VTargetDimension>::
		PrintSelf(std::ostream& os, ::itk::Indent indent) const
		{
			os << indent << "Moving mask: " << _spMovingMask.GetPointer() << std::endl;
			os << indent << "Target mask: " << _spTargetMask.GetPointer() << std::endl;
		}

		template<unsigned int VMovingDimension, unsigned int VTargetDimension>
		::itk::ModifiedTimeType
		MaskedRegistrationAlgorithmBase<VMovingDimension, VTargetDimension>::
		getTargetMaskMTime() const
		{
			return _targetMaskMTime.getMTime();
		};

		template<unsigned int VMovingDimension, unsigned int VTargetDimension>
		::itk::ModifiedTimeType
		MaskedRegistrationAlgorithmBase<VMovingDimension, VTargetDimension>::
		getMovingMaskMTime() const
		{
			return _movingMaskMTime.getMTime();
		};

	}  // namespace algorithm
} // end namespace map

#endif
