add_executable(markers_object_pose_estimation
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

target_include_directories(markers_object_pose_estimation PUBLIC ${OpenCV_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/../TinyTcp")
target_link_libraries(markers_object_pose_estimation pthread ${OpenCV_LIBS})