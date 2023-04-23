cmake_minimum_required(VERSION 3.0.2)
project(pcd_to_rviz)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  pcl_ros
  roscpp
  sensor_msgs
)
include_directories(
  ${catkin_INCLUDE_DIRS}
)
add_executable(pcd_to_rviz src/pcd_to_rviz.cpp)
target_link_libraries(pcd_to_rviz ${catkin_LIBRARIES})
