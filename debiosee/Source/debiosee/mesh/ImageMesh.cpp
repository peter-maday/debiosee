// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-24

#include "ImageMesh.h"
#include <dolfin/mesh/UnitSquare.h>
#include <dolfin/mesh/UnitCube.h>

using namespace debiosee;

//-----------------------------------------------------------------------------
ImageMesh::ImageMesh(const ImagePointerType image)
	: dolfin::Mesh()
{
	unsigned int dim = image->get_dimension();
	GenericImage::SizeType size = image->get_size();
	dolfin::Mesh mesh;

	switch(dim)
	{
	case 2:
		mesh = dolfin::UnitSquare(size[0] - 1, size[1] - 1);
		break;
	case 3:
		mesh = dolfin::UnitCube(size[0] - 1, size[1] - 1, size[2] - 1);
		break;
	default:
		dolfin::error("Cannot create a mesh from image of dimension %d.\n Currently dimensions 2 and 3 are supported.",
				dim);
	};

	static_cast<Mesh&>(*this) = mesh;
}

