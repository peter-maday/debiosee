from ffc import *

# Reserved variables for forms
(a, L, M) = (None, None, None)

# Reserved variable for element
element = None

# Copyright (C) 2009 Ali Tonddast-Navaei
# Licensed under the GNU LGPL Version 2.1.
#
# First added:  2009-02-23


elementS = FiniteElement("Lagrange", "triangle", 1)
elementV = VectorElement("Lagrange", "triangle", 1, 2)

v = TestFunction(elementV)
u = TrialFunction(elementV)
#gradI = Function(elementV)
dxI = Function(elementS)
dyI = Function(elementS)
dtI = Function(elementS)
lambda_ = Constant("triangle")

# This can be used after implementing vector images
#a = ( dot(u, gradI)*dot(v, gradI) + lambda_*dot(grad(u), grad(v)) ) * dx
#L = -dtI * dot(v, gradI) * dx

a = ( (u[0]*dxI + u[1]*dyI)*(v[0]*dxI + v[1]*dyI) + 2e-2*dot(grad(u), grad(v)) ) * dx
L = -dtI * (v[0]*dxI + v[1]*dyI) * dx

compile([a, L, M, element], "HornSchunck", options={'external_signature': None, 'language': 'dolfin', 'blas': False, 'form_postfix': True, 'precision': '15', 'cpp optimize': False, 'split_implementation': False, 'quadrature_points': False, 'output_dir': '.', 'representation': 'tensor', 'cache_dir': None, 'optimize': False}, global_variables=globals())
