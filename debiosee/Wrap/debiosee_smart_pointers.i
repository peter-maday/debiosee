#ifdef SWIG_SHARED_PTR_QNAMESPACE

// debiosee/function
//SWIG_SHARED_PTR_DERIVED(ImageFunction, dolfin::Function, debiosee::ImageFunction)

// debiosee/image
SWIG_SHARED_PTR(FunctionToImage, debiosee::FunctionToImage)
SWIG_SHARED_PTR(GenericImage, debiosee::GenericImage)
SWIG_SHARED_PTR_DERIVED(ITKImage2D, debiosee::GenericImage, ITKImage2D)
//SWIG_SHARED_PTR_DERIVED(ITKImage3D, debiosee::GenericImage, ITKImage3D)

// debiosee/mesh
SWIG_SHARED_PTR(ImageToMesh, debiosee::ImageToMesh)

#endif //SWIG_SHARED_PTR_QNAMESPACE
