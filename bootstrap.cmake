set(SDK_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/SDK)
set(DEPENDENCIES_DIRECTORY ${SDK_DIRECTORY}/dependencies)

file(MAKE_DIRECTORY ${DEPENDENCIES_DIRECTORY})
file(REMOVE_RECURSE ${DEPENDENCIES_DIRECTORY}/CMakeSDK)

message(STATUS "cloning CMakeSDK project")

execute_process(
	COMMAND git clone --branch v2.1 https://github.com/StratifyLabs/CMakeSDK.git
	WORKING_DIRECTORY ${DEPENDENCIES_DIRECTORY})

execute_process(
	COMMAND cmake -DCMSDK_SDK_PATH=${SDK_DIRECTORY} -P ${DEPENDENCIES_DIRECTORY}/CMakeSDK/scripts/sos-bootstrap.cmake)


