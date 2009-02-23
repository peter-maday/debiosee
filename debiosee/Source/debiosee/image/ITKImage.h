// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-20

#ifndef __ITK_IMAGE_H
#define __ITK_IMAGE_H

#ifdef HAS_ITK

#include <dolfin/common/Variable.h>
#include "GenericImage.h"
#include <dolfin/log/log.h>

#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkRescaleIntensityImageFilter.h>

namespace debiosee
{

/// An image structure interface to Insight Toolkit (ITK).
/// Images of any dimensions can be created, however,
/// only 2 and 3 dimensional images can currently be used to establish a
/// variational problem.

template < unsigned int VImageDimension=2>
class ITKImage : public GenericImage, public dolfin::Variable
{
public:

	/// ITK image pixel type
	typedef double PixelType;

	/// ITK image type
	typedef typename itk::Image< PixelType, VImageDimension> ITKImageType;

	/// ITK image pointer type
	typedef typename ITKImageType::Pointer ImageITKPointerType;

	/// Function pointer type
	typedef GenericImage::FunctionPointerType FunctionPointerType;

	/// Create image from a given ITK image pointer of type itk::SmartPointer
	ITKImage(ImageITKPointerType image_ptr) :
	Variable("I", "an ITK image"),
	_image_ptr(image_ptr)
	{
	};

	/// Create image from a given file
	/// See itk::ImageFileReader for supported file types.
	ITKImage(std::string file_name):
	Variable("I", "an ITK image")
	{
		read(file_name);
	}

	/// Destructor
	virtual ~ITKImage()
	{};

	/// Get image dimension
	virtual const unsigned int get_dimension()
	{
		return _dimension;
	};

	/// Get image size
	virtual const SizeType get_size()
	{
		validate_image_pointer();

		// ITK uses unsigned long for image size type, while DOLFIN mesh sizes are of
		// unsigned int. The following does the casting job.
		const unsigned long *size_ =  _image_ptr->GetBufferedRegion().GetSize().GetSize();
		SizeType size(_dimension);
		for(unsigned int n=0; n<_dimension; n++)
			size[n] = (unsigned int) size_[n];

		return size;
	};

	/// Get image data buffer
	virtual double * get_data()
	{
		validate_image_pointer();

		// Increment the smart pointer reference count,
		// or the pointer should go null.
		_image_ptr->Register();
		return _image_ptr->GetBufferPointer();
	}

	/// Get ITK image type pointer
	virtual ImageITKPointerType get_image_pointer()
	{
		validate_image_pointer();

		return _image_ptr;
	}

	/// Write image data to file
	/// By default pixel type is casted to unsigned char before writing.
	/// See itk::ImageFileWriter for supported file types.
	virtual void write(std::string file_name, bool cast=true)
	{
		validate_image_pointer();

		// TODO: There is a more compact way of doing this.
		if(cast)
		{
			typedef itk::Image< unsigned char, VImageDimension> ITKWriteImageType;
			typedef itk::RescaleIntensityImageFilter< ITKImageType, ITKWriteImageType> CastType;
			typename CastType::Pointer caster = CastType::New();
			caster->SetInput(_image_ptr);
			caster->SetOutputMinimum(0);
			caster->SetOutputMaximum(255);

			typedef itk::ImageFileWriter< ITKWriteImageType> WriterType;
			typename WriterType::Pointer writer = WriterType::New();
			writer->SetFileName(file_name);
			writer->SetInput(caster->GetOutput());
			writer->Write();
		}
		else
		{
			typedef itk::ImageFileWriter< ITKImageType> WriterType;
			typename WriterType::Pointer writer = WriterType::New();
			writer->SetFileName(file_name);
			writer->SetInput(_image_ptr);
			writer->Write();
		}
	};

protected:

	/// Validate image pointer
	void validate_image_pointer()
	{
		if(!_image_ptr)
			dolfin::error("ITK image pointer is null.");
	};

	/// Read image data from file
	/// See itk::ImageFileReader for supported file types.
	virtual void read(std::string file_name)
	{
		typedef itk::ImageFileReader< ITKImageType> ReaderType;
		typename ReaderType::Pointer reader = ReaderType::New();
		reader->SetFileName(file_name);
		reader->Update();
		_image_ptr = reader->GetOutput();
	};

	/// ITK image dimension
	static const unsigned int _dimension = VImageDimension;

	/// ITK image object pointer of type itk::SmartPointer
	ImageITKPointerType _image_ptr;
};

}

#endif // HAS_ITK
#endif
