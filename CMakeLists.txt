project(QvPlugin-SS)
cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include(CTest)

option(QVPLUGIN_USE_QT6 "Use Qt6")
if(QVPLUGIN_USE_QT6)
    set(QV_QT_LIBNAME Qt6)
else()
    set(QV_QT_LIBNAME Qt5)
endif()
find_package(${QV_QT_LIBNAME} COMPONENTS Core Widgets Gui Network REQUIRED)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
include(cmake/shadowsocks-uvw.cmake)
set(QVPLUGIN_INTERFACE_INCLUDE_DIR "interface/")
set(QVPLUGIN_HAS_HTTP_TO_SOCKS_HELPER ON)
include(interface/QvPluginInterface.cmake)
include(interface/QvGUIPluginInterface.cmake)
include_directories(${QVPLUGIN_INTERFACE_INCLUDE_DIR})

add_library(${PROJECT_NAME} MODULE
    SSPlugin.hpp
    SSPlugin.cpp
    common/CommonHelpers.cpp
    common/CommonHelpers.hpp
    core/Serializer.cpp
    core/Serializer.hpp
    core/EventHandler.cpp
    core/EventHandler.hpp
    core/kernel/SSInstance.cpp
    core/kernel/SSInstance.hpp
    ui/SSOutboundEditor.cpp
    ui/SSOutboundEditor.hpp
    ui/SSOutboundEditor.ui
    ui/SSSettingsWidget.ui
    ui/SSSettingsWidget.cpp
    ui/SSSettingsWidget.hpp
    ui/GUIInterface.hpp
    resx.qrc
    ${QVPLUGIN_INTERFACE_HEADERS}
    ${QVGUIPLUGIN_INTERFACE_HEADERS})

if(APPLE)
    add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_INSTALL_NAME_TOOL} -add_rpath "@executable_path/../Frameworks/" $<TARGET_FILE:${PROJECT_NAME}>)
endif()

target_link_libraries(${PROJECT_NAME}
    ${QV_QT_LIBNAME}::Core
    ${QV_QT_LIBNAME}::Gui
    ${QV_QT_LIBNAME}::Widgets
    ${QV_QT_LIBNAME}::Network
    ${SHADOWSOCKS_UVW_LIBRARY})

install(TARGETS ${PROJECT_NAME} DESTINATION share/qv2ray/plugins)
if(BUILD_TESTING)
    add_executable(testparsess test/TestParseSS.cpp test/catch.hpp
        common/CommonHelpers.cpp
        common/CommonHelpers.hpp
        core/Serializer.cpp
        core/Serializer.hpp
        ${QVPLUGIN_INTERFACE_HEADERS})
    target_link_libraries(testparsess
        ${QV_QT_LIBNAME}::Core
        ${QV_QT_LIBNAME}::Gui
        ${QV_QT_LIBNAME}::Widgets
        ${QV_QT_LIBNAME}::Network)
    add_test(NAME testparsess COMMAND $<TARGET_FILE:testparsess>)
endif()
