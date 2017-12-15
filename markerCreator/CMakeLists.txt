add_executable(markerCreator
    main.cpp
)

target_include_directories(markerCreator PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(markerCreator ${OpenCV_LIBS})