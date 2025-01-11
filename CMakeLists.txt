cmake_minimum_required(VERSION 3.21)

project(ToDo LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.5.3/mingw_64/lib/cmake;${CMAKE_PREFIX_PATH}")

# Find Qt6 Widgets module
find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Enable automatic MOC and RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# Add executable
add_executable(ToDo
        main.cpp
        src/ToDoList.cpp
        src/CustomListWidget.cpp
        src/SettingsDialog.cpp
        src/AboutDialog.cpp
        resources.qrc
)

# Add resource file for Windows only
if(WIN32)
    target_sources(ToDo PRIVATE to_do.rc)
endif()

# Link with Qt6 Widgets
target_link_libraries(ToDo PRIVATE Qt6::Widgets)

# ---------- Installation ----------
install(TARGETS ToDo
        RUNTIME DESTINATION bin
)

# ---------- CPack Configuration ----------
include(InstallRequiredSystemLibraries)

# Read version from version.txt
file(READ "${CMAKE_SOURCE_DIR}/version.txt" VERSION_CONTENTS)
string(STRIP "${VERSION_CONTENTS}" VERSION_NUMBER)

# Get unique build identifier (e.g., from git)
execute_process(
        COMMAND git rev-parse --short HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
)

# Set package version
if(NOT GIT_COMMIT)
    set(GIT_COMMIT "0")
endif()
set(CPACK_PACKAGE_NAME "To-Do List")
set(CPACK_PACKAGE_VERSION "v1.${VERSION_NUMBER}.${GIT_COMMIT}")
set(CPACK_PACKAGE_CONTACT "Ruslan Gomzyakov <ruslan.gomziakov@math.msu.ru>")
set(CPACK_PACKAGE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if(WIN32)
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_DISPLAY_NAME "ToDo Application")
    set(CPACK_NSIS_PACKAGE_NAME "ToDo")
    set(CPACK_NSIS_CONTACT "Your Name <your.email@example.com>")
    set(CPACK_NSIS_MODIFY_PATH ON)
elseif(UNIX)
    set(CPACK_GENERATOR "TGZ")
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-linux")
endif()

include(CPack)

# ---------- Deploy Qt Dependencies ----------
if(WIN32)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt PATHS "${Qt6_DIR}/../../../bin" REQUIRED)

    install(CODE "
        message(STATUS \"Running windeployqt...\")
        execute_process(
            COMMAND \"${WINDEPLOYQT_EXECUTABLE}\" \"\$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/ToDo.exe\"
            RESULT_VARIABLE result
            OUTPUT_VARIABLE output
            ERROR_VARIABLE error_output
        )
        if(NOT result EQUAL 0)
            message(FATAL_ERROR \"Error running windeployqt: \${error_output}\")
        endif()
    ")
elseif(UNIX)
    # Add step to package Qt libraries on Linux
    install(CODE "
        message(STATUS \"Packaging dependencies on Linux...\")
        execute_process(
            COMMAND ${CMAKE_SOURCE_DIR}/package_dependencies.sh ${CMAKE_INSTALL_PREFIX}/bin/ToDo ${CMAKE_INSTALL_PREFIX}/bin/
            RESULT_VARIABLE result
            OUTPUT_VARIABLE output
            ERROR_VARIABLE error_output
        )
        if(NOT result EQUAL 0)
            message(FATAL_ERROR \"Error packaging dependencies: \${error_output}\")
        endif()
    ")
endif()
