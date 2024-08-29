cmake_minimum_required(VERSION 3.16)

project(Editor)

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(Editor ${SOURCES} ${HEADERS})
target_include_directories(Editor PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(Editor PUBLIC ${CMAKE_SOURCE_DIR}/vendors/include)
target_include_directories(Balkan3DEngine PUBLIC ${CMAKE_SOURCE_DIR}/vendors/include/glad)
target_link_directories(Editor PUBLIC ${CMAKE_SOURCE_DIR}/vendors/lib/GLFW)
target_link_libraries(Editor Balkan3DEngine)

install(TARGETS Editor RUNTIME DESTINATION bin)