set(TARGET_NAME ${PROJECT_NAME})
add_executable(${TARGET_NAME} main.cpp)
set(ARCHIVE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/win/libarchive/include")
if($<$<CONFIG:Debug>:DEBUG_MODE>)
	set(ARCHIVE_LIBRARIES_DIR "${CMAKE_SOURCE_DIR}/lib/win/libarchive/x64/Debug")
	set(ARCHIVE_LIBRARIES
		${ARCHIVE_LIBRARIES_DIR}/archive.lib
		${ARCHIVE_LIBRARIES_DIR}/zlibd.lib
	)
else()
	set(ARCHIVE_LIBRARIES_DIR "${CMAKE_SOURCE_DIR}/lib/win/libarchive/x64/Release")
	set(ARCHIVE_LIBRARIES
		${ARCHIVE_LIBRARIES_DIR}/archive.lib
		${ARCHIVE_LIBRARIES_DIR}/zlib.lib
	)
endif()

target_include_directories(
    ${TARGET_NAME}
    PRIVATE ${ARCHIVE_INCLUDE_DIR}
    PRIVATE "${PROJECT_BINARY_DIR}"
)
target_link_libraries(
    ${TARGET_NAME}
    PRIVATE
    ${ARCHIVE_LIBRARIES}
)