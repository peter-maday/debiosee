// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-21

#include "ImageFunction.h"
#include <dolfin/mesh/UnitSquare.h>
#include <dolfin/mesh/UnitCube.h>

using namespace debiosee;

//-----------------------------------------------------------------------------
ImageFunction::ImageFunction(ImagePointerType image, FunctionSpacePointerType V) :
	dolfin::Function(V)
{
	Init(image);
}

//-----------------------------------------------------------------------------
ImageFunction::ImageFunction(ImagePointerType image, const dolfin::FunctionSpace& V) :
	dolfin::Function(V)
{
	Init(image);
}

//-----------------------------------------------------------------------------
void ImageFunction::Init(ImagePointerType image)
{
	_dim = image->get_dimension();
	if((_dim < 2) || (_dim > 3))
		dolfin::error("Input image is of dimension %d. Currently dimensions 2 and 3 are supported.",
				_dim);

	_size = image->get_size();
	_data = image->get_data();
	_image = image;
}

//-----------------------------------------------------------------------------
void ImageFunction::eval(double* values, const double* x) const
{
	int i, j, k, index;
	switch(_dim)
	{
	case 2:
		i = int((_size[0] - 1) * x[0]);
		j = int((_size[1] - 1) * x[1]);
		index = i + (_size[0] * j);
		values[0] = _data[index];
		break;
	case 3:
		i = int((_size[0] - 1) * x[0]);
		j = int((_size[1] - 1) * x[1]);
		k = int((_size[2] - 1) * x[2]);
		index = i + (_size[0] * j) + (_size[0] * _size[1] * k);
		values[0] = _data[index];
		break;
	default:
		dolfin::error("Cannot evaluate a function from image of dimension %d.\n Currently dimensions 2 and 3 are supported.",
				_dim);
	};
}
