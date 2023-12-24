cmake_minimum_required(VERSION 3.16.0)

project(PIM-attention)

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

if(NOT NR_TASKLETS)
  set(NR_TASKLETS 17)
  message(WARNING "NR_TASKLETS is " ${NR_TASKLETS})
endif()

# For googletest
## if you do not want to download it after you run build.sh clean
## you can put the zip file into the $HOME/local/repo/googletest directory
if(EXISTS $ENV{HOME}/local/repo/googletest)
  message(WARNING "googletest found")
  set(REPO_GOOGLETEST "file://$ENV{HOME}/local/repo/googletest/v1.14.0.zip")
else()
  message(WARNING "googletest not found, need to download")
  set(REPO_GOOGLETEST "https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip")
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL ${REPO_GOOGLETEST}
)
FetchContent_MakeAvailable(googletest)

set(UPMEM_SDK_DIR "$ENV{UPMEM_SDK_DIR}")
if(NOT UPMEM_SDK_DIR)
    message(FATAL_ERROR "environment variable UPMEM_SDK_DIR is not set")
    exit()
endif()

if(WIN32)
    set(CMAKE_CXX_COMPILER "MSVC")
elseif(UNIX)
    set(CMAKE_CXX_COMPILER "g++")
endif()

# set(CMAKE_C_FLAGS "-g -O3 -Wall")
set(CMAKE_CXX_FLAGS "-g -pthread -fopenmp -O3 -Wall -std=c++17")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/attention SRC_ATTENTION)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/model SRC_MODEL)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/util SRC_UTIL)

add_executable(host_app host.cpp ${SRC_ATTENTION} ${SRC_MODEL} ${SRC_UTIL})
target_include_directories(host_app PRIVATE . ${CMAKE_CURRENT_SOURCE_DIR}/attention)
target_include_directories(host_app PRIVATE . ${CMAKE_CURRENT_SOURCE_DIR}/model)
target_include_directories(host_app PRIVATE . ${CMAKE_CURRENT_SOURCE_DIR}/util)
target_include_directories(host_app PRIVATE . ${UPMEM_SDK_DIR}/include/dpu)
target_link_directories(host_app PRIVATE ${UPMEM_SDK_DIR}/lib)
target_link_libraries(host_app dpu)

set(UPMEM_C_COMPILER ${UPMEM_SDK_DIR}/bin/dpu-upmem-dpurte-clang)

if(NOT EXECUTABLE_OUTPUT_PATH)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
endif()

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/dpu DPU_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/util DPU_UTIL_SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/model DPU_MODEL_SOURCES)

file(GLOB DPU_HEADERS "dpu/*.h")

set(DPU_TASK_NAME dpu_task)
add_custom_target(${DPU_TASK_NAME} ALL
    COMMAND ${UPMEM_C_COMPILER} -O3 -fgnu89-inline
            -DNR_TASKLETS=${NR_TASKLETS}
            -DSTACK_SIZE_DEFAULT=2048
            -I${CMAKE_CURRENT_SOURCE_DIR}/dpu
            -I${CMAKE_CURRENT_SOURCE_DIR}/util
            -I${CMAKE_CURRENT_SOURCE_DIR}/model
            ${DPU_SOURCES} ${DPU_UTIL_SOURCES} ${DPU_MODEL_SOURCES}
            -o ${EXECUTABLE_OUTPUT_PATH}/${DPU_TASK_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${DPU_SOURCES}
            ${DPU_HEADERS}
    VERBATIM)

install(PROGRAMS ${EXECUTABLE_OUTPUT_PATH}/${DPU_TASK_NAME} DESTINATION bin)

# Build tests:
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/tests SRC_TEST)
add_executable(test ${SRC_TEST} ${SRC_ATTENTION} ${SRC_MODEL} ${SRC_UTIL})
target_include_directories(test PRIVATE . ${CMAKE_CURRENT_SOURCE_DIR}/attention)
target_include_directories(test PRIVATE . ${CMAKE_CURRENT_SOURCE_DIR}/model)
target_include_directories(test PRIVATE . ${CMAKE_CURRENT_SOURCE_DIR}/util)
target_include_directories(test PRIVATE . ${UPMEM_SDK_DIR}/include/dpu)
target_link_directories(test PRIVATE ${UPMEM_SDK_DIR}/lib)
target_link_libraries(test dpu)
target_link_libraries(test gtest_main)
add_test(NAME example_test COMMAND test)
