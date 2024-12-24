cmake_minimum_required(VERSION 3.21)

project(ToDo LANGUAGES CXX)

# Установить стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.5.3/mingw_64/lib/cmake;${CMAKE_PREFIX_PATH}")

# Найти модуль Qt6 Widgets
find_package(Qt6 REQUIRED COMPONENTS Widgets)


# Автоматическая генерация MOC и RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Добавить исполняемый файл
add_executable(ToDo
        main.cpp
        ToDoList.cpp
        resources.qrc
)

# Добавить ресурсный файл только для Windows
if(WIN32)
    target_sources(ToDo PRIVATE to_do.rc)
endif()

# Линковка с Qt6 Widgets
target_link_libraries(ToDo PRIVATE Qt6::Widgets)

# ---------- Установка ----------
install(TARGETS ToDo
        RUNTIME DESTINATION bin
)

# ---------- Конфигурация CPack ----------
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "ToDo")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_CONTACT "Your Name <your.email@example.com>")
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

# ---------- Развертывание зависимостей Qt ----------
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
    # Добавить шаг для упаковки библиотек Qt на Linux
    install(CODE "
        message(STATUS \"Packaging dependencies on Linux...\")
        execute_process(
            COMMAND ldd ${CMAKE_INSTALL_PREFIX}/bin/ToDo | grep Qt | awk '{print \$3}' | xargs -I '{}' cp '{}' ${CMAKE_INSTALL_PREFIX}/bin/
            RESULT_VARIABLE result
            OUTPUT_VARIABLE output
            ERROR_VARIABLE error_output
        )
        if(NOT result EQUAL 0)
            message(FATAL_ERROR \"Error packaging dependencies: \${error_output}\")
        endif()
    ")
endif()

