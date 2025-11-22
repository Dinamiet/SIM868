cmake_minimum_required(VERSION 4.1)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
	ATTerminal
	GIT_REPOSITORY
		git@github.com:Dinamiet/ATTerminal.git
	GIT_TAG
		main
	SOURCE_DIR
		${CMAKE_SOURCE_DIR}/lib/ATTerminal
)

FetchContent_MakeAvailable(
	ATTerminal
)
