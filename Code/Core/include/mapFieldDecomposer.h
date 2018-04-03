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
// @version $Revision: 1283 $ (last changed revision)
// @date    $Date: 2016-03-30 16:58:36 +0200 (Mi, 30 Mrz 2016) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/branches/Issue-1505/Code/Core/include/mapAffineMatrixDecomposer.h $
*/




#ifndef __FIELD_DECOMPOSER_H
#define __FIELD_DECOMPOSER_H

#include "mapRegistrationKernelBase.h"
#include "mapRegistrationTopology.h"

namespace map
{
    namespace core
    {
        /** Convinience helper to extract a vector field out of transforms/kernel
         * if they are basead on a field..*/
        template<unsigned int VInputDimensions, unsigned int VOutputDimensions>
        struct FieldDecomposer
        {
        public:

            typedef RegistrationKernelBase<VInputDimensions, VOutputDimensions> KernelType;
            typedef typename KernelType::TransformType TransformType;
            typedef typename RegistrationTopology<VInputDimensions, VOutputDimensions>::DirectFieldType FieldType;
            typedef typename FieldType::ConstPointer FieldConstPointer;
            typedef typename FieldType::Pointer FieldPointer;

            /*! Convinient function that tries to get the internals of the kernel as vector field.
             * The function checks if the passed kernel has a transform that containes a vector field.
             * If thats true, it checks if it can retrieve it.
             *
             * @eguarantee strong
             * @pre pKernel musst point to a valid instance.
             * @param [in] Pointer to the kernel that should be decomposed.
             * @param [out] field Referenz to the smart pointer of the extracted field.
             * @return Indicates if a field could be extrakted. If it returns false, it cannot be decomposed
             * and the referenced output parameters are invalid.*/
            static bool decomposeKernel(const KernelType* pKernel, FieldConstPointer& field);

            /*! Convinient function that tries to get the internals of the transform as vector field.
            * The function checks if the passed transform containes a vector field.
            * If thats true, it checks if it can retrieve it.
            *
            * @eguarantee strong
            * @pre pKernel musst point to a valid instance.
            * @param [in] Pointer to the transform that should be decomposed.
            * @param [out] field Referenz to the smart pointer of the extracted field.
            * @return Indicates if a field could be extrakted. If it returns false, it cannot be decomposed
            * and the referenced output parameters are invalid.*/
            static bool decomposeTransform(const TransformType* pTransform, FieldConstPointer& field);
            static bool decomposeTransform(TransformType* pTransform, FieldPointer& field);
        };

    }
}

#ifndef MatchPoint_MANUAL_TPP
# include "mapFieldDecomposer.tpp"
#endif

#endif
