cmake_minimum_required (VERSION 3.12)

set(SDK_DIRECTORY ${CMAKE_SOURCE_DIR}/SDK)
set(SOS_SDK_PATH ${SDK_DIRECTORY}/StratifyLabs-SDK)

set(ENV_SOS_SDK_PATH $ENV{SOS_SDK_PATH})

message(STATUS "ENV SOS_SDK_PATH is ${ENV_SOS_SDK_PATH}")

if(NOT ${ENV_SOS_SDK_PATH} STREQUAL ${SOS_SDK_PATH})
	message(FATAL_ERROR "ENV SOS_SDK_PATH must be ${SOS_SDK_PATH}")
endif()

set(ENV{SOS_SDK_PATH} ${SOS_SDK_PATH})

set(CMAKE_MODULE_PATH ${SOS_SDK_PATH}/cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_MODULE_PATH}/sos-toolchain.cmake)
include(sos-sdk)

project(STM32H735G-DK CXX C ASM)
include(CTest)

set(SOS_ARCH v7em_f5dh)
set(SOS_ARCH_LIST "")

set(SOS_SDK_PULL_TARGET pull)
add_custom_target(pull
	COMMAND git pull
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(API_IS_SDK ON CACHE INTERNAL "Use to prevent include of modules")

add_subdirectory(SDK SDK)
add_subdirectory(STM32H735G-DK)
add_subdirectory(apps)

add_custom_target(publish_header
	COMMAND sl os.publish:header,path=STM32H735G-DK
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)

add_custom_target(publish
	COMMAND sl os.publish:path=STM32H735G-DK,signkey=RhnmvxQ8D4tlh02L8693
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
