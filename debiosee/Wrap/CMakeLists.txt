# Find Swig
find_package(SWIG REQUIRED)
message(STATUS "--Found SWIG ${SWIG_VERSION}.")
# Minimum for dolfin is 1.3.35, for wrapitk is 1.3.36
set(min_swig_version "1.3.36")
if(${SWIG_VERSION} STRLESS ${min_swig_version})
    message(SEND_ERROR "SWIG ${SWIG_VERSION} is too old to work with Debiosee, minimum required version is ${min_swig_version}.")
endif()
INCLUDE(${SWIG_USE_FILE})

# Find python
# Assuming that dolfin dependenccy already comes with python existance.


# Wrap
set(debiosee_swig_module_name "debiosee")
set(debiosee_swig_interface_file "debiosee.i")
set_source_files_properties(${debiosee_swig_interface_file} PROPERTIES CPLUSPLUS ON)
set_source_files_properties(${debiosee_swig_interface_file} PROPERTIES SWIG_FLAGS ${IMAGE_BACKEND_FLAGS})
swig_add_module(${debiosee_swig_module_name} PYTHON ${debiosee_swig_interface_file})

