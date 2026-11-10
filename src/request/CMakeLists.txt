cmake_minimum_required(VERSION 3.15)
project(vfpwreq VERSION 4.2 LANGUAGES C CXX)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
 
if(NOT MSVC)
    message(FATAL_ERROR "vfpwreq requiere arquitectura Win y compilador MSVC.")
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

set(VFP_SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../sdk")

include_directories("${VFP_SDK_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/src/" "${CMAKE_CURRENT_SOURCE_DIR}/src/vfp/sdk")

set(SRC_vfpwreq
    "../../core.h"
    "../../core.c"
    "../../vfp/sdk/vfp_lib.h"
    "../../vfp/sdk/pro_ext.h"
    #
    "../../encoding/core/core_encoding.h"
    "../../encoding/core/core_encoding.c"
    #
    "../../strings/core/core_string.h"
    "../../strings/core/core_string.c"
    #
    "../../io/core/core_io.h"
    "../../io/core/core_io.c"
    #
    "../../crypto/core/core_crypto.h"
    "../../crypto/core/core_crypto.c"
    #
    "../../request/core/core_request.h"
    "../../request/core/core_request.c"
    #
    "../../request/core/core_req_file.h"
    "../../request/core/core_req_file.c"
    #
    "../../request/core/core_rest.h"
    "../../request/core/core_rest.c"   
    #  
    "${CMAKE_CURRENT_SOURCE_DIR}/../sdk/vfp_types.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../sdk/vfp_types.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/request.rc"
    "${CMAKE_CURRENT_SOURCE_DIR}/fox_table.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/fox_table.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/vfp_request.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/vfp_request.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/vfp_req_file.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/vfp_req_file.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/vfp_rest.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/vfp_rest.c"        
)
 
add_library(vfpwreq SHARED ${SRC_vfpwreq})
 
set_target_properties(vfpwreq PROPERTIES LINK_FLAGS "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/request.def")
 
set_target_properties(vfpwreq PROPERTIES
    PREFIX ""
    OUTPUT_NAME "vfpwreq"
    SUFFIX ".fll"
    WINDOWS_EXPORT_ALL_SYMBOLS FALSE 
) 


target_compile_definitions(vfpwreq PRIVATE
    WIN32 _WINDOWS _USRDLL VFP_FLL UNICODE _UNICODE _CRT_SECURE_NO_WARNINGS TARGET_OS_WIN32 WIN32_LEAN_AND_MEAN _WINSOCK_DEPRECATED_NO_WARNINGS
) 


target_link_libraries(vfpwreq PRIVATE winhttp crypt32 bcrypt ncrypt ${VFP_LIB})

set(DIR_BIN "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/${DIR_BUILD}")

set_target_properties(vfpwreq PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${DIR_BIN}/$<CONFIG>"
    LIBRARY_OUTPUT_DIRECTORY "${DIR_BIN}/$<CONFIG>"
    ARCHIVE_OUTPUT_DIRECTORY "${DIR_BIN}/$<CONFIG>"
)
 

add_custom_command(TARGET vfpwreq POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/../examples"
        "$<TARGET_FILE_DIR:vfpwreq>/"
)

find_library(VFP_LIB NAMES winapims winapims.lib PATHS "${VFP_SDK_DIR}" NO_DEFAULT_PATH)
#find_library(VFP_LIB NAMES ocxapi ocxapi.lib PATHS "${VFP_SDK_DIR}" NO_DEFAULT_PATH)
if(NOT VFP_LIB)
    message(FATAL_ERROR "winapims.lib no encontrado en ${VFP_SDK_DIR}")
endif()

link_directories("${VFP_SDK_DIR}/") 
target_link_libraries(vfpwreq PRIVATE "${VFP_SDK_DIR}/winapims.lib")

#target_link_libraries(vfpwreq PRIVATE winapims ${VFP_LIB})

#target_link_libraries(vfpwreq PRIVATE winhttp crypt32 bcrypt ncrypt shell32 ole32 ${VFP_LIB})
