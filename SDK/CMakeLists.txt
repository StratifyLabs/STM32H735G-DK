cmake_minimum_required (VERSION 3.19)

project(STM32H735G-DK-SDK)

set(API_IS_SDK TRUE CACHE INTERNAL "Build SDK projects")
option(IS_PULL "Pull SDK projects" ON)

set(BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
file(MAKE_DIRECTORY ${BASE_DIRECTORY})

message(STATUS "Base directory ${BASE_DIRECTORY}")

#if INSTALL=ON the library will be staged to be part of an application SDK deployment

set(GIT_STATUS_DEPENDS "")

macro(sdk_add_subdirectory NAME BRANCH INSTALL)

	if(IS_PULL)
		sos_sdk_git_clone_or_pull_branch(${BASE_DIRECTORY} ${NAME} ssh://git@github.com/StratifyLabs/${NAME}.git ${BRANCH})
	endif()

	if(${INSTALL})
		message(STATUS "Adding ${NAME} to install target")
		add_subdirectory(${BASE_DIRECTORY}/${NAME} ${NAME})
	else()
		message(STATUS "Excluding ${NAME} from install target")
		add_subdirectory(${BASE_DIRECTORY}/${NAME} ${NAME} EXCLUDE_FROM_ALL)
	endif()

	set(GIT_STATUS_TARGET ${NAME}-git-status)

	list(APPEND GIT_STATUS_DEPENDS ${GIT_STATUS_TARGET})
	add_custom_target(${GIT_STATUS_TARGET}
		COMMAND git status
		WORKING_DIRECTORY ${BASE_DIRECTORY}/${NAME}
		)
endmacro()

set(STRATIFYOS_LWIP_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/dependencies/InetAPI/lwip/include
	${CMAKE_CURRENT_SOURCE_DIR}/dependencies/InetAPI/lwip/lwip-2.1.2/src/include
	CACHE INTERNAL "LWIP INCLUDE PATHS")

set(API_IS_SDK ON CACHE INTERNAL "API_IS_SDK disable include statemenets")

sdk_add_subdirectory(API main ON)
include(${BASE_DIRECTORY}/API/libraries/API.cmake)

set(BUILD_STM32H735 ON CACHE INTERNAL "ENABLE BUILDING OF H735")
set(BUILD_STM32_ALL OFF CACHE INTERNAL "DONT BUILD ALL STM32 BUILDS")

sdk_add_subdirectory(StratifyOS-compiler-rt v1.0 OFF)
sdk_add_subdirectory(StratifyOS-newlib v1.0 OFF)
sdk_add_subdirectory(StratifyOS main ON)
sdk_add_subdirectory(StratifyOS-mcu-stm32 main OFF)
sdk_add_subdirectory(StratifyOS-fatfs v1.0 OFF)
sdk_add_subdirectory(HalAPI v1.0 ON)
sdk_add_subdirectory(SosAPI v1.0 ON)
sdk_add_subdirectory(JsonAPI v1.0 ON)
sdk_add_subdirectory(CryptoAPI v1.0 ON)
sdk_add_subdirectory(InetAPI v1.0 ON)
sdk_add_subdirectory(CloudAPI v1.0 ON)
sdk_add_subdirectory(LvglAPI main ON)


message(STATUS "Add targets: StratifyOS_crt_debug_${SOS_ARCH} to install")
#set_property(TARGET StratifyOS_crt_debug_${SOS_ARCH} PROPERTY EXCLUDE_FROM_ALL FALSE)
#set_property(TARGET StratifyOS_crt_release_${SOS_ARCH} PROPERTY EXCLUDE_FROM_ALL FALSE)

#get_property(EXCLUDE_CRT_RELEASE TARGET StratifyOS_crt_release_${SOS_ARCH} PROPERTY EXCLUDE_FROM_ALL)


#message(STATUS "Exlude is ${EXCLUDE_CRT_RELEASE}")


# Deploy config files
message(STATUS "Deploying user configuration files to libraries")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h
	DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/LvglAPI/lvgl/include/lvgl)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/stm32h7xx_hal_conf.h
	DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/StratifyOS-mcu-stm32/src/stm32h7xx)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lwipopts.h
	DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/InetAPI/lwip/include)

add_custom_target(status DEPENDS ${GIT_STATUS_DEPENDS})
