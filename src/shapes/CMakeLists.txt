set(MTS_PLUGIN_PREFIX "shapes")

add_plugin(obj         obj.cpp)
add_plugin(ply         ply.cpp)
add_plugin(blender     blender.cpp)
add_plugin(serialized  serialized.cpp)

add_plugin(cylinder    cylinder.cpp)
add_plugin(disk        disk.cpp)
add_plugin(rectangle   rectangle.cpp)

# Register the test directory
add_tests(${CMAKE_CURRENT_SOURCE_DIR}/tests)
