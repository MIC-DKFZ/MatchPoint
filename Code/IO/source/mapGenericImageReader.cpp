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

#include "mapGenericImageReader.h"

namespace map
{
	namespace io
	{

		////////////////////////////////////////////////////////////////////////
		/// Implementation of map::GenericImageReader ////////////////////////////////
		////////////////////////////////////////////////////////////////////////


		void
		GenericImageReader::
		load()
		{
			_spImage = NULL;

			core::String probeFileName = this->_fileName;

			if (this->_seriesReadStyle == ImageSeriesReadStyle::Numeric)
			{
				typedef ::itk::NumericSeriesFileNames NamesType;

				NamesType::Pointer names = NamesType::New();

				names->SetStartIndex(1);
				names->SetEndIndex(1);
				names->SetSeriesFormat(this->_fileName.c_str());

				probeFileName = names->GetFileNames()[0];
			}

			::itk::ImageIOBase::Pointer imageIO =
				::itk::ImageIOFactory::CreateImageIO(probeFileName.c_str(),
						::itk::ImageIOFactory::ReadMode);

			if (!imageIO)
			{
				mapDefaultExceptionMacro( <<
										  "No ImageIO found for given file. Please check if the file exists and has a supported format. File:"
										  << probeFileName);
				return;
			}

			// Now that we found the appropriate ImageIO class, ask it to
			// read the meta data from the image file.
			imageIO->SetFileName(probeFileName.c_str());
			imageIO->ReadImageInformation();

			this->_loadedComponentType = imageIO->GetComponentType();
			this->_loadedPixelType = imageIO->GetPixelType();

			if (this->_loadedPixelType == ::itk::ImageIOBase::RGB && imageIO->GetNumberOfComponents() == 1)
			{
				//if only one channel per pixel handle as scalar as long as RGB etc. is not supported
				this->_loadedPixelType = ::itk::ImageIOBase::SCALAR;
			}

			this->_loadedComponentTypeStr = imageIO->GetComponentTypeAsString(this->_loadedComponentType);
			this->_loadedPixelTypeStr = imageIO->GetPixelTypeAsString(this->_loadedPixelType);
			this->_loadedDimensions = imageIO->GetNumberOfDimensions();

			if (this->_seriesReadStyle == ImageSeriesReadStyle::Numeric &&
				this->_loadedDimensions == 2)
			{
				this->_loadedDimensions = 3; //it is a stack of 2D images -> 3D
			}

			if (this->_loadedDimensions < 2 || this->_loadedDimensions > 3)
			{
				mapDefaultExceptionMacro( <<
										  "The file uses a number of dimensions that is not supported in this application. PixelType: " <<
										  this->_loadedPixelTypeStr << "; ComponentType: " << this->_loadedComponentTypeStr <<
										  "; Number of dimension: " << this->_loadedDimensions);
			}

			switch (_loadedPixelType)
			{
				case ::itk::ImageIOBase::SCALAR:
				{
					if (this->_loadedDimensions == 2)
					{
						loadScalar<2>();
					}
					else
					{
						loadScalar<3>();
					}

					break;
				}

				default:
				{
					mapDefaultExceptionMacro( <<
											  "The file uses a pixel type that is not supported in this application. PixelType: " <<
											  this->_loadedPixelTypeStr << "; ComponentType: " << this->_loadedComponentTypeStr <<
											  "; Number of pixel channels: " << imageIO->GetNumberOfComponents() <<
											  "; Number of image dimensions: " << this->_loadedDimensions);
				}
			}

			_upToDate = true;
		};


		template <unsigned int IDimension>
		void
		GenericImageReader::
		loadScalar()
		{
			// Use the pixel type to instantiate the appropriate reader
			switch (this->_loadedComponentType)
			{
				case ::itk::ImageIOBase::UCHAR:
				{
					this->_spImage = readImage<unsigned char, unsigned char, IDimension>(_fileName, _seriesReadStyle,
									 false, 0, 0, _upperSeriesLimit, &_dictionaryArray);
					break;
				}

				case ::itk::ImageIOBase::CHAR:
				{
					this->_spImage = readImage<char, char, IDimension>(_fileName, _seriesReadStyle, false, 0, 0,
									 _upperSeriesLimit, &_dictionaryArray);
					break;
				}

				case ::itk::ImageIOBase::USHORT:
				{
					this->_spImage = readImage<unsigned short, unsigned short, IDimension>(_fileName, _seriesReadStyle,
									 false, 0, 0, _upperSeriesLimit, &_dictionaryArray);
					break;
				}

				case ::itk::ImageIOBase::SHORT:
				{
					this->_spImage = readImage<short, short, IDimension>(_fileName, _seriesReadStyle, false, 0, 0,
									 _upperSeriesLimit, &_dictionaryArray);
					break;
				}

				case ::itk::ImageIOBase::UINT:
				{
					this->_spImage = readImage<unsigned int, unsigned int, IDimension>(_fileName, _seriesReadStyle,
									 false, 0, 0, _upperSeriesLimit, &_dictionaryArray);
					break;
				}

				case ::itk::ImageIOBase::INT:
				{
					this->_spImage = readImage<int, int, IDimension>(_fileName, _seriesReadStyle, false, 0, 0,
									 _upperSeriesLimit, &_dictionaryArray);
					break;
				}

				case ::itk::ImageIOBase::ULONG:
				{
					this->_spImage = readImage<unsigned long, unsigned long, IDimension>(_fileName, _seriesReadStyle,
									 false, 0, 0, _upperSeriesLimit, &_dictionaryArray);
					break;
				}

				case ::itk::ImageIOBase::LONG:
				{
					this->_spImage = readImage<long, long, IDimension>(_fileName, _seriesReadStyle, false, 0, 0,
									 _upperSeriesLimit, &_dictionaryArray);
					break;
				}

				case ::itk::ImageIOBase::FLOAT:
				{
					this->_spImage = readImage<float, float, IDimension>(_fileName, _seriesReadStyle, false, 0, 0,
									 _upperSeriesLimit, &_dictionaryArray);
					break;
				}

				case ::itk::ImageIOBase::DOUBLE:
				{
					this->_spImage = readImage<double, double, IDimension>(_fileName, _seriesReadStyle, false, 0, 0,
									 _upperSeriesLimit, &_dictionaryArray);
					break;
				}

				default:
				{
					mapDefaultExceptionMacro( <<
											  "The file uses a pixel component type that is not supported in this application. PixelType: " <<
											  this->_loadedPixelTypeStr << "; ComponentType: " << this->_loadedComponentTypeStr <<
											  "; Number of dimension: " << this->_loadedDimensions);
				}
			}
		};

		//template <unsigned int IDimension>
		//void
		//  GenericImageReader::
		//  loadRGB()
		//{
		//  assert(false);
		//  mapDefaultExceptionStaticMacro(<<"RGB support is yet not implemented.");
		//  switch( this->_loadedComponentType )
		//  {
		//  case ::itk::ImageIOBase::UCHAR:
		//    {
		//      this->_spImage = readImageA<::itk::RGBPixel<unsigned char>, ::itk::RGBPixel<unsigned char>, IDimension>(_fileName,_seriesReadStyle);
		//      break;
		//    }
		//  case ::itk::ImageIOBase::CHAR:
		//    {
		//      this->_spImage = readImageA< ::itk::RGBPixel<char>, ::itk::RGBPixel<char>, IDimension>(_fileName,_seriesReadStyle);
		//      break;
		//    }
		//  case ::itk::ImageIOBase::USHORT:
		//    {
		//      this->_spImage = readImageA< ::itk::RGBPixel<unsigned short>, ::itk::RGBPixel<unsigned short>, IDimension>(_fileName,_seriesReadStyle);
		//      break;
		//    }
		//  case ::itk::ImageIOBase::SHORT:
		//    {
		//      this->_spImage = readImageA< ::itk::RGBPixel<short>, ::itk::RGBPixel<short>, IDimension>(_fileName,_seriesReadStyle);
		//      break;
		//    }
		//  case ::itk::ImageIOBase::UINT:
		//    {
		//      this->_spImage = readImageA< ::itk::RGBPixel<unsigned int>, ::itk::RGBPixel<unsigned int>, IDimension>(_fileName,_seriesReadStyle);
		//      break;
		//    }
		//  case ::itk::ImageIOBase::INT:
		//    {
		//      this->_spImage = readImageA< ::itk::RGBPixel<int>, ::itk::RGBPixel<int>, IDimension>(_fileName,_seriesReadStyle);
		//      break;
		//    }
		//  case ::itk::ImageIOBase::ULONG:
		//    {
		//      this->_spImage = readImageA< ::itk::RGBPixel<unsigned long>, ::itk::RGBPixel<unsigned long>, IDimension>(_fileName,_seriesReadStyle);
		//      break;
		//    }
		//  case ::itk::ImageIOBase::LONG:
		//    {
		//      this->_spImage = readImageA< ::itk::RGBPixel<long>, ::itk::RGBPixel<long>, IDimension>(_fileName,_seriesReadStyle);
		//      break;
		//    }
		//  case ::itk::ImageIOBase::FLOAT:
		//    {
		//      this->_spImage = readImageA< ::itk::RGBPixel<float>, ::itk::RGBPixel<float>, IDimension>(_fileName,_seriesReadStyle);
		//      break;
		//    }
		//  case ::itk::ImageIOBase::DOUBLE:
		//    {
		//      this->_spImage = readImageA< ::itk::RGBPixel<double>, ::itk::RGBPixel<double>, IDimension>(_fileName,_seriesReadStyle);
		//      break;
		//    }
		//  default:
		//    {
		//      mapDefaultExceptionMacro(<<"The file uses a pixel component type that is not supported in this application. PixelType: "<<this->_loadedPixelTypeStr<<"; ComponentType: "<<this->_loadedComponentTypeStr<<"; Number of dimension: "<<this->_loadedDimensions);
		//    }
		//  }
		//};

		const core::String&
		GenericImageReader::
		getFileName() const
		{
			return _fileName;
		};


		void
		GenericImageReader::
		setFileName(const core::String& fileName)
		{
			if (fileName != _fileName)
			{
				_upToDate = false;
				_fileName = fileName;
			}
		}


		const unsigned int
		GenericImageReader::
		getUpperSeriesLimit() const
		{
			return _upperSeriesLimit;
		};


		void
		GenericImageReader::
		setUpperSeriesLimit(const unsigned int upperLimit)
		{
			if (upperLimit != _upperSeriesLimit)
			{
				_upToDate = false;
				_upperSeriesLimit = upperLimit;
			};
		};


		const ImageSeriesReadStyle::Type
		GenericImageReader::
		getSeriesReadStyle() const
		{
			return _seriesReadStyle;
		};


		void
		GenericImageReader::
		setSeriesReadStyle(ImageSeriesReadStyle::Type readStyle)
		{
			if (readStyle != _seriesReadStyle)
			{
				_upToDate = false;
				_seriesReadStyle = readStyle;
			};
		};


		GenericImageReader::GenericOutputImageType*
		GenericImageReader::
		GetOutput(unsigned int& loadedDimensions, LoadedPixelType& loadedPixelType,
				  LoadedComponentType& loadedComponentType)
		{
			if (!_upToDate)
			{
				load();
				loadedPixelType = _loadedPixelType;
				loadedComponentType = _loadedComponentType;
				loadedDimensions = _loadedDimensions;
			};

			return _spImage;
		};



		GenericImageReader::
		GenericImageReader()
		{
			_fileName = "";
			_upperSeriesLimit = 255;
			_upToDate = false;
			_seriesReadStyle = ImageSeriesReadStyle::Default;
		};


		GenericImageReader::
		~GenericImageReader()
		{
		};

		const GenericImageReader::MetaDataDictionaryArrayType&
		GenericImageReader::
		getMetaDictionaryArray()
		{
			return _dictionaryArray;
		};

	}
}
