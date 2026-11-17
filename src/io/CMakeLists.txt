cmake_minimum_required(VERSION 3.15)
project(vfpio VERSION 4.2 LANGUAGES C CXX)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
 
if(NOT MSVC)
    message(FATAL_ERROR "vfpio requiere arquitectura Win y compilador MSVC.")
endif()
 
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(PLATFORM_DIR "x32")
else()
    set(PLATFORM_DIR "x64")
endif()

set(ARQUITECTURE_DIR ${CMAKE_SYSTEM_PROCESSOR})
if(NOT ARQUITECTURE_DIR)
    set(ARQUITECTURE_DIR ${CMAKE_HOST_SYSTEM_NAME})
endif()

set(DIR_BUILD "${PLATFORM_DIR}-${ARQUITECTURE_DIR}")

set(CORESDK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/core-c-sdk)
set(LIBSTRING_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/libstring)
set(LIBIO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/libio)


include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "No buscar actualizaciones en GitHub si ya existe")

FetchContent_Declare(
  coresdk
  GIT_REPOSITORY https://github.com/christian-gutman/core-c-sdk
  GIT_TAG        v2.6.0.0
  SOURCE_DIR     ${CORESDK_DIR}
)
FetchContent_MakeAvailable(coresdk)

FetchContent_Declare(
  libstring
  GIT_REPOSITORY https://github.com/christian-gutman/libstring.git
  GIT_TAG        v2.6.0.0
  SOURCE_DIR     ${LIBSTRING_DIR}
)
FetchContent_MakeAvailable(libstring)

FetchContent_Declare(
  libio
  GIT_REPOSITORY https://github.com/christian-gutman/libio.git
  GIT_TAG        v2.6.0.0
  SOURCE_DIR     ${LIBIO_DIR}
)
FetchContent_MakeAvailable(libio)


set(VFP_SDK_DIR  "${CORESDK_DIR}/src/vfp-sdk/x32"  )  


include_directories(
    "${CORESDK_DIR}/src/core" 
    "${VFP_SDK_DIR}" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/vfp/sdk"
    "${LIBSTRING_DIR}/src/strings/core"
    "${LIBIO_DIR}/src/io/core"
)

set(SRC_vfpio
   
    "${CORESDK_DIR}/src/core/core.h"   
    "${CORESDK_DIR}/src/core/core.c"  
    
    
    "${CORESDK_DIR}/src/vfp-sdk/x32/vfp_lib.h"   
    "${CORESDK_DIR}/src/vfp-sdk/x32/pro_ext.h"  

    "${CORESDK_DIR}/src/vfp-sdk/x32/vfp_types.h"   
    "${CORESDK_DIR}/src/vfp-sdk/x32/vfp_types.c"  

    "${LIBSTRING_DIR}/src/strings/core/core_encoding.h"    
    "${LIBSTRING_DIR}/src/strings/core/core_encoding.c"    

    "${LIBSTRING_DIR}/src/strings/core/core_string.h"    
    "${LIBSTRING_DIR}/src/strings/core/core_string.c" 

    "${LIBIO_DIR}/src/io/core/core_io.h"    
    "${LIBIO_DIR}/src/io/core/core_io.c" 
    
    "${CMAKE_CURRENT_SOURCE_DIR}/io.rc"
    "${CMAKE_CURRENT_SOURCE_DIR}/fox_table.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/fox_table.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/vfp_io.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/vfp_io.c"    
)
 
add_library(vfpio SHARED ${SRC_vfpio})
 
set_target_properties(vfpio PROPERTIES LINK_FLAGS "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/io.def")
 
set_target_properties(vfpio PROPERTIES
    PREFIX ""
    OUTPUT_NAME "vfpio"
    SUFFIX ".fll"
    WINDOWS_EXPORT_ALL_SYMBOLS FALSE 
) 


target_compile_definitions(vfpio PRIVATE
    WIN32 _WINDOWS _USRDLL VFP_FLL UNICODE _UNICODE _CRT_SECURE_NO_WARNINGS TARGET_OS_WIN32 WIN32_LEAN_AND_MEAN
) 
 
set(DIR_BIN "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/${DIR_BUILD}")

set_target_properties(vfpio PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${DIR_BIN}/$<CONFIG>"
    LIBRARY_OUTPUT_DIRECTORY "${DIR_BIN}/$<CONFIG>"
    ARCHIVE_OUTPUT_DIRECTORY "${DIR_BIN}/$<CONFIG>"
)
 

add_custom_command(TARGET vfpio POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/examples"
        "$<TARGET_FILE_DIR:vfpio>/"
)

find_library(VFP_LIB NAMES winapims winapims.lib PATHS "${VFP_SDK_DIR}" NO_DEFAULT_PATH)
#find_library(VFP_LIB NAMES ocxapi ocxapi.lib PATHS "${VFP_SDK_DIR}" NO_DEFAULT_PATH)
if(NOT VFP_LIB)
    message(FATAL_ERROR "winapims.lib no encontrado en ${VFP_SDK_DIR}")
endif()

link_directories("${VFP_SDK_DIR}/") 
target_link_libraries(vfpio PRIVATE "${VFP_SDK_DIR}/winapims.lib")

#target_link_libraries(vfpio PRIVATE winapims ${VFP_LIB})

#target_link_libraries(vfpio PRIVATE winhttp crypt32 bcrypt ncrypt shell32 ole32 ${VFP_LIB})
