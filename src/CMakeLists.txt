set(TARGET_NAME ${PROJECT_NAME})
add_executable(${TARGET_NAME} main.cpp)
set(ARCHIVE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/win/archive/include")
set(ARCHIVE_LIBRARIES_DIR "${CMAKE_SOURCE_DIR}/lib/win/archive/x64/Debug")
set(ARCHIVE_LIBRARIES
    ${ARCHIVE_LIBRARIES_DIR}/archive.lib
    ${ARCHIVE_LIBRARIES_DIR}/bz2d.lib
    ${ARCHIVE_LIBRARIES_DIR}/trueconf/charset.lib
    ${ARCHIVE_LIBRARIES_DIR}/trueconf/iconv.lib
    ${ARCHIVE_LIBRARIES_DIR}/libcrypto.lib
    ${ARCHIVE_LIBRARIES_DIR}/trueconf/libssl.lib
    ${ARCHIVE_LIBRARIES_DIR}/libxml2.lib
    ${ARCHIVE_LIBRARIES_DIR}/lz4d.lib
    ${ARCHIVE_LIBRARIES_DIR}/lzma.lib
    ${ARCHIVE_LIBRARIES_DIR}/zlibd.lib
    ${ARCHIVE_LIBRARIES_DIR}/zstd.lib
)
target_include_directories(
    ${TARGET_NAME}
    PRIVATE ${ARCHIVE_INCLUDE_DIR}
    PRIVATE "${PROJECT_BINARY_DIR}"
)
#set(ARCHIVE_LIB_DIR ${CMAKE_SOURCE_DIR}/lib/win/archive/x64/Debug
#target_link_directories(${TARGET_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/lib/win/archive/x64/Debug")
target_link_libraries(
    ${TARGET_NAME}
    PRIVATE
    ${ARCHIVE_LIBRARIES}
    crypt32.lib
    Ws2_32.lib
)