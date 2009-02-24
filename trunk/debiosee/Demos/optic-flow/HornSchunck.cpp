// Copyright (C) 2009 Ali Tonddast-Navaei.
// Licensed under the GNU LGPL Version 2.1.
//
// First added:  2009-02-23

/// Classical Horn & Schunck optic flow

#include "debiosee.h"
#include <dolfin.h>
#include "HornSchunck.h"

#include "itkImageFileReader.h"
#include "dbsDoubleFrameDerivativesImageFilter.h"

using namespace debiosee;
using namespace dolfin;

//#define img_file1 "/media/USB-WD-1/data/tests/image_0014.bmp"
//#define img_file2 "/media/USB-WD-1/data/tests/image_0015.bmp"
#define img_file1 "/media/USB-WD-1/data/tests/bad_000.bmp"
#define img_file2 "/media/USB-WD-1/data/tests/bad_001.bmp"
#define img_file_out "/media/USB-WD-1/data/tests/out/out-01.bmp"
#define soln_file "/media/USB-WD-1/data/tests/out/soln.pvd"

#define lambda 1e-4

int main(int, char* [])
{
	message("---------------------------------------");
	message("Debiosee demo");
	message("Classical Horn and Schunck optic flow");
	message("---------------------------------------");

	typedef ITKImage< 2 > ImageType;
	typedef boost::shared_ptr< ImageType > ImagePointerType;
	typedef ImageType::ITKImageType ITKImageType;

	message("--Readering input images");
	typedef itk::ImageFileReader< ITKImageType > ReaderType;
	ReaderType::Pointer reader1 = ReaderType::New();
	ReaderType::Pointer reader2 = ReaderType::New();
	reader1->SetFileName(img_file1);
	reader2->SetFileName(img_file2);

	message("--Calculating image derivatives");
	typedef DoubleFrameDerivativesImageFilter< ITKImageType, ITKImageType > DerivType;
	DerivType::Pointer derivative = DerivType::New();
	derivative->SetInput1(reader1->GetOutput());
	derivative->SetInput2(reader2->GetOutput());
	derivative->Update();

	// Get the image derivatives as debiosee images
	ImagePointerType im_dxI(new ImageType(derivative->GetOutput(0)));
	ImagePointerType im_dyI(new ImageType(derivative->GetOutput(1)));
	ImagePointerType im_dtI(new ImageType(derivative->GetOutput(2)));
//	dtI->write(img_file_out); // Test the output

	message("--Creating image mesh");
	// Creating mesh only needs image size information -- use any images
	ImageMesh imesh(im_dxI);

	message("--Assembling");
	HornSchunckFunctionSpace V(imesh);
	SubSpace Vx(V, 0);
	SubSpace Vy(V, 1);
	ImageFunction dxI(im_dxI, Vx);
	ImageFunction dyI(im_dyI, Vx);
	ImageFunction dtI(im_dtI, Vx);
	HornSchunckBilinearForm a(V, V);
//	a.lambda_ = Constant(lambda);
	a.dxI = dxI;
	a.dyI = dyI;
	HornSchunckLinearForm L(V);
	L.dxI = dxI;
	L.dyI = dyI;
	L.dtI = dtI;

	message("--Solving PDE");
	VariationalProblem pde(a, L);
	pde.set("linear solver", "direct");
//	pde.set("linear solver", "iterative");
	dolfin::Function u;
	pde.solve(u);

	message("--Writing solutions");
	File file(soln_file);
	file << u;

//	plot(u);

    return 0;
}
