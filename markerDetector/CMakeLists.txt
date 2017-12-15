add_executable(markerDetector
    main.cpp
)

target_include_directories(markerDetector PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(markerDetector ${OpenCV_LIBS})