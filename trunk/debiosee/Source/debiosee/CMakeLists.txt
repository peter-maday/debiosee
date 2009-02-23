set(DBS_SRC_FILES "" CACHE INTERNAL "Debiosee library source file list.")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/function")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/image")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/mesh")

set(DBS_SRC_FILES
    function/ImageFunction.cpp
    image/FunctionToImage.cpp
    mesh/ImageToMesh.cpp
    )

add_library(debiosee SHARED ${DBS_SRC_FILES})
