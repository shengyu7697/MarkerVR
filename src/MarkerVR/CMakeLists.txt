add_executable(marker_vr
    main.cpp
    MarkerManager.h
    MarkerManager.cpp
    MarkerTacker.h
    MarkerTacker.cpp
    Quaternion.h
    Quaternion.cpp
    RotationUtil.cpp
    SocketPoseClient.cpp
    ../TinyTcp/TinyTcpClient.cpp
    ../TinyTcp/SocketUtil.cpp
)

target_include_directories(marker_vr PUBLIC ${OpenCV_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/../TinyTcp")
target_link_libraries(marker_vr pthread ${OpenCV_LIBS})