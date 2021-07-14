cmake_minimum_required (VERSION 3.19)

project(STM32H735G-DK-Apps)

set(BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "Base directory ${BASE_DIRECTORY}")

option(IS_TESTSUITE ON)
option(IS_DEMO OFF)

macro(sdk_add_subdirectory NAME BRANCH)
	if(IS_PULL OR NOT EXISTS ${BASE_DIRECTORY}/${NAME})
		sos_sdk_git_clone_or_pull_branch(${BASE_DIRECTORY} ${NAME} ssh://git@github.com/StratifyLabs/${NAME}.git ${BRANCH})
	endif()
	add_subdirectory(${BASE_DIRECTORY}/${NAME} ${NAME})
endmacro()

if(IS_DEMO)
	sdk_add_subdirectory(HelloWorld main)
	sdk_add_subdirectory(Blinky main)
endif()
sdk_add_subdirectory(SystemApps main)
if(IS_TESTSUITE)
	sdk_add_subdirectory(testsuite main)
endif()



