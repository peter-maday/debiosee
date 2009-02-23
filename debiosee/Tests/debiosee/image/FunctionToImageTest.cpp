// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-22

// TODO: HAS_ITK is temporary and will be removed once
// the image factory is ready


#ifdef HAS_ITK
#include <debiosee/image/ITKImage.h>
#endif // HAS_ITK

#include <debiosee/mesh/ImageToMesh.h>
#include <debiosee/function/ImageFunction.h>
#include <debiosee/image/FunctionToImage.h>
#include "../function/Projection.h"

#include <dolfin.h>

using namespace debiosee;
using namespace dolfin;

#define img_file "/media/USB-WD-1/data/tests/image_0010.bmp"
#define img_file_out "/media/USB-WD-1/data/tests/image_0010_out.bmp"

int main(int, char* [])
{
#ifdef HAS_ITK

	message("--Creating image... ");
	typedef ITKImage< 2 > ImageType;
	typedef boost::shared_ptr< ImageType > ImagePointerType;
	ImagePointerType image(new ImageType(img_file));
	message("  [Done]");

	message("--Creating image mesh...");
	ImageToMesh i2m(image);
	Mesh imesh = i2m.get_mesh();
	std::cout << imesh.str() << std::endl;
	message("  [Done]");

	message("--Creating image function...");
	boost::shared_ptr<ProjectionFunctionSpace> V(new ProjectionFunctionSpace(imesh));
	ImageFunction f(image, V);
	message("--Interpolating image function...");
	f.interpolate();
	message("  [Done]");

	message("--Converting back image from function...");
	FunctionToImage f2i(f);
//	FunctionToImage::ImagePointerType fimage = f2i.get_image();
//	message("--Writing the image...");
//	fimage->write(img_file_out);
	message("  [Done]");

#endif // HAS_ITK

    return 0;
}
