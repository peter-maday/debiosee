set(TEST_CLASS "GenericImageTest")
add_executable(${TEST_CLASS} ${TEST_CLASS}.cpp)
target_link_libraries(${TEST_CLASS} debiosee dolfin ITKCommon ITKIO)

set(TEST_CLASS "FunctionToImageTest")
add_executable(${TEST_CLASS} ${TEST_CLASS}.cpp)
target_link_libraries(${TEST_CLASS} debiosee dolfin ITKCommon ITKIO)

