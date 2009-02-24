set(TEST_CLASS "ImageMeshTest")
add_executable(${TEST_CLASS} ${TEST_CLASS}.cpp)
target_link_libraries(${TEST_CLASS} debiosee dolfin ITKCommon ITKIO)
