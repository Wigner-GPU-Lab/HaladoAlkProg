project (hello)
add_executable(hello main.cpp)
set_target_properties(hello PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)