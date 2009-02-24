// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-20

#ifndef __IMAGE_MESH_H
#define __IMAGE_MESH_H

#include <dolfin/mesh/Mesh.h>
#include <dolfin/mesh/UnitSquare.h>
#include <boost/shared_ptr.hpp>
#include "GenericImage.h"

namespace debiosee
{

/// <Description>

class ImageMesh : public dolfin::Mesh
{
public:

	/// Generic image pointer type
	typedef boost::shared_ptr< GenericImage > ImagePointerType;

	/// Create mesh by a given image
	ImageMesh(const ImagePointerType image);
};

}

#endif
