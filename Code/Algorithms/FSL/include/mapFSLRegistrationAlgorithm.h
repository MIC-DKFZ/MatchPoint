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


#ifndef __MAP_FSL_REGISTRATION_ALGORITHM_H
#define __MAP_FSL_REGISTRATION_ALGORITHM_H

#include "mapContinuous.h"

#include "mapIterativeRegistrationAlgorithm.h"
#include "mapImageRegistrationAlgorithmBase.h"
#include "mapITKAffineTransform.h"
#include "mapClassMacros.h"
#include "mapMetaPropertyAlgorithmBase.h"


/*! @namespace map The namespace map is used throughout the MatchPoint project to
mark code as components of this project
*/
namespace map
{
	namespace algorithm
	{
		namespace fsl
		{

			struct DegreesOfFreedom
			{
				enum Type
				{
					DoF6 = 6,
					DoF7 = 7,
					DoF9 = 9,
					DoF12 = 12,
					DoF2D = 2
				};
			};

			struct CostFunction
			{
				enum Type
				{
					LeastSquares,
					NormalisedCorrelation,
					CorrelationRatio,
					MutualInformation,
					NormalisedMutualInformation
				};
			};

			/*! @class FSLRegistrationAlgorithm
			@brief The class is an algorithm that serves as a wrapper for the FSL registration tool "flirt".
			The algorithm generates a temporary working directory, where it stores the given moving and target
			image. Then the algorithms calls 'flirt' with appropriated command line arguments to trigger the
			registration as an external process. After flirt is finished the result
			transformation will be converted into an MatchPoint registration object and returned.
			After the registration job is done, the temporary directory will be deleted by the algorithm.
			@ingroup Algorithms
			@ingroup FSL
			*/
			template<class TMovingImage, class TTargetImage, class TIdentificationPolicy>
			class FSLRegistrationAlgorithm : public
				IterativeRegistrationAlgorithm<TMovingImage::ImageDimension, TTargetImage::ImageDimension>,
			public ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>,
			public MetaPropertyAlgorithmBase,
			public TIdentificationPolicy
			{
			public:
				typedef FSLRegistrationAlgorithm<TMovingImage, TTargetImage, TIdentificationPolicy> Self;
				typedef IterativeRegistrationAlgorithm<TMovingImage::ImageDimension, TTargetImage::ImageDimension>
				Superclass;

				typedef ::itk::SmartPointer<Self>                                     Pointer;
				typedef ::itk::SmartPointer<const Self>                               ConstPointer;
				itkTypeMacro(FSLRegistrationAlgorithm, IterativeRegistrationAlgorithm);
				mapNewAlgorithmMacro(Self);

				typedef typename Superclass::UIDType UIDType;
				typedef typename Superclass::UIDPointer UIDPointer;

				typedef typename
				IterativeRegistrationAlgorithm<TMovingImage::ImageDimension, TTargetImage::ImageDimension>::OptimizerMeasureType
				OptimizerMeasureType;

				typedef ImageRegistrationAlgorithmBase<TMovingImage, TTargetImage>
				ImageRegistrationAlgorithmBaseType;

				typedef typename ImageRegistrationAlgorithmBaseType::TargetImageType TargetImageType;
				typedef typename ImageRegistrationAlgorithmBaseType::MovingImageType MovingImageType;
				typedef typename Superclass::MovingRepresentationDescriptorType MovingRepresentationDescriptorType;
				typedef typename Superclass::TargetRepresentationDescriptorType TargetRepresentationDescriptorType;

				typedef typename Superclass::RegistrationPointer RegistrationPointer;
				typedef typename Superclass::RegistrationType RegistrationType;
				typedef typename Superclass::FieldRepRequirement FieldRepRequirement;

                        typedef typename MetaPropertyAlgorithmBase::MetaPropertyPointer MetaPropertyPointer;

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
				@return Indicates if the algorithm can determin its current value.
				*/
				virtual bool hasCurrentOptimizerValue() const;

				virtual UIDPointer getUID() const;
				virtual map::core::String getAlgorithmProfile() const;
				virtual map::core::String getAlgorithmDescription() const;

				virtual typename FieldRepRequirement::Type isMovingRepresentationRequired() const;

				virtual typename FieldRepRequirement::Type isTargetRepresentationRequired() const;

				/*! @reimplemented */
				virtual bool isReusable() const;

				mapGetMetaMacro(WorkingDirectory, core::String);
				mapSetMetaMacro(WorkingDirectory, core::String);

				mapGetMetaMacro(FlirtDirectory, core::String);
				mapSetMetaMacro(FlirtDirectory, core::String);

				mapGetMetaMacro(DeleteTempDirectory, bool);
				mapSetMetaMacro(DeleteTempDirectory, bool);

				mapGetMetaMacro(CostFunction, CostFunction::Type);
				mapSetMetaMacro(CostFunction, CostFunction::Type);

				mapGetMetaMacro(DegreesOfFreedom, DegreesOfFreedom::Type);
				mapSetMetaMacro(DegreesOfFreedom, DegreesOfFreedom::Type);

			protected:
				FSLRegistrationAlgorithm();
				virtual ~FSLRegistrationAlgorithm();

				typedef typename Superclass::InterimRegistrationType InterimRegistrationType;
				typedef typename Superclass::InterimRegistrationPointer InterimRegistrationPointer;
				typedef typename Superclass::IterationCountType IterationCountType;
				typedef typename ImageRegistrationAlgorithmBaseType::MovingImageConstPointer
				MovingImageConstPointer;
				typedef typename ImageRegistrationAlgorithmBaseType::TargetImageConstPointer
				TargetImageConstPointer;

				typedef itk::ITKTransformModel< ::itk::AffineTransform<map::core::continuous::ScalarType, TTargetImage::ImageDimension> >
				ModelType;

				/* @reimplemented*/
				virtual void configureAlgorithm();

				// MetaPropertyAlgorithmBase
				/*! @reimplemented*/
				virtual void compileInfos(MetaPropertyVectorType& infos) const;

				/*! @reimplemented*/
				virtual MetaPropertyPointer doGetProperty(const MetaPropertyNameType& name) const;

				/*! @reimplemented*/
				virtual void doSetProperty(const MetaPropertyNameType& name, const MetaPropertyType* pProperty);

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
				virtual InterimRegistrationPointer determineInterimRegistration(const
						MovingRepresentationDescriptorType* pMovingRepresentation,
						const TargetRepresentationDescriptorType* pTargetRepresentation) const;

				/*!
				* Returns the final registration
				@eguarantee strong
				*/
				virtual RegistrationPointer doGetRegistration() const;

				/*! Returns if the registration should be computed. The registration is outdated if doGetRegistration returns null
				* or the modification times of at least one policy is newer then the modification time of the registration.
				@eguarantee strong
				@return true if the registration should be (re)computed. False if the registration is uptodate.
				*/
				virtual bool registrationIsOutdated() const;

				virtual bool doStopAlgorithm();

				/*! This method should do all preparation tasks right before the algorithms execution. At the end of this method
				* the algorithm should be set up and ready to use.
				* @remark If you want to change the execution style, then overwrite iterateAlgorithm().
				@eguarantee strong
				*/
				virtual void prepareAlgorithm();

				/*! This method should be reimplemented if you want to prepare the input data before they go into the internal
				* registration method. E.g. blurring or normalizing the moving and target image before registration.
				* @remark The default implementation does nothing. Thus the public input data will be the data used by the
				* internal algorithm.
				@eguarantee strong
				*/
				virtual void prepPerpareInternalInputData();

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
				virtual void PrintSelf(std::ostream& os, ::itk::Indent indent) const;

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

				/*!Pointer to the moving image used by the algorithm internally. This is used to allow the algorithm
				* or its derived classes to modify the moving image with out changing the public moving image pointer.
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
				/*!Directory where the FSL tool 'flirt' is located.*/
				core::String _flirtDir;
				/*!Directory that is used to store temporary data on the current run*/
				core::String _currentTempDir;

				core::String _movingImageTempPath;
				core::String _targetImageTempPath;
				core::String _resultMatrixTempPath;

				/*!Cost function that should be used by flirt (default is CorrelationRatio).*/
				CostFunction::Type _costFnc;

				/*!Degrees of freedom that should be used by flirt (default is 12).*/
				DegreesOfFreedom::Type _dof;

				bool _deleteTempDirectory;

				/*! This member function is called by the process executer, when ever fsl generates an output on stdout.*/
				void onFSLOutputEvent(::itk::Object* caller, const ::itk::EventObject& eventObject);

				/*! Helper method that removes the current temp dir (if it exists and _deleteTempDirectory is true).
				* @eguarantee no throw*/
				void cleanTempDir() const;

			private:

				/*! The parameters of the registration transform of the last successfull registration determiniation. Will be set by finalizeAlgorithm()*/
				typename ModelType::TransformType::ParametersType _finalizedTransformParameters;

				/*! Smartpointer to the finalized registration. Will be set by finalizeAlgorithm()*/
				typename RegistrationType::Pointer _spFinalizedRegistration;

				/*! The lock is used to manage the access to the member variable _currentIterationCount.*/
				mutable ::itk::SimpleFastMutexLock _currentIterationLock;

				FSLRegistrationAlgorithm(const Self& source);
				void operator=(const Self&);  //purposely not implemented
			};

		}
	}
}

#ifndef MatchPoint_MANUAL_TPP
#include "mapFSLRegistrationAlgorithm.tpp"
#endif

#endif
