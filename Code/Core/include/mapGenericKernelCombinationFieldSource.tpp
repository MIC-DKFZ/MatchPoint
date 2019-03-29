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
// @version $Revision: 1316 $ (last changed revision)
// @date    $Date: 2016-04-13 14:50:09 +0200 (Mi, 13 Apr 2016) $ (last change date)
// @author  $Author: floca $ (last changed by)
// Subversion HeadURL: $HeadURL: https://svn.inet.dkfz-heidelberg.de/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/Core/include/mapGenericFieldGeneratingCombinationFunctor.tpp $
*/


#ifndef __MAP_GENERIC_KERNEL_COMBINATION_FIELD_SOURCE_TPP
#define __MAP_GENERIC_KERNEL_COMBINATION_FIELD_SOURCE_TPP

#include "mapGenericKernelCombinationFieldSource.h"
#include "mapRepresentationException.h"
#include "mapPointVectorCombinationPolicy.h"
#include "itkProgressReporter.h"
#include "itkImageRegionIteratorWithIndex.h"

namespace map
{
    namespace core
    {

        template< unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions, typename TScalarType >
        void
            GenericKernelCombinationFieldSource< VInputDimensions, VInterimDimensions, VOutputDimensions, TScalarType >
            ::GenerateOutputInformation()
        {
            Superclass::GenerateOutputInformation();

            if (this->m_SourceKernel1.IsNull())
            {
                mapDefaultExceptionMacro(<< "Error. Cannot generate field. Source kernel 1 is not set.");
            }
            if (this->m_SourceKernel2.IsNull())
            {
                mapDefaultExceptionMacro(<< "Error. Cannot generate field. Source kernel 2 is not set.");
            }
        }

        template< unsigned int VInputDimensions, unsigned int VInterimDimensions, unsigned int VOutputDimensions, typename TScalarType >
        void
            GenericKernelCombinationFieldSource< VInputDimensions, VInterimDimensions, VOutputDimensions, TScalarType >
            ::ThreadedGenerateData(const RegionType &outputRegionForThread, ::itk::ThreadIdType threadId)
        {
            // Support progress methods/callbacks
            ::itk::ProgressReporter progress(this, threadId, outputRegionForThread.GetNumberOfPixels());

            OutputImageType *image = this->GetOutput(0);

            ::itk::ImageRegionIteratorWithIndex< OutputImageType > it(image, outputRegionForThread);

            typename OutputImageType::PointType inPoint;

            typedef typename SourceKernel2BaseType::MappingVectorType::Superclass VectorSuperclassType;
            typename SourceKernel2BaseType::MappingVectorType nullVector;
            nullVector.VectorSuperclassType::operator = (this->m_NullPoint);

            for (; !it.IsAtEnd(); ++it)
            {

                image->TransformIndexToPhysicalPoint(it.GetIndex(), inPoint);

                typename SourceKernel1BaseType::OutputPointType interimPoint;

                bool valid = m_SourceKernel1->mapPoint(inPoint, interimPoint);

                typename SourceKernel2BaseType::OutputPointType endPoint;
                bool valid2 = m_SourceKernel2->mapPoint(interimPoint, endPoint);

                typename SourceKernel2BaseType::MappingVectorType outVector = nullVector;

                if (valid && valid2)
                {
                    PointVectorCombinationPolicy<VInputDimensions, VOutputDimensions>::computeVector(inPoint,
                        endPoint, outVector);
                }
                else
                {
                    if (!this->m_UseNullPoint)
                    {
                        mapExceptionMacro(::map::core::RepresentationException, << "Error. Cannot generate combined kernel. At least one source kernel was not able to map points. valid source kernel 1: " << valid << "; valid source kernel 2:" << valid2);
                    }
                }

                it.Set(outVector);

                progress.CompletedPixel();
            }
        }

    }  // namespace core
}  // namespace map


#endif 
