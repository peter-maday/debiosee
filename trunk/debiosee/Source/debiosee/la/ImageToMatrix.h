// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-25

#ifndef __IMAGE_TO_MATRIX_H
#define __IMAGE_TO_MATRIX_H

#include <dolfin/la/Matrix.h>
#include <boost/shared_ptr.hpp>
#include "GenericImage.h"

namespace debiosee
{

/// <Description>

class ImageToMatrix
{
public:

	/// Matrix pointer type
	typedef boost::shared_ptr< dolfin::Matrix > MatrixPointerType;

	/// Generic image pointer type
	typedef boost::shared_ptr< GenericImage > ImagePointerType;

	/// Create matrix by a given image
	ImageToMatrix(const ImagePointerType image);

	/// Get the output matrix created based on the input image
	MatrixPointerType get_matrix();

protected:

	/// Output matrix
	MatrixPointerType _matrix;
};

}

#endif
