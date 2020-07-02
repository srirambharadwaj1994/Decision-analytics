# Decision-analytics
We have used C++/gecode for implementation
for windowns user use the below for Cmake:

//cmake_minimum_required(VERSION 3.13)
//project(DA_cat_assignment)

//set(CMAKE_CXX_STANDARD 14)

//INCLUDE_DIRECTORIES(BEFORE "C:/Program Files/Gecode/include")
//INCLUDE_DIRECTORIES(BEFORE "C:/Program Files/Gecode/bin")

//Change below to your target folders
add_executable(DA_cat_assignment cat_house.cpp)

target_link_libraries(DA_cat_assignment "C:/Program Files/Gecode/lib/GecodeDriver-5-1-0-r-x64.lib")
target_link_libraries(DA_cat_assignment "C:/Program Files/Gecode/lib/GecodeFlatZinc-5-1-0-r-x64.lib")
target_link_libraries(DA_cat_assignment "C:/Program Files/Gecode/lib/GecodeFloat-5-1-0-r-x64.lib")
target_link_libraries(DA_cat_assignment "C:/Program Files/Gecode/lib/GecodeGist-5-1-0-r-x64.lib")
target_link_libraries(DA_cat_assignment "C:/Program Files/Gecode/lib/GecodeInt-5-1-0-r-x64.lib")
target_link_libraries(DA_cat_assignment "C:/Program Files/Gecode/lib/GecodeKernel-5-1-0-r-x64.lib")
target_link_libraries(DA_cat_assignment "C:/Program Files/Gecode/lib/GecodeMinimodel-5-1-0-r-x64.lib")
target_link_libraries(DA_cat_assignment "C:/Program Files/Gecode/lib/GecodeSearch-5-1-0-r-x64.lib")
target_link_libraries(DA_cat_assignment "C:/Program Files/Gecode/lib/GecodeSet-5-1-0-r-x64.lib")
target_link_libraries(DA_cat_assignment "C:/Program Files/Gecode/lib/GecodeSupport-5-1-0-r-x64.lib")
