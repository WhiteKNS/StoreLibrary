# CMakeList.txt : CMake project for StoreApps, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# File name =>
add_library(
  Server          # Target Name 
  SHARED           # Specify that target is a shared library
  RunServer.cpp
  )


set_target_properties(
  Server PROPERTIES CXX_VISIBILITY_PRESET hidden
) 


include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(Server PRIVATE nlohmann_json::nlohmann_json)


# TODO: Add tests and install targets if needed.
