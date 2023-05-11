#ifndef ECHIQUIERQT_H
#define ECHIQUIERQT_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>
#include "chessboard-logique.h"

namespace objetsQT {

    class GridPushButton : public QPushButton {
    Q_OBJECT

    public:
        GridPushButton(int coordX, int coordY, QWidget *parent = 0) {
            _coordX = coordX;
            _coordY = coordY;
        };

        int coordinateX() { return _coordX; }

        int coordinateY() { return _coordY; }

    protected:
        int _coordX;
        int _coordY;
    };

    class ChessboardQT : public QWidget {
    Q_OBJECT

    public:
        ChessboardQT(QWidget *parent = nullptr, int gameModeSelect = 1);

        ~ChessboardQT() {};

    private:
        void placeAllPawnsUI(int gameModeSelect);
        QString stylesheetSaved;
        vector<pair<int,int>> vectorToShow;
        QGridLayout *gridLayout;
        GridPushButton *cells[8][8];
        ChessBoardLog board;
        int oldX, oldY, newX, newY;
        bool firstClickDone = false;

    private slots:

        void cellClicked();
    };
}
#endif
