cmake_minimum_required(VERSION 3.15)
project(vfputils VERSION 4.2 LANGUAGES C CXX)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
 
if(NOT MSVC)
    message(FATAL_ERROR "vfputils requiere arquitectura Win y compilador MSVC.")
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
set(LIBCRYPTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/libcrypto)
set(LIBWREQ_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/libwreq) 
set(LIBHTML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/libhtml) 
set(LIBSYSTEM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/libsystem)
set(LIBGOOGLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/libgoogle)
set(LIBCERTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/libcerts)
set(LIBJSON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/libjson)

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

FetchContent_Declare(
  libcrypto
  GIT_REPOSITORY https://github.com/christian-gutman/libcrypto.git
  GIT_TAG        v2.6.0.0
  SOURCE_DIR     ${LIBCRYPTO_DIR}
)
FetchContent_MakeAvailable(libcrypto)


FetchContent_Declare(
  libwreq
  GIT_REPOSITORY https://github.com/christian-gutman/libwreq.git
  GIT_TAG        v2.6.0.0
  SOURCE_DIR     ${LIBWREQ_DIR}
)
FetchContent_MakeAvailable(libwreq)


FetchContent_Declare(
  libhtml
  GIT_REPOSITORY https://github.com/christian-gutman/libhtml.git
  GIT_TAG        v2.6.0.0
  SOURCE_DIR     ${LIBHTML_DIR}
)
FetchContent_MakeAvailable(libhtml)

FetchContent_Declare(
  libsystem
  GIT_REPOSITORY https://github.com/christian-gutman/libsystem.git
  GIT_TAG        v2.6.0.0
  SOURCE_DIR     ${LIBSYSTEM_DIR}
)
FetchContent_MakeAvailable(libsystem)

FetchContent_Declare(
  libgoogle
  GIT_REPOSITORY https://github.com/christian-gutman/libgoogle.git
  GIT_TAG        v2.6.0.0
  SOURCE_DIR     ${LIBGOOGLE_DIR}
)
FetchContent_MakeAvailable(libgoogle)

FetchContent_Declare(
  libcerts
  GIT_REPOSITORY https://github.com/christian-gutman/libcerts.git
  GIT_TAG        v2.6.0.0
  SOURCE_DIR     ${LIBCERTS_DIR}
)
FetchContent_MakeAvailable(libcerts)

FetchContent_Declare(
  libjson
  GIT_REPOSITORY https://github.com/christian-gutman/libjson.git
  GIT_TAG        v2.6.0.0
  SOURCE_DIR     ${LIBJSON_DIR}
)
FetchContent_MakeAvailable(libjson)

set(VFP_SDK_DIR  "${CORESDK_DIR}/src/vfp-sdk/x32"  )
 


include_directories(
    "${CORESDK_DIR}/src/core" 
    "${VFP_SDK_DIR}" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/vfp/sdk"
    "${LIBSTRING_DIR}/src/strings/core"    
)
 

set(SRC_vfputils
   
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
    
    "${LIBCRYPTO_DIR}/src/crypto/core/core_crypto.h"    
    "${LIBCRYPTO_DIR}/src/crypto/core/core_crypto.c" 

    "${LIBWREQ_DIR}/src/request/core/core_request.h"    
    "${LIBWREQ_DIR}/src/request/core/core_request.c" 

    "${LIBWREQ_DIR}/src/request/core/core_req_file.h"    
    "${LIBWREQ_DIR}/src/request/core/core_req_file.c" 

    "${LIBWREQ_DIR}/src/request/core/core_rest.h"    
    "${LIBWREQ_DIR}/src/request/core/core_rest.c" 

    "${LIBHTML_DIR}/src/html/core/core_html.h"    
    "${LIBHTML_DIR}/src/html/core/core_html.c" 
    
    "${LIBJSON_DIR}/src/json/core/engine/json.h" 
    "${LIBJSON_DIR}/src/json/core/core_json.h" 
    "${LIBJSON_DIR}/src/json/core/core_json.c" 

    "${LIBSYSTEM_DIR}/src/system/core/core_system.h" 
    "${LIBSYSTEM_DIR}/src/system/core/core_system.c" 
 
    "${LIBCERTS_DIR}/src/certs/core/core_certs.h" 
    "${LIBCERTS_DIR}/src/certs/core/core_certs.c" 
 
   # "${LIBGOOGLE_DIR}/src/google/core/google.h" 
   # "${LIBGOOGLE_DIR}/src/google/core/google_geopos.h" 
   # "${LIBGOOGLE_DIR}/src/google/core/google_geopos.c" 
 


  
    #  
    "../json/vfp_json.h"
    "../json/vfp_json.c"
    #
    "../io/vfp_io.h"
    "../io/vfp_io.c"  
    #
    "../crypto/vfp_crypto.h"
    "../crypto/vfp_crypto.c"  
    #
    "../html/vfp_html.h"
    "../html/vfp_html.c"
    #
    "../request/vfp_request.h"
    "../request/vfp_request.c"
    #
    "../request/vfp_req_file.h"
    "../request/vfp_req_file.c"
    #
    "../request/vfp_rest.h"
    "../request/vfp_rest.c"
    #
    "../system/vfp_system.h"
    "../system/vfp_system.c"
    #
    "../certs/vfp_certs.h"
    "../certs/vfp_certs.c"    

    
    # 
    "../encoding/vfp_encoding.h"
    "../encoding/vfp_encoding.c" 
    #
    "../strings/vfp_strings.h"
    "../strings/vfp_strings.c" 
    #
   # "../google/vfp_google_geopos.h"
   # "../google/vfp_google_geopos.c"

    "${CMAKE_CURRENT_SOURCE_DIR}/fox_table.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/fox_table.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/vfputils.rc" 
)
 
add_library(vfputils SHARED ${SRC_vfputils})


target_include_directories(vfputils PRIVATE
    "${CORESDK_DIR}/src/core"
    "${CORESDK_DIR}/src/vfp-sdk/x32"                             
    "${LIBSTRING_DIR}/src/strings/core"  
    "${LIBIO_DIR}/src/io/core"  
    "${LIBCRYPTO_DIR}/src/crypto/core"
    "${LIBWREQ_DIR}/src/request/core"
    "${LIBHTML_DIR}/src/html/core"
    "${LIBSYSTEM_DIR}/src/system/core"
    "${LIBCERTS_DIR}/src/certs/core"
    "${LIBJSON_DIR}/src/json/core"
    "${LIBGOOGLE_DIR}/src/google/core"      
) 

set_target_properties(vfputils PROPERTIES LINK_FLAGS "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/vfputils.def")
 
set_target_properties(vfputils PROPERTIES
    PREFIX ""
    OUTPUT_NAME "vfputils"
    SUFFIX ".fll"
    WINDOWS_EXPORT_ALL_SYMBOLS FALSE 
) 


target_compile_definitions(vfputils PRIVATE
    WIN32 _WINDOWS _USRDLL VFP_FLL UNICODE _UNICODE _CRT_SECURE_NO_WARNINGS TARGET_OS_WIN32 WIN32_LEAN_AND_MEAN
) 
 
set(DIR_BIN "${CMAKE_CURRENT_SOURCE_DIR}/../../../bin/${DIR_BUILD}")

set_target_properties(vfputils PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${DIR_BIN}/$<CONFIG>"
    LIBRARY_OUTPUT_DIRECTORY "${DIR_BIN}/$<CONFIG>"
    ARCHIVE_OUTPUT_DIRECTORY "${DIR_BIN}/$<CONFIG>"
)
 

find_library(VFP_LIB NAMES winapims winapims.lib PATHS "${VFP_SDK_DIR}" NO_DEFAULT_PATH)
#find_library(VFP_LIB NAMES ocxapi ocxapi.lib PATHS "${VFP_SDK_DIR}" NO_DEFAULT_PATH)
if(NOT VFP_LIB)
    message(FATAL_ERROR "winapims.lib no encontrado en ${VFP_SDK_DIR}")
endif()

link_directories("${VFP_SDK_DIR}/") 
target_link_libraries(vfputils PRIVATE "${VFP_SDK_DIR}/winapims.lib")

#target_link_libraries(vfputils PRIVATE vfpstrenc vfpstr vfpjson)
#target_link_libraries(vfputils PRIVATE winapims ${VFP_LIB})

target_link_libraries(vfputils PRIVATE winhttp crypt32 bcrypt ncrypt shell32 ole32 ${VFP_LIB})
 
