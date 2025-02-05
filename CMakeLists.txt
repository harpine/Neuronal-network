cmake_minimum_required(VERSION 2.6)
project(Neuron_network)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -W -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
option(test "Build tests." ON)

include_directories("/usr/local/include" ${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)
add_executable(neuron_network src/main.cpp src/random.cpp src/network.cpp src/neuron.cpp src/inhibitoryNeuron.cpp src/excitatoryNeuron.cpp src/simulation.cpp)

if (test)
  enable_testing()
  find_package(GTest)
  if (NOT GTEST_FOUND)
    set(GTEST_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include)
    set(GTEST_BOTH_LIBRARIES libgtest.a libgtest_main.a)
  endif(NOT GTEST_FOUND)
  include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/test)
  add_executable (Test test/main.cpp src/random.cpp src/network.cpp src/neuron.cpp src/inhibitoryNeuron.cpp src/excitatoryNeuron.cpp src/simulation.cpp)
  target_link_libraries(Test ${GTEST_BOTH_LIBRARIES} pthread)
  add_test(main_Test Test)
endif(test)

find_package(Doxygen)
if (DOXYGEN_FOUND)
        add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)

