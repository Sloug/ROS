cmake_minimum_required(VERSION 3.0.2)
project(husky_highlevel_controller_client)

## Use C++11
add_definitions(--std=c++11)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  geometry_msgs
  visualization_msgs
  husky_highlevel_controller_msgs
  tf
  tf2
  tf2_ros

)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS
    include
#  LIBRARIES
  CATKIN_DEPENDS
    roscpp
    sensor_msgs
    geometry_msgs
    visualization_msgs
    tf
    tf2
    tf2_ros
    husky_highlevel_controller_msgs
#  DEPENDS
)

###########
## Build ##
###########
add_executable(${PROJECT_NAME}
  src/husky_highlevel_controller_client.cpp
)
target_link_libraries( 
  husky_highlevel_controller_client
  ${catkin_LIBRARIES}
)
## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)




## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)
