// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-21

// TODO: HAS_ITK is temporary and will be removed once
// the image factory is ready


#ifdef HAS_ITK
#include <debiosee/image/ITKImage.h>
#endif // HAS_ITK

using namespace debiosee;

#define img_file "/media/USB-WD-1/data/tests/image_0010.bmp"

int main(int, char* [])
{
	// ITKImage test
#ifdef HAS_ITK
	typedef ITKImage< 2 > Image2DType;
	Image2DType itk_image(img_file);
	std::cout << itk_image.get_size()[0] << ", " << itk_image.get_size()[1] << std::endl;
#endif // HAS_ITK

    return 0;
}
