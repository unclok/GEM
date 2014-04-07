IF(NOT DEFINED ENV{CADMESH_PATH})
	SET(ENV{CADMESH_PATH} ${cadmesh_DIR})
ENDIF()

find_library(cadmesh_LIBRARIES NAMES cadmesh HINTS $ENV{CADMESH_PATH} $ENV{CADMESH_PATH}/lib)
find_path(cadmesh_INCLUDE_DIR NAMES CADMesh.hh HINTS $ENV{CADMESH_PATH} $ENV{CADMESH_PATH}/include )

message( STATUS cadmesh_LIBRARIES ${cadmesh_LIBRARIES})
message( STATUS cadmesh_INCLUDE_DIR ${cadmesh_INCLUDE_DIR})

# Open Asset Importer Library
IF(DEFINED ENV{ASSIMP_PATH})
    find_package(assimp)
    set(cadmesh_LIBRARIES ${cadmesh_LIBRARIES} ${ASSIMP_LIBRARIES})
    #message( assimp LIBRARIES : ${ASSIMP_LIBRARIES})
    add_definitions(${CMAKE_CXX_FLAGS} " -DNOVCGLIB")
ENDIF()

IF(DEFINED ENV{VCGLIB_PATH})
    include_directories($ENV{VCGLIB_PATH})
    set(VCGLIB_SRC $ENV{VCGLIB_PATH}/wrap/ply/plylib.cpp)
    add_definitions(${CMAKE_CXX_FLAGS} " -DNOASSIMP")
    #    set(VCGLIB_TARGET plylib)
ENDIF()

IF(DEFINED ENV{TET_PATH})
    set(cadmesh_LIBRARIES ${cadmesh_LIBRARIES} tet)
    include_directories(${TETGEN_DIR})
ELSE()
    add_definitions(${CMAKE_CXX_FLAGS} " -DNOTET")
ENDIF()


INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(cadmesh DEFAULT_MSG cadmesh_LIBRARIES)

mark_as_advanced(cadmesh_FOUND cadmesh_LIBRARIES cadmesh_INCLUDE_DIR)
