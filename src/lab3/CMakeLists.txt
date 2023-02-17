find_package(Qt${QT_VERSION} REQUIRED COMPONENTS Widgets)

add_executable(lab3
    "main.cpp"
    "mainwindow.cpp"
    "qcustomplot.cpp"
)
target_link_libraries(lab3 PRIVATE Qt${QT_VERSION}::Widgets)
target_compile_definitions(lab3 PRIVATE QT_NO_PRINTER)