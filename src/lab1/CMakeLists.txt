find_package(Qt${QT_VERSION} REQUIRED COMPONENTS Widgets)

add_executable(lab1
    "main.cpp"
    "mainwindow.cpp"
)
target_link_libraries(lab1 PRIVATE Qt${QT_VERSION}::Widgets)