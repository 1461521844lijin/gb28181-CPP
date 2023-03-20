cmake_minimum_required(VERSION 3.10.2)
project(gb28181_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(src)

# 方便修改全局变量
function(update_cached name value)
  set("${name}" "${value}" CACHE INTERNAL "*** Internal ***" FORCE)
endfunction()

function(update_cached_list name)
  set(_tmp_list "${${name}}")
  list(APPEND _tmp_list "${ARGN}")
  list(REMOVE_DUPLICATES _tmp_list)
  update_cached(${name} "${_tmp_list}")
endfunction()

set(CMAKE_CXX_FLAGS "-ffunction-sections -fdata-sections -Wall -std=c++11 -DPOSIX -DDEBUG_ -w")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdpart/ZLToolKit/src)
add_subdirectory(3rdpart)

link_directories(${PROJECT_SOURCE_DIR}/lib/m64x86/)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
find_package(glog)

file(GLOB_RECURSE gb28181_src ${CMAKE_SOURCE_DIR}/src/gb28181/*.cpp  ${CMAKE_SOURCE_DIR}/src/gb28181/*.c)
file(GLOB_RECURSE webserver_src  
        ${CMAKE_SOURCE_DIR}/src/application/*.cpp 
        ${CMAKE_SOURCE_DIR}/src/application/service/*.cpp)
file(GLOB_RECURSE util_src  ${CMAKE_SOURCE_DIR}/src/utils/*.cpp)
file(GLOB_RECURSE zlmedia_src  ${CMAKE_SOURCE_DIR}/src/zlmedia/*.cpp)


set(app 
        src/App.cpp
        src/ErrorHandler.cpp
)


set(EXECUTABLE_OUTPUT_PATH ./bin)

add_definitions(
        -DOATPP_SWAGGER_RES_PATH="${CMAKE_SOURCE_DIR}/include/oatpp-1.3.0/bin/oatpp-swagger/res"
        -DDEV_CONFIG_PATH="${CMAKE_SOURCE_DIR}/config/dev_config.json"
)


add_executable(
gb28181_cpp
        ${app}
        ${gb28181_src}
        ${webserver_src}
        ${util_src}
        ${zlmedia_src}

)

        
target_link_libraries(gb28181_cpp 
        pthread 
        eXosip2 osip2 osipparser2  
        ssl crypto resolv yaml  
        zltoolkit
        ${CONAN_LIBS})


add_executable(
        ptzcmd
        test/ptz_test.cpp
)