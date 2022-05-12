cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(BarberShop VERSION 1.0)

include_directories(include)

set(SRC_FILES src/main.cpp src/logicManager.cpp src/barberShop.cpp src/barber.cpp src/customer.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)