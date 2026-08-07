cmake_minimum_required(VERSION 3.16)

project(fortuna VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Sql)
find_package(SQLite3 REQUIRED)

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

        widgets/categorias/CategoriasWidget.cpp
        widgets/categorias/CategoriasWidget.h
        widgets/categorias/CategoriasWidget.ui
        dialogs/categorias/CategoriaWidget.h
        dialogs/categorias/CategoriaWidget.cpp
        dialogs/categorias/CategoriaWidget.ui
        models/Categoria.h
        repositories/CategoriasRepository.h
        repositories/CategoriasRepository.cpp

        widgets/contas/ContasWidget.cpp
        widgets/contas/ContasWidget.h
        widgets/contas/ContasWidget.ui
        dialogs/contas/ContaWidget.h
        dialogs/contas/ContaWidget.cpp
        dialogs/contas/ContaWidget.ui
        models/Conta.h
        repositories/ContasRepository.h
        repositories/ContasRepository.cpp

        widgets/tags/TagsWidget.h
        widgets/tags/TagsWidget.cpp
        widgets/tags/TagsWidget.ui
        dialogs/tags/TagWidget.h
        dialogs/tags/TagWidget.cpp
        dialogs/tags/TagWidget.ui
        models/Tag.h
        repositories/TagsRepository.h
        repositories/TagsRepository.cpp

        widgets/movimentacoes/MovimentacoesWidget.ui
        widgets/movimentacoes/MovimentacoesWidget.cpp
        widgets/movimentacoes/MovimentacoesWidget.h
        dialogs/movimentacoes/MovimentacaoWidget.ui
        dialogs/movimentacoes/MovimentacaoWidget.cpp
        dialogs/movimentacoes/MovimentacaoWidget.h
        models/Movimentacao.h

        repositories/MovimentacoesRepository.h
        repositories/MovimentacoesRepository.cpp

        resources.qrc
        models/Format.h

        widgets/BaseWidget.h

        core/config/configmanager.h
        core/config/configmanager.cpp
        core/database/Database.h
        core/database/Database.cpp

        config/localsettings.example.json
        config/localsettings.json
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

target_link_libraries(fortuna PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt6::Sql
    SQLite::SQLite3
)

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
