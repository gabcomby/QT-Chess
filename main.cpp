#include <QApplication>
#include <QMainWindow>
#include "chessboard-QT.h"
#include "mainmenu.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Montre la fenêtre de sélection du mode de jeu
    GameModeSelectWindow gameModeWindow;
    int result = gameModeWindow.exec();

    //Si l'utilisateur appuie sur "Jouer"
    if (result == QDialog::Accepted) {
        int selectedGameMode = gameModeWindow.getSelectedGameMode();

        //Démarre le jeu d'échec
        QMainWindow mainWindow;
        objetsQT::ChessboardQT *chessBoard = new objetsQT::ChessboardQT(&mainWindow, selectedGameMode);
        mainWindow.setCentralWidget(chessBoard);
        mainWindow.setWindowTitle("Echiquier");
        mainWindow.setFixedSize(chessBoard->sizeHint());

        mainWindow.show();

        return app.exec();
    } else {
        //Quitte le programme si la fenêtre de sélection de mode a été fermée
        return 0;
    }
}