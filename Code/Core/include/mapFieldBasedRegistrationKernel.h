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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/include/mapFieldBasedRegistrationKernel.h $
*/




#ifndef __FIELD_BASED_REGISTRATION_KERNEL_H
#define __FIELD_BASED_REGISTRATION_KERNEL_H

#include "mapFieldBasedRegistrationKernelInterface.h"
#include "mapRegistrationKernelBase.h"
#include "mapRegistrationTopology.h"

#include "itkNumericTraits.h"


/*! @namespace map The namespace map::core is for the library of MatchPoint
 */
namespace map
{
	namespace core
	{

		/*! Abstract base class for any kernel using a vector field to define the mapping.
		 * Every field kernel may define a NULL-vector. This vector indicates if a voxel
		 * of the field is invalid (NULL). You may activate or check the NULL-Vector-support
		 * via the kernel api. The default mapper implemented in MatchPoint regard this information.
		 * The default null vector is a vector containing the nonpositive minimum of its value type.
		 * Null vector support is activated by default.
		 *@ingroup RegKernel
		 */
		template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
		class FieldBasedRegistrationKernel : public FieldBasedRegistrationKernelInterface,
			public RegistrationKernelBase<VInputDimensions, VOutputDimensions>
		{
		public:
			typedef FieldBasedRegistrationKernel<VInputDimensions, VOutputDimensions> Self;
			typedef RegistrationKernelBase<VInputDimensions, VOutputDimensions> Superclass;
			typedef itk::SmartPointer<Self> Pointer;
			typedef itk::SmartPointer<const Self> ConstPointer;

			itkTypeMacro(FieldBasedRegistrationKernel, RegistrationKernelBase);

			typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectFieldType FieldType;
			typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectMappingVectorType MappingVectorType;
			typedef typename FieldType::RegionType FieldRegionType;

			typedef typename Superclass::InputPointType  InputPointType;
			typedef typename Superclass::OutputPointType OutputPointType;

			/*! gets the field
			  @eguarantee strong
			  @return const pointer to a FieldType
			 */
			virtual const FieldType *getField() const = 0;

			/*! gets the field
			  @eguarantee strong
			  @return pointer to a FieldType
			 */
			virtual FieldType *getField() = 0;

			const MappingVectorType &getNullVector() const
			{
				return _nullVector;
			};

			void setNullVector(const MappingVectorType &nullVector)
			{
				_nullVector = nullVector;
			};

			bool usesNullVector() const
			{
				return _useNullVector;
			};

			void setNullVectorUsage(bool use)
			{
				_useNullVector = use;
			};

		protected:
			~FieldBasedRegistrationKernel() {};

			FieldBasedRegistrationKernel() : _nullVector(::itk::NumericTraits< typename MappingVectorType::ValueType >::NonpositiveMin()), _useNullVector(true)
			{};

			MappingVectorType _nullVector;
			bool _useNullVector;

		private:

			//No copy constructor allowed
			FieldBasedRegistrationKernel(const Self &source);
			void operator=(const Self &); //purposely not implemented

		};

	}
}

#endif
