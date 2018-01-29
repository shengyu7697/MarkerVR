add_executable(marker_detector
    main.cpp
)

target_include_directories(marker_detector PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(marker_detector ${OpenCV_LIBS})