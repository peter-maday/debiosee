// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-22

#include "ImageToMatrix.h"
#include <dolfin/function/FunctionSpace.h>
#include <dolfin/mesh/Mesh.h>
#include <dolfin/common/Array.h>

using namespace debiosee;

//-----------------------------------------------------------------------------
ImageToMatrix::ImageToMatrix(const ImagePointerType image)
{
	unsigned int dim = image->get_dimension();
	if(dim != 2)
		dolfin::error("Cannot create a dolfin::Matrix from image of dimension %d.\n Currently only 2D images are supported.",
			dim);

	GenericImage::SizeType size = image->get_size();

	dolfin::Array< unsigned int > rows(size[1]);
	for(unsigned int n=0; n<size[1]; n++)
		rows[n] = n;
	dolfin::Array< unsigned int > cols(size[0]);
	for(unsigned int n=0; n<size[0]; n++)
			cols[n] = n;

	_matrix = MatrixPointerType(new dolfin::Matrix);
	_matrix->resize(size[1], size[0]);
	_matrix->set(image->get_data(), size[1], &rows[0], size[0], &cols[0]);
}

//-----------------------------------------------------------------------------
ImageToMatrix::MatrixPointerType ImageToMatrix::get_matrix()
{
	return _matrix;
}
