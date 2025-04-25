cmake_minimum_required(VERSION 3.29)
project(dsna_3_qt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/path/to/cmake")
set(MACOSX_BUNDLE_ICON_FILE llk.icns)

set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/resources/llk.icns"
        BasicModeWIndow.cpp
        BasicModeWindow.h
        BasicModeWindow.ui
        GlobalData.cpp
        GlobalData.h
        utils.cpp
        utils.h
        Fruit.cpp
        Fruit.h
        Game.h
        TimerText.cpp
        TimerText.h
        Game.cpp
        test.cpp
        test.h
        FruitGenerator.cpp
        FruitGenerator.h
        RecordManager.cpp
        RecordManager.h
        scoreboardwindow.cpp
        scoreboardwindow.h
        scoreboardwindow.ui
)
set_source_files_properties(${app_icon_macos} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(dsna_3_qt MACOSX_BUNDLE main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui ${app_icon_macos})

target_link_libraries(dsna_3_qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

