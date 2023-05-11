#include "chessboard-QT.h"
#include <iostream>
#include <memory>

//Place tous les pions sur le chessboard QT
void objetsQT::ChessboardQT::placeAllPawnsUI(int gameModeSelect) {
    QIcon iconRookBlack;
    QIcon iconKingBlack;
    QIcon iconPawnBlack;
    QIcon iconRookWhite;
    QIcon iconKingWhite;
    QIcon iconPawnWhite;
    QIcon iconBlackBishop;
    QIcon iconWhiteBishop;
    QIcon iconWhiteKnight;
    QIcon iconBlackKnight;
    QIcon iconWhiteQueen;
    QIcon iconBlackQueen;
    iconRookBlack.addPixmap(QPixmap("../image_resources/BlackRook.png"),QIcon::Normal,QIcon::On);
    iconKingBlack.addPixmap(QPixmap("../image_resources/BlackKing.png"),QIcon::Normal,QIcon::On);
    iconPawnBlack.addPixmap(QPixmap("../image_resources/BlackPawn.png"),QIcon::Normal,QIcon::On);
    iconRookWhite.addPixmap(QPixmap("../image_resources/WhiteRook.png"),QIcon::Normal,QIcon::On);
    iconKingWhite.addPixmap(QPixmap("../image_resources/WhiteKing.png"),QIcon::Normal,QIcon::On);
    iconPawnWhite.addPixmap(QPixmap("../image_resources/WhitePawn.png"),QIcon::Normal,QIcon::On);
    iconBlackBishop.addPixmap(QPixmap("../image_resources/BlackBishop.png"),QIcon::Normal,QIcon::On);
    iconWhiteBishop.addPixmap(QPixmap("../image_resources/WhiteBishop.png"),QIcon::Normal,QIcon::On);
    iconBlackKnight.addPixmap(QPixmap("../image_resources/BlackKnight.png"),QIcon::Normal,QIcon::On);
    iconWhiteKnight.addPixmap(QPixmap("../image_resources/WhiteKnight.png"),QIcon::Normal,QIcon::On);
    iconBlackQueen.addPixmap(QPixmap("../image_resources/BlackQueen.png"),QIcon::Normal,QIcon::On);
    iconWhiteQueen.addPixmap(QPixmap("../image_resources/WhiteQueen.png"),QIcon::Normal,QIcon::On);

    cells[0][0]->setIcon(iconRookBlack);
    cells[0][0]->setIconSize(QSize(100, 100));
    cells[0][1]->setIcon(iconBlackKnight);
    cells[0][1]->setIconSize(QSize(100, 100));
    cells[0][2]->setIcon(iconBlackBishop);
    cells[0][2]->setIconSize(QSize(100, 100));
    cells[0][3]->setIcon(iconBlackQueen);
    cells[0][3]->setIconSize(QSize(100, 100));
    cells[0][4]->setIcon(iconKingBlack);
    cells[0][4]->setIconSize(QSize(100, 100));
    cells[0][5]->setIcon(iconBlackBishop);
    cells[0][5]->setIconSize(QSize(100, 100));
    cells[0][6]->setIcon(iconBlackKnight);
    cells[0][6]->setIconSize(QSize(100, 100));
    cells[0][7]->setIcon(iconRookBlack);
    cells[0][7]->setIconSize(QSize(100, 100));

    cells[7][0]->setIcon(iconRookWhite);
    cells[7][0]->setIconSize(QSize(100, 100));
    cells[7][1]->setIcon(iconWhiteKnight);
    cells[7][1]->setIconSize(QSize(100, 100));
    cells[7][2]->setIcon(iconWhiteBishop);
    cells[7][2]->setIconSize(QSize(100, 100));
    cells[7][3]->setIcon(iconWhiteQueen);
    cells[7][3]->setIconSize(QSize(100, 100));
    cells[7][4]->setIcon(iconKingWhite);
    cells[7][4]->setIconSize(QSize(100, 100));
    cells[7][5]->setIcon(iconWhiteBishop);
    cells[7][5]->setIconSize(QSize(100, 100));
    cells[7][6]->setIcon(iconWhiteKnight);
    cells[7][6]->setIconSize(QSize(100, 100));
    cells[7][7]->setIcon(iconRookWhite);
    cells[7][7]->setIconSize(QSize(100, 100));

    if(gameModeSelect == 1) {
        for(int i = 0; i < 8; i++) {
            cells[1][i]->setIcon(iconPawnBlack);
            cells[1][i]->setIconSize(QSize(100, 100));
        }
        for(int i = 0; i < 8; i++) {
            cells[6][i]->setIcon(iconPawnWhite);
            cells[6][i]->setIconSize(QSize(100, 100));
        }
    } else if (gameModeSelect == 2) {
        for(int i = 0; i < 8; i++) {
            cells[1][i]->setIcon(iconBlackQueen);
            cells[1][i]->setIconSize(QSize(100, 100));
        }
        for(int i = 0; i < 8; i++) {
            cells[6][i]->setIcon(iconWhiteQueen);
            cells[6][i]->setIconSize(QSize(100, 100));
        }
    }
}

//Crée le chessboard QT
objetsQT::ChessboardQT::ChessboardQT(QWidget *parent, int gameModeSelect) : QWidget(parent)
{
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            cells[row][col] = new GridPushButton(col, row, this);
            cells[row][col]->setFixedSize(100, 100);

            if ((row + col) % 2 == 0)
                cells[row][col]->setStyleSheet("background-color: beige;");
            else
                cells[row][col]->setStyleSheet("background-color: grey;");

            gridLayout->addWidget(cells[row][col], row, col);
            connect(cells[row][col], &GridPushButton::clicked, this, &ChessboardQT::cellClicked);

        }
    }
    board.initializeChessboard(gameModeSelect);
    placeAllPawnsUI(gameModeSelect);
}

//Gère la logique quand on appuie sur une case du chessboard QT
void objetsQT::ChessboardQT::cellClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (clickedButton)
    {
        GridPushButton *clickedButton = qobject_cast<GridPushButton *>(sender());
        if(firstClickDone == false) {
            oldX = clickedButton->coordinateX();
            oldY = clickedButton->coordinateY();

            //Vérifie qu'on a pas cliqué sur une case vide
            if((board.chessboard[oldY][oldX]).get() != nullptr) {
                firstClickDone = true;

                //Affiche la case cliquée en vert & les mouvements possibles en vert
                if(board.getWhitesTurn() == true && (board.chessboard[oldY][oldX])->color_ == Color::WHITE) {
                    stylesheetSaved = cells[oldY][oldX]->styleSheet();
                    cells[oldY][oldX]->setStyleSheet("background-color: green;");
                    board.checkPossibleMovesForUI(oldX, oldY);
                    for(int i = 0; i < board.vectorPossiblePiece.size(); i++) {
                        cells[board.vectorPossiblePiece[i].first][board.vectorPossiblePiece[i].second]->setStyleSheet("background-color: green;");
                    }
                }
                //Affiche la case cliquée en vert & les mouvements possibles en vert
                else if (board.getWhitesTurn() == false && (board.chessboard[oldY][oldX])->color_ == Color::BLACK) {
                    stylesheetSaved = cells[oldY][oldX]->styleSheet();
                    cells[oldY][oldX]->setStyleSheet("background-color: green;");
                    board.checkPossibleMovesForUI(oldX, oldY);
                    for(int i = 0; i < board.vectorPossiblePiece.size(); i++) {
                        cells[board.vectorPossiblePiece[i].first][board.vectorPossiblePiece[i].second]->setStyleSheet("background-color: green;");
                    }
                }
                //Si on clique sur une pièce dont ce n'est pas le tour de jouer, on l'allume en rouge
                else {
                    stylesheetSaved = cells[oldY][oldX]->styleSheet();
                    cells[oldY][oldX]->setStyleSheet("background-color: red;");
                }
            }
        }
        else {
            newX = clickedButton->coordinateX();
            newY = clickedButton->coordinateY();
            if(board.movePiece(oldX, oldY, newX, newY) == true) {
                cells[newY][newX]->setIcon(cells[oldY][oldX]->icon());
                cells[newY][newX]->setIconSize(QSize(100,100));
                cells[oldY][oldX]->setIcon(QIcon());
            }
            //Remettre la couleur originale de la case cliquee en premier
            cells[oldY][oldX]->setStyleSheet(stylesheetSaved);
            firstClickDone = false;

            //Remet le quadrillage par défaut
            for (int row = 0; row < 8; ++row){
                for (int col = 0; col < 8; ++col){
                    if ((row + col) % 2 == 0)
                        cells[row][col]->setStyleSheet("background-color: beige;");
                    else
                        cells[row][col]->setStyleSheet("background-color: grey;");
                }
            }

            //Affiche les rois en rouge si ils sont en échec
            if(board.whiteIsChecked) {
                cells[board.whiteKingPos.first][board.whiteKingPos.second]->setStyleSheet("background-color: red;");
            }
            if(board.blackIsChecked) {
                cells[board.blackKingPos.first][board.blackKingPos.second]->setStyleSheet("background-color: red;");
            }
        }
    }
}
