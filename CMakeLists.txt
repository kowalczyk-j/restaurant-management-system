cmake_minimum_required(VERSION 3.18)

project(hello VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH /home/kajotello/Qt/6.2.4/gcc_64/lib/cmake)

find_package(Qt6 6.2 COMPONENTS Quick Gui REQUIRED)

qt_add_executable(myapp
    main.cpp
)

target_link_libraries(myapp PRIVATE Qt6::Gui Qt6::Quick)

qt_add_qml_module(myapp
    URI hello
    VERSION 1.0
    QML_FILES
    main.qml
    FramedImage.qml
    RESOURCES
    img/world.png)