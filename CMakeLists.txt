cmake_minimum_required(VERSION 3.24)
project(Projet_Echec)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#Si le CMake pour QT n'est pas dans le PATH, il est possible de hardcode le directory avec la ligne commentée ci-dessous
#set(CMAKE_PREFIX_PATH "/opt/Qt/6.5.0/gcc_64/lib/cmake")
find_package(QT NAMES Qt5 REQUIRED Widgets)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Projet main.cpp Modele.cpp Modele.h chessboard-QT.cpp chessboard-QT.h chessboard-logique.cpp chessboard-logique.h mainmenu.cpp mainmenu.h)

target_link_libraries(Projet
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

include_directories(include image_resources)
add_subdirectory(Google_tests)