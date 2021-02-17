#.rst:
# FindPhysFS
# -------------
#
# Locate PhysFS library
#
# This module defines:
#
# ::
#
# PHYSFS_LIBRARIES, the name of the library to link against
# PHYSFS_INCLUDE_DIRS, where to find the headers
# PHYSFS_FOUND, if false, do not try to link against
# PHYSFS_VERSION_STRING - human-readable string containing the
# version of PHYSFS
#
#
#
# For backward compatibility the following variables are also set:
#
# ::
#
# PHYSFS_LIBRARY
# PHYSFS_INCLUDE_DIR
# PHYSFS_FOUND
#
#
#
# Created by Eric Wing. This was influenced by the FindSDL.cmake
# module, but with modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).

if(NOT PHYSFS_INCLUDE_DIR AND PHYSFS_INCLUDE_DIR)
  set(PHYSFS_INCLUDE_DIR ${PHYSFS_INCLUDE_DIR} CACHE PATH "directory cache entry initialized from old variable name")
endif()
find_path(PHYSFS_INCLUDE_DIR physfs.h
  HINTS
    ENV PHYSFSDIR
  PATH_SUFFIXES include
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(VC_LIB_PATH_SUFFIX lib/x64)
else()
  set(VC_LIB_PATH_SUFFIX lib/x86)
endif()

if(NOT PHYSFS_LIBRARY AND PHYSFS_LIBRARY)
  set(PHYSFS_LIBRARY ${PHYSFS_LIBRARY} CACHE FILEPATH "file cache entry initialized from old variable name")
endif()
find_library(PHYSFS_LIBRARY
  NAMES physfs
  HINTS
    ENV PHYSFSDIR
    ${PHYSFS_SEARCH_PATHS}
  PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX}
)

if(PHYSFS_INCLUDE_DIR AND EXISTS "${PHYSFS_INCLUDE_DIR}/physfs.h")
  file(STRINGS "${PHYSFS_INCLUDE_DIR}/physfs.h" PHYSFS_VERSION_MAJOR_LINE REGEX "^#define[ \t]+PHYSFS_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${PHYSFS_INCLUDE_DIR}/physfs.h" PHYSFS_VERSION_MINOR_LINE REGEX "^#define[ \t]+PHYSFS_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${PHYSFS_INCLUDE_DIR}/physfs.h" PHYSFS_VERSION_PATCH_LINE REGEX "^#define[ \t]+PHYSFS_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+PHYSFS_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" PHYSFS_VERSION_MAJOR "${PHYSFS_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+PHYSFS_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" PHYSFS_VERSION_MINOR "${PHYSFS_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+PHYSFS_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" PHYSFS_VERSION_PATCH "${PHYSFS_VERSION_PATCH_LINE}")
  set(PHYSFS_VERSION_STRING ${PHYSFS_VERSION_MAJOR}.${PHYSFS_VERSION_MINOR}.${PHYSFS_VERSION_PATCH})
  unset(PHYSFS_VERSION_MAJOR_LINE)
  unset(PHYSFS_VERSION_MINOR_LINE)
  unset(PHYSFS_VERSION_PATCH_LINE)
  unset(PHYSFS_VERSION_MAJOR)
  unset(PHYSFS_VERSION_MINOR)
  unset(PHYSFS_VERSION_PATCH)
endif()

set(PHYSFS_LIBRARIES ${PHYSFS_LIBRARY})
set(PHYSFS_INCLUDE_DIRS ${PHYSFS_INCLUDE_DIR})

FIND_PACKAGE_HANDLE_STANDARD_ARGS(PhysFS
                                  REQUIRED_VARS PHYSFS_LIBRARIES PHYSFS_INCLUDE_DIRS
                                  VERSION_VAR PHYSFS_VERSION_STRING)

# for backward compatibility
set(PHYSFS_LIBRARY ${PHYSFS_LIBRARIES})
set(PHYSFS_INCLUDE_DIR ${PHYSFS_INCLUDE_DIRS})
set(PHYSFS_FOUND ${PHYSFS_FOUND})

mark_as_advanced(PHYSFS_LIBRARY PHYSFS_INCLUDE_DIR)
