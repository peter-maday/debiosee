%module debiosee

// Import dolfin swig interface
%import dolfin/swig/dolfin.i

%{
#include <dolfin.h>
#include <debiosee/debiosee.h>
%}

%include debiosee_ignores.i

%include debiosee_smart_pointers.i

%include debiosee_headers.i

%include debiosee_templates.i
