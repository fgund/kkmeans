cmake_minimum_required(VERSION 3.2)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) 
conan_basic_setup(TARGETS)

project(point_generator)
add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(
	${PROJECT_NAME}
PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    CONAN_PKG::dlib
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4 /MD
    )
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

if (MSVC)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/)
endif()
message("CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)


include(CPack)
