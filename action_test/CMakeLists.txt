cmake_minimum_required(VERSION 2.8.3)
project(action_test)

set(PACKAGE_DEPENDS
  roscpp
  std_msgs
  actionlib
  actionlib_msgs
  control_msgs
)

find_package(catkin REQUIRED COMPONENTS ${PACKAGE_DEPENDS} message_generation)

catkin_package(
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS ${PACKAGE_DEPENDS}
  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(server src/server.cpp)
target_link_libraries(server ${catkin_LIBRARIES})
add_dependencies(server ${catkin_EXPORTED_TARGETS})

add_executable(client src/client.cpp)
target_link_libraries(client ${catkin_LIBRARIES})
add_dependencies(client ${catkin_EXPORTED_TARGETS})

if(CATKIN_ENABLE_TESTING)
  find_package(rostest)
  add_rostest_gtest(test_client test/test.test src/test_client.cpp)
  target_link_libraries(test_client ${catkin_LIBRARIES})
  add_dependencies(test_client ${catkin_EXPORTED_TARGETS})
endif()
