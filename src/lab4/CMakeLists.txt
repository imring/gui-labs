find_package(Qt${QT_VERSION} REQUIRED COMPONENTS Widgets Qml Quick)

add_executable(lab4
    "main.cpp"
)
target_link_libraries(lab4 PRIVATE Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::Qml Qt${QT_VERSION}::Quick)