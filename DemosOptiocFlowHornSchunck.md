![http://debiosee.googlecode.com/svn/trunk/debiosee/Publish/Brand/Debiosee.png](http://debiosee.googlecode.com/svn/trunk/debiosee/Publish/Brand/Debiosee.png)

---


# Demo: Classical Horn-Schunck optic flow #

_The full c++ code for this demo can be found [here](http://code.google.com/p/debiosee/source/browse/trunk/debiosee/Demos/optic-flow/)._

## Overview ##
The [Horn-Schunck](http://en.wikipedia.org/wiki/Horn%E2%80%93Schunck_method) method is a well-known differrential [optic flow](http://en.wikipedia.org/wiki/Optical_Flow) technique which performs motion estimation based on global smoothness assumption. This demo tries to minimize the functional:

![http://debiosee.googlecode.com/svn/trunk/debiosee/Publish/Web/Demos/OpticFlow/eq01.png](http://debiosee.googlecode.com/svn/trunk/debiosee/Publish/Web/Demos/OpticFlow/eq01.png)

, where _I_(**x**) is the image brightness value, defined over the domain Ω, and **u**(**x**) stands for the velocity (displacement) field which registers two successive images by minimising the functional. The first part of the functional is the data term which satisfies the _Brightness Constancy Constraint_ in its linear form. Having this constraint by itself leads to the infamous [aperture problem](http://en.wikipedia.org/wiki/Aperture_problem#The_aperture_problem). The second term of the functional tries to alleviate this ill-posedness by regularization. The coefficient λ is a user input which balances the data term and regularization term contributions. The value of this number is found empirically by the user and the solutions are normally very sensitive to it.

**Fig 1** shows a typical set of input images processed by _Debiosee_ to obtain the registering velocity field. As expected, due to the global smoothness assumption, the velocity field at discontinuities, as seen around the edge of the moving objects, is not sharp.

|![http://debiosee.googlecode.com/svn/trunk/debiosee/Publish/Web/Demos/OpticFlow/demos-op-hs-01.gif](http://debiosee.googlecode.com/svn/trunk/debiosee/Publish/Web/Demos/OpticFlow/demos-op-hs-01.gif)|![http://debiosee.googlecode.com/svn/trunk/debiosee/Publish/Web/Demos/OpticFlow/demos-op-hs-02.png](http://debiosee.googlecode.com/svn/trunk/debiosee/Publish/Web/Demos/OpticFlow/demos-op-hs-02.png)|
|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|**Fig 1.a.** The input double-frame.                                                                                                                                                                 |**Fig 1.b.** The PDE solutions shown as velocity vectors with velocity magnitude in background.                                                                                                      |

## Implementation ##

The weak form of the functional is given by:

![http://debiosee.googlecode.com/svn/trunk/debiosee/Publish/Web/Demos/OpticFlow/eq02.png](http://debiosee.googlecode.com/svn/trunk/debiosee/Publish/Web/Demos/OpticFlow/eq02.png)

The above equation can be written in the variational form syntax as:

```
# HornSchunck.form

elementS = FiniteElement("Lagrange", "triangle", 1)
elementV = VectorElement("Lagrange", "triangle", 1, 2)

v = TestFunction(elementV)
u = TrialFunction(elementV)
dxI = Function(elementS)
dyI = Function(elementS)
dtI = Function(elementS)
lambda_ = Constant("triangle") # Do not use 'lambda', Python doesn't like it.

a = ( (u[0]*dxI + u[1]*dyI)*(v[0]*dxI + v[1]*dyI) + 2e-2*dot(grad(u), grad(v)) ) * dx
L = -dtI * (v[0]*dxI + v[1]*dyI) * dx
```

The image spatial derivatives are calculated using a convolution kernel, while the temporal derivative is simply given by the difference of the the double-frame. Details of this can be found in [debiosee::DoubleFrameDerivativesImageFilter](http://code.google.com/p/debiosee/source/browse/trunk/debiosee/Source/debiosee/itk/dbsDoubleFrameDerivativesImageFilter.h) class which is an ITK image filter. After calculating the derivatives, the end of the ITK image pipeline is converted to data of _Debiosee_ image type, simply by internally assigning the image data pointers:

```
// HornSchunck.cpp

typedef ITKImage< 2 > ImageType;
typedef boost::shared_ptr< ImageType > ImagePointerType;

//...

ImagePointerType im_dxI(new ImageType(derivative->GetOutput(0)));
ImagePointerType im_dyI(new ImageType(derivative->GetOutput(1)));
ImagePointerType im_dtI(new ImageType(derivative->GetOutput(2)));

```

Given one of these images, `debiosee::ImageToMesh` creates a `dolfin::UnitSquare` in the 2-dimensional case:

```
// HornSchunck.cpp

ImageToMesh i2m(im_dxI);
Mesh imesh = i2m.get_mesh();
```

Based on the mesh, now it is possible to create a function space using the compiled variational form. At this point we can convert image derivatives to `dolfin::Function` coefficients. This is implemented as `debiosee::ImageFunction`.

```
// HornSchunck.cpp

HornSchunckFunctionSpace V(imesh);
SubSpace Vx(V, 0);
SubSpace Vy(V, 1);
ImageFunction dxI(im_dxI, Vx);
ImageFunction dyI(im_dyI, Vx);
ImageFunction dtI(im_dtI, Vx);
```

Finally, all the requirements are available to prepare the PDE for assembling and solving it:

```
// HornSchunck.cpp

HornSchunckBilinearForm a(V, V);
a.dxI = dxI;
a.dyI = dyI;
HornSchunckLinearForm L(V);
L.dxI = dxI;
L.dyI = dyI;
L.dtI = dtI;

VariationalProblem pde(a, L);
pde.set("linear solver", "direct");
dolfin::Function u;
pde.solve(u);
```