// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-21

#ifndef __IMAGE_FUNCTION_H
#define __IMAGE_FUNCTION_H

#include <dolfin/function/Function.h>
#include <dolfin/function/FunctionSpace.h>
#include <boost/shared_ptr.hpp>
#include "debiosee/image/GenericImage.h"

namespace debiosee
{

/// <Description>

class ImageFunction : public dolfin::Function
{
public:

	/// Self pointer type
	typedef boost::shared_ptr< ImageFunction > Pointer;

	/// Generic image pointer type
	typedef GenericImage::Pointer ImagePointerType;

	/// Function space pointer type
	typedef boost::shared_ptr< dolfin::FunctionSpace > FunctionSpacePointerType;

	/// Create function from an image pointer and function space pointer
	ImageFunction(ImagePointerType image, FunctionSpacePointerType V);

	/// Create function from an image pointer and function space reference
	ImageFunction(ImagePointerType image, const dolfin::FunctionSpace& V);

	/// Override function evaluation
	void eval(double* values, const double* x) const;

protected:

	/// Image pointer based on which the mesh is created
	ImagePointerType _image;

	/// Image dimension
	unsigned int _dim;

	/// Image size
	GenericImage::SizeType _size;

	/// Image data
	double * _data;

	/// Initialise
	void Init(ImagePointerType image);
};

}

#endif
