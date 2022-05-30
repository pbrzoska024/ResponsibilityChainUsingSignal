cmake_minimum_required(VERSION 3.22)
project(ResponsibilityChain)

set(CMAKE_CXX_STANDARD 17)

message(STATUS "start running cmake...")

find_package(Boost 1.71.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

add_executable( BoostTest main.cpp)

if(Boost_FOUND)

    target_link_libraries(BoostTest ${Boost_LIBRARIES})

endif()

add_executable(ResponsibilityChain main.cpp)
