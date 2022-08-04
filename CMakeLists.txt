cmake_minimum_required (VERSION 3.12)

set(SDK_DIRECTORY ${CMAKE_SOURCE_DIR}/SDK)
set(CMSDK_LOCAL_PATH ${SDK_DIRECTORY}/local)

set(CMAKE_MODULE_PATH ${CMSDK_LOCAL_PATH}/cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_MODULE_PATH}/cmsdk-toolchain.cmake)
include(cmsdk)

project(STM32H735G-DK CXX C ASM)
include(CTest)

set(CMSDK_ARCH v7em_f5dh)
set(CMSDK_ARCH_LIST "")

set(CMSDK_PULL_TARGET pull)
add_custom_target(pull
	COMMAND git pull
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


add_subdirectory(SDK SDK)
add_subdirectory(STM32H735G-DK)
add_subdirectory(apps)
add_subdirectory(fonts)

add_custom_target(publish_header
	COMMAND sl os.publish:header,path=STM32H735G-DK
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)

add_custom_target(publish
	COMMAND sl os.publish:path=STM32H735G-DK,signkey=RhnmvxQ8D4tlh02L8693
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
