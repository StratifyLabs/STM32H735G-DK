cmake_minimum_required (VERSION 3.19)

project(STM32H735G-DK-SDK)

set(API_IS_SDK TRUE CACHE INTERNAL "Build SDK projects")
option(IS_PULL "Pull SDK projects" ON)

set(BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
file(MAKE_DIRECTORY ${BASE_DIRECTORY})

message(STATUS "Base directory ${BASE_DIRECTORY}")

#if INSTALL=ON the library will be staged to be part of an application SDK deployment

macro(sdk_add_subdirectory NAME BRANCH INSTALL)

	sos_sdk_git_clone_or_pull_branch(${BASE_DIRECTORY} ${NAME} https://github.com/StratifyLabs/${NAME}.git ${BRANCH})

	if(${INSTALL})
		message(STATUS "Adding ${NAME} to install target")
		add_subdirectory(${BASE_DIRECTORY}/${NAME} ${NAME})
	else()
		message(STATUS "Excluding ${NAME} from install target")
		add_subdirectory(${BASE_DIRECTORY}/${NAME} ${NAME} EXCLUDE_FROM_ALL)
	endif()

endmacro()

set(STRATIFYOS_LWIP_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/dependencies/InetAPI/lwip/include
	${CMAKE_CURRENT_SOURCE_DIR}/dependencies/InetAPI/lwip/lwip-2.1.2/src/include
	CACHE INTERNAL "LWIP INCLUDE PATHS")

set(API_IS_SDK ON CACHE INTERNAL "API_IS_SDK disable include statements")

sdk_add_subdirectory(API v1.4 ON)
include(${BASE_DIRECTORY}/API/libraries/API.cmake)


set(STM32_CONFIG_PATH ${CMAKE_CURRENT_SOURCE_DIR}/config CACHE INTERNAL "STM32 config path")
set(MBEDTLS_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/config/mbedtls/config.h CACHE INTERNAL "MBEDTLS config file")
set(LWIP_CONFIG_PATH ${CMAKE_CURRENT_SOURCE_DIR}/config CACHE INTERNAL "LWIP config path")
set(LVGL_CONFIG_PATH ${CMAKE_CURRENT_SOURCE_DIR}/config CACHE INTERNAL "LVGL config path")
set(LWIP_STRATIFYOS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/StratifyOS/include CACHE INTERNAL "Stratify OS include directory")
set(STRATIFYOS_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/StratifyOS/include CACHE INTERNAL "Stratify OS include directory")
set(SOS_CONFIG_PATH ${CMAKE_CURRENT_SOURCE_DIR}/config CACHE INTERNAL "StratifyOS config directory")

set(BUILD_STM32H735 ON CACHE INTERNAL "ENABLE BUILDING OF H735")
set(BUILD_STM32_ALL OFF CACHE INTERNAL "DONT BUILD ALL STM32 BUILDS")

sdk_add_subdirectory(StratifyOS-compiler-rt v1.1 OFF)
sdk_add_subdirectory(StratifyOS-newlib v1.1 OFF)
sdk_add_subdirectory(StratifyOS v4.2 ON)
sdk_add_subdirectory(StratifyOS-mcu-stm32 v4.1 OFF)
sdk_add_subdirectory(StratifyOS-fatfs v1.1 OFF)
sdk_add_subdirectory(HalAPI v1.2 ON)
sdk_add_subdirectory(SosAPI v1.2 ON)
sdk_add_subdirectory(JsonAPI v1.2 ON)
sdk_add_subdirectory(CryptoAPI v1.2 ON)
sdk_add_subdirectory(InetAPI v1.2 ON)
sdk_add_subdirectory(CloudAPI v1.1 ON)
sdk_add_subdirectory(LvglAPI v0.0 ON)
sdk_add_subdirectory(DesignAPI v0.0 ON)


message(STATUS "Add targets: StratifyOS_crt_debug_${SOS_ARCH} to install")
#set_property(TARGET StratifyOS_crt_debug_${SOS_ARCH} PROPERTY EXCLUDE_FROM_ALL FALSE)
#set_property(TARGET StratifyOS_crt_release_${SOS_ARCH} PROPERTY EXCLUDE_FROM_ALL FALSE)

#get_property(EXCLUDE_CRT_RELEASE TARGET StratifyOS_crt_release_${SOS_ARCH} PROPERTY EXCLUDE_FROM_ALL)


#message(STATUS "Exlude is ${EXCLUDE_CRT_RELEASE}")


add_custom_target(status DEPENDS ${GIT_STATUS_DEPENDS})
