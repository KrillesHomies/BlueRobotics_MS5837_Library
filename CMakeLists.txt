cmake_minimum_required(VERSION 2.8.3)
project(ms5837)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES unicorn_roborio_bridge
  CATKIN_DEPENDS roscpp sensor_msgs 
#  DEPENDS system_lib
)

catkin_package()

include_directories(
  include
  ${BOOST_DIR}
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node src/ms5837_node.cpp src/MS5837.cpp)
target_link_libraries(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_LIBRARIES})
target_link_libraries (${PROJECT_NAME}_node wiringPi)
