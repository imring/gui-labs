find_package(Qt${QT_VERSION} REQUIRED COMPONENTS Widgets)

add_executable(idz
    "main.cpp"
    "mainwindow.cpp"
)
target_link_libraries(idz PRIVATE Qt${QT_VERSION}::Widgets)
target_compile_definitions(idz PRIVATE QT_NO_PRINTER)