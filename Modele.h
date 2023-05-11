#include <iostream>
#include <utility>
#include <memory>
#include <vector>

#ifndef PROJET_ECHEC_MODÈLE_H
#define PROJET_ECHEC_MODÈLE_H
using namespace std;

enum Direction {
    VERTICAL,
    HORIZONTAL,
    DIAGONAL
};

enum Color {
    WHITE,
    BLACK
};

namespace pieceLogic {
    using namespace std;

    class Piece {
    public :
        Piece() = default;

        Piece(Color couleur, int firstX, int firstY) : color_(couleur), actualX(firstX), actualY(firstY) {}

        virtual ~Piece() = default;

        virtual bool moveIsValid(int newX, int newY) = 0;

        virtual vector<pair<int, int>> calculatePossibleAttackPositions() = 0;

        Color color_;
        int actualX = 0;
        int actualY = 0;

    };

    class Pawn : public Piece {
    public:
        Pawn() = default;

        Pawn(Color couleur, int firstX, int firstY) : Piece(couleur, firstX, firstY) {}

        ~Pawn() = default;

        bool moveIsValid(int newX, int newY) override;

        vector<pair<int, int>> calculatePossibleAttackPositions() override;

        vector<pair<int, int>> calculatePossiblePositionsForUI();

    protected:
        bool isFirstMove_ = true;
    };

    class King : public Piece {
    public:
        King() = default;

        King(Color couleur, int firstX, int firstY) : Piece(couleur, firstX, firstY) {}

        ~King() = default;

        bool moveIsValid(int newX, int newY) override;

        vector<pair<int, int>> calculatePossibleAttackPositions() override;

    protected:
        bool enEchec = false;

    };

    class Rook : public Piece {
    public:
        Rook() = default;

        Rook(Color couleur, int firstX, int firstY) : Piece(couleur, firstX, firstY) {}

        ~Rook() = default;

        bool moveIsValid(int newX, int newY) override;

        vector<pair<int, int>> calculatePossibleAttackPositions() override;
    };

    class Bishop : public Piece {
    public:
        Bishop() = default;

        Bishop(Color couleur, int firstX, int firstY) : Piece(couleur, firstX, firstY) {}

        ~Bishop() = default;

        bool moveIsValid(int newX, int newY) override;

        vector<pair<int, int>> calculatePossibleAttackPositions() override;
    };

    class Knight : public Piece {
    public:
        Knight() = default;

        Knight(Color couleur, int firstX, int firstY) : Piece(couleur, firstX, firstY) {}

        ~Knight() = default;

        bool moveIsValid(int newX, int newY) override;

        vector<pair<int, int>> calculatePossibleAttackPositions() override;
    };

    class Queen : public Piece {
    public:
        Queen() = default;

        Queen(Color couleur, int firstX, int firstY) : Piece(couleur, firstX, firstY) {}

        ~Queen() = default;

        bool moveIsValid(int newX, int newY) override;

        vector<pair<int, int>> calculatePossibleAttackPositions() override;
    };

}

class PieceTemporaire {
public:
    PieceTemporaire(unique_ptr<pieceLogic::Piece> tempPiece,
                    unique_ptr<pieceLogic::Piece> (&echiquier)[8][8],
                    int newX, int newY)
            : echiquier_(echiquier), newX_(newX), newY_(newY),
              pieceInitiale_(move(echiquier_[newX][newY])) {
        echiquier_[newX][newY] = move(tempPiece);
    }

    ~PieceTemporaire() {
        echiquier_[newX_][newY_] = move(pieceInitiale_);
    }

private:
    unique_ptr<pieceLogic::Piece> (&echiquier_)[8][8];
    int newX_;
    int newY_;
    unique_ptr<pieceLogic::Piece> pieceInitiale_;
};

#endif