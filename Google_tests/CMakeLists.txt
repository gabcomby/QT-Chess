# 'Google_test' is the subproject name
project(Google_tests)

find_package(QT NAMES Qt5 REQUIRED Widgets)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run modele_test.cpp ../Modele.cpp ../chessboard-logique.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main Qt::Core Qt::Gui Qt::Widgets)