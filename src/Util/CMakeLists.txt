set(GML_SOURCES

	GML/Constants.h
	GML/Utils.h

	GML/Numbers/Complex.h
	GML/Numbers/Complex.cpp
	#GML/Numbers/Quaternion.h
	#GML/Numbers/Quaternion.cpp

	GML/LinearAlgebra/Vec2f.h
	GML/LinearAlgebra/Vec2f.cpp
	GML/LinearAlgebra/Mat2f.h
	GML/LinearAlgebra/Mat2f.cpp
	GML/LinearAlgebra/Vec3f.h
	GML/LinearAlgebra/Vec3f.cpp
	GML/LinearAlgebra/Mat3f.h
	GML/LinearAlgebra/Mat3f.cpp
	GML/LinearAlgebra/Vec4f.h
	GML/LinearAlgebra/Vec4f.cpp
	GML/LinearAlgebra/Mat4f.h
	GML/LinearAlgebra/Mat4f.cpp

)

add_library(lib_gml ${GML_SOURCES})

# Apply project options to this library
target_link_libraries(lib_gml PRIVATE project::project_options project::project_warnings)

# Library build
target_include_directories(lib_gml PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_features(lib_gml PUBLIC cxx_std_20)
target_compile_definitions(lib_gml PUBLIC SAMPLE_LIBRARY_STATIC_DEFINE)
