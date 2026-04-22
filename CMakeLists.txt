cmake_minimum_required(VERSION 3.19)
project(vs_code_qt LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

# add_executable(my_app main.cpp)


qt_standard_project_setup()

qt_add_executable(vs_code_qt
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    Paint/painter.cpp
    Paint/painter.h
    Paint/images/pingvin.png
    encryption/encrypt.cpp
    encryption/func.hpp
    mainwindow.ui
)

target_link_libraries(vs_code_qt
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS vs_code_qt
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET vs_code_qt
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})