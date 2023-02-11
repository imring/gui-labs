find_package(Qt${QT_VERSION} REQUIRED COMPONENTS Widgets)

add_executable(lab2
    "main.cpp"
    "mainwindow.cpp"
)
target_link_libraries(lab2 PRIVATE Qt${QT_VERSION}::Widgets)