// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-20

#ifndef __IMAGE_TO_MESH_H
#define __IMAGE_TO_MESH_H

#include <dolfin/mesh/Mesh.h>
#include <boost/shared_ptr.hpp>
#include "debiosee/image/GenericImage.h"

namespace debiosee
{

/// <Description>

class ImageToMesh
{
public:

	/// Generic image pointer type
	typedef boost::shared_ptr< GenericImage > ImagePointerType;

	/// Mesh pointer type
	typedef boost::shared_ptr< dolfin::Mesh > MeshPointerType;

	/// Create mesh by a given image
	ImageToMesh(const ImagePointerType image);

	/// Get the output mesh created based on the input image
	const dolfin::Mesh& get_mesh();

protected:

	/// Output mesh
	dolfin::Mesh _mesh;
};

}

#endif
