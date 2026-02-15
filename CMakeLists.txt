cmake_minimum_required(VERSION 3.19)
project(Electite LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_standard_project_setup()

qt_add_executable(Electite
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Electite.hpp Electite.cpp
    DataBreakInfoModel.hpp DataBreakInfoModel.cpp
    ElectiteViewModel.hpp ElectiteViewModel.cpp
)

target_include_directories(Electite
    PRIVATE
        D:/msys64/mingw64/User/Include
)

target_link_directories(Electite
    PRIVATE
        D:/msys64/mingw64/User/Lib
)

target_link_libraries(Electite
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
        IO
        Network
)

include(GNUInstallDirs)

install(TARGETS Electite
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Electite
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
