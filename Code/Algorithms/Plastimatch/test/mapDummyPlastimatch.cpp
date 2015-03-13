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

#include <fstream>
#include <stdlib.h>

#include "itkImageFileWriter.h"

#include "litTestImageIO.h"

#include "mapString.h"
#include "mapFileDispatch.h"
#include "mapPlmAlgorithmHelper.h"
#include "mapFieldByModelFunctor.h"
#include "mapITKTranslationTransform.h"

int main(int argc, char* argv[])
{
	std::cout << "MatchPoint Plastimatch testing dummy." << std::endl <<
			  "This is a mock up exe, used by MatchPoint to test its Plastimatch integration." << std::endl <<
			  std::endl;

	std::cout << "Passed command line arguments:" << std::endl;

	std::ofstream file;
	std::ios_base::openmode iOpenFlag = std::ios_base::out | std::ios_base::trunc;
	file.open("plastimatchDummyCall.log", iOpenFlag);

	for (int i = 0; i < argc; ++i)
	{
		std::cout << argv[i] << std::endl;
		file << argv[i] << std::endl;
	}

	file.close();

	if (argc > 3)
	{
		std::cerr << "Error. No valid call. Illegal commandline parameter count.";
		return EXIT_FAILURE;
	}

	map::core::String configPath = argv[2];

	map::algorithm::plastimatch::ConfigurationType config =
		map::algorithm::plastimatch::loadConfigurationFromFile(configPath);

	if (config.size() < 2)
	{
		std::cerr << "Error. Invalid config file. Config file:" << configPath;
		return EXIT_FAILURE;
	}

	map::core::String outputPath = config[0]["vf_out"][0];
	map::core::String targetPath = config[0]["fixed"][0];

	////////////////////////////////////////
	//generate a result field

	typedef map::core::functors::FieldByModelFunctor<3, 3> FunctorType;
    typedef itk::TranslationTransform<map::core::continuous::ScalarType, 3>
	TransformType;

	FunctorType::TransformModelType::Pointer spModel = TransformType::New().GetPointer();
	FunctorType::TransformModelType::ParametersType params(3);
	params[0] = 10.0;
	params[1] = -16.0;
	params[2] = -5.0;
    spModel->SetParameters(params);

	//load target image for field descriptor
	typedef map::core::discrete::Elements<3>::InternalImageType ImageType;
	ImageType::Pointer spTargetImage = lit::TestImageIO<float, ImageType>::readImage(targetPath);
	FunctorType::InFieldRepresentationType::Pointer spInRep = map::core::createFieldRepresentation(*
			(spTargetImage.GetPointer()));

	FunctorType::Pointer spFunc = FunctorType::New(*spModel, spInRep);
	FunctorType::FieldPointer spField = spFunc->generateField();

	typedef ::itk::ImageFileWriter< typename FunctorType::FieldType  > FieldWriterType;
	FieldWriterType::Pointer  spFieldWriter  = FieldWriterType::New();

	spFieldWriter->SetFileName(outputPath.c_str());
	spFieldWriter->SetInput(spField);
	spFieldWriter->Update();

	return EXIT_SUCCESS;
}
