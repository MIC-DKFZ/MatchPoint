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
#include <iostream>
#include <stdlib.h>

#include "itkImageFileWriter.h"

#include "mapString.h"
#include "test/mapTestFieldGenerationFunctor.h"
#include "mapFileDispatch.h"

int main(int argc, char* argv[])
{
	std::cout << "MatchPoint Transformix testing dummy." << std::endl <<
			  "This is a mock up exe, used by MatchPoint to test its Transformix integration." << std::endl <<
			  std::endl;

	std::cout << "Passed command line arguments:" << std::endl;

	std::ofstream file;
	std::ios_base::openmode iOpenFlag = std::ios_base::out | std::ios_base::trunc;
	file.open("transformixDummyCall.log", iOpenFlag);

	map::core::String outputPath;
	bool nextIsOutput = false;

	for (int i = 0; i < argc; ++i)
	{
		std::cout << argv[i] << std::endl;
		file << argv[i] << std::endl;

		if (nextIsOutput)
		{
			outputPath = argv[i];
		}

		nextIsOutput = argv[i] == map::core::String("-out");
	}

	file.close();

	//generate result a field
	typedef map::testing::TestFieldGenerationFunctor<2, 2> FieldFunctorType;
	FieldFunctorType::InFieldRepresentationType::SpacingType spacing(0.5);
	FieldFunctorType::InFieldRepresentationType::PointType origin;
	origin.Fill(0);
	FieldFunctorType::InFieldRepresentationType::SizeType size;
	size.fill(10);

	FieldFunctorType::InFieldRepresentationType::Pointer spInRep =
		FieldFunctorType::InFieldRepresentationType::New();
	spInRep->setSize(size);
	spInRep->setSpacing(spacing);
	spInRep->setOrigin(origin);
	FieldFunctorType::Pointer spFunctor = FieldFunctorType::New(spInRep);
	FieldFunctorType::FieldPointer spField = spFunctor->generateField();

	typedef ::itk::ImageFileWriter< FieldFunctorType::FieldType  > FieldWriterType;
	FieldWriterType::Pointer  spFieldWriter  = FieldWriterType::New();

	spFieldWriter->SetFileName(map::core::FileDispatch::createFullPath(outputPath,
							   "deformationField.mhd").c_str());
	spFieldWriter->SetInput(spField);
	spFieldWriter->Update();

	return EXIT_SUCCESS;
}
