# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (Computer_Graphics_Labs)

find_package(OpenGL REQUIRED)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory!" )
endif()

# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

include_directories(
	external/glfw-3.1.2/include/
	external/glew-1.13.0/include/
	external/glm-0.9.7.1/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# ==============================================================================
# Lab01
add_executable(Lab01_Intro_to_c++
	Lab01_Intro_to_c++/Lab01_Intro_to_c++.cpp
	Lab01_Intro_to_c++/Car.cpp
	Lab01_Intro_to_c++/Car.hpp
	Lab01_Intro_to_c++/Student.cpp
	Lab01_Intro_to_c++/Student.hpp
)
target_link_libraries(Lab01_Intro_to_c++
	${ALL_LIBS}
)

# ==============================================================================
# Lab02
add_executable(Lab02_Basic_shapes 
	Lab02_Basic_shapes/Lab02_Basic_shapes.cpp
	Lab02_Basic_shapes/vertexShader.glsl
	Lab02_Basic_shapes/fragmentShader.glsl

	common/shader.hpp
)
target_link_libraries(Lab02_Basic_shapes
	${ALL_LIBS}
)

# Xcode and Visual working directories
set_target_properties(Lab02_Basic_shapes PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Lab02_Basic_shapes/")
create_target_launcher(Lab02_Basic_shapes WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Lab02_Basic_shapes/")
create_default_target_launcher(Lab02_Basic_shapes WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Lab02_Basic_shapes/") # tut 1 is not the default or people would complain that tut 2 doesn't work

# ==============================================================================
# Lab03
add_executable(Lab03_Textures
	Lab03_Textures/Lab03_Textures.cpp
	Lab03_Textures/vertexShader.glsl
	Lab03_Textures/fragmentShader.glsl

	common/shader.hpp
	common/texture.hpp
	common/stb_image.hpp
)
target_link_libraries(Lab03_Textures
	${ALL_LIBS}
)

# Xcode and Visual working directories
set_target_properties(Lab03_Textures PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Lab03_Textures/")
create_target_launcher(Lab03_Textures WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Lab03_Textures/")

# ==============================================================================
# Lab04
add_executable(Lab04_Vectors_and_matrices
	Lab04_Vectors_and_matrices/Lab04_Vectors_and_matrices.cpp
)
target_link_libraries(Lab04_Vectors_and_matrices
	${ALL_LIBS}
)

# Xcode and Visual working directories
set_target_properties(Lab04_Vectors_and_matrices PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Lab04_Vectors_and_matrices/")
create_target_launcher(Lab04_Vectors_and_matrices WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Lab04_Vectors_and_matrices/")

# ==============================================================================
# Lab05
add_executable(Lab05_Transformations
	Lab05_Transformations/Lab05_Transformations.cpp
	Lab05_Transformations/vertexShader.glsl
	Lab05_Transformations/fragmentShader.glsl

	common/shader.hpp
	common/texture.hpp
	common/stb_image.hpp
	common/maths.hpp
	common/maths.cpp
)
target_link_libraries(Lab05_Transformations
	${ALL_LIBS}
)

# Xcode and Visual working directories
set_target_properties(Lab05_Transformations PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Lab05_Transformations/")
create_target_launcher(Lab05_Transformations WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Lab05_Transformations/")

# ==============================================================================
# Lab06
add_executable(Lab06_3D_worlds
	Lab06_3D_worlds/Lab06_3D_worlds.cpp
	Lab06_3D_worlds/vertexShader.glsl
	Lab06_3D_worlds/fragmentShader.glsl

	common/shader.hpp
	common/texture.hpp
	common/stb_image.hpp
	common/maths.hpp
	common/maths.cpp
	common/camera.hpp
	common/camera.cpp
)
target_link_libraries(Lab06_3D_worlds
	${ALL_LIBS}
)

# Xcode and Visual working directories
set_target_properties(Lab06_3D_worlds PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Lab06_3D_worlds/")
create_target_launcher(Lab06_3D_worlds WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Lab06_3D_worlds/")

# ==============================================================================
# Lab07
add_executable(Lab07_Moving_the_camera
	Lab07_Moving_the_camera/Lab07_Moving_the_camera.cpp
	Lab07_Moving_the_camera/vertexShader.glsl
	Lab07_Moving_the_camera/fragmentShader.glsl

	common/shader.hpp
	common/texture.hpp
	common/stb_image.hpp
	common/maths.hpp
	common/maths.cpp
	common/camera.hpp
	common/camera.cpp
)
target_link_libraries(Lab07_Moving_the_camera
	${ALL_LIBS}
)

# Xcode and Visual working directories
set_target_properties(Lab07_Moving_the_camera PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Lab07_Moving_the_camera/")
create_target_launcher(Lab07_Moving_the_camera WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Lab07_Moving_the_camera/")


# ==============================================================================
# Lab08
add_executable(Lab08_Lighting
	Lab08_Lighting/Lab08_Lighting.cpp
	Lab08_Lighting/vertexShader.glsl
	Lab08_Lighting/fragmentShader.glsl
	Lab08_Lighting/lightVertexShader.glsl
	Lab08_Lighting/lightFragmentShader.glsl
	Lab08_Lighting/multipleLightsFragmentShader.glsl

	common/shader.hpp
	common/texture.hpp
	common/stb_image.hpp
	common/maths.hpp
	common/maths.cpp
	common/camera.hpp
	common/camera.cpp
	common/model.hpp
	common/model.cpp
)
target_link_libraries(Lab08_Lighting
	${ALL_LIBS}
)

# Xcode and Visual working directories
set_target_properties(Lab08_Lighting PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Lab08_Lighting/")
create_target_launcher(Lab08_Lighting WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Lab08_Lighting/")

# ==============================================================================
# Lab09
add_executable(Lab09_Normal_maps
	Lab09_Normal_maps/Lab09_Normal_maps.cpp
	Lab09_Normal_maps/vertexShader.glsl
	Lab09_Normal_maps/fragmentShader.glsl
	Lab09_Normal_maps/lightVertexShader.glsl
	Lab09_Normal_maps/lightFragmentShader.glsl

	common/shader.hpp
	common/texture.hpp
	common/stb_image.hpp
	common/maths.hpp
	common/maths.cpp
	common/camera.hpp
	common/camera.cpp
	common/model.hpp
	common/model.cpp
	common/light.hpp
	common/light.cpp
)
target_link_libraries(Lab09_Normal_maps
	${ALL_LIBS}
)

# Xcode and Visual working directories
set_target_properties(Lab09_Normal_maps PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Lab09_Normal_maps/")
create_target_launcher(Lab09_Normal_maps WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Lab09_Normal_maps/")

# ==============================================================================
# Lab10
add_executable(Lab10_Quaternions
	Lab10_Quaternions/Lab10_Quaternions.cpp
	Lab10_Quaternions/vertexShader.glsl
	Lab10_Quaternions/fragmentShader.glsl
	Lab09_Normal_maps/lightVertexShader.glsl
	Lab09_Normal_maps/lightFragmentShader.glsl

	common/shader.hpp
	common/texture.hpp
	common/stb_image.hpp
	common/maths.hpp
	common/maths.cpp
	common/camera.hpp
	common/camera.cpp
	common/model.hpp
	common/model.cpp
	common/light.hpp
	common/light.cpp
)
target_link_libraries(Lab10_Quaternions
	${ALL_LIBS}
)

# Xcode and Visual working directories
set_target_properties(Lab10_Quaternions PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Lab10_Quaternions/")
create_target_launcher(Lab10_Quaternions WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Lab10_Quaternions/")

# ==============================================================================
if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

add_custom_command(
   TARGET Lab01_Intro_to_c++ POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Lab01_Intro_to_c++${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/Lab01_Intro_to_c++/"
)

add_custom_command(
   TARGET Lab02_Basic_shapes POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Lab02_Basic_shapes${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/Lab02_Basic_shapes/"
)

add_custom_command(
	TARGET Lab03_Textures POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Lab03_Textures${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/Lab03_Textures/"
)

add_custom_command(
	TARGET Lab04_Vectors_and_matrices POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Lab04_Vectors_and_matrices${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/Lab04_Vectors_and_matrices/"
)

add_custom_command(
	TARGET Lab05_Transformations POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Lab05_Transformations${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/Lab05_Transformations/"
)

add_custom_command(
	TARGET Lab06_3D_worlds POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Lab06_3D_worlds${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/Lab06_3D_worlds/"
)

add_custom_command(
	TARGET Lab07_Moving_the_camera POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Lab07_Moving_the_camera${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/Lab07_Moving_the_camera/"
)

add_custom_command(
	TARGET Lab08_Lighting POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Lab08_Lighting${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/Lab08_Lighting/"
)

add_custom_command(
	TARGET Lab09_Normal_maps POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Lab09_Normal_maps${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/Lab09_Normal_maps/"
)

add_custom_command(
	TARGET Lab10_Quaternions POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Lab10_Quaternions${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/Lab10_Quaternions/"
)

elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

