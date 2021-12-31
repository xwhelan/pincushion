cmake_minimum_required(VERSION 3.0.0)

# Configuration types
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
IF(DEFINED CMAKE_BUILD_TYPE)
  SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS  ${CMAKE_CONFIGURATION_TYPES})
ENDIF()

# read debian/changelog and parse the version/build number
FILE (READ "${CMAKE_CURRENT_SOURCE_DIR}/CHANGELOG.md" CHANGELOG)

# Note: CMAKE doesn't support semantic versioning!
# STRING (REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+((-([0-9a-zA-Z-]+(\\.[0-9a-zA-Z-]+)*))?)(\\+([0-9a-zA-Z-]+(\\.[0-9a-zA-Z-]+)*))?"
STRING (REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+"
    CHANGELOG_VERSION "${CHANGELOG}")

SET(CHANGELOG_VERSION ${CHANGELOG_VERSION} CACHE INTERNAL "Project version from CHANGELOG."
FORCE)


project(pincushion VERSION "${CHANGELOG_VERSION}")
set (CMAKE_CXX_STANDARD 11)

include(CTest)

add_subdirectory(CSV)
add_executable(csv2json src/csv2json.cpp)
target_link_libraries(csv2json PUBLIC CSV)

target_include_directories(csv2json PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/CSV"
                          )

install(TARGETS csv2json DESTINATION bin)
