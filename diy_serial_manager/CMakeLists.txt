cmake_minimum_required(VERSION 3.9.1)
########################################################################################################################
# CMake project
########################################################################################################################
project(diy_serial_manager)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-W -Wall -Wextra
          -Wwrite-strings -Wunreachable-code -Wpointer-arith
          -Winit-self -Wredundant-decls
          -Wno-unused-parameter -Wno-unused-function)
endif()

# Required ament packages
find_package(ament_cmake REQUIRED)

# Other dependencies
find_package(serial REQUIRED)
find_package(Threads REQUIRED)

########################################################################################################################
# Settings
########################################################################################################################

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  message(STATUS "${PROJECT_NAME}: Defaulting build type to RelWithDebInfo")
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

if(WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

########################################################################################################################
# Build targets
########################################################################################################################

set(
        src_files
        src/serial_manager.cpp
)

add_library(${PROJECT_NAME} ${src_files})

target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>"
        ${serial_INCLUDE_DIRS}  # Adding serial library's include directories
)


ament_target_dependencies(${PROJECT_NAME}
        serial
)

target_link_libraries(${PROJECT_NAME}
        Threads::Threads
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)
target_compile_definitions(${PROJECT_NAME} PRIVATE -D_USE_MATH_DEFINES)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(${PROJECT_NAME} PUBLIC "ABB_EGM_RWS_MANAGERS_STATIC_DEFINE")
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()

if(MSVC)
  # Force include the export header when using Microsoft Visual C++ compiler.
  target_compile_options(${PROJECT_NAME} PUBLIC "/FI${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_export.h")
endif()

########################################################################################################################
# Installation
########################################################################################################################

# Install library and headers
ament_export_targets(${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(serial Threads)

install(
        DIRECTORY include/
        DESTINATION include
)

install(
        TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

########################################################################################################################
# Finish up
########################################################################################################################

ament_package()