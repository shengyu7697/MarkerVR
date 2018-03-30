set(FILES
    main.cpp
    MarkerManager.h
    MarkerManager.cpp
    MarkerTacker.h
    MarkerTacker.cpp
    Quaternion.h
    Quaternion.cpp
    RotationUtil.cpp
    SocketPoseClient.cpp
    ../../thirdparty/TinyTcp/src/TinyTcp/TinyTcpClient.cpp
    ../../thirdparty/TinyTcp/src/TinyTcp/SocketUtil.cpp
)

if(USE_PROTOBUF)
    find_package(Protobuf REQUIRED)
    PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS pose.proto)
    list(APPEND FILES ${PROTO_SRCS})
endif()

add_executable(marker_vr ${FILES})

if(USE_PROTOBUF)
target_include_directories(marker_vr PUBLIC ${OpenCV_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/TinyTcp/src/TinyTcp" ${PROTOBUF_INCLUDE_DIRS})
target_link_libraries(marker_vr pthread ${OpenCV_LIBS} ${PROTOBUF_LIBRARIES})
else()
target_include_directories(marker_vr PUBLIC ${OpenCV_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdparty/TinyTcp/src/TinyTcp")
target_link_libraries(marker_vr pthread ${OpenCV_LIBS})
endif()