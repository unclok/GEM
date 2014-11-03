cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Newgem)
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

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../CMake_config")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Geant4_DIR}/Modules")
#set(Geant4_DIR /pnfs/opt/SLC5.9/geant4.9.5/lib64/Geant4-9.5.1)
#find_package(cadmesh)

find_package(ROOT)
include(${Geant4_USE_FILE})

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${Geant4_INCLUDE_DIR}
#${cadmesh_INCLUDE_DIR} ${ASSIMP_INCLUDE_DIRS})
#set(Geant4_INCLUDE_DIR execute_process(COMMAND scram tool tag geant4core INCLUDE))
#set(Geant4_LIBRARIES execute_process(COMMAND scram tool tag geant4core LIB))
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${Geant4_INCLUDE_DIR} ${ROOT_INCLUDE_DIR})


#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ASSIMP_CFLAGS_OTHER}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

#INSTALL(CODE "EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_directory 
#${CMAKE_CURRENT_SOURCE_DIR}/../model
#\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/model)")

#file(MAKE_DIRECTORY ./model)
#file(DOWNLOAD http://uosaf0002.sscc.uos.ac.kr/validation/kijin/GEM_70_10_400V_extension.txt ./model/GEM_70_10_400V_extension.txt)
#file(DOWNLOAD http://uosaf0002.sscc.uos.ac.kr/validation/kijin/GEM_70_30_400V_extension.txt ./model/GEM_70_30_400V_extension.txt)
#file(DOWNLOAD http://uosaf0002.sscc.uos.ac.kr/validation/kijin/GEM_70_40_400V_extension.txt ./model/GEM_70_40_400V_extension.txt)
#file(DOWNLOAD http://uosaf0002.sscc.uos.ac.kr/validation/kijin/GEM_70_50_400V_extension.txt ./model/GEM_70_50_400V_extension.txt)
#file(DOWNLOAD http://uosaf0002.sscc.uos.ac.kr/validation/kijin/GEM_70_70_400V_extension.txt ./model/GEM_70_70_400V_extension.txt)

#INSTALL(CODE "EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_directory 
#${CMAKE_CURRENT_SOURCE_DIR}/../model
#$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/model)")

#file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/model)
#file(DOWNLOAD http://uosaf0002.sscc.uos.ac.kr/validation/kijin/GEM_70_10_400V_extension.txt ${CMAKE_INSTALL_PREFIX}/model/GEM_70_10_400V_extension.txt)
#file(DOWNLOAD http://uosaf0002.sscc.uos.ac.kr/validation/kijin/GEM_70_30_400V_extension.txt ${CMAKE_INSTALL_PREFIX}/model/GEM_70_30_400V_extension.txt)
#file(DOWNLOAD http://uosaf0002.sscc.uos.ac.kr/validation/kijin/GEM_70_40_400V_extension.txt ${CMAKE_INSTALL_PREFIX}/model/GEM_70_40_400V_extension.txt)
#file(DOWNLOAD http://uosaf0002.sscc.uos.ac.kr/validation/kijin/GEM_70_50_400V_extension.txt ${CMAKE_INSTALL_PREFIX}/model/GEM_70_50_400V_extension.txt)
#file(DOWNLOAD http://uosaf0002.sscc.uos.ac.kr/validation/kijin/GEM_70_70_400V_extension.txt ${CMAKE_INSTALL_PREFIX}/model/GEM_70_70_400V_extension.txt)

#find_library(ASSIMP_LIBRARY assimp PATHS $ENV{ASSIMP_PATH}/lib)
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)

add_executable(Newgem Newgem.cc ${sources} ${headers})
#target_link_libraries(GEMapp ${Geant4_LIBRARIES} ${cadmesh_LIBRARIES} )
target_link_libraries(Newgem ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})


