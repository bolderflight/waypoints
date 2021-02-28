cmake_minimum_required(VERSION 3.13)
# Project information
project(Waypoints
	VERSION 2.0.0
	DESCRIPTION "Library to store and retrieve waypoint data"
	LANGUAGES CXX
)
# Add the library target
add_library(waypoints INTERFACE)
# Setup include directories 
target_include_directories(waypoints INTERFACE /include)

# Example and test if this project is built separately
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
	# Add the example target
	add_executable(waypoints_example examples/waypoints_example.cc)
	# Add the includes
	target_include_directories(waypoints_example PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	)
	# Link libraries to the example target
	target_link_libraries(waypoints_example
		PRIVATE 
			waypoints
	)
endif()
