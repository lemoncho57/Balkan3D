cmake_minimum_required(VERSION 3.16)

project(Balkan3DEngine)

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_library(Balkan3DEngine SHARED ${SOURCES} ${CMAKE_SOURCE_DIR}/vendors/include/glad/glad.c ${CMAKE_SOURCE_DIR}/vendors/include/stb_image/stb_image.cpp ${HEADERS})
target_include_directories(Balkan3DEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Balkan3DEngine PUBLIC ${CMAKE_SOURCE_DIR}/vendors/include)
target_include_directories(Balkan3DEngine PUBLIC ${CMAKE_SOURCE_DIR}/vendors/include/glad)
#target_link_directories(Balkan3DEngine PUBLIC ${CMAKE_SOURCE_DIR}/vendors/lib)
if(WIN32)
target_link_libraries(Balkan3DEngine PUBLIC ${CMAKE_SOURCE_DIR}/vendors/lib/GLFW/glfw3.lib)
else()
target_link_libraries(Balkan3DEngine PUBLIC /usr/lib64/libglfw.so.3)
endif(WIN32)


target_compile_definitions(Balkan3DEngine PUBLIC BALKAN3D_EXPORT)

#install(TARGETS Balkan3DEngine LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)