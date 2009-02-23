// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-22

#include "FunctionToImage.h"
#include <dolfin/function/FunctionSpace.h>
#include <dolfin/mesh/Mesh.h>

using namespace debiosee;

//-----------------------------------------------------------------------------
FunctionToImage::FunctionToImage(const dolfin::Function& function)
{
	// Make sure there is some data to create an image from
	if (!function.has_vector())
		dolfin::error("Cannot create an image from a Function with no vector.");

	// Determine the output image dimension
	unsigned int dim = function.function_space().mesh().geometry().dim();

	// TODO: how to get the image size in each dimension?
	// Determine the output image size
//	GenericImage::SizeType size(dim);
//	for(unsigned int n=0; n<dim; n++)
//	{
//	}
}

//-----------------------------------------------------------------------------
const FunctionToImage::ImagePointerType FunctionToImage::get_image()
{
	return _image;
}
