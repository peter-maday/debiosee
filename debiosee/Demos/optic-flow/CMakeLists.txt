set(DEMO_NAME "HornSchunck")
add_executable(${DEMO_NAME} ${DEMO_NAME}.cpp)
target_link_libraries(${DEMO_NAME} debiosee dolfin ITKCommon ITKIO)
