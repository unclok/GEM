cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(GEM)
#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()


set(CMAKE_MOUDLE_PATH
/pnfs/opt/cemachines/geant4.9.6/lib64/Geant4-9.6.2/Modules)
set(Geant4_DIR /pnfs/opt/cemachines/geant4.9.6/lib64/Geant4-9.6.2)
set(cadmesh_DIR /pnfs/opt/cadmesh/forgeant4.9.6/lib/cmake/cadmesh-0.9)
set(assimp_DIR /pnfs/opt/assimp/lib/cmake/assimp-3.0)
find_package(cadmesh)

include(${Geant4_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${Geant4_INCLUDE_DIR}
${cadmesh_INCLUDE})

set()


message("include :  ${CMAKE_CURRENT_SOURCE_DIR}/include ${Geant4_INCLUDE_DIR} ${cadmesh_INCLUDE}")
message("Option : ${CMAKE_CXX_FLAGS}")
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)

add_executable(GEMapp EXCLUDE_FROM_ALL GEMapp.cc ${sources})
target_link_libraries(GEMapp ${Geant4_LIBRARIES})


