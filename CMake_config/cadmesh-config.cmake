
set(cadmesh_LIBRARIES cadmesh)
set(cadmesh_INCLUDE ${cadmesh_DIR}/../../../include)

#message("Defined cadmesh")
# Open Asset Importer Library
IF(DEFINED ENV{ASSIMP_PATH})
#    message("Defined ASSIMP")
    find_package(assimp)
    set(cadmesh_LIBRARIES ${cadmesh_LIBRARIES} assimp)
    add_definitions(${CMAKE_CXX_FLAGS} " -DNOVCGLIB")
ENDIF()

IF(DEFINED ENV{VCGLIB_PATH})
    include_directories(/pnfs/opt/vcglib/)
    set(VCGLIB_SRC /pnfs/opt/vcglib//wrap/ply/plylib.cpp)
    add_definitions(${CMAKE_CXX_FLAGS} " -DNOASSIMP")
    #    set(VCGLIB_TARGET plylib)
ENDIF()

IF(DEFINED ENV{TET_PATH})
    set(cadmesh_LIBRARIES ${cadmesh_LIBRARIES} tet)
    include_directories(${TETGEN_DIR})
ELSE()
    add_definitions(${CMAKE_CXX_FLAGS} " -DNOTET")
ENDIF()

