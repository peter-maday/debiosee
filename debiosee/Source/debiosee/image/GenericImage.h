// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-20

#ifndef __GENERIC_IMAGE_H
#define __GENERIC_IMAGE_H

#include <dolfin/common/Array.h>
#include <dolfin/function/Function.h>

namespace debiosee
{

/// A generic image structure interface to external image processing libraries.
/// Since PDE problems are based on double-type data, only double-type
/// images are considered. It is advised to perform any pre-/post-processing
/// image evaluations with a less computationally-expensive type, such as
/// unsigned char, and cast the type to/from double when using this interface.

class GenericImage
{
public:

	/// Self pointer type
	typedef boost::shared_ptr< GenericImage > Pointer;

	/// Image size type
	typedef dolfin::Array< unsigned int > SizeType;

	/// Function pointer type
	typedef boost::shared_ptr< dolfin::Function > FunctionPointerType;

	/// Destructor
	virtual ~GenericImage()
	{
	};

	/// Get image dimension
	virtual const unsigned int get_dimension() = 0;

	/// Get image size
	virtual const SizeType get_size() = 0;

	/// Get image data buffer
	virtual double * get_data() = 0;

	/// Read image data from file
	virtual void read(std::string file_name) = 0;

    /// Write image data to file
};

}

#endif
