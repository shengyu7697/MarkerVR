add_executable(marker_creator
    main.cpp
)

target_include_directories(marker_creator PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(marker_creator ${OpenCV_LIBS})