cmake_minimum_required(VERSION 3.0.2)
project(ros_basics)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ros_basics
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(timer_basics src/timer_basics.cpp)
add_executable(timer_callback src/timer_callback.cpp)
add_executable(timer_publisher_service src/timer_publisher_service.cpp)


target_link_libraries(timer_basics ${catkin_LIBRARIES})
target_link_libraries(timer_callback ${catkin_LIBRARIES})
target_link_libraries(timer_publisher_service ${catkin_LIBRARIES})
