// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-21

// TODO: HAS_ITK is temporary and will be removed once
// the image factory is ready


#ifdef HAS_ITK
#include "ITKImage.h"
#endif // HAS_ITK

#include "ImageMesh.h"

using namespace debiosee;
using namespace dolfin;

#define img_file "/media/USB-WD-1/data/tests/image_0010.bmp"

int main(int, char* [])
{
#ifdef HAS_ITK
	typedef ITKImage< 2 > ImageType;
	typedef boost::shared_ptr< ImageType > ImagePointerType;
	ImagePointerType image(new ImageType(img_file));

	ImageMesh mesh(image);
	std::cout << mesh.str() << std::endl;
#endif // HAS_ITK

    return 0;
}
