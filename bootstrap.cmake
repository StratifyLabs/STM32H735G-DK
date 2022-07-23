cmake_minimum_required (VERSION 3.19)

set(SDK_DIRECTORY ${CMAKE_SOURCE_DIR}/SDK)
set(SDK_PATH ${SDK_DIRECTORY}/StratifyLabs-SDK)

file(MAKE_DIRECTORY ${SDK_PATH})
set(DEPENDENCIES_DIRECTORY ${SDK_DIRECTORY}/dependencies)


if(NOT EXISTS ${DEPENDENCIES_DIRECTORY}/CMakeSDK/CMakeLists.txt)
	file(MAKE_DIRECTORY ${DEPENDENCIES_DIRECTORY})
	execute_process(
		COMMAND git clone --branch v1.2 https://github.com/StratifyLabs/CMakeSDK.git
		WORKING_DIRECTORY ${DEPENDENCIES_DIRECTORY}
		)
endif()

execute_process(
	COMMAND cmake -DSDK_DIRECTORY=${SDK_DIRECTORY} -P ${DEPENDENCIES_DIRECTORY}/CMakeSDK/scripts/bootstrap.cmake
	)


