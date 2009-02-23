// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-22

#ifndef __FUNCTION_TO_IMAGE_H
#define __FUNCTION_TO_IMAGE_H

#include <dolfin/mesh/Mesh.h>
#include <boost/shared_ptr.hpp>
#include "debiosee/image/GenericImage.h"

namespace debiosee
{

/// <Description>

class FunctionToImage
{
public:

	/// Function pointer type
	typedef boost::shared_ptr< dolfin::Function > FunctionPointerType;

	/// Generic image pointer type
	typedef boost::shared_ptr< GenericImage > ImagePointerType;

	/// Create image by a given function
	FunctionToImage(const dolfin::Function& function);

	/// Get the output image created based on the input function
	const ImagePointerType get_image();

protected:

	/// Output image
	ImagePointerType _image;
};

}

#endif
