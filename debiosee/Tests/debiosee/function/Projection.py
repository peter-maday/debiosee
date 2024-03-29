from ffc import *

# Reserved variables for forms
(a, L, M) = (None, None, None)

# Reserved variable for element
element = None

# Copyright (C) 2009 Ali Tonddast-Navaei
# Licensed under the GNU LGPL Version 2.1.
#
# First added:  2009-02-21


element = FiniteElement("Lagrange", "triangle", 1)

v = TestFunction(element)
u = TrialFunction(element)
f = Function(element)

a = v*u*dx
L = v*f*dx

compile([a, L, M, element], "Projection", options={'external_signature': None, 'language': 'dolfin', 'blas': False, 'form_postfix': True, 'precision': '15', 'cpp optimize': False, 'split_implementation': False, 'quadrature_points': False, 'output_dir': '.', 'representation': 'tensor', 'cache_dir': None, 'optimize': False}, global_variables=globals())
