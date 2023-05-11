#include <QObject>
#include "Modele.h"
#include <memory>
#ifndef PROJET_ECHEC_CHESSBOARD_LOGIQUE_H
#define PROJET_ECHEC_CHESSBOARD_LOGIQUE_H

class ChessBoardLog: public QObject {
public:
    ChessBoardLog(){};
    void initializeChessboard(int gameMode);
    bool movePiece(int oldX, int oldY, int newX, int newY);
    bool isPathClear(int oldX, int oldY, int newX, int newY);
    void killPiece(int actualX, int actualY);
    void checkForCheck();
    void checkPossibleMovesForUI(int oldX, int oldY);
    pieceLogic::unique_ptr<pieceLogic::Piece> chessboard [8][8];
    bool getWhitesTurn();
    bool whiteIsChecked = false;
    bool blackIsChecked = false;
    vector<pair<int, int>> vectorForCheck;
    vector<pair<int, int>> vectorPossiblePiece;
    pair<int, int> whiteKingPos;
    pair<int, int> blackKingPos;
private:
    pieceLogic::unique_ptr<pieceLogic::Piece> backupPiece;
    int backupX;
    int backupY;
    bool whitesTurn = true;
    void turnLogicWhenChecked(int oldX, int oldY, int newX, int newY);
    void turnLogicNormal(int oldX, int oldY, int newX, int newY);
    void printWhenMoveIsDone(int oldX, int oldY, int newX, int newY);
    bool checkIfMoveEndangersOwnKing(int oldX, int oldY, int newX, int newY);
    bool moveDoneIndicatorForUi;
};

#endif
