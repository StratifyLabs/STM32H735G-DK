cmake_minimum_required (VERSION 3.19)

set(SDK_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/SDK)
set(SDK_PATH ${SDK_DIRECTORY}/StratifyLabs-SDK)

file(MAKE_DIRECTORY ${SDK_PATH})
set(DEPENDENCIES_DIRECTORY ${SDK_DIRECTORY}/dependencies)

set(ENV{SOS_SDK_PATH} ${SDK_PATH})

if(NOT EXISTS ${SDK_PATH}/bin/sl)
	# Grab sl and put it in the SDK
	file(DOWNLOAD https://stratifylabs.page.link/${SL_ARCH} ${SDK_PATH}/bin/sl)
	file(CHMOD ${SDK_PATH}/bin/sl
		PERMISSIONS  OWNER_READ  OWNER_WRITE OWNER_EXECUTE WORLD_READ WORLD_EXECUTE GROUP_READ GROUP_EXECUTE)
endif()

# Check to see if sl is logged in -- abort if it is not

if(NOT EXISTS ${SDK_PATH}/bin/arm-none-eabi-gcc)
	execute_process(
		COMMAND ${SDK_PATH}/bin/sl cloud.install:compiler
		)
endif()

file(MAKE_DIRECTORY ${DEPENDENCIES_DIRECTORY})

if(NOT EXISTS ${DEPENDENCIES_DIRECTORY}/CMakeSDK/CMakeLists.txt)
execute_process(
	COMMAND git clone --branch main https://github.com/StratifyLabs/CMakeSDK.git
	WORKING_DIRECTORY ${DEPENDENCIES_DIRECTORY}
	)
endif()

set(CMAKE_SDK_DIRECTORY ${DEPENDENCIES_DIRECTORY}/CMakeSDK)
file(MAKE_DIRECTORY ${CMAKE_SDK_DIRECTORY}/cmake_link)

execute_process(
	COMMAND cmake ..
	WORKING_DIRECTORY ${CMAKE_SDK_DIRECTORY}/cmake_link
	)

execute_process(
	COMMAND cmake --build . --target install
	WORKING_DIRECTORY ${CMAKE_SDK_DIRECTORY}/cmake_link
	)


