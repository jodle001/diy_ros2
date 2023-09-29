cmake_minimum_required(VERSION 3.8)
project(DIY_ROS2_Driver)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(serial REQUIRED)

set(THIS_PACKAGE_INCLUDE_DEPENDS
        hardware_interface
        pluginlib
        rclcpp
        rclcpp_lifecycle
        std_msgs
        sensor_msgs
        serial
)

# find dependencies
find_package(ament_cmake REQUIRED)

foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${Dependency} REQUIRED)
endforeach()

###########
## Build ##
###########

add_library(
        diy_hardware_interface
        SHARED
        src/diy_hardware_interface.cpp
)
ament_target_dependencies(diy_hardware_interface ${THIS_PACKAGE_INCLUDE_DEPENDS})
target_include_directories(
        diy_hardware_interface
        PRIVATE
        include
)

pluginlib_export_plugin_description_file(hardware_interface diy_hardware_interface.xml)

#############
## Install ##
#############

install(
        TARGETS ${PROJECT_NAME}
        DESTINATION lib
)
install(
        DIRECTORY include/
        DESTINATION include
)

#############
## Testing ##
#############

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # Disable ament_copyright
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  set(ament_cmake_uncrustify_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})
