cmake_minimum_required(VERSION 3.10)

# Set the project name
project(DemProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(dem_mng main.cpp dem.cpp dem_manager.cpp)

# Find and include necessary packages
find_package(Boost REQUIRED)
find_package(fmt REQUIRED)
find_package(OpenCV REQUIRED)
find_package(GDAL REQUIRED)
find_package(TBB REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# Include directories
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${fmt_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${GDAL_INCLUDE_DIRS})
include_directories(${TBB_INCLUDE_DIRS})
include_directories(${PQXX_INCLUDE_DIRS})

# Link libraries
target_link_libraries(dem_mng ${Boost_LIBRARIES} fmt::fmt ${OpenCV_LIBS} ${GDAL_LIBRARIES} ${TBB_LIBRARIES} ${PQXX_LIBRARIES} tbb)