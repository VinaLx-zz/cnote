cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_INSTALL_PREFIX /home/xuemq12/)

project(CNote)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Infra SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Executor SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Helpers SOURCES)

add_executable(cnote ${SOURCES})

install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/bin/cnote
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE SETUID
        GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
        RENAME note)

target_link_libraries(cnote crypt)
