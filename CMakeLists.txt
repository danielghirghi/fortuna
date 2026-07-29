cmake_minimum_required(VERSION 3.16)

project(fortuna VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Sql)

set(TS_FILES fortuna_pt_BR.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(fortuna
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        mainwindow.ui
        categorias/CategoriasWidget.cpp
        categorias/CategoriasWidget.h
        categorias/CategoriasWidget.ui
        categorias/CategoriaWidget.h
        categorias/CategoriaWidget.cpp
        categorias/CategoriaWidget.ui
        categorias/CategoriaConfirmDialog.h
        categorias/CategoriaConfirmDialog.cpp
        categorias/CategoriaConfirmDialog.ui
        contas/ContasWidget.cpp
        contas/ContasWidget.h
        contas/ContasWidget.ui
        contas/ContaWidget.h
        contas/ContaWidget.cpp
        contas/ContaWidget.ui
        tags/TagsWidget.h
        tags/TagsWidget.cpp
        tags/TagsWidget.ui
        tags/TagWidget.h
        tags/TagWidget.cpp
        tags/TagWidget.ui
        tags/TagConfirmDialog.h
        tags/TagConfirmDialog.cpp
        tags/TagConfirmDialog.ui
        movimentacoes/MovimentacoesWidget.ui
        movimentacoes/MovimentacoesWidget.cpp
        movimentacoes/MovimentacoesWidget.h
        movimentacoes/ReceitaWidget.ui
        movimentacoes/ReceitaWidget.cpp
        movimentacoes/ReceitaWidget.h
        movimentacoes/DespesaWidget.ui
        movimentacoes/DespesaWidget.cpp
        movimentacoes/DespesaWidget.h
        movimentacoes/TransferenciaWidget.ui
        movimentacoes/TransferenciaWidget.cpp
        movimentacoes/TransferenciaWidget.h
        movimentacoes/MovimentacaoConfirmDialog.h
        movimentacoes/MovimentacaoConfirmDialog.cpp
        movimentacoes/MovimentacaoConfirmDialog.ui
        database/Database.h
        database/Database.cpp
        models/Conta.h
        repositories/ContasRepository.h
        repositories/ContaRepository.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET fortuna APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(fortuna SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(fortuna
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(fortuna PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.fortuna)
endif()
set_target_properties(fortuna PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS fortuna
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(fortuna)
endif()
