cmake_minimum_required (VERSION 3.19)

set(SDK_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/SDK)
set(SDK_PATH ${SDK_DIRECTORY}/StratifyLabs-SDK)

if(NOT EXISTS ${SDK_PATH})
	file(MAKE_DIRECTORY ${SDK_PATH})
	set(DEPENDENCIES_DIRECTORY ${SDK_DIRECTORY}/dependencies)

	set(ENV{SOS_SDK_PATH} ${SDK_PATH})

	# Grab sl and put it in the SDK
	file(DOWNLOAD https://stratifylabs.page.link/sl_Darwin_x86_64 ${SDK_PATH}/bin/sl)
	file(CHMOD ${SDK_PATH}/bin/sl
		PERMISSIONS  OWNER_READ  OWNER_WRITE OWNER_EXECUTE WORLD_READ WORLD_EXECUTE GROUP_READ GROUP_EXECUTE)

	execute_process(
		COMMAND ${SDK_PATH}/bin/sl cloud.install:compiler
		)

	file(MAKE_DIRECTORY ${DEPENDENCIES_DIRECTORY})
	execute_process(
		COMMAND git clone --branch main https://github.com/StratifyLabs/CMakeSDK.git
		WORKING_DIRECTORY ${DEPENDENCIES_DIRECTORY}
		)

	set(CMAKE_SDK_DIRECTORY ${DEPENDENCIES_DIRECTORY}/CmakeSDK)

	file(MAKE_DIRECTORY ${CMAKE_SDK_DIRECTORY}/cmake_link)
	execute_process(
		COMMAND cmake ..
		WORKING_DIRECTORY ${CMAKE_SDK_DIRECTORY}/cmake_link
		)

	execute_process(
		COMMAND cmake --build . --target install
		WORKING_DIRECTORY ${CMAKE_SDK_DIRECTORY}/cmake_link
		)

endif()

