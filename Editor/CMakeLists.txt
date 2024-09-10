cmake_minimum_required(VERSION 3.16)

project(Editor)

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(Editor ${SOURCES} ${HEADERS})
target_include_directories(Editor PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(Editor PUBLIC ${CMAKE_SOURCE_DIR/Balkan3D/include})
target_include_directories(Editor PUBLIC ${CMAKE_SOURCE_DIR}/vendors/include)
target_include_directories(Balkan3DEngine PUBLIC ${CMAKE_SOURCE_DIR}/vendors/include/glad)
if(WIN32)
    target_link_libraries(Editor PUBLIC ${CMAKE_SOURCE_DIR}/vendors/lib/GLFW/glfw3.lib)
    target_link_libraries(Editor ${CMAKE_SOURCE_DIR}/build/Balkan3D/Balkan3D.lib)
else()
    target_link_libraries(Editor PUBLIC /usr/lib64/libglfw.so.3)
    target_link_libraries(Editor PUBLIC ${CMAKE_SOURCE_DIR}/build/Balkan3D/libBalkan3DEngine.so)
endif(WIN32)


install(TARGETS Editor RUNTIME DESTINATION bin)