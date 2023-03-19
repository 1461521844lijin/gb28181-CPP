include(CMakeParseArguments)

macro(conan_find_apple_frameworks FRAMEWORKS_FOUND FRAMEWORKS SUFFIX BUILD_TYPE)
    if(APPLE)
        if(CMAKE_BUILD_TYPE)
            set(_BTYPE ${CMAKE_BUILD_TYPE})
        elseif(NOT BUILD_TYPE STREQUAL "")
            set(_BTYPE ${BUILD_TYPE})
        endif()
        if(_BTYPE)
            if(${_BTYPE} MATCHES "Debug|_DEBUG")
                set(CONAN_FRAMEWORKS${SUFFIX} ${CONAN_FRAMEWORKS${SUFFIX}_DEBUG} ${CONAN_FRAMEWORKS${SUFFIX}})
                set(CONAN_FRAMEWORK_DIRS${SUFFIX} ${CONAN_FRAMEWORK_DIRS${SUFFIX}_DEBUG} ${CONAN_FRAMEWORK_DIRS${SUFFIX}})
            elseif(${_BTYPE} MATCHES "Release|_RELEASE")
                set(CONAN_FRAMEWORKS${SUFFIX} ${CONAN_FRAMEWORKS${SUFFIX}_RELEASE} ${CONAN_FRAMEWORKS${SUFFIX}})
                set(CONAN_FRAMEWORK_DIRS${SUFFIX} ${CONAN_FRAMEWORK_DIRS${SUFFIX}_RELEASE} ${CONAN_FRAMEWORK_DIRS${SUFFIX}})
            elseif(${_BTYPE} MATCHES "RelWithDebInfo|_RELWITHDEBINFO")
                set(CONAN_FRAMEWORKS${SUFFIX} ${CONAN_FRAMEWORKS${SUFFIX}_RELWITHDEBINFO} ${CONAN_FRAMEWORKS${SUFFIX}})
                set(CONAN_FRAMEWORK_DIRS${SUFFIX} ${CONAN_FRAMEWORK_DIRS${SUFFIX}_RELWITHDEBINFO} ${CONAN_FRAMEWORK_DIRS${SUFFIX}})
            elseif(${_BTYPE} MATCHES "MinSizeRel|_MINSIZEREL")
                set(CONAN_FRAMEWORKS${SUFFIX} ${CONAN_FRAMEWORKS${SUFFIX}_MINSIZEREL} ${CONAN_FRAMEWORKS${SUFFIX}})
                set(CONAN_FRAMEWORK_DIRS${SUFFIX} ${CONAN_FRAMEWORK_DIRS${SUFFIX}_MINSIZEREL} ${CONAN_FRAMEWORK_DIRS${SUFFIX}})
            endif()
        endif()
        foreach(_FRAMEWORK ${FRAMEWORKS})
            # https://cmake.org/pipermail/cmake-developers/2017-August/030199.html
            find_library(CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND NAMES ${_FRAMEWORK} PATHS ${CONAN_FRAMEWORK_DIRS${SUFFIX}} CMAKE_FIND_ROOT_PATH_BOTH)
            if(CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND)
                list(APPEND ${FRAMEWORKS_FOUND} ${CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND})
            else()
                message(FATAL_ERROR "Framework library ${_FRAMEWORK} not found in paths: ${CONAN_FRAMEWORK_DIRS${SUFFIX}}")
            endif()
        endforeach()
    endif()
endmacro()


#################
###  GLOG
#################
set(CONAN_GLOG_ROOT "/home/lijin/.conan/data/glog/0.6.0/_/_/package/41daf7a791a5dd60128e41caf6439d87e867771a")
set(CONAN_INCLUDE_DIRS_GLOG "/home/lijin/.conan/data/glog/0.6.0/_/_/package/41daf7a791a5dd60128e41caf6439d87e867771a/include")
set(CONAN_LIB_DIRS_GLOG "/home/lijin/.conan/data/glog/0.6.0/_/_/package/41daf7a791a5dd60128e41caf6439d87e867771a/lib")
set(CONAN_BIN_DIRS_GLOG )
set(CONAN_RES_DIRS_GLOG )
set(CONAN_SRC_DIRS_GLOG )
set(CONAN_BUILD_DIRS_GLOG "/home/lijin/.conan/data/glog/0.6.0/_/_/package/41daf7a791a5dd60128e41caf6439d87e867771a/")
set(CONAN_FRAMEWORK_DIRS_GLOG )
set(CONAN_LIBS_GLOG glog)
set(CONAN_PKG_LIBS_GLOG glog)
set(CONAN_SYSTEM_LIBS_GLOG pthread)
set(CONAN_FRAMEWORKS_GLOG )
set(CONAN_FRAMEWORKS_FOUND_GLOG "")  # Will be filled later
set(CONAN_DEFINES_GLOG "-DGFLAGS_DLL_DECLARE_FLAG="
			"-DGFLAGS_DLL_DEFINE_FLAG=")
set(CONAN_BUILD_MODULES_PATHS_GLOG )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_GLOG "GFLAGS_DLL_DECLARE_FLAG="
			"GFLAGS_DLL_DEFINE_FLAG=")

set(CONAN_C_FLAGS_GLOG "")
set(CONAN_CXX_FLAGS_GLOG "")
set(CONAN_SHARED_LINKER_FLAGS_GLOG "")
set(CONAN_EXE_LINKER_FLAGS_GLOG "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_GLOG_LIST "")
set(CONAN_CXX_FLAGS_GLOG_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_GLOG_LIST "")
set(CONAN_EXE_LINKER_FLAGS_GLOG_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_GLOG "${CONAN_FRAMEWORKS_GLOG}" "_GLOG" "")
# Append to aggregated values variable
set(CONAN_LIBS_GLOG ${CONAN_PKG_LIBS_GLOG} ${CONAN_SYSTEM_LIBS_GLOG} ${CONAN_FRAMEWORKS_FOUND_GLOG})


#################
###  OATPP-SWAGGER
#################
set(CONAN_OATPP-SWAGGER_ROOT "/home/lijin/.conan/data/oatpp-swagger/1.3.0/_/_/package/588e9ffc6ea189032a12c5b70c253cd3a49f7daf")
set(CONAN_INCLUDE_DIRS_OATPP-SWAGGER "/home/lijin/.conan/data/oatpp-swagger/1.3.0/_/_/package/588e9ffc6ea189032a12c5b70c253cd3a49f7daf/include/oatpp-1.3.0/oatpp-swagger")
set(CONAN_LIB_DIRS_OATPP-SWAGGER "/home/lijin/.conan/data/oatpp-swagger/1.3.0/_/_/package/588e9ffc6ea189032a12c5b70c253cd3a49f7daf/lib/oatpp-1.3.0")
set(CONAN_BIN_DIRS_OATPP-SWAGGER )
set(CONAN_RES_DIRS_OATPP-SWAGGER )
set(CONAN_SRC_DIRS_OATPP-SWAGGER )
set(CONAN_BUILD_DIRS_OATPP-SWAGGER )
set(CONAN_FRAMEWORK_DIRS_OATPP-SWAGGER )
set(CONAN_LIBS_OATPP-SWAGGER oatpp-swagger)
set(CONAN_PKG_LIBS_OATPP-SWAGGER oatpp-swagger)
set(CONAN_SYSTEM_LIBS_OATPP-SWAGGER pthread)
set(CONAN_FRAMEWORKS_OATPP-SWAGGER )
set(CONAN_FRAMEWORKS_FOUND_OATPP-SWAGGER "")  # Will be filled later
set(CONAN_DEFINES_OATPP-SWAGGER )
set(CONAN_BUILD_MODULES_PATHS_OATPP-SWAGGER )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_OATPP-SWAGGER )

set(CONAN_C_FLAGS_OATPP-SWAGGER "")
set(CONAN_CXX_FLAGS_OATPP-SWAGGER "")
set(CONAN_SHARED_LINKER_FLAGS_OATPP-SWAGGER "")
set(CONAN_EXE_LINKER_FLAGS_OATPP-SWAGGER "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_OATPP-SWAGGER_LIST "")
set(CONAN_CXX_FLAGS_OATPP-SWAGGER_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_OATPP-SWAGGER_LIST "")
set(CONAN_EXE_LINKER_FLAGS_OATPP-SWAGGER_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_OATPP-SWAGGER "${CONAN_FRAMEWORKS_OATPP-SWAGGER}" "_OATPP-SWAGGER" "")
# Append to aggregated values variable
set(CONAN_LIBS_OATPP-SWAGGER ${CONAN_PKG_LIBS_OATPP-SWAGGER} ${CONAN_SYSTEM_LIBS_OATPP-SWAGGER} ${CONAN_FRAMEWORKS_FOUND_OATPP-SWAGGER})


#################
###  OATPP-POSTGRESQL
#################
set(CONAN_OATPP-POSTGRESQL_ROOT "/home/lijin/.conan/data/oatpp-postgresql/1.3.0/_/_/package/f0f89194917f5af786292314155360abd5ccc2b9")
set(CONAN_INCLUDE_DIRS_OATPP-POSTGRESQL "/home/lijin/.conan/data/oatpp-postgresql/1.3.0/_/_/package/f0f89194917f5af786292314155360abd5ccc2b9/include/oatpp-1.3.0/oatpp-postgresql")
set(CONAN_LIB_DIRS_OATPP-POSTGRESQL "/home/lijin/.conan/data/oatpp-postgresql/1.3.0/_/_/package/f0f89194917f5af786292314155360abd5ccc2b9/lib/oatpp-1.3.0")
set(CONAN_BIN_DIRS_OATPP-POSTGRESQL )
set(CONAN_RES_DIRS_OATPP-POSTGRESQL )
set(CONAN_SRC_DIRS_OATPP-POSTGRESQL )
set(CONAN_BUILD_DIRS_OATPP-POSTGRESQL )
set(CONAN_FRAMEWORK_DIRS_OATPP-POSTGRESQL )
set(CONAN_LIBS_OATPP-POSTGRESQL oatpp-postgresql)
set(CONAN_PKG_LIBS_OATPP-POSTGRESQL oatpp-postgresql)
set(CONAN_SYSTEM_LIBS_OATPP-POSTGRESQL pthread)
set(CONAN_FRAMEWORKS_OATPP-POSTGRESQL )
set(CONAN_FRAMEWORKS_FOUND_OATPP-POSTGRESQL "")  # Will be filled later
set(CONAN_DEFINES_OATPP-POSTGRESQL )
set(CONAN_BUILD_MODULES_PATHS_OATPP-POSTGRESQL )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_OATPP-POSTGRESQL )

set(CONAN_C_FLAGS_OATPP-POSTGRESQL "")
set(CONAN_CXX_FLAGS_OATPP-POSTGRESQL "")
set(CONAN_SHARED_LINKER_FLAGS_OATPP-POSTGRESQL "")
set(CONAN_EXE_LINKER_FLAGS_OATPP-POSTGRESQL "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_OATPP-POSTGRESQL_LIST "")
set(CONAN_CXX_FLAGS_OATPP-POSTGRESQL_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_OATPP-POSTGRESQL_LIST "")
set(CONAN_EXE_LINKER_FLAGS_OATPP-POSTGRESQL_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_OATPP-POSTGRESQL "${CONAN_FRAMEWORKS_OATPP-POSTGRESQL}" "_OATPP-POSTGRESQL" "")
# Append to aggregated values variable
set(CONAN_LIBS_OATPP-POSTGRESQL ${CONAN_PKG_LIBS_OATPP-POSTGRESQL} ${CONAN_SYSTEM_LIBS_OATPP-POSTGRESQL} ${CONAN_FRAMEWORKS_FOUND_OATPP-POSTGRESQL})


#################
###  GFLAGS
#################
set(CONAN_GFLAGS_ROOT "/home/lijin/.conan/data/gflags/2.2.2/_/_/package/7dc25015787468f535fb4a4e937554e5185b7848")
set(CONAN_INCLUDE_DIRS_GFLAGS "/home/lijin/.conan/data/gflags/2.2.2/_/_/package/7dc25015787468f535fb4a4e937554e5185b7848/include")
set(CONAN_LIB_DIRS_GFLAGS "/home/lijin/.conan/data/gflags/2.2.2/_/_/package/7dc25015787468f535fb4a4e937554e5185b7848/lib")
set(CONAN_BIN_DIRS_GFLAGS "/home/lijin/.conan/data/gflags/2.2.2/_/_/package/7dc25015787468f535fb4a4e937554e5185b7848/bin")
set(CONAN_RES_DIRS_GFLAGS )
set(CONAN_SRC_DIRS_GFLAGS )
set(CONAN_BUILD_DIRS_GFLAGS "/home/lijin/.conan/data/gflags/2.2.2/_/_/package/7dc25015787468f535fb4a4e937554e5185b7848/")
set(CONAN_FRAMEWORK_DIRS_GFLAGS )
set(CONAN_LIBS_GFLAGS gflags_nothreads)
set(CONAN_PKG_LIBS_GFLAGS gflags_nothreads)
set(CONAN_SYSTEM_LIBS_GFLAGS pthread m)
set(CONAN_FRAMEWORKS_GFLAGS )
set(CONAN_FRAMEWORKS_FOUND_GFLAGS "")  # Will be filled later
set(CONAN_DEFINES_GFLAGS )
set(CONAN_BUILD_MODULES_PATHS_GFLAGS )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_GFLAGS )

set(CONAN_C_FLAGS_GFLAGS "")
set(CONAN_CXX_FLAGS_GFLAGS "")
set(CONAN_SHARED_LINKER_FLAGS_GFLAGS "")
set(CONAN_EXE_LINKER_FLAGS_GFLAGS "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_GFLAGS_LIST "")
set(CONAN_CXX_FLAGS_GFLAGS_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_GFLAGS_LIST "")
set(CONAN_EXE_LINKER_FLAGS_GFLAGS_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_GFLAGS "${CONAN_FRAMEWORKS_GFLAGS}" "_GFLAGS" "")
# Append to aggregated values variable
set(CONAN_LIBS_GFLAGS ${CONAN_PKG_LIBS_GFLAGS} ${CONAN_SYSTEM_LIBS_GFLAGS} ${CONAN_FRAMEWORKS_FOUND_GFLAGS})


#################
###  LIBUNWIND
#################
set(CONAN_LIBUNWIND_ROOT "/home/lijin/.conan/data/libunwind/1.6.2/_/_/package/fe8a6e628857abec9574898c3e8cfbe2ee6bd7dd")
set(CONAN_INCLUDE_DIRS_LIBUNWIND "/home/lijin/.conan/data/libunwind/1.6.2/_/_/package/fe8a6e628857abec9574898c3e8cfbe2ee6bd7dd/include")
set(CONAN_LIB_DIRS_LIBUNWIND "/home/lijin/.conan/data/libunwind/1.6.2/_/_/package/fe8a6e628857abec9574898c3e8cfbe2ee6bd7dd/lib")
set(CONAN_BIN_DIRS_LIBUNWIND )
set(CONAN_RES_DIRS_LIBUNWIND )
set(CONAN_SRC_DIRS_LIBUNWIND )
set(CONAN_BUILD_DIRS_LIBUNWIND )
set(CONAN_FRAMEWORK_DIRS_LIBUNWIND )
set(CONAN_LIBS_LIBUNWIND unwind-ptrace unwind-setjmp unwind-coredump unwind-generic unwind)
set(CONAN_PKG_LIBS_LIBUNWIND unwind-ptrace unwind-setjmp unwind-coredump unwind-generic unwind)
set(CONAN_SYSTEM_LIBS_LIBUNWIND pthread)
set(CONAN_FRAMEWORKS_LIBUNWIND )
set(CONAN_FRAMEWORKS_FOUND_LIBUNWIND "")  # Will be filled later
set(CONAN_DEFINES_LIBUNWIND )
set(CONAN_BUILD_MODULES_PATHS_LIBUNWIND )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBUNWIND )

set(CONAN_C_FLAGS_LIBUNWIND "")
set(CONAN_CXX_FLAGS_LIBUNWIND "")
set(CONAN_SHARED_LINKER_FLAGS_LIBUNWIND "")
set(CONAN_EXE_LINKER_FLAGS_LIBUNWIND "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBUNWIND_LIST "")
set(CONAN_CXX_FLAGS_LIBUNWIND_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBUNWIND_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBUNWIND "${CONAN_FRAMEWORKS_LIBUNWIND}" "_LIBUNWIND" "")
# Append to aggregated values variable
set(CONAN_LIBS_LIBUNWIND ${CONAN_PKG_LIBS_LIBUNWIND} ${CONAN_SYSTEM_LIBS_LIBUNWIND} ${CONAN_FRAMEWORKS_FOUND_LIBUNWIND})


#################
###  OATPP
#################
set(CONAN_OATPP_ROOT "/home/lijin/.conan/data/oatpp/1.3.0/_/_/package/a2582e1f57e524e15d7e84f4c862d0a472d3216f")
set(CONAN_INCLUDE_DIRS_OATPP "/home/lijin/.conan/data/oatpp/1.3.0/_/_/package/a2582e1f57e524e15d7e84f4c862d0a472d3216f/include/oatpp-1.3.0/oatpp")
set(CONAN_LIB_DIRS_OATPP "/home/lijin/.conan/data/oatpp/1.3.0/_/_/package/a2582e1f57e524e15d7e84f4c862d0a472d3216f/lib/oatpp-1.3.0")
set(CONAN_BIN_DIRS_OATPP )
set(CONAN_RES_DIRS_OATPP )
set(CONAN_SRC_DIRS_OATPP )
set(CONAN_BUILD_DIRS_OATPP )
set(CONAN_FRAMEWORK_DIRS_OATPP )
set(CONAN_LIBS_OATPP oatpp-test oatpp)
set(CONAN_PKG_LIBS_OATPP oatpp-test oatpp)
set(CONAN_SYSTEM_LIBS_OATPP pthread)
set(CONAN_FRAMEWORKS_OATPP )
set(CONAN_FRAMEWORKS_FOUND_OATPP "")  # Will be filled later
set(CONAN_DEFINES_OATPP )
set(CONAN_BUILD_MODULES_PATHS_OATPP )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_OATPP )

set(CONAN_C_FLAGS_OATPP "")
set(CONAN_CXX_FLAGS_OATPP "")
set(CONAN_SHARED_LINKER_FLAGS_OATPP "")
set(CONAN_EXE_LINKER_FLAGS_OATPP "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_OATPP_LIST "")
set(CONAN_CXX_FLAGS_OATPP_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_OATPP_LIST "")
set(CONAN_EXE_LINKER_FLAGS_OATPP_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_OATPP "${CONAN_FRAMEWORKS_OATPP}" "_OATPP" "")
# Append to aggregated values variable
set(CONAN_LIBS_OATPP ${CONAN_PKG_LIBS_OATPP} ${CONAN_SYSTEM_LIBS_OATPP} ${CONAN_FRAMEWORKS_FOUND_OATPP})


#################
###  LIBPQ
#################
set(CONAN_LIBPQ_ROOT "/home/lijin/.conan/data/libpq/14.5/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a")
set(CONAN_INCLUDE_DIRS_LIBPQ "/home/lijin/.conan/data/libpq/14.5/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/include")
set(CONAN_LIB_DIRS_LIBPQ "/home/lijin/.conan/data/libpq/14.5/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/lib")
set(CONAN_BIN_DIRS_LIBPQ "/home/lijin/.conan/data/libpq/14.5/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/bin")
set(CONAN_RES_DIRS_LIBPQ )
set(CONAN_SRC_DIRS_LIBPQ )
set(CONAN_BUILD_DIRS_LIBPQ )
set(CONAN_FRAMEWORK_DIRS_LIBPQ )
set(CONAN_LIBS_LIBPQ pq pgcommon pgcommon_shlib pgport pgport_shlib)
set(CONAN_PKG_LIBS_LIBPQ pq pgcommon pgcommon_shlib pgport pgport_shlib)
set(CONAN_SYSTEM_LIBS_LIBPQ pthread)
set(CONAN_FRAMEWORKS_LIBPQ )
set(CONAN_FRAMEWORKS_FOUND_LIBPQ "")  # Will be filled later
set(CONAN_DEFINES_LIBPQ )
set(CONAN_BUILD_MODULES_PATHS_LIBPQ )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_LIBPQ )

set(CONAN_C_FLAGS_LIBPQ "")
set(CONAN_CXX_FLAGS_LIBPQ "")
set(CONAN_SHARED_LINKER_FLAGS_LIBPQ "")
set(CONAN_EXE_LINKER_FLAGS_LIBPQ "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_LIBPQ_LIST "")
set(CONAN_CXX_FLAGS_LIBPQ_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_LIBPQ_LIST "")
set(CONAN_EXE_LINKER_FLAGS_LIBPQ_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_LIBPQ "${CONAN_FRAMEWORKS_LIBPQ}" "_LIBPQ" "")
# Append to aggregated values variable
set(CONAN_LIBS_LIBPQ ${CONAN_PKG_LIBS_LIBPQ} ${CONAN_SYSTEM_LIBS_LIBPQ} ${CONAN_FRAMEWORKS_FOUND_LIBPQ})


#################
###  XZ_UTILS
#################
set(CONAN_XZ_UTILS_ROOT "/home/lijin/.conan/data/xz_utils/5.2.5/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a")
set(CONAN_INCLUDE_DIRS_XZ_UTILS "/home/lijin/.conan/data/xz_utils/5.2.5/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/include")
set(CONAN_LIB_DIRS_XZ_UTILS "/home/lijin/.conan/data/xz_utils/5.2.5/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/lib")
set(CONAN_BIN_DIRS_XZ_UTILS "/home/lijin/.conan/data/xz_utils/5.2.5/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/bin")
set(CONAN_RES_DIRS_XZ_UTILS )
set(CONAN_SRC_DIRS_XZ_UTILS )
set(CONAN_BUILD_DIRS_XZ_UTILS "/home/lijin/.conan/data/xz_utils/5.2.5/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/")
set(CONAN_FRAMEWORK_DIRS_XZ_UTILS )
set(CONAN_LIBS_XZ_UTILS lzma)
set(CONAN_PKG_LIBS_XZ_UTILS lzma)
set(CONAN_SYSTEM_LIBS_XZ_UTILS pthread)
set(CONAN_FRAMEWORKS_XZ_UTILS )
set(CONAN_FRAMEWORKS_FOUND_XZ_UTILS "")  # Will be filled later
set(CONAN_DEFINES_XZ_UTILS "-DLZMA_API_STATIC")
set(CONAN_BUILD_MODULES_PATHS_XZ_UTILS )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_XZ_UTILS "LZMA_API_STATIC")

set(CONAN_C_FLAGS_XZ_UTILS "")
set(CONAN_CXX_FLAGS_XZ_UTILS "")
set(CONAN_SHARED_LINKER_FLAGS_XZ_UTILS "")
set(CONAN_EXE_LINKER_FLAGS_XZ_UTILS "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_XZ_UTILS_LIST "")
set(CONAN_CXX_FLAGS_XZ_UTILS_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_LIST "")
set(CONAN_EXE_LINKER_FLAGS_XZ_UTILS_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_XZ_UTILS "${CONAN_FRAMEWORKS_XZ_UTILS}" "_XZ_UTILS" "")
# Append to aggregated values variable
set(CONAN_LIBS_XZ_UTILS ${CONAN_PKG_LIBS_XZ_UTILS} ${CONAN_SYSTEM_LIBS_XZ_UTILS} ${CONAN_FRAMEWORKS_FOUND_XZ_UTILS})


#################
###  ZLIB
#################
set(CONAN_ZLIB_ROOT "/home/lijin/.conan/data/zlib/1.2.13/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a")
set(CONAN_INCLUDE_DIRS_ZLIB "/home/lijin/.conan/data/zlib/1.2.13/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/include")
set(CONAN_LIB_DIRS_ZLIB "/home/lijin/.conan/data/zlib/1.2.13/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/lib")
set(CONAN_BIN_DIRS_ZLIB )
set(CONAN_RES_DIRS_ZLIB )
set(CONAN_SRC_DIRS_ZLIB )
set(CONAN_BUILD_DIRS_ZLIB "/home/lijin/.conan/data/zlib/1.2.13/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/")
set(CONAN_FRAMEWORK_DIRS_ZLIB )
set(CONAN_LIBS_ZLIB z)
set(CONAN_PKG_LIBS_ZLIB z)
set(CONAN_SYSTEM_LIBS_ZLIB )
set(CONAN_FRAMEWORKS_ZLIB )
set(CONAN_FRAMEWORKS_FOUND_ZLIB "")  # Will be filled later
set(CONAN_DEFINES_ZLIB )
set(CONAN_BUILD_MODULES_PATHS_ZLIB )
# COMPILE_DEFINITIONS are equal to CONAN_DEFINES without -D, for targets
set(CONAN_COMPILE_DEFINITIONS_ZLIB )

set(CONAN_C_FLAGS_ZLIB "")
set(CONAN_CXX_FLAGS_ZLIB "")
set(CONAN_SHARED_LINKER_FLAGS_ZLIB "")
set(CONAN_EXE_LINKER_FLAGS_ZLIB "")

# For modern cmake targets we use the list variables (separated with ;)
set(CONAN_C_FLAGS_ZLIB_LIST "")
set(CONAN_CXX_FLAGS_ZLIB_LIST "")
set(CONAN_SHARED_LINKER_FLAGS_ZLIB_LIST "")
set(CONAN_EXE_LINKER_FLAGS_ZLIB_LIST "")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND_ZLIB "${CONAN_FRAMEWORKS_ZLIB}" "_ZLIB" "")
# Append to aggregated values variable
set(CONAN_LIBS_ZLIB ${CONAN_PKG_LIBS_ZLIB} ${CONAN_SYSTEM_LIBS_ZLIB} ${CONAN_FRAMEWORKS_FOUND_ZLIB})


### Definition of global aggregated variables ###

set(CONAN_PACKAGE_NAME None)
set(CONAN_PACKAGE_VERSION None)

set(CONAN_SETTINGS_ARCH "x86_64")
set(CONAN_SETTINGS_ARCH_BUILD "x86_64")
set(CONAN_SETTINGS_BUILD_TYPE "Release")
set(CONAN_SETTINGS_COMPILER "gcc")
set(CONAN_SETTINGS_COMPILER_LIBCXX "libstdc++")
set(CONAN_SETTINGS_COMPILER_VERSION "8")
set(CONAN_SETTINGS_OS "Linux")
set(CONAN_SETTINGS_OS_BUILD "Linux")

set(CONAN_DEPENDENCIES glog oatpp-swagger oatpp-postgresql gflags libunwind oatpp libpq xz_utils zlib)
# Storing original command line args (CMake helper) flags
set(CONAN_CMD_CXX_FLAGS ${CONAN_CXX_FLAGS})

set(CONAN_CMD_SHARED_LINKER_FLAGS ${CONAN_SHARED_LINKER_FLAGS})
set(CONAN_CMD_C_FLAGS ${CONAN_C_FLAGS})
# Defining accumulated conan variables for all deps

set(CONAN_INCLUDE_DIRS "/home/lijin/.conan/data/glog/0.6.0/_/_/package/41daf7a791a5dd60128e41caf6439d87e867771a/include"
			"/home/lijin/.conan/data/oatpp-swagger/1.3.0/_/_/package/588e9ffc6ea189032a12c5b70c253cd3a49f7daf/include/oatpp-1.3.0/oatpp-swagger"
			"/home/lijin/.conan/data/oatpp-postgresql/1.3.0/_/_/package/f0f89194917f5af786292314155360abd5ccc2b9/include/oatpp-1.3.0/oatpp-postgresql"
			"/home/lijin/.conan/data/gflags/2.2.2/_/_/package/7dc25015787468f535fb4a4e937554e5185b7848/include"
			"/home/lijin/.conan/data/libunwind/1.6.2/_/_/package/fe8a6e628857abec9574898c3e8cfbe2ee6bd7dd/include"
			"/home/lijin/.conan/data/oatpp/1.3.0/_/_/package/a2582e1f57e524e15d7e84f4c862d0a472d3216f/include/oatpp-1.3.0/oatpp"
			"/home/lijin/.conan/data/libpq/14.5/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/include"
			"/home/lijin/.conan/data/xz_utils/5.2.5/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/include"
			"/home/lijin/.conan/data/zlib/1.2.13/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/include" ${CONAN_INCLUDE_DIRS})
set(CONAN_LIB_DIRS "/home/lijin/.conan/data/glog/0.6.0/_/_/package/41daf7a791a5dd60128e41caf6439d87e867771a/lib"
			"/home/lijin/.conan/data/oatpp-swagger/1.3.0/_/_/package/588e9ffc6ea189032a12c5b70c253cd3a49f7daf/lib/oatpp-1.3.0"
			"/home/lijin/.conan/data/oatpp-postgresql/1.3.0/_/_/package/f0f89194917f5af786292314155360abd5ccc2b9/lib/oatpp-1.3.0"
			"/home/lijin/.conan/data/gflags/2.2.2/_/_/package/7dc25015787468f535fb4a4e937554e5185b7848/lib"
			"/home/lijin/.conan/data/libunwind/1.6.2/_/_/package/fe8a6e628857abec9574898c3e8cfbe2ee6bd7dd/lib"
			"/home/lijin/.conan/data/oatpp/1.3.0/_/_/package/a2582e1f57e524e15d7e84f4c862d0a472d3216f/lib/oatpp-1.3.0"
			"/home/lijin/.conan/data/libpq/14.5/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/lib"
			"/home/lijin/.conan/data/xz_utils/5.2.5/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/lib"
			"/home/lijin/.conan/data/zlib/1.2.13/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/lib" ${CONAN_LIB_DIRS})
set(CONAN_BIN_DIRS "/home/lijin/.conan/data/gflags/2.2.2/_/_/package/7dc25015787468f535fb4a4e937554e5185b7848/bin"
			"/home/lijin/.conan/data/libpq/14.5/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/bin"
			"/home/lijin/.conan/data/xz_utils/5.2.5/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/bin" ${CONAN_BIN_DIRS})
set(CONAN_RES_DIRS  ${CONAN_RES_DIRS})
set(CONAN_FRAMEWORK_DIRS  ${CONAN_FRAMEWORK_DIRS})
set(CONAN_LIBS glog oatpp-swagger oatpp-postgresql gflags_nothreads unwind-ptrace unwind-setjmp unwind-coredump unwind-generic unwind oatpp-test oatpp pq pgcommon pgcommon_shlib pgport pgport_shlib lzma z ${CONAN_LIBS})
set(CONAN_PKG_LIBS glog oatpp-swagger oatpp-postgresql gflags_nothreads unwind-ptrace unwind-setjmp unwind-coredump unwind-generic unwind oatpp-test oatpp pq pgcommon pgcommon_shlib pgport pgport_shlib lzma z ${CONAN_PKG_LIBS})
set(CONAN_SYSTEM_LIBS m pthread ${CONAN_SYSTEM_LIBS})
set(CONAN_FRAMEWORKS  ${CONAN_FRAMEWORKS})
set(CONAN_FRAMEWORKS_FOUND "")  # Will be filled later
set(CONAN_DEFINES "-DLZMA_API_STATIC"
			"-DGFLAGS_DLL_DECLARE_FLAG="
			"-DGFLAGS_DLL_DEFINE_FLAG=" ${CONAN_DEFINES})
set(CONAN_BUILD_MODULES_PATHS  ${CONAN_BUILD_MODULES_PATHS})
set(CONAN_CMAKE_MODULE_PATH "/home/lijin/.conan/data/glog/0.6.0/_/_/package/41daf7a791a5dd60128e41caf6439d87e867771a/"
			"/home/lijin/.conan/data/gflags/2.2.2/_/_/package/7dc25015787468f535fb4a4e937554e5185b7848/"
			"/home/lijin/.conan/data/xz_utils/5.2.5/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/"
			"/home/lijin/.conan/data/zlib/1.2.13/_/_/package/1d877a3df840030e6a8abb74c5ffb9088d08b47a/" ${CONAN_CMAKE_MODULE_PATH})

set(CONAN_CXX_FLAGS " ${CONAN_CXX_FLAGS}")
set(CONAN_SHARED_LINKER_FLAGS " ${CONAN_SHARED_LINKER_FLAGS}")
set(CONAN_EXE_LINKER_FLAGS " ${CONAN_EXE_LINKER_FLAGS}")
set(CONAN_C_FLAGS " ${CONAN_C_FLAGS}")

# Apple Frameworks
conan_find_apple_frameworks(CONAN_FRAMEWORKS_FOUND "${CONAN_FRAMEWORKS}" "" "")
# Append to aggregated values variable: Use CONAN_LIBS instead of CONAN_PKG_LIBS to include user appended vars
set(CONAN_LIBS ${CONAN_LIBS} ${CONAN_SYSTEM_LIBS} ${CONAN_FRAMEWORKS_FOUND})


###  Definition of macros and functions ###

macro(conan_define_targets)
    if(${CMAKE_VERSION} VERSION_LESS "3.1.2")
        message(FATAL_ERROR "TARGETS not supported by your CMake version!")
    endif()  # CMAKE > 3.x
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CONAN_CMD_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CONAN_CMD_C_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${CONAN_CMD_SHARED_LINKER_FLAGS}")


    set(_CONAN_PKG_LIBS_GLOG_DEPENDENCIES "${CONAN_SYSTEM_LIBS_GLOG} ${CONAN_FRAMEWORKS_FOUND_GLOG} CONAN_PKG::gflags CONAN_PKG::libunwind")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_GLOG_DEPENDENCIES "${_CONAN_PKG_LIBS_GLOG_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_GLOG}" "${CONAN_LIB_DIRS_GLOG}"
                                  CONAN_PACKAGE_TARGETS_GLOG "${_CONAN_PKG_LIBS_GLOG_DEPENDENCIES}"
                                  "" glog)
    set(_CONAN_PKG_LIBS_GLOG_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_GLOG_DEBUG} ${CONAN_FRAMEWORKS_FOUND_GLOG_DEBUG} CONAN_PKG::gflags CONAN_PKG::libunwind")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_GLOG_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_GLOG_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_GLOG_DEBUG}" "${CONAN_LIB_DIRS_GLOG_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_GLOG_DEBUG "${_CONAN_PKG_LIBS_GLOG_DEPENDENCIES_DEBUG}"
                                  "debug" glog)
    set(_CONAN_PKG_LIBS_GLOG_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_GLOG_RELEASE} ${CONAN_FRAMEWORKS_FOUND_GLOG_RELEASE} CONAN_PKG::gflags CONAN_PKG::libunwind")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_GLOG_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_GLOG_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_GLOG_RELEASE}" "${CONAN_LIB_DIRS_GLOG_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_GLOG_RELEASE "${_CONAN_PKG_LIBS_GLOG_DEPENDENCIES_RELEASE}"
                                  "release" glog)
    set(_CONAN_PKG_LIBS_GLOG_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_GLOG_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_GLOG_RELWITHDEBINFO} CONAN_PKG::gflags CONAN_PKG::libunwind")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_GLOG_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_GLOG_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_GLOG_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_GLOG_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_GLOG_RELWITHDEBINFO "${_CONAN_PKG_LIBS_GLOG_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" glog)
    set(_CONAN_PKG_LIBS_GLOG_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_GLOG_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_GLOG_MINSIZEREL} CONAN_PKG::gflags CONAN_PKG::libunwind")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_GLOG_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_GLOG_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_GLOG_MINSIZEREL}" "${CONAN_LIB_DIRS_GLOG_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_GLOG_MINSIZEREL "${_CONAN_PKG_LIBS_GLOG_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" glog)

    add_library(CONAN_PKG::glog INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::glog PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_GLOG} ${_CONAN_PKG_LIBS_GLOG_DEPENDENCIES}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GLOG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GLOG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_GLOG_LIST}>

                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_GLOG_RELEASE} ${_CONAN_PKG_LIBS_GLOG_DEPENDENCIES_RELEASE}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GLOG_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GLOG_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_GLOG_RELEASE_LIST}>>

                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_GLOG_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_GLOG_DEPENDENCIES_RELWITHDEBINFO}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GLOG_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GLOG_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_GLOG_RELWITHDEBINFO_LIST}>>

                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_GLOG_MINSIZEREL} ${_CONAN_PKG_LIBS_GLOG_DEPENDENCIES_MINSIZEREL}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GLOG_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GLOG_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_GLOG_MINSIZEREL_LIST}>>

                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_GLOG_DEBUG} ${_CONAN_PKG_LIBS_GLOG_DEPENDENCIES_DEBUG}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GLOG_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GLOG_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_GLOG_DEBUG_LIST}>>)
    set_property(TARGET CONAN_PKG::glog PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_GLOG}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_GLOG_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_GLOG_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_GLOG_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_GLOG_DEBUG}>)
    set_property(TARGET CONAN_PKG::glog PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_GLOG}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_GLOG_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_GLOG_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_GLOG_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_GLOG_DEBUG}>)
    set_property(TARGET CONAN_PKG::glog PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_GLOG_LIST} ${CONAN_CXX_FLAGS_GLOG_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_GLOG_RELEASE_LIST} ${CONAN_CXX_FLAGS_GLOG_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_GLOG_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_GLOG_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_GLOG_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_GLOG_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_GLOG_DEBUG_LIST}  ${CONAN_CXX_FLAGS_GLOG_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES "${CONAN_SYSTEM_LIBS_OATPP-SWAGGER} ${CONAN_FRAMEWORKS_FOUND_OATPP-SWAGGER} CONAN_PKG::oatpp")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES "${_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_OATPP-SWAGGER}" "${CONAN_LIB_DIRS_OATPP-SWAGGER}"
                                  CONAN_PACKAGE_TARGETS_OATPP-SWAGGER "${_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES}"
                                  "" oatpp-swagger)
    set(_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_OATPP-SWAGGER_DEBUG} ${CONAN_FRAMEWORKS_FOUND_OATPP-SWAGGER_DEBUG} CONAN_PKG::oatpp")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_OATPP-SWAGGER_DEBUG}" "${CONAN_LIB_DIRS_OATPP-SWAGGER_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_OATPP-SWAGGER_DEBUG "${_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_DEBUG}"
                                  "debug" oatpp-swagger)
    set(_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_OATPP-SWAGGER_RELEASE} ${CONAN_FRAMEWORKS_FOUND_OATPP-SWAGGER_RELEASE} CONAN_PKG::oatpp")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_OATPP-SWAGGER_RELEASE}" "${CONAN_LIB_DIRS_OATPP-SWAGGER_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_OATPP-SWAGGER_RELEASE "${_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_RELEASE}"
                                  "release" oatpp-swagger)
    set(_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_OATPP-SWAGGER_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_OATPP-SWAGGER_RELWITHDEBINFO} CONAN_PKG::oatpp")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_OATPP-SWAGGER_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_OATPP-SWAGGER_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_OATPP-SWAGGER_RELWITHDEBINFO "${_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" oatpp-swagger)
    set(_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_OATPP-SWAGGER_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_OATPP-SWAGGER_MINSIZEREL} CONAN_PKG::oatpp")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_OATPP-SWAGGER_MINSIZEREL}" "${CONAN_LIB_DIRS_OATPP-SWAGGER_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_OATPP-SWAGGER_MINSIZEREL "${_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" oatpp-swagger)

    add_library(CONAN_PKG::oatpp-swagger INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::oatpp-swagger PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_OATPP-SWAGGER} ${_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-SWAGGER_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-SWAGGER_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_OATPP-SWAGGER_LIST}>

                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_OATPP-SWAGGER_RELEASE} ${_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_RELEASE}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-SWAGGER_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-SWAGGER_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_OATPP-SWAGGER_RELEASE_LIST}>>

                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_OATPP-SWAGGER_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_RELWITHDEBINFO}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-SWAGGER_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-SWAGGER_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_OATPP-SWAGGER_RELWITHDEBINFO_LIST}>>

                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_OATPP-SWAGGER_MINSIZEREL} ${_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_MINSIZEREL}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-SWAGGER_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-SWAGGER_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_OATPP-SWAGGER_MINSIZEREL_LIST}>>

                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_OATPP-SWAGGER_DEBUG} ${_CONAN_PKG_LIBS_OATPP-SWAGGER_DEPENDENCIES_DEBUG}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-SWAGGER_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-SWAGGER_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_OATPP-SWAGGER_DEBUG_LIST}>>)
    set_property(TARGET CONAN_PKG::oatpp-swagger PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_OATPP-SWAGGER}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_OATPP-SWAGGER_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_OATPP-SWAGGER_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_OATPP-SWAGGER_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_OATPP-SWAGGER_DEBUG}>)
    set_property(TARGET CONAN_PKG::oatpp-swagger PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_OATPP-SWAGGER}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_OATPP-SWAGGER_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_OATPP-SWAGGER_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_OATPP-SWAGGER_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_OATPP-SWAGGER_DEBUG}>)
    set_property(TARGET CONAN_PKG::oatpp-swagger PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_OATPP-SWAGGER_LIST} ${CONAN_CXX_FLAGS_OATPP-SWAGGER_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_OATPP-SWAGGER_RELEASE_LIST} ${CONAN_CXX_FLAGS_OATPP-SWAGGER_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_OATPP-SWAGGER_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_OATPP-SWAGGER_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_OATPP-SWAGGER_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_OATPP-SWAGGER_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_OATPP-SWAGGER_DEBUG_LIST}  ${CONAN_CXX_FLAGS_OATPP-SWAGGER_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES "${CONAN_SYSTEM_LIBS_OATPP-POSTGRESQL} ${CONAN_FRAMEWORKS_FOUND_OATPP-POSTGRESQL} CONAN_PKG::oatpp CONAN_PKG::libpq")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES "${_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_OATPP-POSTGRESQL}" "${CONAN_LIB_DIRS_OATPP-POSTGRESQL}"
                                  CONAN_PACKAGE_TARGETS_OATPP-POSTGRESQL "${_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES}"
                                  "" oatpp-postgresql)
    set(_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_OATPP-POSTGRESQL_DEBUG} ${CONAN_FRAMEWORKS_FOUND_OATPP-POSTGRESQL_DEBUG} CONAN_PKG::oatpp CONAN_PKG::libpq")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEBUG}" "${CONAN_LIB_DIRS_OATPP-POSTGRESQL_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_OATPP-POSTGRESQL_DEBUG "${_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_DEBUG}"
                                  "debug" oatpp-postgresql)
    set(_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_OATPP-POSTGRESQL_RELEASE} ${CONAN_FRAMEWORKS_FOUND_OATPP-POSTGRESQL_RELEASE} CONAN_PKG::oatpp CONAN_PKG::libpq")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_OATPP-POSTGRESQL_RELEASE}" "${CONAN_LIB_DIRS_OATPP-POSTGRESQL_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_OATPP-POSTGRESQL_RELEASE "${_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_RELEASE}"
                                  "release" oatpp-postgresql)
    set(_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_OATPP-POSTGRESQL_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_OATPP-POSTGRESQL_RELWITHDEBINFO} CONAN_PKG::oatpp CONAN_PKG::libpq")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_OATPP-POSTGRESQL_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_OATPP-POSTGRESQL_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_OATPP-POSTGRESQL_RELWITHDEBINFO "${_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" oatpp-postgresql)
    set(_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_OATPP-POSTGRESQL_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_OATPP-POSTGRESQL_MINSIZEREL} CONAN_PKG::oatpp CONAN_PKG::libpq")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_OATPP-POSTGRESQL_MINSIZEREL}" "${CONAN_LIB_DIRS_OATPP-POSTGRESQL_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_OATPP-POSTGRESQL_MINSIZEREL "${_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" oatpp-postgresql)

    add_library(CONAN_PKG::oatpp-postgresql INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::oatpp-postgresql PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_OATPP-POSTGRESQL} ${_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-POSTGRESQL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-POSTGRESQL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_OATPP-POSTGRESQL_LIST}>

                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_OATPP-POSTGRESQL_RELEASE} ${_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_RELEASE}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-POSTGRESQL_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-POSTGRESQL_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_OATPP-POSTGRESQL_RELEASE_LIST}>>

                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_OATPP-POSTGRESQL_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_RELWITHDEBINFO}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-POSTGRESQL_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-POSTGRESQL_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_OATPP-POSTGRESQL_RELWITHDEBINFO_LIST}>>

                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_OATPP-POSTGRESQL_MINSIZEREL} ${_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_MINSIZEREL}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-POSTGRESQL_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-POSTGRESQL_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_OATPP-POSTGRESQL_MINSIZEREL_LIST}>>

                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_OATPP-POSTGRESQL_DEBUG} ${_CONAN_PKG_LIBS_OATPP-POSTGRESQL_DEPENDENCIES_DEBUG}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-POSTGRESQL_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP-POSTGRESQL_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_OATPP-POSTGRESQL_DEBUG_LIST}>>)
    set_property(TARGET CONAN_PKG::oatpp-postgresql PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_OATPP-POSTGRESQL}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_OATPP-POSTGRESQL_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_OATPP-POSTGRESQL_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_OATPP-POSTGRESQL_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_OATPP-POSTGRESQL_DEBUG}>)
    set_property(TARGET CONAN_PKG::oatpp-postgresql PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_OATPP-POSTGRESQL}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_OATPP-POSTGRESQL_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_OATPP-POSTGRESQL_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_OATPP-POSTGRESQL_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_OATPP-POSTGRESQL_DEBUG}>)
    set_property(TARGET CONAN_PKG::oatpp-postgresql PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_OATPP-POSTGRESQL_LIST} ${CONAN_CXX_FLAGS_OATPP-POSTGRESQL_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_OATPP-POSTGRESQL_RELEASE_LIST} ${CONAN_CXX_FLAGS_OATPP-POSTGRESQL_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_OATPP-POSTGRESQL_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_OATPP-POSTGRESQL_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_OATPP-POSTGRESQL_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_OATPP-POSTGRESQL_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_OATPP-POSTGRESQL_DEBUG_LIST}  ${CONAN_CXX_FLAGS_OATPP-POSTGRESQL_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES "${CONAN_SYSTEM_LIBS_GFLAGS} ${CONAN_FRAMEWORKS_FOUND_GFLAGS} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES "${_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_GFLAGS}" "${CONAN_LIB_DIRS_GFLAGS}"
                                  CONAN_PACKAGE_TARGETS_GFLAGS "${_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES}"
                                  "" gflags)
    set(_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_GFLAGS_DEBUG} ${CONAN_FRAMEWORKS_FOUND_GFLAGS_DEBUG} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_GFLAGS_DEBUG}" "${CONAN_LIB_DIRS_GFLAGS_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_GFLAGS_DEBUG "${_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_DEBUG}"
                                  "debug" gflags)
    set(_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_GFLAGS_RELEASE} ${CONAN_FRAMEWORKS_FOUND_GFLAGS_RELEASE} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_GFLAGS_RELEASE}" "${CONAN_LIB_DIRS_GFLAGS_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_GFLAGS_RELEASE "${_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_RELEASE}"
                                  "release" gflags)
    set(_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_GFLAGS_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_GFLAGS_RELWITHDEBINFO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_GFLAGS_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_GFLAGS_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_GFLAGS_RELWITHDEBINFO "${_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" gflags)
    set(_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_GFLAGS_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_GFLAGS_MINSIZEREL} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_GFLAGS_MINSIZEREL}" "${CONAN_LIB_DIRS_GFLAGS_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_GFLAGS_MINSIZEREL "${_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" gflags)

    add_library(CONAN_PKG::gflags INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::gflags PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_GFLAGS} ${_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GFLAGS_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GFLAGS_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_GFLAGS_LIST}>

                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_GFLAGS_RELEASE} ${_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_RELEASE}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GFLAGS_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GFLAGS_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_GFLAGS_RELEASE_LIST}>>

                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_GFLAGS_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_RELWITHDEBINFO}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GFLAGS_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GFLAGS_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_GFLAGS_RELWITHDEBINFO_LIST}>>

                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_GFLAGS_MINSIZEREL} ${_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_MINSIZEREL}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GFLAGS_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GFLAGS_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_GFLAGS_MINSIZEREL_LIST}>>

                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_GFLAGS_DEBUG} ${_CONAN_PKG_LIBS_GFLAGS_DEPENDENCIES_DEBUG}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GFLAGS_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_GFLAGS_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_GFLAGS_DEBUG_LIST}>>)
    set_property(TARGET CONAN_PKG::gflags PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_GFLAGS}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_GFLAGS_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_GFLAGS_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_GFLAGS_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_GFLAGS_DEBUG}>)
    set_property(TARGET CONAN_PKG::gflags PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_GFLAGS}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_GFLAGS_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_GFLAGS_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_GFLAGS_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_GFLAGS_DEBUG}>)
    set_property(TARGET CONAN_PKG::gflags PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_GFLAGS_LIST} ${CONAN_CXX_FLAGS_GFLAGS_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_GFLAGS_RELEASE_LIST} ${CONAN_CXX_FLAGS_GFLAGS_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_GFLAGS_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_GFLAGS_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_GFLAGS_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_GFLAGS_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_GFLAGS_DEBUG_LIST}  ${CONAN_CXX_FLAGS_GFLAGS_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBUNWIND} ${CONAN_FRAMEWORKS_FOUND_LIBUNWIND} CONAN_PKG::xz_utils CONAN_PKG::zlib")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBUNWIND}" "${CONAN_LIB_DIRS_LIBUNWIND}"
                                  CONAN_PACKAGE_TARGETS_LIBUNWIND "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES}"
                                  "" libunwind)
    set(_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBUNWIND_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBUNWIND_DEBUG} CONAN_PKG::xz_utils CONAN_PKG::zlib")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBUNWIND_DEBUG}" "${CONAN_LIB_DIRS_LIBUNWIND_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBUNWIND_DEBUG "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_DEBUG}"
                                  "debug" libunwind)
    set(_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBUNWIND_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBUNWIND_RELEASE} CONAN_PKG::xz_utils CONAN_PKG::zlib")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBUNWIND_RELEASE}" "${CONAN_LIB_DIRS_LIBUNWIND_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBUNWIND_RELEASE "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELEASE}"
                                  "release" libunwind)
    set(_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBUNWIND_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBUNWIND_RELWITHDEBINFO} CONAN_PKG::xz_utils CONAN_PKG::zlib")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBUNWIND_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBUNWIND_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBUNWIND_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libunwind)
    set(_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBUNWIND_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBUNWIND_MINSIZEREL} CONAN_PKG::xz_utils CONAN_PKG::zlib")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBUNWIND_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBUNWIND_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBUNWIND_MINSIZEREL "${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libunwind)

    add_library(CONAN_PKG::libunwind INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libunwind PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBUNWIND} ${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_LIBUNWIND_LIST}>

                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBUNWIND_RELEASE} ${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELEASE}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_LIBUNWIND_RELEASE_LIST}>>

                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBUNWIND_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_RELWITHDEBINFO}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_LIBUNWIND_RELWITHDEBINFO_LIST}>>

                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBUNWIND_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_MINSIZEREL}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_LIBUNWIND_MINSIZEREL_LIST}>>

                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBUNWIND_DEBUG} ${_CONAN_PKG_LIBS_LIBUNWIND_DEPENDENCIES_DEBUG}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBUNWIND_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_LIBUNWIND_DEBUG_LIST}>>)
    set_property(TARGET CONAN_PKG::libunwind PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBUNWIND}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBUNWIND_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBUNWIND_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBUNWIND_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBUNWIND_DEBUG}>)
    set_property(TARGET CONAN_PKG::libunwind PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBUNWIND}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBUNWIND_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBUNWIND_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBUNWIND_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBUNWIND_DEBUG}>)
    set_property(TARGET CONAN_PKG::libunwind PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBUNWIND_LIST} ${CONAN_CXX_FLAGS_LIBUNWIND_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBUNWIND_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBUNWIND_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBUNWIND_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBUNWIND_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBUNWIND_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBUNWIND_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBUNWIND_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBUNWIND_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_OATPP_DEPENDENCIES "${CONAN_SYSTEM_LIBS_OATPP} ${CONAN_FRAMEWORKS_FOUND_OATPP} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_OATPP_DEPENDENCIES "${_CONAN_PKG_LIBS_OATPP_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_OATPP}" "${CONAN_LIB_DIRS_OATPP}"
                                  CONAN_PACKAGE_TARGETS_OATPP "${_CONAN_PKG_LIBS_OATPP_DEPENDENCIES}"
                                  "" oatpp)
    set(_CONAN_PKG_LIBS_OATPP_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_OATPP_DEBUG} ${CONAN_FRAMEWORKS_FOUND_OATPP_DEBUG} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_OATPP_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_OATPP_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_OATPP_DEBUG}" "${CONAN_LIB_DIRS_OATPP_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_OATPP_DEBUG "${_CONAN_PKG_LIBS_OATPP_DEPENDENCIES_DEBUG}"
                                  "debug" oatpp)
    set(_CONAN_PKG_LIBS_OATPP_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_OATPP_RELEASE} ${CONAN_FRAMEWORKS_FOUND_OATPP_RELEASE} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_OATPP_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_OATPP_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_OATPP_RELEASE}" "${CONAN_LIB_DIRS_OATPP_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_OATPP_RELEASE "${_CONAN_PKG_LIBS_OATPP_DEPENDENCIES_RELEASE}"
                                  "release" oatpp)
    set(_CONAN_PKG_LIBS_OATPP_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_OATPP_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_OATPP_RELWITHDEBINFO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_OATPP_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_OATPP_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_OATPP_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_OATPP_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_OATPP_RELWITHDEBINFO "${_CONAN_PKG_LIBS_OATPP_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" oatpp)
    set(_CONAN_PKG_LIBS_OATPP_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_OATPP_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_OATPP_MINSIZEREL} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_OATPP_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_OATPP_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_OATPP_MINSIZEREL}" "${CONAN_LIB_DIRS_OATPP_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_OATPP_MINSIZEREL "${_CONAN_PKG_LIBS_OATPP_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" oatpp)

    add_library(CONAN_PKG::oatpp INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::oatpp PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_OATPP} ${_CONAN_PKG_LIBS_OATPP_DEPENDENCIES}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_OATPP_LIST}>

                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_OATPP_RELEASE} ${_CONAN_PKG_LIBS_OATPP_DEPENDENCIES_RELEASE}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_OATPP_RELEASE_LIST}>>

                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_OATPP_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_OATPP_DEPENDENCIES_RELWITHDEBINFO}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_OATPP_RELWITHDEBINFO_LIST}>>

                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_OATPP_MINSIZEREL} ${_CONAN_PKG_LIBS_OATPP_DEPENDENCIES_MINSIZEREL}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_OATPP_MINSIZEREL_LIST}>>

                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_OATPP_DEBUG} ${_CONAN_PKG_LIBS_OATPP_DEPENDENCIES_DEBUG}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_OATPP_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_OATPP_DEBUG_LIST}>>)
    set_property(TARGET CONAN_PKG::oatpp PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_OATPP}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_OATPP_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_OATPP_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_OATPP_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_OATPP_DEBUG}>)
    set_property(TARGET CONAN_PKG::oatpp PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_OATPP}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_OATPP_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_OATPP_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_OATPP_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_OATPP_DEBUG}>)
    set_property(TARGET CONAN_PKG::oatpp PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_OATPP_LIST} ${CONAN_CXX_FLAGS_OATPP_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_OATPP_RELEASE_LIST} ${CONAN_CXX_FLAGS_OATPP_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_OATPP_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_OATPP_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_OATPP_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_OATPP_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_OATPP_DEBUG_LIST}  ${CONAN_CXX_FLAGS_OATPP_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES "${CONAN_SYSTEM_LIBS_LIBPQ} ${CONAN_FRAMEWORKS_FOUND_LIBPQ} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES "${_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBPQ}" "${CONAN_LIB_DIRS_LIBPQ}"
                                  CONAN_PACKAGE_TARGETS_LIBPQ "${_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES}"
                                  "" libpq)
    set(_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_LIBPQ_DEBUG} ${CONAN_FRAMEWORKS_FOUND_LIBPQ_DEBUG} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBPQ_DEBUG}" "${CONAN_LIB_DIRS_LIBPQ_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_LIBPQ_DEBUG "${_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_DEBUG}"
                                  "debug" libpq)
    set(_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_LIBPQ_RELEASE} ${CONAN_FRAMEWORKS_FOUND_LIBPQ_RELEASE} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBPQ_RELEASE}" "${CONAN_LIB_DIRS_LIBPQ_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_LIBPQ_RELEASE "${_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_RELEASE}"
                                  "release" libpq)
    set(_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_LIBPQ_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_LIBPQ_RELWITHDEBINFO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBPQ_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_LIBPQ_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_LIBPQ_RELWITHDEBINFO "${_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" libpq)
    set(_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_LIBPQ_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_LIBPQ_MINSIZEREL} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_LIBPQ_MINSIZEREL}" "${CONAN_LIB_DIRS_LIBPQ_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_LIBPQ_MINSIZEREL "${_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" libpq)

    add_library(CONAN_PKG::libpq INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::libpq PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_LIBPQ} ${_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBPQ_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBPQ_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_LIBPQ_LIST}>

                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_LIBPQ_RELEASE} ${_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_RELEASE}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBPQ_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBPQ_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_LIBPQ_RELEASE_LIST}>>

                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_LIBPQ_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_RELWITHDEBINFO}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBPQ_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBPQ_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_LIBPQ_RELWITHDEBINFO_LIST}>>

                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_LIBPQ_MINSIZEREL} ${_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_MINSIZEREL}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBPQ_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBPQ_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_LIBPQ_MINSIZEREL_LIST}>>

                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_LIBPQ_DEBUG} ${_CONAN_PKG_LIBS_LIBPQ_DEPENDENCIES_DEBUG}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBPQ_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_LIBPQ_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_LIBPQ_DEBUG_LIST}>>)
    set_property(TARGET CONAN_PKG::libpq PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_LIBPQ}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_LIBPQ_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_LIBPQ_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_LIBPQ_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_LIBPQ_DEBUG}>)
    set_property(TARGET CONAN_PKG::libpq PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_LIBPQ}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_LIBPQ_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_LIBPQ_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_LIBPQ_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_LIBPQ_DEBUG}>)
    set_property(TARGET CONAN_PKG::libpq PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_LIBPQ_LIST} ${CONAN_CXX_FLAGS_LIBPQ_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_LIBPQ_RELEASE_LIST} ${CONAN_CXX_FLAGS_LIBPQ_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_LIBPQ_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_LIBPQ_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_LIBPQ_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_LIBPQ_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_LIBPQ_DEBUG_LIST}  ${CONAN_CXX_FLAGS_LIBPQ_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES "${CONAN_SYSTEM_LIBS_XZ_UTILS} ${CONAN_FRAMEWORKS_FOUND_XZ_UTILS} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XZ_UTILS}" "${CONAN_LIB_DIRS_XZ_UTILS}"
                                  CONAN_PACKAGE_TARGETS_XZ_UTILS "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES}"
                                  "" xz_utils)
    set(_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_XZ_UTILS_DEBUG} ${CONAN_FRAMEWORKS_FOUND_XZ_UTILS_DEBUG} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XZ_UTILS_DEBUG}" "${CONAN_LIB_DIRS_XZ_UTILS_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_XZ_UTILS_DEBUG "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_DEBUG}"
                                  "debug" xz_utils)
    set(_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_XZ_UTILS_RELEASE} ${CONAN_FRAMEWORKS_FOUND_XZ_UTILS_RELEASE} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XZ_UTILS_RELEASE}" "${CONAN_LIB_DIRS_XZ_UTILS_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_XZ_UTILS_RELEASE "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELEASE}"
                                  "release" xz_utils)
    set(_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_XZ_UTILS_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_XZ_UTILS_RELWITHDEBINFO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XZ_UTILS_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_XZ_UTILS_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_XZ_UTILS_RELWITHDEBINFO "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" xz_utils)
    set(_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_XZ_UTILS_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_XZ_UTILS_MINSIZEREL} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_XZ_UTILS_MINSIZEREL}" "${CONAN_LIB_DIRS_XZ_UTILS_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_XZ_UTILS_MINSIZEREL "${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" xz_utils)

    add_library(CONAN_PKG::xz_utils INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::xz_utils PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_XZ_UTILS} ${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_XZ_UTILS_LIST}>

                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_XZ_UTILS_RELEASE} ${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELEASE}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_XZ_UTILS_RELEASE_LIST}>>

                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_XZ_UTILS_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_RELWITHDEBINFO}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_XZ_UTILS_RELWITHDEBINFO_LIST}>>

                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_XZ_UTILS_MINSIZEREL} ${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_MINSIZEREL}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_XZ_UTILS_MINSIZEREL_LIST}>>

                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_XZ_UTILS_DEBUG} ${_CONAN_PKG_LIBS_XZ_UTILS_DEPENDENCIES_DEBUG}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_XZ_UTILS_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_XZ_UTILS_DEBUG_LIST}>>)
    set_property(TARGET CONAN_PKG::xz_utils PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_XZ_UTILS}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_XZ_UTILS_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_XZ_UTILS_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_XZ_UTILS_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_XZ_UTILS_DEBUG}>)
    set_property(TARGET CONAN_PKG::xz_utils PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_XZ_UTILS}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_XZ_UTILS_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_XZ_UTILS_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_XZ_UTILS_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_XZ_UTILS_DEBUG}>)
    set_property(TARGET CONAN_PKG::xz_utils PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_XZ_UTILS_LIST} ${CONAN_CXX_FLAGS_XZ_UTILS_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_XZ_UTILS_RELEASE_LIST} ${CONAN_CXX_FLAGS_XZ_UTILS_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_XZ_UTILS_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_XZ_UTILS_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_XZ_UTILS_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_XZ_UTILS_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_XZ_UTILS_DEBUG_LIST}  ${CONAN_CXX_FLAGS_XZ_UTILS_DEBUG_LIST}>)


    set(_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES "${CONAN_SYSTEM_LIBS_ZLIB} ${CONAN_FRAMEWORKS_FOUND_ZLIB} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_ZLIB_DEPENDENCIES "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES}")
    conan_package_library_targets("${CONAN_PKG_LIBS_ZLIB}" "${CONAN_LIB_DIRS_ZLIB}"
                                  CONAN_PACKAGE_TARGETS_ZLIB "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES}"
                                  "" zlib)
    set(_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_DEBUG "${CONAN_SYSTEM_LIBS_ZLIB_DEBUG} ${CONAN_FRAMEWORKS_FOUND_ZLIB_DEBUG} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_DEBUG "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_DEBUG}")
    conan_package_library_targets("${CONAN_PKG_LIBS_ZLIB_DEBUG}" "${CONAN_LIB_DIRS_ZLIB_DEBUG}"
                                  CONAN_PACKAGE_TARGETS_ZLIB_DEBUG "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_DEBUG}"
                                  "debug" zlib)
    set(_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELEASE "${CONAN_SYSTEM_LIBS_ZLIB_RELEASE} ${CONAN_FRAMEWORKS_FOUND_ZLIB_RELEASE} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELEASE "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELEASE}")
    conan_package_library_targets("${CONAN_PKG_LIBS_ZLIB_RELEASE}" "${CONAN_LIB_DIRS_ZLIB_RELEASE}"
                                  CONAN_PACKAGE_TARGETS_ZLIB_RELEASE "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELEASE}"
                                  "release" zlib)
    set(_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELWITHDEBINFO "${CONAN_SYSTEM_LIBS_ZLIB_RELWITHDEBINFO} ${CONAN_FRAMEWORKS_FOUND_ZLIB_RELWITHDEBINFO} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELWITHDEBINFO "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELWITHDEBINFO}")
    conan_package_library_targets("${CONAN_PKG_LIBS_ZLIB_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_ZLIB_RELWITHDEBINFO}"
                                  CONAN_PACKAGE_TARGETS_ZLIB_RELWITHDEBINFO "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELWITHDEBINFO}"
                                  "relwithdebinfo" zlib)
    set(_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_MINSIZEREL "${CONAN_SYSTEM_LIBS_ZLIB_MINSIZEREL} ${CONAN_FRAMEWORKS_FOUND_ZLIB_MINSIZEREL} ")
    string(REPLACE " " ";" _CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_MINSIZEREL "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_MINSIZEREL}")
    conan_package_library_targets("${CONAN_PKG_LIBS_ZLIB_MINSIZEREL}" "${CONAN_LIB_DIRS_ZLIB_MINSIZEREL}"
                                  CONAN_PACKAGE_TARGETS_ZLIB_MINSIZEREL "${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_MINSIZEREL}"
                                  "minsizerel" zlib)

    add_library(CONAN_PKG::zlib INTERFACE IMPORTED)

    # Property INTERFACE_LINK_FLAGS do not work, necessary to add to INTERFACE_LINK_LIBRARIES
    set_property(TARGET CONAN_PKG::zlib PROPERTY INTERFACE_LINK_LIBRARIES ${CONAN_PACKAGE_TARGETS_ZLIB} ${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_ZLIB_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_ZLIB_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_ZLIB_LIST}>

                                                                 $<$<CONFIG:Release>:${CONAN_PACKAGE_TARGETS_ZLIB_RELEASE} ${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELEASE}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_ZLIB_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_ZLIB_RELEASE_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_ZLIB_RELEASE_LIST}>>

                                                                 $<$<CONFIG:RelWithDebInfo>:${CONAN_PACKAGE_TARGETS_ZLIB_RELWITHDEBINFO} ${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_RELWITHDEBINFO}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_ZLIB_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_ZLIB_RELWITHDEBINFO_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_ZLIB_RELWITHDEBINFO_LIST}>>

                                                                 $<$<CONFIG:MinSizeRel>:${CONAN_PACKAGE_TARGETS_ZLIB_MINSIZEREL} ${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_MINSIZEREL}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_ZLIB_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_ZLIB_MINSIZEREL_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_ZLIB_MINSIZEREL_LIST}>>

                                                                 $<$<CONFIG:Debug>:${CONAN_PACKAGE_TARGETS_ZLIB_DEBUG} ${_CONAN_PKG_LIBS_ZLIB_DEPENDENCIES_DEBUG}
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_ZLIB_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${CONAN_SHARED_LINKER_FLAGS_ZLIB_DEBUG_LIST}>
                                                                 $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${CONAN_EXE_LINKER_FLAGS_ZLIB_DEBUG_LIST}>>)
    set_property(TARGET CONAN_PKG::zlib PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${CONAN_INCLUDE_DIRS_ZLIB}
                                                                      $<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_ZLIB_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_ZLIB_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_ZLIB_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_ZLIB_DEBUG}>)
    set_property(TARGET CONAN_PKG::zlib PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CONAN_COMPILE_DEFINITIONS_ZLIB}
                                                                      $<$<CONFIG:Release>:${CONAN_COMPILE_DEFINITIONS_ZLIB_RELEASE}>
                                                                      $<$<CONFIG:RelWithDebInfo>:${CONAN_COMPILE_DEFINITIONS_ZLIB_RELWITHDEBINFO}>
                                                                      $<$<CONFIG:MinSizeRel>:${CONAN_COMPILE_DEFINITIONS_ZLIB_MINSIZEREL}>
                                                                      $<$<CONFIG:Debug>:${CONAN_COMPILE_DEFINITIONS_ZLIB_DEBUG}>)
    set_property(TARGET CONAN_PKG::zlib PROPERTY INTERFACE_COMPILE_OPTIONS ${CONAN_C_FLAGS_ZLIB_LIST} ${CONAN_CXX_FLAGS_ZLIB_LIST}
                                                                  $<$<CONFIG:Release>:${CONAN_C_FLAGS_ZLIB_RELEASE_LIST} ${CONAN_CXX_FLAGS_ZLIB_RELEASE_LIST}>
                                                                  $<$<CONFIG:RelWithDebInfo>:${CONAN_C_FLAGS_ZLIB_RELWITHDEBINFO_LIST} ${CONAN_CXX_FLAGS_ZLIB_RELWITHDEBINFO_LIST}>
                                                                  $<$<CONFIG:MinSizeRel>:${CONAN_C_FLAGS_ZLIB_MINSIZEREL_LIST} ${CONAN_CXX_FLAGS_ZLIB_MINSIZEREL_LIST}>
                                                                  $<$<CONFIG:Debug>:${CONAN_C_FLAGS_ZLIB_DEBUG_LIST}  ${CONAN_CXX_FLAGS_ZLIB_DEBUG_LIST}>)

    set(CONAN_TARGETS CONAN_PKG::glog CONAN_PKG::oatpp-swagger CONAN_PKG::oatpp-postgresql CONAN_PKG::gflags CONAN_PKG::libunwind CONAN_PKG::oatpp CONAN_PKG::libpq CONAN_PKG::xz_utils CONAN_PKG::zlib)

endmacro()


macro(conan_basic_setup)
    set(options TARGETS NO_OUTPUT_DIRS SKIP_RPATH KEEP_RPATHS SKIP_STD SKIP_FPIC)
    cmake_parse_arguments(ARGUMENTS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if(CONAN_EXPORTED)
        conan_message(STATUS "Conan: called by CMake conan helper")
    endif()

    if(CONAN_IN_LOCAL_CACHE)
        conan_message(STATUS "Conan: called inside local cache")
    endif()

    if(NOT ARGUMENTS_NO_OUTPUT_DIRS)
        conan_message(STATUS "Conan: Adjusting output directories")
        conan_output_dirs_setup()
    endif()

    if(NOT ARGUMENTS_TARGETS)
        conan_message(STATUS "Conan: Using cmake global configuration")
        conan_global_flags()
    else()
        conan_message(STATUS "Conan: Using cmake targets configuration")
        conan_define_targets()
    endif()

    if(ARGUMENTS_SKIP_RPATH)
        # Change by "DEPRECATION" or "SEND_ERROR" when we are ready
        conan_message(WARNING "Conan: SKIP_RPATH is deprecated, it has been renamed to KEEP_RPATHS")
    endif()

    if(NOT ARGUMENTS_SKIP_RPATH AND NOT ARGUMENTS_KEEP_RPATHS)
        # Parameter has renamed, but we keep the compatibility with old SKIP_RPATH
        conan_set_rpath()
    endif()

    if(NOT ARGUMENTS_SKIP_STD)
        conan_set_std()
    endif()

    if(NOT ARGUMENTS_SKIP_FPIC)
        conan_set_fpic()
    endif()

    conan_check_compiler()
    conan_set_libcxx()
    conan_set_vs_runtime()
    conan_set_find_paths()
    conan_include_build_modules()
    conan_set_find_library_paths()
endmacro()


macro(conan_set_find_paths)
    # CMAKE_MODULE_PATH does not have Debug/Release config, but there are variables
    # CONAN_CMAKE_MODULE_PATH_DEBUG to be used by the consumer
    # CMake can find findXXX.cmake files in the root of packages
    set(CMAKE_MODULE_PATH ${CONAN_CMAKE_MODULE_PATH} ${CMAKE_MODULE_PATH})

    # Make find_package() to work
    set(CMAKE_PREFIX_PATH ${CONAN_CMAKE_MODULE_PATH} ${CMAKE_PREFIX_PATH})

    # Set the find root path (cross build)
    set(CMAKE_FIND_ROOT_PATH ${CONAN_CMAKE_FIND_ROOT_PATH} ${CMAKE_FIND_ROOT_PATH})
    if(CONAN_CMAKE_FIND_ROOT_PATH_MODE_PROGRAM)
        set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ${CONAN_CMAKE_FIND_ROOT_PATH_MODE_PROGRAM})
    endif()
    if(CONAN_CMAKE_FIND_ROOT_PATH_MODE_LIBRARY)
        set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ${CONAN_CMAKE_FIND_ROOT_PATH_MODE_LIBRARY})
    endif()
    if(CONAN_CMAKE_FIND_ROOT_PATH_MODE_INCLUDE)
        set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ${CONAN_CMAKE_FIND_ROOT_PATH_MODE_INCLUDE})
    endif()
endmacro()


macro(conan_set_find_library_paths)
    # CMAKE_INCLUDE_PATH, CMAKE_LIBRARY_PATH does not have Debug/Release config, but there are variables
    # CONAN_INCLUDE_DIRS_DEBUG/RELEASE CONAN_LIB_DIRS_DEBUG/RELEASE to be used by the consumer
    # For find_library
    set(CMAKE_INCLUDE_PATH ${CONAN_INCLUDE_DIRS} ${CMAKE_INCLUDE_PATH})
    set(CMAKE_LIBRARY_PATH ${CONAN_LIB_DIRS} ${CMAKE_LIBRARY_PATH})
endmacro()


macro(conan_set_vs_runtime)
    if(CONAN_LINK_RUNTIME)
        conan_get_policy(CMP0091 policy_0091)
        if(policy_0091 STREQUAL "NEW")
            if(CONAN_LINK_RUNTIME MATCHES "MTd")
                set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
            elseif(CONAN_LINK_RUNTIME MATCHES "MDd")
                set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
            elseif(CONAN_LINK_RUNTIME MATCHES "MT")
                set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
            elseif(CONAN_LINK_RUNTIME MATCHES "MD")
                set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
            endif()
        else()
            foreach(flag CMAKE_C_FLAGS_RELEASE CMAKE_CXX_FLAGS_RELEASE
                         CMAKE_C_FLAGS_RELWITHDEBINFO CMAKE_CXX_FLAGS_RELWITHDEBINFO
                         CMAKE_C_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_MINSIZEREL)
                if(DEFINED ${flag})
                    string(REPLACE "/MD" ${CONAN_LINK_RUNTIME} ${flag} "${${flag}}")
                endif()
            endforeach()
            foreach(flag CMAKE_C_FLAGS_DEBUG CMAKE_CXX_FLAGS_DEBUG)
                if(DEFINED ${flag})
                    string(REPLACE "/MDd" ${CONAN_LINK_RUNTIME} ${flag} "${${flag}}")
                endif()
            endforeach()
        endif()
    endif()
endmacro()


macro(conan_flags_setup)
    # Macro maintained for backwards compatibility
    conan_set_find_library_paths()
    conan_global_flags()
    conan_set_rpath()
    conan_set_vs_runtime()
    conan_set_libcxx()
endmacro()


function(conan_message MESSAGE_OUTPUT)
    if(NOT CONAN_CMAKE_SILENT_OUTPUT)
        message(${ARGV${0}})
    endif()
endfunction()


function(conan_get_policy policy_id policy)
    if(POLICY "${policy_id}")
        cmake_policy(GET "${policy_id}" _policy)
        set(${policy} "${_policy}" PARENT_SCOPE)
    else()
        set(${policy} "" PARENT_SCOPE)
    endif()
endfunction()


function(conan_find_libraries_abs_path libraries package_libdir libraries_abs_path)
    foreach(_LIBRARY_NAME ${libraries})
        find_library(CONAN_FOUND_LIBRARY NAMES ${_LIBRARY_NAME} PATHS ${package_libdir}
                     NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
        if(CONAN_FOUND_LIBRARY)
            conan_message(STATUS "Library ${_LIBRARY_NAME} found ${CONAN_FOUND_LIBRARY}")
            set(CONAN_FULLPATH_LIBS ${CONAN_FULLPATH_LIBS} ${CONAN_FOUND_LIBRARY})
        else()
            conan_message(STATUS "Library ${_LIBRARY_NAME} not found in package, might be system one")
            set(CONAN_FULLPATH_LIBS ${CONAN_FULLPATH_LIBS} ${_LIBRARY_NAME})
        endif()
        unset(CONAN_FOUND_LIBRARY CACHE)
    endforeach()
    set(${libraries_abs_path} ${CONAN_FULLPATH_LIBS} PARENT_SCOPE)
endfunction()


function(conan_package_library_targets libraries package_libdir libraries_abs_path deps build_type package_name)
    unset(_CONAN_ACTUAL_TARGETS CACHE)
    unset(_CONAN_FOUND_SYSTEM_LIBS CACHE)
    foreach(_LIBRARY_NAME ${libraries})
        find_library(CONAN_FOUND_LIBRARY NAMES ${_LIBRARY_NAME} PATHS ${package_libdir}
                     NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
        if(CONAN_FOUND_LIBRARY)
            conan_message(STATUS "Library ${_LIBRARY_NAME} found ${CONAN_FOUND_LIBRARY}")
            set(_LIB_NAME CONAN_LIB::${package_name}_${_LIBRARY_NAME}${build_type})
            add_library(${_LIB_NAME} UNKNOWN IMPORTED)
            set_target_properties(${_LIB_NAME} PROPERTIES IMPORTED_LOCATION ${CONAN_FOUND_LIBRARY})
            set(CONAN_FULLPATH_LIBS ${CONAN_FULLPATH_LIBS} ${_LIB_NAME})
            set(_CONAN_ACTUAL_TARGETS ${_CONAN_ACTUAL_TARGETS} ${_LIB_NAME})
        else()
            conan_message(STATUS "Library ${_LIBRARY_NAME} not found in package, might be system one")
            set(CONAN_FULLPATH_LIBS ${CONAN_FULLPATH_LIBS} ${_LIBRARY_NAME})
            set(_CONAN_FOUND_SYSTEM_LIBS "${_CONAN_FOUND_SYSTEM_LIBS};${_LIBRARY_NAME}")
        endif()
        unset(CONAN_FOUND_LIBRARY CACHE)
    endforeach()

    # Add all dependencies to all targets
    string(REPLACE " " ";" deps_list "${deps}")
    foreach(_CONAN_ACTUAL_TARGET ${_CONAN_ACTUAL_TARGETS})
        set_property(TARGET ${_CONAN_ACTUAL_TARGET} PROPERTY INTERFACE_LINK_LIBRARIES "${_CONAN_FOUND_SYSTEM_LIBS};${deps_list}")
    endforeach()

    set(${libraries_abs_path} ${CONAN_FULLPATH_LIBS} PARENT_SCOPE)
endfunction()


macro(conan_set_libcxx)
    if(DEFINED CONAN_LIBCXX)
        conan_message(STATUS "Conan: C++ stdlib: ${CONAN_LIBCXX}")
        if(CONAN_COMPILER STREQUAL "clang" OR CONAN_COMPILER STREQUAL "apple-clang")
            if(CONAN_LIBCXX STREQUAL "libstdc++" OR CONAN_LIBCXX STREQUAL "libstdc++11" )
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
            elseif(CONAN_LIBCXX STREQUAL "libc++")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
            endif()
        endif()
        if(CONAN_COMPILER STREQUAL "sun-cc")
            if(CONAN_LIBCXX STREQUAL "libCstd")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -library=Cstd")
            elseif(CONAN_LIBCXX STREQUAL "libstdcxx")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -library=stdcxx4")
            elseif(CONAN_LIBCXX STREQUAL "libstlport")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -library=stlport4")
            elseif(CONAN_LIBCXX STREQUAL "libstdc++")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -library=stdcpp")
            endif()
        endif()
        if(CONAN_LIBCXX STREQUAL "libstdc++11")
            add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)
        elseif(CONAN_LIBCXX STREQUAL "libstdc++")
            add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
        endif()
    endif()
endmacro()


macro(conan_set_std)
    conan_message(STATUS "Conan: Adjusting language standard")
    # Do not warn "Manually-specified variables were not used by the project"
    set(ignorevar "${CONAN_STD_CXX_FLAG}${CONAN_CMAKE_CXX_STANDARD}${CONAN_CMAKE_CXX_EXTENSIONS}")
    if (CMAKE_VERSION VERSION_LESS "3.1" OR
        (CMAKE_VERSION VERSION_LESS "3.12" AND ("${CONAN_CMAKE_CXX_STANDARD}" STREQUAL "20" OR "${CONAN_CMAKE_CXX_STANDARD}" STREQUAL "gnu20")))
        if(CONAN_STD_CXX_FLAG)
            conan_message(STATUS "Conan setting CXX_FLAGS flags: ${CONAN_STD_CXX_FLAG}")
            set(CMAKE_CXX_FLAGS "${CONAN_STD_CXX_FLAG} ${CMAKE_CXX_FLAGS}")
        endif()
    else()
        if(CONAN_CMAKE_CXX_STANDARD)
            conan_message(STATUS "Conan setting CPP STANDARD: ${CONAN_CMAKE_CXX_STANDARD} WITH EXTENSIONS ${CONAN_CMAKE_CXX_EXTENSIONS}")
            set(CMAKE_CXX_STANDARD ${CONAN_CMAKE_CXX_STANDARD})
            set(CMAKE_CXX_EXTENSIONS ${CONAN_CMAKE_CXX_EXTENSIONS})
        endif()
    endif()
endmacro()


macro(conan_set_rpath)
    conan_message(STATUS "Conan: Adjusting default RPATHs Conan policies")
    if(APPLE)
        # https://cmake.org/Wiki/CMake_RPATH_handling
        # CONAN GUIDE: All generated libraries should have the id and dependencies to other
        # dylibs without path, just the name, EX:
        # libMyLib1.dylib:
        #     libMyLib1.dylib (compatibility version 0.0.0, current version 0.0.0)
        #     libMyLib0.dylib (compatibility version 0.0.0, current version 0.0.0)
        #     /usr/lib/libc++.1.dylib (compatibility version 1.0.0, current version 120.0.0)
        #     /usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1197.1.1)
        # AVOID RPATH FOR *.dylib, ALL LIBS BETWEEN THEM AND THE EXE
        # SHOULD BE ON THE LINKER RESOLVER PATH (./ IS ONE OF THEM)
        set(CMAKE_SKIP_RPATH 1 CACHE BOOL "rpaths" FORCE)
        # Policy CMP0068
        # We want the old behavior, in CMake >= 3.9 CMAKE_SKIP_RPATH won't affect the install_name in OSX
        set(CMAKE_INSTALL_NAME_DIR "")
    endif()
endmacro()


macro(conan_set_fpic)
    if(DEFINED CONAN_CMAKE_POSITION_INDEPENDENT_CODE)
        conan_message(STATUS "Conan: Adjusting fPIC flag (${CONAN_CMAKE_POSITION_INDEPENDENT_CODE})")
        set(CMAKE_POSITION_INDEPENDENT_CODE ${CONAN_CMAKE_POSITION_INDEPENDENT_CODE})
    endif()
endmacro()


macro(conan_output_dirs_setup)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endmacro()


macro(conan_split_version VERSION_STRING MAJOR MINOR)
    #make a list from the version string
    string(REPLACE "." ";" VERSION_LIST "${VERSION_STRING}")

    #write output values
    list(LENGTH VERSION_LIST _version_len)
    list(GET VERSION_LIST 0 ${MAJOR})
    if(${_version_len} GREATER 1)
        list(GET VERSION_LIST 1 ${MINOR})
    endif()
endmacro()


macro(conan_error_compiler_version)
    message(FATAL_ERROR "Detected a mismatch for the compiler version between your conan profile settings and CMake: \n"
                        "Compiler version specified in your conan profile: ${CONAN_COMPILER_VERSION}\n"
                        "Compiler version detected in CMake: ${VERSION_MAJOR}.${VERSION_MINOR}\n"
                        "Please check your conan profile settings (conan profile show [default|your_profile_name])\n"
                        "P.S. You may set CONAN_DISABLE_CHECK_COMPILER CMake variable in order to disable this check."
           )
endmacro()

set(_CONAN_CURRENT_DIR ${CMAKE_CURRENT_LIST_DIR})

function(conan_get_compiler CONAN_INFO_COMPILER CONAN_INFO_COMPILER_VERSION)
    conan_message(STATUS "Current conanbuildinfo.cmake directory: " ${_CONAN_CURRENT_DIR})
    if(NOT EXISTS ${_CONAN_CURRENT_DIR}/conaninfo.txt)
        conan_message(STATUS "WARN: conaninfo.txt not found")
        return()
    endif()

    file (READ "${_CONAN_CURRENT_DIR}/conaninfo.txt" CONANINFO)

    # MATCHALL will match all, including the last one, which is the full_settings one
    string(REGEX MATCH "full_settings.*" _FULL_SETTINGS_MATCHED ${CONANINFO})
    string(REGEX MATCH "compiler=([-A-Za-z0-9_ ]+)" _MATCHED ${_FULL_SETTINGS_MATCHED})
    if(DEFINED CMAKE_MATCH_1)
        string(STRIP "${CMAKE_MATCH_1}" _CONAN_INFO_COMPILER)
        set(${CONAN_INFO_COMPILER} ${_CONAN_INFO_COMPILER} PARENT_SCOPE)
    endif()

    string(REGEX MATCH "compiler.version=([-A-Za-z0-9_.]+)" _MATCHED ${_FULL_SETTINGS_MATCHED})
    if(DEFINED CMAKE_MATCH_1)
        string(STRIP "${CMAKE_MATCH_1}" _CONAN_INFO_COMPILER_VERSION)
        set(${CONAN_INFO_COMPILER_VERSION} ${_CONAN_INFO_COMPILER_VERSION} PARENT_SCOPE)
    endif()
endfunction()


function(check_compiler_version)
    conan_split_version(${CMAKE_CXX_COMPILER_VERSION} VERSION_MAJOR VERSION_MINOR)
    if(DEFINED CONAN_SETTINGS_COMPILER_TOOLSET)
       conan_message(STATUS "Conan: Skipping compiler check: Declared 'compiler.toolset'")
       return()
    endif()
    if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
        # MSVC_VERSION is defined since 2.8.2 at least
        # https://cmake.org/cmake/help/v2.8.2/cmake.html#variable:MSVC_VERSION
        # https://cmake.org/cmake/help/v3.14/variable/MSVC_VERSION.html
        if(
            # 1930 = VS 17.0 (v143 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "17" AND NOT((MSVC_VERSION EQUAL 1930) OR (MSVC_VERSION GREATER 1930))) OR
            # 1920-1929 = VS 16.0 (v142 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "16" AND NOT((MSVC_VERSION GREATER 1919) AND (MSVC_VERSION LESS 1930))) OR
            # 1910-1919 = VS 15.0 (v141 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "15" AND NOT((MSVC_VERSION GREATER 1909) AND (MSVC_VERSION LESS 1920))) OR
            # 1900      = VS 14.0 (v140 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "14" AND NOT(MSVC_VERSION EQUAL 1900)) OR
            # 1800      = VS 12.0 (v120 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "12" AND NOT VERSION_MAJOR STREQUAL "18") OR
            # 1700      = VS 11.0 (v110 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "11" AND NOT VERSION_MAJOR STREQUAL "17") OR
            # 1600      = VS 10.0 (v100 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "10" AND NOT VERSION_MAJOR STREQUAL "16") OR
            # 1500      = VS  9.0 (v90 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "9" AND NOT VERSION_MAJOR STREQUAL "15") OR
            # 1400      = VS  8.0 (v80 toolset)
            (CONAN_COMPILER_VERSION STREQUAL "8" AND NOT VERSION_MAJOR STREQUAL "14") OR
            # 1310      = VS  7.1, 1300      = VS  7.0
            (CONAN_COMPILER_VERSION STREQUAL "7" AND NOT VERSION_MAJOR STREQUAL "13") OR
            # 1200      = VS  6.0
            (CONAN_COMPILER_VERSION STREQUAL "6" AND NOT VERSION_MAJOR STREQUAL "12") )
            conan_error_compiler_version()
        endif()
    elseif(CONAN_COMPILER STREQUAL "gcc")
        conan_split_version(${CONAN_COMPILER_VERSION} CONAN_COMPILER_MAJOR CONAN_COMPILER_MINOR)
        set(_CHECK_VERSION ${VERSION_MAJOR}.${VERSION_MINOR})
        set(_CONAN_VERSION ${CONAN_COMPILER_MAJOR}.${CONAN_COMPILER_MINOR})
        if(NOT ${CONAN_COMPILER_VERSION} VERSION_LESS 5.0)
            conan_message(STATUS "Conan: Compiler GCC>=5, checking major version ${CONAN_COMPILER_VERSION}")
            conan_split_version(${CONAN_COMPILER_VERSION} CONAN_COMPILER_MAJOR CONAN_COMPILER_MINOR)
            if("${CONAN_COMPILER_MINOR}" STREQUAL "")
                set(_CHECK_VERSION ${VERSION_MAJOR})
                set(_CONAN_VERSION ${CONAN_COMPILER_MAJOR})
            endif()
        endif()
        conan_message(STATUS "Conan: Checking correct version: ${_CHECK_VERSION}")
        if(NOT ${_CHECK_VERSION} VERSION_EQUAL ${_CONAN_VERSION})
            conan_error_compiler_version()
        endif()
    elseif(CONAN_COMPILER STREQUAL "clang")
        conan_split_version(${CONAN_COMPILER_VERSION} CONAN_COMPILER_MAJOR CONAN_COMPILER_MINOR)
        set(_CHECK_VERSION ${VERSION_MAJOR}.${VERSION_MINOR})
        set(_CONAN_VERSION ${CONAN_COMPILER_MAJOR}.${CONAN_COMPILER_MINOR})
        if(NOT ${CONAN_COMPILER_VERSION} VERSION_LESS 8.0)
            conan_message(STATUS "Conan: Compiler Clang>=8, checking major version ${CONAN_COMPILER_VERSION}")
            if("${CONAN_COMPILER_MINOR}" STREQUAL "")
                set(_CHECK_VERSION ${VERSION_MAJOR})
                set(_CONAN_VERSION ${CONAN_COMPILER_MAJOR})
            endif()
        endif()
        conan_message(STATUS "Conan: Checking correct version: ${_CHECK_VERSION}")
        if(NOT ${_CHECK_VERSION} VERSION_EQUAL ${_CONAN_VERSION})
            conan_error_compiler_version()
        endif()
    elseif(CONAN_COMPILER STREQUAL "apple-clang" OR CONAN_COMPILER STREQUAL "sun-cc" OR CONAN_COMPILER STREQUAL "mcst-lcc")
        conan_split_version(${CONAN_COMPILER_VERSION} CONAN_COMPILER_MAJOR CONAN_COMPILER_MINOR)
        if(${CONAN_COMPILER_MAJOR} VERSION_GREATER_EQUAL "13" AND "${CONAN_COMPILER_MINOR}" STREQUAL "" AND ${CONAN_COMPILER_MAJOR} VERSION_EQUAL ${VERSION_MAJOR})
           # This is correct,  13.X is considered 13
        elseif(NOT ${VERSION_MAJOR}.${VERSION_MINOR} VERSION_EQUAL ${CONAN_COMPILER_MAJOR}.${CONAN_COMPILER_MINOR})
           conan_error_compiler_version()
        endif()
    elseif(CONAN_COMPILER STREQUAL "intel")
        conan_split_version(${CONAN_COMPILER_VERSION} CONAN_COMPILER_MAJOR CONAN_COMPILER_MINOR)
        if(NOT ${CONAN_COMPILER_VERSION} VERSION_LESS 19.1)
            if(NOT ${VERSION_MAJOR}.${VERSION_MINOR} VERSION_EQUAL ${CONAN_COMPILER_MAJOR}.${CONAN_COMPILER_MINOR})
               conan_error_compiler_version()
            endif()
        else()
            if(NOT ${VERSION_MAJOR} VERSION_EQUAL ${CONAN_COMPILER_MAJOR})
               conan_error_compiler_version()
            endif()
        endif()
    else()
        conan_message(STATUS "WARN: Unknown compiler '${CONAN_COMPILER}', skipping the version check...")
    endif()
endfunction()


function(conan_check_compiler)
    if(CONAN_DISABLE_CHECK_COMPILER)
        conan_message(STATUS "WARN: Disabled conan compiler checks")
        return()
    endif()
    if(NOT DEFINED CMAKE_CXX_COMPILER_ID)
        if(DEFINED CMAKE_C_COMPILER_ID)
            conan_message(STATUS "This project seems to be plain C, using '${CMAKE_C_COMPILER_ID}' compiler")
            set(CMAKE_CXX_COMPILER_ID ${CMAKE_C_COMPILER_ID})
            set(CMAKE_CXX_COMPILER_VERSION ${CMAKE_C_COMPILER_VERSION})
        else()
            message(FATAL_ERROR "This project seems to be plain C, but no compiler defined")
        endif()
    endif()
    if(NOT CMAKE_CXX_COMPILER_ID AND NOT CMAKE_C_COMPILER_ID)
        # This use case happens when compiler is not identified by CMake, but the compilers are there and work
        conan_message(STATUS "*** WARN: CMake was not able to identify a C or C++ compiler ***")
        conan_message(STATUS "*** WARN: Disabling compiler checks. Please make sure your settings match your environment ***")
        return()
    endif()
    if(NOT DEFINED CONAN_COMPILER)
        conan_get_compiler(CONAN_COMPILER CONAN_COMPILER_VERSION)
        if(NOT DEFINED CONAN_COMPILER)
            conan_message(STATUS "WARN: CONAN_COMPILER variable not set, please make sure yourself that "
                          "your compiler and version matches your declared settings")
            return()
        endif()
    endif()

    if(NOT CMAKE_HOST_SYSTEM_NAME STREQUAL ${CMAKE_SYSTEM_NAME})
        set(CROSS_BUILDING 1)
    endif()

    # If using VS, verify toolset
    if (CONAN_COMPILER STREQUAL "Visual Studio")
        if (CONAN_SETTINGS_COMPILER_TOOLSET MATCHES "LLVM" OR
            CONAN_SETTINGS_COMPILER_TOOLSET MATCHES "llvm" OR
            CONAN_SETTINGS_COMPILER_TOOLSET MATCHES "clang" OR
            CONAN_SETTINGS_COMPILER_TOOLSET MATCHES "Clang")
            set(EXPECTED_CMAKE_CXX_COMPILER_ID "Clang")
        elseif (CONAN_SETTINGS_COMPILER_TOOLSET MATCHES "Intel")
            set(EXPECTED_CMAKE_CXX_COMPILER_ID "Intel")
        else()
            set(EXPECTED_CMAKE_CXX_COMPILER_ID "MSVC")
        endif()

        if (NOT CMAKE_CXX_COMPILER_ID MATCHES ${EXPECTED_CMAKE_CXX_COMPILER_ID})
            message(FATAL_ERROR "Incorrect '${CONAN_COMPILER}'. Toolset specifies compiler as '${EXPECTED_CMAKE_CXX_COMPILER_ID}' "
                                "but CMake detected '${CMAKE_CXX_COMPILER_ID}'")
        endif()

    # Avoid checks when cross compiling, apple-clang crashes because its APPLE but not apple-clang
    # Actually CMake is detecting "clang" when you are using apple-clang, only if CMP0025 is set to NEW will detect apple-clang
    elseif((CONAN_COMPILER STREQUAL "gcc" AND NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR
        (CONAN_COMPILER STREQUAL "apple-clang" AND NOT CROSS_BUILDING AND (NOT APPLE OR NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")) OR
        (CONAN_COMPILER STREQUAL "clang" AND NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR
        (CONAN_COMPILER STREQUAL "sun-cc" AND NOT CMAKE_CXX_COMPILER_ID MATCHES "SunPro") )
        message(FATAL_ERROR "Incorrect '${CONAN_COMPILER}', is not the one detected by CMake: '${CMAKE_CXX_COMPILER_ID}'")
    endif()


    if(NOT DEFINED CONAN_COMPILER_VERSION)
        conan_message(STATUS "WARN: CONAN_COMPILER_VERSION variable not set, please make sure yourself "
                             "that your compiler version matches your declared settings")
        return()
    endif()
    check_compiler_version()
endfunction()


macro(conan_set_flags build_type)
    set(CMAKE_CXX_FLAGS${build_type} "${CMAKE_CXX_FLAGS${build_type}} ${CONAN_CXX_FLAGS${build_type}}")
    set(CMAKE_C_FLAGS${build_type} "${CMAKE_C_FLAGS${build_type}} ${CONAN_C_FLAGS${build_type}}")
    set(CMAKE_SHARED_LINKER_FLAGS${build_type} "${CMAKE_SHARED_LINKER_FLAGS${build_type}} ${CONAN_SHARED_LINKER_FLAGS${build_type}}")
    set(CMAKE_EXE_LINKER_FLAGS${build_type} "${CMAKE_EXE_LINKER_FLAGS${build_type}} ${CONAN_EXE_LINKER_FLAGS${build_type}}")
endmacro()


macro(conan_global_flags)
    if(CONAN_SYSTEM_INCLUDES)
        include_directories(SYSTEM ${CONAN_INCLUDE_DIRS}
                                   "$<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_RELEASE}>"
                                   "$<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_RELWITHDEBINFO}>"
                                   "$<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_MINSIZEREL}>"
                                   "$<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_DEBUG}>")
    else()
        include_directories(${CONAN_INCLUDE_DIRS}
                            "$<$<CONFIG:Release>:${CONAN_INCLUDE_DIRS_RELEASE}>"
                            "$<$<CONFIG:RelWithDebInfo>:${CONAN_INCLUDE_DIRS_RELWITHDEBINFO}>"
                            "$<$<CONFIG:MinSizeRel>:${CONAN_INCLUDE_DIRS_MINSIZEREL}>"
                            "$<$<CONFIG:Debug>:${CONAN_INCLUDE_DIRS_DEBUG}>")
    endif()

    link_directories(${CONAN_LIB_DIRS})

    conan_find_libraries_abs_path("${CONAN_LIBS_DEBUG}" "${CONAN_LIB_DIRS_DEBUG}"
                                  CONAN_LIBS_DEBUG)
    conan_find_libraries_abs_path("${CONAN_LIBS_RELEASE}" "${CONAN_LIB_DIRS_RELEASE}"
                                  CONAN_LIBS_RELEASE)
    conan_find_libraries_abs_path("${CONAN_LIBS_RELWITHDEBINFO}" "${CONAN_LIB_DIRS_RELWITHDEBINFO}"
                                  CONAN_LIBS_RELWITHDEBINFO)
    conan_find_libraries_abs_path("${CONAN_LIBS_MINSIZEREL}" "${CONAN_LIB_DIRS_MINSIZEREL}"
                                  CONAN_LIBS_MINSIZEREL)

    add_compile_options(${CONAN_DEFINES}
                        "$<$<CONFIG:Debug>:${CONAN_DEFINES_DEBUG}>"
                        "$<$<CONFIG:Release>:${CONAN_DEFINES_RELEASE}>"
                        "$<$<CONFIG:RelWithDebInfo>:${CONAN_DEFINES_RELWITHDEBINFO}>"
                        "$<$<CONFIG:MinSizeRel>:${CONAN_DEFINES_MINSIZEREL}>")

    conan_set_flags("")
    conan_set_flags("_RELEASE")
    conan_set_flags("_DEBUG")

endmacro()


macro(conan_target_link_libraries target)
    if(CONAN_TARGETS)
        target_link_libraries(${target} ${CONAN_TARGETS})
    else()
        target_link_libraries(${target} ${CONAN_LIBS})
        foreach(_LIB ${CONAN_LIBS_RELEASE})
            target_link_libraries(${target} optimized ${_LIB})
        endforeach()
        foreach(_LIB ${CONAN_LIBS_DEBUG})
            target_link_libraries(${target} debug ${_LIB})
        endforeach()
    endif()
endmacro()


macro(conan_include_build_modules)
    if(CMAKE_BUILD_TYPE)
        if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
            set(CONAN_BUILD_MODULES_PATHS ${CONAN_BUILD_MODULES_PATHS_DEBUG} ${CONAN_BUILD_MODULES_PATHS})
        elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
            set(CONAN_BUILD_MODULES_PATHS ${CONAN_BUILD_MODULES_PATHS_RELEASE} ${CONAN_BUILD_MODULES_PATHS})
        elseif(${CMAKE_BUILD_TYPE} MATCHES "RelWithDebInfo")
            set(CONAN_BUILD_MODULES_PATHS ${CONAN_BUILD_MODULES_PATHS_RELWITHDEBINFO} ${CONAN_BUILD_MODULES_PATHS})
        elseif(${CMAKE_BUILD_TYPE} MATCHES "MinSizeRel")
            set(CONAN_BUILD_MODULES_PATHS ${CONAN_BUILD_MODULES_PATHS_MINSIZEREL} ${CONAN_BUILD_MODULES_PATHS})
        endif()
    endif()

    foreach(_BUILD_MODULE_PATH ${CONAN_BUILD_MODULES_PATHS})
        include(${_BUILD_MODULE_PATH})
    endforeach()
endmacro()


### Definition of user declared vars (user_info) ###

