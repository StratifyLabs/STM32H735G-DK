cmake_minimum_required (VERSION 3.19)

project(STM32H735G-DK-SDK)

set(API_IS_SDK TRUE CACHE INTERNAL "Build SDK projects")
option(IS_PULL "Pull SDK projects" ON)

set(BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
file(MAKE_DIRECTORY ${BASE_DIRECTORY})

message(STATUS "Base directory ${BASE_DIRECTORY}")

macro(sdk_add_subdirectory NAME BRANCH)
	if(IS_PULL)
		sos_sdk_git_clone_or_pull_branch(${BASE_DIRECTORY} ${NAME} ssh://git@github.com/StratifyLabs/${NAME}.git ${BRANCH})
	endif()
	add_subdirectory(${BASE_DIRECTORY}/${NAME} ${NAME})
endmacro()

include(CTest)

set(STRATIFYOS_LWIP_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/../InetAPI/lwip/include
	${CMAKE_CURRENT_SOURCE_DIR}/../InetAPI/lwip/lwip-2.1.2/src/include
	CACHE INTERNAL "LWIP INCLUDE PATHS")


sdk_add_subdirectory(API v1.0)
include(${BASE_DIRECTORY}/API/libraries/API.cmake)

set(BUILD_STM32H735 ON CACHE INTERNAL "ENABLE BUILDING OF H735")
set(BUILD_STM32_ALL OFF CACHE INTERNAL "DONT BUILD ALL STM32 BUILDS")

sdk_add_subdirectory(StratifyOS-compiler-rt v1.0)
sdk_add_subdirectory(StratifyOS-newlib v1.0)
sdk_add_subdirectory(StratifyOS main)
sdk_add_subdirectory(StratifyOS-mcu-stm32 main)
sdk_add_subdirectory(StratifyOS-fatfs v1.0)
sdk_add_subdirectory(LvglAPI main)



