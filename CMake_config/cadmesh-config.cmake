
set(cadmesh_LIBRARIES cadmesh)

# Open Asset Importer Library
IF(DEFINED ENV{ASSIMP_PATH})
    find_package(assimp)
    set(cadmesh_LIBRARIES ${cadmesh_LIBRARIES} assimp)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOVCGLIB")
    set(cadmesh_INCLUDE ${cadmesh_DIR}/../../../include)
ENDIF()

IF(DEFINED ENV{VCGLIB_PATH})
    include_directories(/pnfs/opt/vcglib/)
    set(VCGLIB_SRC /pnfs/opt/vcglib//wrap/ply/plylib.cpp)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOASSIMP")
    #    set(VCGLIB_TARGET plylib)
ENDIF()

IF(DEFINED ENV{TET_PATH})
    set(cadmesh_LIBRARIES ${cadmesh_LIBRARIES} tet)
    include_directories(${TETGEN_DIR})
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOTET")
ENDIF()

