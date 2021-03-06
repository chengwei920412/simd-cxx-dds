cmake_minimum_required (VERSION 2.6)
set(CMAKE_MODULE_PATH ../../cmake)
project (ishapes-driver)
include (MacroOpenSplice)
include (osmacros)
find_package (OpenSplice REQUIRED)
find_package (Boost REQUIRED thread program_options system)
find_package (SimD REQUIRED)

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${OpenSplice_INCLUDE_DIRS}
  ${SimD_INCLUDE_DIRS}
)


set (idls ishapes.idl)


foreach(idl ${idls})
	OpenSplice_IDLGEN (${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1.cpp" VARS_1 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1.h" VARS_2 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1Dcps.cpp" VARS_3 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1Dcps.h" VARS_4 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1Dcps_impl.cpp" VARS_5 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1Dcps_impl.h" VARS_6 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1SplDcps.cpp" VARS_7 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/\\1SplDcps.h" VARS_8 ${idl})
        string (REGEX REPLACE "\(.*\).idl" "gen/ccpp_\\1.h" VARS_9 ${idl})
	set(OpenSplice_DATAMODEL ${OpenSplice_DATAMODEL} ${VARS_1} ${VARS_2} ${VARS_3} ${VARS_4} ${VARS_5} ${VARS_6} ${VARS_7} ${VARS_8} ${VARS_9})
endforeach(idl)

set (SOURCES
 main.cpp
 util.cpp
)


set (EXE ishapes-driver)
set (DATAMODEL datamodel)

add_executable (${EXE} ${SOURCES})
add_library (${DATAMODEL} STATIC ${OpenSplice_DATAMODEL})

add_definitions (
 ${OpenSplice_DEFINITIONS}
 ${DEFINITIONS}
)

target_link_libraries (
  ${DATAMODEL} 
  ${OpenSplice_LIBRARIES}
  ${Boost_LIBRARIES}
  ${SimD_LIBRARIES}
)

target_link_libraries (${EXE}
 ${OpenSplice_LIBRARIES}
 ${Boost_LIBRARIES}
 ${DATAMODEL} 
)
