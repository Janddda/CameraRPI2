cmake_minimum_required (VERSION 2.8)
project (cvlib)

#Find prerequisite packages
include (FindPkgConfig)
pkg_check_modules (OpenCV opencv REQUIRED)
#find_package (OpenCV REQUIRED)
#include_directories (${OpenCV_INCLUDE_DIR})
include_directories (${OpenCV_INCLUDE_DIRS})

set (SOURCE
	camera_rpi2.c
)

set (HEADERS
	camera_rpi2.h
)

# gcc compiler options
if (CMAKE_COMPILER_IS_GNUCC)
	set (CMAKE_C_FLAGS "-std=c99 -Wall -pedantic -gdwarf-3")
	set (CMAKE_CXX_FLAGS "-std=c++11 -Wall -pedantic -gdwarf-3")
endif (CMAKE_COMPILER_IS_GNUCC)

add_library (camera_rpi2 STATIC ${SOURCE} ${HEADERS})
add_executable (cvtest camera_test.c)
#add_executable (cvtest2 camera_test.cpp)

#target_link_libraries(camera_rpi2 LINK_PRIVATE ${OpenCV_LIBS} m)
target_link_libraries(camera_rpi2 LINK_PRIVATE ${OpenCV_LIBRARIES} m)
target_link_libraries(cvtest LINK_PRIVATE camera_rpi2)
#target_link_libraries(cvtest2 LINK_PRIVATE camera_rpi2)