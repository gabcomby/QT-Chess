#include "../Modele.h"
#include "../chessboard-logique.h"
#include <memory>
#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

// Ces tests verifient les mouvements basiques de chaque pièce
TEST(Piece, basicPieceMovementTest){
    pieceLogic::Pawn pawn(Color::BLACK, 1, 1);
    //Vérifie que l'on peut avancer de 2 au premier coup
    EXPECT_EQ(pawn.moveIsValid(1, 3), true);
    //Vérifie que l'on ne peut plus avancer de 2 par la suite
    EXPECT_EQ(pawn.moveIsValid(1,3), false);
    //Vérifie quelques mouvements possibles du Pawn (y compris les diagonales directes de 1)
    EXPECT_EQ(pawn.moveIsValid(1,2), true);
    EXPECT_EQ(pawn.moveIsValid(2,2), true);
    EXPECT_EQ(pawn.moveIsValid(0,2), true);
    //Vérifie quelques exemples de mouvements non-valides
    EXPECT_EQ(pawn.moveIsValid(5,5), false);

    pieceLogic::King king(Color::BLACK, 5, 5);
    //Vérifie tous les mouvements possibles du King
    EXPECT_EQ(king.moveIsValid(4,5), true);
    EXPECT_EQ(king.moveIsValid(6,5), true);
    EXPECT_EQ(king.moveIsValid(5,4), true);
    EXPECT_EQ(king.moveIsValid(5,6), true);
    EXPECT_EQ(king.moveIsValid(6,6), true);
    EXPECT_EQ(king.moveIsValid(4,4), true);
    EXPECT_EQ(king.moveIsValid(6,4), true);
    EXPECT_EQ(king.moveIsValid(4,6), true);
    //Vérifie quelques exemples de mouvements non-valides
    EXPECT_EQ(king.moveIsValid(3,5), false);
    EXPECT_EQ(king.moveIsValid(6,8), false);
    EXPECT_EQ(king.moveIsValid(1,3), false);
    EXPECT_EQ(king.moveIsValid(1,1), false);
    EXPECT_EQ(king.moveIsValid(7,4), false);

    pieceLogic::Rook rook(Color::BLACK, 0, 0);
    //Vérifie tous les mouvements possibles du Rook
    EXPECT_EQ(rook.moveIsValid(0,2), true);
    EXPECT_EQ(rook.moveIsValid(0,5), true);
    EXPECT_EQ(rook.moveIsValid(0,7), true);
    EXPECT_EQ(rook.moveIsValid(2,0), true);
    EXPECT_EQ(rook.moveIsValid(5,0), true);
    EXPECT_EQ(rook.moveIsValid(7,0), true);
    //Vérifie quelques exemples de mouvements non-valides
    EXPECT_EQ(rook.moveIsValid(3,1), false);
    EXPECT_EQ(rook.moveIsValid(1,6), false);
    EXPECT_EQ(rook.moveIsValid(3,3), false);

    pieceLogic::Bishop bishop(Color::BLACK, 4, 3);
    //Vérifie tous les mouvements possibles du Bishop
    EXPECT_EQ(bishop.moveIsValid(3,2), true);
    EXPECT_EQ(bishop.moveIsValid(5,2), true);
    EXPECT_EQ(bishop.moveIsValid(3,4), true);
    EXPECT_EQ(bishop.moveIsValid(5,4), true);
    //Vérifie quelques exemples de mouvements non-valides
    EXPECT_EQ(bishop.moveIsValid(2,2), false);
    EXPECT_EQ(bishop.moveIsValid(7,3), false);
    EXPECT_EQ(bishop.moveIsValid(3,3), false);
    EXPECT_EQ(bishop.moveIsValid(4,1), false);

    pieceLogic::Knight knight(Color::BLACK, 4, 4);
    //Vérifie tous les mouvements possibles du Knight
    EXPECT_EQ(knight.moveIsValid(2,3), true);
    EXPECT_EQ(knight.moveIsValid(2,5), true);
    EXPECT_EQ(knight.moveIsValid(6,3), true);
    EXPECT_EQ(knight.moveIsValid(6,5), true);
    EXPECT_EQ(knight.moveIsValid(3,2), true);
    EXPECT_EQ(knight.moveIsValid(5,2), true);
    EXPECT_EQ(knight.moveIsValid(3,6), true);
    EXPECT_EQ(knight.moveIsValid(5,6), true);
    //Vérifie quelques exemples de mouvements non-valides
    EXPECT_EQ(knight.moveIsValid(4,5), false);
    EXPECT_EQ(knight.moveIsValid(4,6), false);
    EXPECT_EQ(knight.moveIsValid(1,2), false);

    pieceLogic::Queen queen(Color::BLACK, 4, 4);
    //Vérifie tous les mouvements diagonaux de la Queen
    EXPECT_EQ(queen.moveIsValid(6,6), true);
    EXPECT_EQ(queen.moveIsValid(2,2), true);
    EXPECT_EQ(queen.moveIsValid(6,2), true);
    EXPECT_EQ(queen.moveIsValid(2,6), true);
    //Vérifie les mouvements en ligne droite de la Queen
    EXPECT_EQ(queen.moveIsValid(6,4), true);
    EXPECT_EQ(queen.moveIsValid(2,4), true);
    EXPECT_EQ(queen.moveIsValid(4,6), true);
    EXPECT_EQ(queen.moveIsValid(4,2), true);
    //Vérifie quelques exemples de mouvement non-valides
    EXPECT_EQ(queen.moveIsValid(5,7), false);
    EXPECT_EQ(queen.moveIsValid(1,3), false);
    EXPECT_EQ(queen.moveIsValid(2,7), false);
    EXPECT_EQ(queen.moveIsValid(3,2), false);
}

// Ces tests verifie si le board est bien initalisé dans le 1e mode, en vérifiant qu'il y'a des pointeurs de pièces sur les cases
TEST(ChessBoard, chessboardInitializeMode1){
    ChessBoardLog chessboard;
    chessboard.initializeChessboard(1);
    auto piece = dynamic_cast<pieceLogic::Rook*>(chessboard.chessboard[0][0].get());
    ASSERT_NE(piece, nullptr);
    auto piece2 = dynamic_cast<pieceLogic::Rook*>(chessboard.chessboard[7][7].get());
    ASSERT_NE(piece2, nullptr);
}

// Ces tests verifie si le board est bien initalisé dans le 2e mode, en vérifiant qu'il y'a des pointeurs de pièces sur les cases
TEST(ChessBoard, chessboardInitializeMode2){
    ChessBoardLog chessboard;
    chessboard.initializeChessboard(2);
    auto piece = dynamic_cast<pieceLogic::Queen*>(chessboard.chessboard[1][1].get());
    ASSERT_NE(piece, nullptr);
}

// Ce test vérifie que c'est bien le tour des blancs
TEST(ChessBoard, chessboardWhitesTurn){
    ChessBoardLog chessboard;
    chessboard.initializeChessboard(1);
    EXPECT_EQ(chessboard.getWhitesTurn(), true);
}

// Ces tests vérifient que les mouvements sont faisables ou non
TEST(ChessBoard, chessboardMovePiece){
    ChessBoardLog chessboard;
    chessboard.initializeChessboard(1);
    EXPECT_EQ(chessboard.movePiece(1,6,1,5), true);
    EXPECT_EQ(chessboard.movePiece(1,1,1,2), true);
    EXPECT_EQ(chessboard.movePiece(1,7,2,5), true);
    EXPECT_EQ(chessboard.movePiece(6,7,3,6), false);
}

// Ces tests verifient que la fonction isPathClear fonctionne
TEST(ChessBoard, chessboardPathClear){
    ChessBoardLog chessboard;
    chessboard.initializeChessboard(1);
    EXPECT_EQ(chessboard.isPathClear(7,7,7,3), false);
    EXPECT_EQ(chessboard.isPathClear(7,6,7,4), true);
    EXPECT_EQ(chessboard.isPathClear(2,7,4,5), false);
    EXPECT_EQ(chessboard.isPathClear(1,1,1,2), true);
}

TEST(ChessBoard, chessboardKillPiece){
    ChessBoardLog chessboard;
    chessboard.initializeChessboard(1);
    chessboard.killPiece(1,1);
    auto killedPiece = chessboard.chessboard[1][1].get();
    ASSERT_EQ(killedPiece, nullptr);
    chessboard.killPiece(6,1);
    auto killedPiece2 = chessboard.chessboard[1][6].get();
    ASSERT_EQ(killedPiece2, nullptr);
}

TEST(ChessBoard, chessboardCheckForCheck){
    ChessBoardLog chessboard;
    chessboard.initializeChessboard(1);
    chessboard.checkForCheck();
    ASSERT_EQ(chessboard.whiteIsChecked, false);
    chessboard.movePiece(4,6,4,4);
    chessboard.movePiece(5,1,5,2);
    chessboard.movePiece(3,7,7,3);
    chessboard.checkForCheck();
    ASSERT_EQ(chessboard.blackIsChecked, true);
}

TEST(ChessBoardLog, CheckPossibleMovesForUIContainsCoordinate) {
    ChessBoardLog chessboard;
    chessboard.initializeChessboard(1);
    pair<int, int> expectedCoordinates = make_pair(5, 0);
    chessboard.checkPossibleMovesForUI(0, 6);
    bool found = false;
    for (const auto &coord : chessboard.vectorPossiblePiece) {
        if (coord == expectedCoordinates) {
            found = true;
            break;
        }
    }
    ASSERT_TRUE(found);
}
#endif

