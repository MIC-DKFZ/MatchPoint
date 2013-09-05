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
// Subversion HeadURL: $HeadURL: http://sidt-hpc1/dkfz_repository/NotMeVisLab/SIDT/MatchPoint/trunk/Code/Algorithms/Plastimatch/include/mapPlmCLIRegistrationAlgorithmBase.h $
*/




#ifndef __MAP_PLM_CLI_REGISTRATION_ALGORITHM_BASE_H
#define __MAP_PLM_CLI_REGISTRATION_ALGORITHM_BASE_H

//MatchPoint
#include "mapContinuous.h"

#include "mapIterativeRegistrationAlgorithm.h"
#include "mapImageRegistrationAlgorithmBase.h"
#include "mapClassMacros.h"
#include "mapPlmAlgorithmHelper.h"
#include "mapMetaPropertyAlgorithmBase.h"
#include "mapMaskedRegistrationAlgorithmBase.h"

namespace map
{
	namespace algorithm
	{
		namespace plastimatch
		{

			/*! @class CLIRegistrationAlgorithmBase
						@brief This is the base class for algorithms that serve as a wrapper for the registration
						tool "plastimatch". The algorithm is a very simple wrapper using a command line interface to
						facilitate plastimatch.	For a registration task a temporary working directory is generated,
						where the algorithm stores the given moving and target image. Then the algorithms calls
						'plastimatch' with appropriated command line arguments to trigger the registration as an external
						process and to produce a deformation field as output. This field will be loaded, converted into
						a MatchPoint registration object and returned.
						After the registration job is done, the temporary directory will be deleted by the algorithm.
						@remark
			    @ingroup Algorithms
						@ingroup Plastimatch
			 */
			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			class CLIRegistrationAlgorithmBase : public IterativeRegistrationAlgorithm<TMovingImage::ImageDimension, TTargetImage::ImageDimension>,
				public ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>,
				public MetaPropertyAlgorithmBase,
				public MaskedRegistrationAlgorithmBase<TMovingImage::ImageDimension, TTargetImage::ImageDimension>,
        public TIdentificationPolicy
			{
			public:
				typedef CLIRegistrationAlgorithmBase<TMovingImage, TTargetImage, TIdentificationPolicy> Self;
				typedef IterativeRegistrationAlgorithm<TMovingImage::ImageDimension, TTargetImage::ImageDimension>  Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;
				itkTypeMacro(CLIRegistrationAlgorithmBase, IterativeRegistrationAlgorithm);

				typedef typename Superclass::UIDType UIDType;
				typedef typename Superclass::UIDPointer UIDPointer;

				typedef typename IterativeRegistrationAlgorithm<TMovingImage::ImageDimension, TTargetImage::ImageDimension>::OptimizerMeasureType OptimizerMeasureType;

				typedef ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage> ImageRegistrationAlgorithmBaseType;

				typedef typename ImageRegistrationAlgorithmBaseType::TargetImageType TargetImageType;
				typedef typename ImageRegistrationAlgorithmBaseType::MovingImageType MovingImageType;
				typedef typename Superclass::MovingRepresentationDescriptorType MovingRepresentationDescriptorType;
				typedef typename Superclass::TargetRepresentationDescriptorType TargetRepresentationDescriptorType;

				typedef typename Superclass::RegistrationPointer RegistrationPointer;
				typedef typename Superclass::RegistrationType RegistrationType;
				typedef typename Superclass::FieldRepRequirement FieldRepRequirement;

				typedef typename MetaPropertyAlgorithmBase::MetaPropertyType MetaPropertyType;
				typedef typename MetaPropertyAlgorithmBase::MetaPropertyPointer MetaPropertyPointer;
				typedef typename MetaPropertyAlgorithmBase::MetaPropertyNameType MetaPropertyNameType;

        mapDefineAlgorithmIdentificationByPolicyMacro;

				// IterativeRegistrationAlgorithm
				/*! @eguarantee strong*/
				virtual bool isStoppable() const;

				/*! has the algorithm an iteration count?
				@eguarantee no fail
				@return Indicates if the algorithm can determin its current iteration count
				*/
				virtual bool hasIterationCount() const;

				/*! has the algorithm an maximum iteration count?
				@eguarantee no fail
				@return Indicates if the algorithm can determin its maximum iteration count
				*/
				virtual bool hasMaxIterationCount() const;

				/*! This function indicates if the optimizer of the iterative registration algorithm is
				* able to return its current metric/optimizer value(s)?
				@eguarantee no fail
				@return Indicates if the algorithm can determin its curent value.
				*/
				virtual bool hasCurrentOptimizerValue() const;

				virtual typename FieldRepRequirement::Type isMovingRepresentationRequired() const;

				virtual typename FieldRepRequirement::Type isTargetRepresentationRequired() const;

				/*! @reimplemented */
				virtual bool isReusable() const;

				mapGetMetaMacro(WorkingDirectory, core::String);
				mapSetMetaMacro(WorkingDirectory, core::String);

				mapGetMetaMacro(PlastimatchDirectory, core::String);
				mapSetMetaMacro(PlastimatchDirectory, core::String);

				mapGetMetaMacro(DeleteTempDirectory, bool);
				mapSetMetaMacro(DeleteTempDirectory, bool);

			protected:
				CLIRegistrationAlgorithmBase();
				virtual ~CLIRegistrationAlgorithmBase();

				typedef typename Superclass::InterimRegistrationType InterimRegistrationType;
				typedef typename Superclass::InterimRegistrationPointer InterimRegistrationPointer;
				typedef typename Superclass::IterationCountType IterationCountType;
				typedef typename ImageRegistrationAlgorithmBaseType::MovingImageConstPointer MovingImageConstPointer;
				typedef typename ImageRegistrationAlgorithmBaseType::TargetImageConstPointer TargetImageConstPointer;

				typedef typename map::core::RegistrationTopology<Superclass::MovingDimensions, Superclass::TargetDimensions>::InverseFieldType FinalFieldType;
				typedef typename FinalFieldType::Pointer FinalFieldPointer;

				/* @reimplemented*/
				virtual void configureAlgorithm();

				// MetaPropertyAlgorithmBase
				/*! @reimplemented*/
				virtual void compileInfos(MetaPropertyVectorType &infos) const;

				/*! @reimplemented*/
				virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType &name) const;

				/*! @reimplemented*/
				virtual void doSetProperty(const MetaPropertyNameType &name, const MetaPropertyType *pProperty);

				// IterativeRegistrationAlgorithmInterface
				/*! @brief gets the registration result that has been computed in the last iteration.
				  This result is limited by the passed region descriptors (pMovingRepresentation, pTargetRepresentation).
				  @pre pMovingRepresentation and pTargetRepresentation must not be null.
				  @param [in] pMovingRepresentation Pointer to
				  @eguarantee strong
				  @return the interim registration result as smart pointer
				  @retval a Registration object
				  @sa Registration
				 */
				virtual InterimRegistrationPointer determineInterimRegistration(const MovingRepresentationDescriptorType *pMovingRepresentation,
				                                                                const TargetRepresentationDescriptorType *pTargetRepresentation) const;

				/*!
				 * Returns the final registration
				  @eguarantee strong
				 */
				virtual RegistrationPointer doGetRegistration() const;

				/*! Returns if the registration should be computed. The registration is outdated if doGetRegistration returns null
				 * or the modification time of at least one sub component is newer then the modification time of the registration.
				  @eguarantee strong
				  @return true if the registration should be (re)computed. False if the registration is uptodate.
				 */
				virtual bool registrationIsOutdated() const;

				virtual bool doStopAlgorithm();


				/*! This method should do all preparation tasks right before the algorithm is executed. At the end of this method
				 the algorithm should be set up and ready to use.\n
				 The method delegates the main work of initialization to several sub methods. These sub methods serve as slots
				 that can be rewritten by an algorithm developer to alter certain aspects and keep the rest untouched.\n
				 The sequence of slot calls is: \n
				 - prepCheckValidity
				 - prepPerpareInternalInputData
				 - prepSavePlastimatchInputData
				 - prepParameterMaps
				 - prepFinalizePreparation
				 @remark If you want to change the execution style, then overwrite runAlgorithm().
				 @eguarantee strong*/
				virtual void prepareAlgorithm();

				/*! This method is the slot to check if all internal components and input data are properly set.
				 @remark The default implementation checks the moving and target image. Overload this method to alter the validity check.
				 @remark It is assumed that the implementation of this method throws an exception if the algorithm is not configured
				 correctly.*/
				virtual void prepCheckValidity();

				/*! This method is the slot for internal preprocessing of input data. This method should
				 be reimplemented if you want to prepare the input data before they go into the internal
				 registration method. E.g. blurring or normalizing the moving and target image before registration.
				 @remark The default implementation does nothing. Thus the public input data will be the data used by the
				 internal algorithm.
				 @remark Implementations of this method should work on _spInternalMoving and _spInternalTargetImage. In the default
				 implementation of prepSetInternalInputData() these member will be passed to the internal algorithm.
				 @eguarantee strong*/
				virtual void prepPerpareInternalInputData();

				/*! This method is the slot for storing the relevant input data to the working directory of plastimatch.
				* @remark The default implementation stores _spInternalMoving and _spInternalTargetImage and the masks if set.
				@eguarantee strong
				*/
				virtual void prepSavePlastimatchInputData();

				/*! This method is the slot for the generation of the configuration that should be passed to plastimatch. The base class assumes that
				 after calling this methods the member _configurationPLM contains all parameters for all stages.
				 @eguarantee strong
				*/
				virtual void prepConfigurationPLM() = 0;

				/*! This method is used after preConfifurationPLM() to ensure that parameters for input images, masks and resulting vector field
				 are correctly set. If the parameters are already set, they will be overwritten. In addition the function removes all settings for
				 the output of result images or xform (they are deactivated).
				 @eguarantee strong
				*/
				void ensureCorrectGlobalConfigSettings();

				/*! This method should just execute the iteration loop.
				* @remark If you want to change the initialization or the finalization, then overwrite prepareIteration() or finalizeAlgorithm().
				* @return Indicates if the registration was successfully determined (e.g. could be
				* false if an iterative algorithm was stopped prematurely by the user).
				* @eguarantee strong
				*/
				virtual bool runAlgorithm();

				/*! This method should do all the finalization work (e.g. generating the registration based on the iteration results).
				 * @remark If you want to change the initialization or the iteration, then overwrite prepareIteration() or iterateAlgorithm().
				  @eguarantee strong
				 */
				virtual void finalizeAlgorithm();

				/*! return the optimizer value(s) of the current iteration step.
				Will be called by getCurrentOptimizerValue() if hasCurrentValue() returns true.
				@eguarantee strong
				@return current measure
				*/
				virtual OptimizerMeasureType doGetCurrentOptimizerValue() const;

				/*! Methods invoked by derivated classes.  */
				virtual void PrintSelf(std::ostream &os, ::itk::Indent indent) const;

				/*! Feature is not supported by this wrapper. Therefore the methods returns only a dummy value (0).
				 * @eguarantee strong*/
				virtual IterationCountType doGetCurrentIteration() const;

				/*! Feature is not supported by this wrapper. Therefore the methods returns only a dummy value (0).
				  @eguarantee strong
				 */
				virtual IterationCountType doGetMaxIterations() const;

				/*! This method generates a unique and random subdirectory contained by _workingDir.
				 * The path to this directory is stored in _currentTempDir.
				 * @eguarantee strong
				 */
				void initializeCurrentTempDir();

				/*! Helper function that loads the deformation file generated by plastimatch.
				The generated file is loaded and returned by the function.*/
				FinalFieldPointer	generateField() const;

				/*! Helper function that generates the file path to the parameter file.*/
				core::String getParameterFilePath() const;

				/*! Helper function that generates the file path to the result parameters
				  for the final(last stage) transform.
					@pre Algorithm must have at least one stage.*/
				core::String getFinalTransformFilePath() const;

				/*!Pointer to the moving image used by the algorithm internally. This is used to allow the algorithm
				* or its derived classes to modify the moving image without changing the public moving image pointer.
				* The variable is set by prepareIteration() to _spMovingImage before calling prepareInternalInputData().
				* (e.g.: An algorithm always normalizes an image before registration. Then the algorithm can use the prepareInternalInputData()
				* function to manipulate _spInternalMovingImage before it is used by prepareIteration() to set the internal algorithm)*/
				MovingImageConstPointer _spInternalMovingImage;

				/*!Pointer to the target image used by the algorithm internally. This is used to allow the algorithm
				 * or its derived classes to modify the target image with out changing the public target image pointer.
				 * The variable is set by prepareIteration() to _spTargetImage before calling prepareInternalInputData().
				 * (e.g.: An algorithm always normalizes an image before registration. Then the algorithm can use the prepareInternalInputData()
				 * function to manipulate _spInternalTargetImage before it is used by prepareIteration() to set the internal algorithm)*/
				TargetImageConstPointer _spInternalTargetImage;

				/*!Directory that can be used to store temporary data. Process must have write access to this directory*/
				core::String _workingDir;
				/*!Directory where the plastimatch tool 'plastimatch' is located.*/
				core::String _plastimatchDir;
				/*!Directory that is used to store temporary data on the current run*/
				core::String _currentTempDir;

				/*!Vector with plastimatch parameter maps, each element of the vector is the parameter
				 map for one registration stage of plastimatch*/
				ConfigurationType _configurationPLM;

				core::String _movingImageTempPath;
				core::String _targetImageTempPath;
				core::String _finalFieldTempPath;
				core::String _movingMaskTempPath;
				core::String _targetMaskTempPath;

				bool _deleteTempDirectory;

				/*! This member function is called by the process executer, whenever Plastimatch generates an output on stdout.*/
				void onPlmOutputEvent(::itk::Object *caller, const ::itk::EventObject &eventObject);

				/*! Helper method that removes the current temp dir (if it exists and _deleteTempDirectory is true).
				 * @eguarantee no throw*/
				void cleanTempDir() const;

			private:

				/*! The parameters of the registration field generated by plastimatch.*/
				typename FinalFieldPointer _spFinalizedField;

				/*! Smartpointer to the finalized registration. Will be set by finalizeAlgorithm()*/
				typename RegistrationType::Pointer _spFinalizedRegistration;

				/*! The lock is used to manage the access to the member variable _currentIterationCount.*/
				mutable ::itk::SimpleFastMutexLock _currentIterationLock;

				CLIRegistrationAlgorithmBase(const Self &source);
				void operator=(const Self &); //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapPlmCLIRegistrationAlgorithmBase.tpp"
#endif

#endif
