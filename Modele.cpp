#include "Modele.h"
#include "chessboard-logique.h"

//Pour chaque pièce: moveIsValid vérifie que le mouvement entre sa position actuelle et sa position future PEUT-ÊTRE
//effectué selon les déplacements spécifiques à chaque pièce

//Pour chaque pièce: calculatePossibleAttackPositions calcule toutes les cases vers lesquelles peuvent se déplacer
//une pièce depuis leur position actuelle (et aussi celles qu'elles peuvent attaquer)
//NOTE: Pour le pion, cela calcule les diagonales directes, puisqu'il s'agit des cases qu'il peut attaquer!

//Pour le Pawn: calculatePossiblePositionsForUI calcule les cases vers lesquelles peut se déplacer un pion (donc uniquement
//celles en ligne droite)

namespace pieceLogic {

    bool Pawn::moveIsValid(int newX, int newY) {
        if (color_ == Color::BLACK) {
            if ((newX == actualX + 1 || newX == actualX - 1) && newY == actualY + 1)
                return true;
            if (newX != actualX)
                return false;
            if (isFirstMove_ == true) {
                if ((newY > actualY) && (newY <= actualY + 2)) {
                    isFirstMove_ = false;
                    return true;
                } else
                    return false;
            } else {
                if (newY == actualY + 1)
                    return true;
                else
                    return false;
            }
        } else {
            if ((newX == actualX + 1 || newX == actualX - 1) && newY == actualY - 1)
                return true;
            if (newX != actualX)
                return false;
            if (isFirstMove_ == true) {
                if ((newY < actualY) && (newY >= actualY - 2)) {
                    isFirstMove_ = false;
                    return true;
                } else
                    return false;
            } else {
                if (newY == actualY - 1)
                    return true;
                else
                    return false;
            }
        }
    }

    vector<pair<int, int>> Pawn::calculatePossibleAttackPositions() {
        vector<pair<int, int>> possibleAttackPositions;
        if (color_ == Color::BLACK) {
            possibleAttackPositions.emplace_back(actualY + 1, actualX - 1);
            possibleAttackPositions.emplace_back(actualY + 1, actualX + 1);
        } else {
            possibleAttackPositions.emplace_back(actualY - 1, actualX - 1);
            possibleAttackPositions.emplace_back(actualY - 1, actualX + 1);
        }
        return possibleAttackPositions;
    }

    vector<pair<int, int>> Pawn::calculatePossiblePositionsForUI() {
        vector<pair<int, int>> possibleMovePositions;
        if(color_ == Color::BLACK) {
            if (isFirstMove_ == true){
                possibleMovePositions.emplace_back(actualY + 1, actualX);
                possibleMovePositions.emplace_back(actualY + 2, actualX);
            }else {
                possibleMovePositions.emplace_back(actualY + 1, actualX);
            }
        } else {
            if (isFirstMove_ == true){
                possibleMovePositions.emplace_back(actualY - 1, actualX);
                possibleMovePositions.emplace_back(actualY - 2, actualX);
            }else {
                possibleMovePositions.emplace_back(actualY - 1, actualX);
            }
        }
        return possibleMovePositions;
    }

    bool King::moveIsValid(int newX, int newY) {
        if ((newX >= actualX - 1) && (newX <= actualX + 1)) {
            if ((newY >= actualY - 1) && (newY <= actualY + 1)) {
                return true;
            } else { return false; }
        } else { return false; }
    }

    vector<pair<int, int>> King::calculatePossibleAttackPositions() {
        vector<pair<int, int>> possibleAttackPositions;
        bool checkRight = (actualX + 1) <= 7;
        bool checkLeft = (actualX - 1) >= 0;
        bool checkTop = (actualY - 1) >= 0;
        bool checkBottom = (actualY + 1) <= 7;
        if(checkRight) {
            possibleAttackPositions.emplace_back(actualY, actualX + 1);
            if(checkBottom)
                possibleAttackPositions.emplace_back(actualY + 1, actualX + 1);
            if(checkTop)
                possibleAttackPositions.emplace_back(actualY - 1, actualX + 1);
        }

        if(checkLeft) {
            possibleAttackPositions.emplace_back(actualY, actualX - 1);
            if(checkBottom)
                possibleAttackPositions.emplace_back(actualY + 1, actualX - 1);
            if(checkTop)
                possibleAttackPositions.emplace_back(actualY - 1, actualX - 1);
        }

        if(checkTop) {
            possibleAttackPositions.emplace_back(actualY - 1, actualX);
            if(checkRight)
                possibleAttackPositions.emplace_back(actualY - 1, actualX + 1);
            if(checkLeft)
                possibleAttackPositions.emplace_back(actualY - 1, actualX - 1);
        }

        if(checkBottom) {
            possibleAttackPositions.emplace_back(actualY + 1, actualX);
            if(checkRight)
                possibleAttackPositions.emplace_back(actualY + 1, actualX + 1);
            if(checkLeft)
                possibleAttackPositions.emplace_back(actualY + 1, actualX - 1);
        }

        return possibleAttackPositions;
    }

    bool Rook::moveIsValid(int newX, int newY) {
        if ((newY == actualY) || (newX == actualX))
            return true;
        else
            return false;
    }

    vector<pair<int, int>> Rook::calculatePossibleAttackPositions() {
        vector<pair<int, int>> possibleAttackPositions;
        //Toutes les positions possibles dans sa rangée sauf la sienne
        for(int i = 0; i < 8; i++) {
            if(i != actualX) {
                possibleAttackPositions.emplace_back(actualY, i);
            }
        }
        //Toutes les positions possibles dans une colonne sauf la sienne
        for(int i = 0; i < 8; i++) {
            if(i != actualY) {
                possibleAttackPositions.emplace_back(i, actualX);
            }
        }

        return possibleAttackPositions;
    }

    bool Bishop::moveIsValid(int newX, int newY) {
        if (abs(newY - actualY) == abs(newX - actualX)) {
            return true;
        } else
            return false;
    }

    vector<pair<int, int>> Bishop::calculatePossibleAttackPositions() {
        vector<pair<int, int>> possibleAttackPositions;
        // Top-left and bottom-right diagonals
        for (int i = actualX - 1, j = actualY - 1; i >= 0 && j >= 0; --i, --j) {
            possibleAttackPositions.emplace_back(j, i);
        }
        for (int i = actualX + 1, j = actualY + 1; i < 8 && j < 8; ++i, ++j) {
            possibleAttackPositions.emplace_back(j, i);
        }

        // Top-right and bottom-left diagonals
        for (int i = actualX - 1, j = actualY + 1; i >= 0 && j < 8; --i, ++j) {
            possibleAttackPositions.emplace_back(j, i);
        }
        for (int i = actualX + 1, j = actualY - 1; i < 8 && j >= 0; ++i, --j) {
            possibleAttackPositions.emplace_back(j, i);
        }

        return possibleAttackPositions;
    }

    bool Knight::moveIsValid(int newX, int newY) {
        if ((abs(newY - actualY) + abs(newX - actualX)) == 3) {
            return true;
        } else
            return false;
    }

    vector<pair<int, int>> Knight::calculatePossibleAttackPositions() {
        vector<pair<int, int>> possibleAttackPositions;
        if(actualX - 2 >= 0) {
            if(actualY + 1 <= 7) {
                possibleAttackPositions.emplace_back(actualY + 1, actualX - 2);
            }
            if(actualY - 1 >= 0) {
                possibleAttackPositions.emplace_back(actualY - 1, actualX - 2);
            }
        }

        if(actualX + 2 <= 7) {
            if(actualY + 1 <= 7) {
                possibleAttackPositions.emplace_back(actualY + 1, actualX + 2);
            }
            if(actualY - 1 >= 0) {
                possibleAttackPositions.emplace_back(actualY - 1, actualX + 2);
            }
        }

        if(actualY + 2 <= 7) {
            if(actualX + 1 <= 7) {
                possibleAttackPositions.emplace_back(actualY + 2, actualX + 1);
            }
            if(actualX - 1 >= 0) {
                possibleAttackPositions.emplace_back(actualY + 2, actualX - 1);
            }
        }

        if(actualY - 2 >= 0) {
            if(actualX + 1 <= 7) {
                possibleAttackPositions.emplace_back(actualY - 2, actualX + 1);
            }
            if(actualX - 1 >= 0) {
                possibleAttackPositions.emplace_back(actualY - 2, actualX - 1);
            }
        }

        return possibleAttackPositions;
    }

    bool Queen::moveIsValid(int newX, int newY) {
        if ((newY == actualY) || (newX == actualX)) {
            return true;
        } else if (abs(newY - actualY) == abs(newX - actualX)) {
            return true;
        } else { return false; }
    }

    vector<pair<int, int>> Queen::calculatePossibleAttackPositions() {
        vector<pair<int, int>> possibleAttackPositions;
        //Toutes les positions possibles dans sa rangée sauf la sienne
        for(int i = 0; i < 8; i++) {
            if(i != actualX) {
                possibleAttackPositions.emplace_back(actualY, i);
            }
        }

        //Toutes les positions possibles dans une colonne sauf la sienne
        for(int i = 0; i < 8; i++) {
            if(i != actualY) {
                possibleAttackPositions.emplace_back(i, actualX);
            }
        }

        // Top-left and bottom-right diagonals
        for (int i = actualX - 1, j = actualY - 1; i >= 0 && j >= 0; --i, --j) {
            possibleAttackPositions.emplace_back(j, i);
        }
        for (int i = actualX + 1, j = actualY + 1; i < 8 && j < 8; ++i, ++j) {
            possibleAttackPositions.emplace_back(j, i);
        }

        // Top-right and bottom-left diagonals
        for (int i = actualX - 1, j = actualY + 1; i >= 0 && j < 8; --i, ++j) {
            possibleAttackPositions.emplace_back(j, i);
        }
        for (int i = actualX + 1, j = actualY - 1; i < 8 && j >= 0; ++i, --j) {
            possibleAttackPositions.emplace_back(j, i);
        }
        return possibleAttackPositions;
    }
}