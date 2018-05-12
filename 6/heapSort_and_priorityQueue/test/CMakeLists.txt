cmake_minimum_required(VERSION 2.8)

project(test)
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SOURCE)
add_compile_options(-std=c++11)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
add_executable(${PROJECT_NAME} ${DIR_SOURCE})
