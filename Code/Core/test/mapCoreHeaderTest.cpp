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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Core/test/mapCoreHeaderTest.cpp $
*/
#if defined(_MSC_VER)
#pragma warning ( disable : 4786 )
#endif

#include <iostream>

#include "mapMacros.h"
#include "mapString.h"
#include "mapContinuous.h"
#include "mapContinuousElements.h"
#include "mapDiscrete.h"
#include "mapDiscreteElements.h"
#include "mapEvents.h"
#include "mapPMVolume.h"
#include "mapRegistrationTopology.h"
#include "mapVolume.h"
#include "mapVolumeSize.h"
#include "mapXMLLogger.h"
#include "mapLogbook.h"
#include "mapLogbookImplementation.h"
#include "mapLogbookMacros.h"
#include "mapExceptionObject.h"
#include "mapExceptionObjectMacros.h"
#include "mapRegistrationBase.h"
#include "mapInverseRegistrationKernelGenerator.h"
#include "mapRegistrationKernelInverterBase.h"
#include "mapModelBasedKernelInverter.h"
#include "mapFieldBasedKernelInverter.h"
#include "mapKernelInverterLoadPolicy.h"
#include "mapRegistrationCombinationRequest.h"
#include "mapRegistrationKernelCombinatorBase.h"
#include "mapKernelCombinatorLoadPolicy.h"
#include "mapRegistrationCombinator.h"
#include "mapModelModelKernelCombinator.h"
#include "mapFieldFieldKernelCombinator.h"
#include "mapFieldModelKernelCombinator.h"
#include "mapModelFieldKernelCombinator.h"
#include "mapMappingTaskBase.h"
#include "mapPointSetMappingTask.h"
#include "mapImageMappingTask.h"
#include "mapPointSetMappingPerformerLoadPolicy.h"
#include "mapImageMappingPerformerLoadPolicy.h"
#include "mapNoneMappingPerformerLoadPolicy.h"
#include "mapMappingTaskBatchThread.h"
#include "mapMappingTaskBatch.h"
#include "mapMappingPerformerRequestBase.h"
#include "mapPointSetMappingPerformerRequest.h"
#include "mapImageMappingPerformerRequest.h"
#include "mapMappingPerformerBase.h"
#include "mapImageMappingPerformerBase.h"
#include "mapPointSetByModelPerformer.h"
#include "mapPointSetByFieldPerformer.h"
#include "mapImageByModelPerformer.h"
#include "mapImageByFieldPerformer.h"
#include "mapConcreteFieldBasedRegistrationKernel.h"
#include "mapCombinedFieldBasedRegistrationKernel.h"
#include "mapDefaultRegistrationTopologyPolicy.h"
#include "mapPreCachedFieldPolicy.h"
#include "mapFieldBasedRegistrationKernel.h"
#include "mapFieldBasedRegistrationKernelInterface.h"
#include "mapFieldBasedRegistrationKernels.h"
#include "mapFieldRepresentationDescriptor.h"
#include "mapLazyFieldPolicy.h"
#include "mapModelBasedRegistrationKernel.h"
#include "mapModelBasedRegistrationKernelInterface.h"
#include "mapNullRegistrationKernel.h"
#include "mapRegistration.h"
#include "mapRegistrationBase.h"
#include "mapRegistrationKernelBase.h"
#include "mapRegistrationException.h"
#include "mapTransformModelBase.h"
#include "mapITKUnaryTransformModel.h"
#include "mapITKDimensionedTransformModel.h"
#include "mapServiceException.h"
#include "mapMissingProviderException.h"
#include "mapMappingException.h"
#include "mapPointVectorCombinationPolicy.h"
#include "mapMetaProperty.h"
#include "mapSmartMetaProperty.h"
#include "mapMetaPropertyAccessor.h"
#include "mapAffineMatrixDecomposer.h"


// subdir ./services
#include "mapServiceProvider.h"
#include "mapServiceStack.h"
#include "mapNoneStaticLoadPolicy.h"
#include "mapServiceRepositoryPolicyLoadInterface.h"
#include "mapGenericStaticLoadPolicyBase.h"
#include "mapFastLockedThreadingPolicy.h"
#include "mapSingleThreadedThreadingPolicy.h"
#include "mapStaticServiceStack.h"
#include "mapDefaultSLStaticPolicy.h"
#include "mapFastLockedThreadingStaticPolicy.h"
#include "mapFastMutexLockSentinel.h"

// subdir ./functors
#include "mapFieldGenerationFunctor.h"
#include "mapFieldByModelFunctor.h"
#include "mapFieldByModelInversionFunctor.h"
#include "mapFieldByFieldInversionFunctor.h"
#include "mapFieldCombinationFunctorInterface.h"
#include "mapFieldByModelFieldCombinationFunctor.h"
#include "mapFieldByFieldModelCombinationFunctor.h"
#include "mapFieldByFieldFieldCombinationFunctor.h"

int main(int , char **)
{

	return EXIT_SUCCESS;
}

