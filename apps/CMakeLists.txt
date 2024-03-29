cmake_minimum_required (VERSION 3.19)

project(STM32H735G-DK-Apps)

set(BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "Base directory ${BASE_DIRECTORY}")

option(APPS_IS_TESTSUITE "Clone and build the Test suite" ON)
option(APPS_IS_DEMO "Clone and build the Demo applications" ON)
option(APPS_IS_GUI "Clone and build the Demo applications" ON)

macro(sdk_add_subdirectory NAME BRANCH)
	cmsdk_git_clone_or_pull_branch(${BASE_DIRECTORY} ${NAME} ssh://git@github.com/StratifyLabs/${NAME}.git ${BRANCH})
	add_subdirectory(${BASE_DIRECTORY}/${NAME} ${NAME})
endmacro()

if(APPS_IS_DEMO)
	sdk_add_subdirectory(HelloWorld main)
	sdk_add_subdirectory(Blinky main)
endif()
sdk_add_subdirectory(SystemApps main)
if(APPS_IS_TESTSUITE)
	sdk_add_subdirectory(testsuite main)
endif()
if(APPS_IS_GUI)
	if(IS_PULL OR NOT EXISTS ${BASE_DIRECTORY}/gui)
		cmsdk_git_clone_or_pull_branch(${BASE_DIRECTORY} gui ssh://git@github.com/StratifyLabs/gui.git main)
	endif()
	# we skip the top level directory (SDK stuff) and just pull in the application
	add_subdirectory(${BASE_DIRECTORY}/gui/gui gui)
endif()

