set(TARGET_NAME ${PROJECT_NAME})
add_executable(${TARGET_NAME} main.cpp)
SET(LIBARCHIVE_DIR "${PROJECT_SOURCE_DIR}/lib/libarchive/win")
SET(LIBARCHIVE_INCLUDE_DIR "${LIBARCHIVE_DIR}/include")
SET(LIBARCHIVE_LIBRARY_DIR
		"${LIBARCHIVE_DIR}/$<IF:$<STREQUAL:${CMAKE_GENERATOR_PLATFORM},x64>,x64,x86>/$<IF:$<CONFIG:DEBUG>,Debug,Release>"
)
SET(LIBARCHIVE_LIBRARY
        "${LIBARCHIVE_LIBRARY_DIR}/archive.lib"
        "${LIBARCHIVE_LIBRARY_DIR}/$<IF:$<CONFIG:DEBUG>,zlibd.lib,zlib.lib>"
)

target_include_directories(
    ${TARGET_NAME}
    PRIVATE "${LIBARCHIVE_INCLUDE_DIR}"
    PRIVATE "${PROJECT_BINARY_DIR}"
)
target_link_libraries(
    ${TARGET_NAME}
    PRIVATE
    "${LIBARCHIVE_LIBRARY}"
)