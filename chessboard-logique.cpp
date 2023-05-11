#include "chessboard-logique.h"

using namespace std;

//Initialise le chessboard avec les pièces aux bons endroits. Selon le mode de jeu sélectionné, on place soit
//des pions, soit des reines sur la première rangée.
void ChessBoardLog::initializeChessboard(int gameMode) {
    chessboard[0][0] = make_unique<pieceLogic::Rook>(Color::BLACK, 0, 0);
    chessboard[0][1] = make_unique<pieceLogic::Knight>(Color::BLACK, 1, 0);
    chessboard[0][2] = make_unique<pieceLogic::Bishop>(Color::BLACK, 2, 0);
    chessboard[0][3] = make_unique<pieceLogic::Queen>(Color::BLACK, 3, 0);
    chessboard[0][4] = make_unique<pieceLogic::King>(Color::BLACK, 4, 0);
    blackKingPos.first = 0;
    blackKingPos.second = 4;
    chessboard[0][5] = make_unique<pieceLogic::Bishop>(Color::BLACK, 5, 0);
    chessboard[0][6] = make_unique<pieceLogic::Knight>(Color::BLACK, 6, 0);
    chessboard[0][7] = make_unique<pieceLogic::Rook>(Color::BLACK, 7, 0);

    chessboard[7][0] = make_unique<pieceLogic::Rook>(Color::WHITE, 0, 7);
    chessboard[7][1] = make_unique<pieceLogic::Knight>(Color::WHITE, 1, 7);
    chessboard[7][2] = make_unique<pieceLogic::Bishop>(Color::WHITE, 2, 7);
    chessboard[7][3] = make_unique<pieceLogic::Queen>(Color::WHITE, 3, 7);
    chessboard[7][4] = make_unique<pieceLogic::King>(Color::WHITE, 4, 7);
    whiteKingPos.first = 7;
    whiteKingPos.second = 4;
    chessboard[7][5] = make_unique<pieceLogic::Bishop>(Color::WHITE, 5, 7);
    chessboard[7][6] = make_unique<pieceLogic::Knight>(Color::WHITE, 6, 7);
    chessboard[7][7] = make_unique<pieceLogic::Rook>(Color::WHITE, 7, 7);

    if (gameMode == 1) {
        for (int i = 0; i < 8; i++) {
            chessboard[1][i] = make_unique<pieceLogic::Pawn>(Color::BLACK, i, 1);
        }
        for (int i = 0; i < 8; i++) {
            chessboard[6][i] = make_unique<pieceLogic::Pawn>(Color::WHITE, i, 6);
        }
    } else if (gameMode == 2) {
        for (int i = 0; i < 8; i++) {
            chessboard[1][i] = make_unique<pieceLogic::Queen>(Color::BLACK, i, 1);
        }
        for (int i = 0; i < 8; i++) {
            chessboard[6][i] = make_unique<pieceLogic::Queen>(Color::WHITE, i, 6);
        }
    }
    //Génère une erreur si il y a trop de rois en jeu
    try {
        int kingCounter = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (chessboard[i][j] && typeid(*chessboard[i][j]) == typeid(pieceLogic::King)) {
                    kingCounter++;
                }
            }
        }
        if (kingCounter > 2) {
            throw std::runtime_error("Error: More than 2 kings in the game");
        }
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

bool ChessBoardLog::getWhitesTurn() {
    return whitesTurn;
}

//Logique des déplacements si le roi est menacé
void ChessBoardLog::turnLogicWhenChecked(int oldX, int oldY, int newX, int newY) {
    //Crée un "backup" de la situation actuelle sur l'échiquier
    bool killedPiece = false;
    if (chessboard[newY][newX] != nullptr) {
        backupPiece = move(chessboard[newY][newX]);
        killedPiece = true;
    }
    backupX = chessboard[oldY][oldX]->actualX;
    backupY = chessboard[oldY][oldX]->actualY;
    chessboard[newY][newX] = move(chessboard[oldY][oldX]); //Déplace la pièce dans l'échiquier logique
    chessboard[newY][newX]->actualX = newX; //Mets à jour la position actuelle de la pièce
    chessboard[newY][newX]->actualY = newY;

    if(whitesTurn)
        whiteIsChecked = false;
    else
        blackIsChecked = false;

    //Vérifie si le roi est toujours en échec après son mouvement
    checkForCheck();

    //Si il est toujours en échec, on remet le chessboard dans l'état ou il était et on refuse le mouvement
    if ((whiteIsChecked && whitesTurn) || (blackIsChecked && !whitesTurn)) {
        chessboard[backupY][backupX] = move(chessboard[newY][newX]);
        chessboard[backupY][backupX]->actualX = backupX;
        chessboard[backupY][backupX]->actualY = backupY;
        if (killedPiece) {
            chessboard[newY][newX] = move(backupPiece);
            chessboard[newY][newX]->actualX = newX;
            chessboard[newY][newX]->actualY = newY;
        }
        cout << "Move doesn't un-check the king!" << endl;
        moveDoneIndicatorForUi = false;
        return;
    }

    //Si le mouvement a réussi à protéger le roi, on l'accepte
    backupPiece.reset();
    if (dynamic_cast<pieceLogic::King *>(chessboard[newY][newX].get()) != nullptr) {
        if(chessboard[newY][newX]->color_ == Color::WHITE) {
            whiteKingPos.first = newY;
            whiteKingPos.second = newX;
        } else {
            blackKingPos.first = newY;
            blackKingPos.second = newX;
        }
    }
    //Passe au tour de l'équipe adverse
    whitesTurn = !whitesTurn;
    moveDoneIndicatorForUi = true;
}

//Fonction qui vérifie si un mouvement met en danger son propre roi (si oui, il n'est pas valide)
bool ChessBoardLog::checkIfMoveEndangersOwnKing(int oldX, int oldY, int newX, int newY) {
    //Fais le mouvement sur le chessboard en créant un backup
    bool moveEndangersOwnKing;
    bool killedPiece = false;
    if (chessboard[newY][newX] != nullptr) {
        backupPiece = move(chessboard[newY][newX]);
        killedPiece = true;
    }
    backupX = chessboard[oldY][oldX]->actualX;
    backupY = chessboard[oldY][oldX]->actualY;
    chessboard[newY][newX] = move(chessboard[oldY][oldX]); //Déplace la pièce dans l'échiquier logique
    chessboard[newY][newX]->actualX = newX; //Mets à jour la position actuelle de la pièce
    chessboard[newY][newX]->actualY = newY;

    //Si le mouvement cause un échec sur sa propre couleur
    checkForCheck();
    if((whitesTurn && whiteIsChecked) || (!whitesTurn && blackIsChecked))
        moveEndangersOwnKing = true;
    else
        moveEndangersOwnKing = false;

    //Remets le chessboard dans l'état du backup
    chessboard[backupY][backupX] = move(chessboard[newY][newX]);
    chessboard[backupY][backupX]->actualX = backupX;
    chessboard[backupY][backupX]->actualY = backupY;
    if (killedPiece) {
        chessboard[newY][newX] = move(backupPiece);
        chessboard[newY][newX]->actualX = newX;
        chessboard[newY][newX]->actualY = newY;
    }

    //Reset l'indicateur d'échec et retourne si le move est valide ou non
    whiteIsChecked = false;
    blackIsChecked = false;
    return moveEndangersOwnKing;
}

//Logique des déplacements normaux (quand le roi n'est pas en échec)
void ChessBoardLog::turnLogicNormal(int oldX, int oldY, int newX, int newY) {
    //Vérifie si le mouvement met en danger le roi
    if(checkIfMoveEndangersOwnKing(oldX, oldY, newX, newY)) {
        cout << "This move could endanger your own king!" << endl;
        moveDoneIndicatorForUi = false;
    }
    else {
        //Si la case sur laquelle se déplace la pièce contient une pièce adverse, on la tue avant de se déplacer
        if (chessboard[newY][newX] != nullptr) {
            killPiece(newY, newX);
        }
        chessboard[newY][newX] = move(chessboard[oldY][oldX]); //Déplace la pièce dans l'échiquier logique
        chessboard[newY][newX]->actualX = newX; //Mets à jour la position actuelle de la pièce
        chessboard[newY][newX]->actualY = newY;

        //Si le roi est celui que l'on a déplacé, on met à jour sa position (utile pour le UI)
        if (dynamic_cast<pieceLogic::King *>(chessboard[newY][newX].get()) != nullptr) {
            if(chessboard[newY][newX]->color_ == Color::WHITE) {
                whiteKingPos.first = newY;
                whiteKingPos.second = newX;
            } else {
                blackKingPos.first = newY;
                blackKingPos.second = newX;
            }
        }

        //Vérifie si les rois sont en échec
        checkForCheck();
        if (whiteIsChecked) {
            cout << "White king is checked!" << endl;
        }
        if (blackIsChecked) {
            cout << "Black king is checked!" << endl;
        }

        //Passe au tour de l'adversaire et envoie le signal au UI d'effectuer le déplacement sur l'échiquier QT
        whitesTurn = !whitesTurn;
        moveDoneIndicatorForUi = true;
    }
}

//Sert à imprimer lorsque l'on effectue un déplacement (utile pour debug)
void ChessBoardLog::printWhenMoveIsDone(int oldX, int oldY, int newX, int newY) {
    if(moveDoneIndicatorForUi) {
        cout << "Moving piece from (" << oldX << "," << oldY << ") to (" << newX << "," << newY << ")"<< endl;
    }
}

//Fonction PRINCIPALE du chessboard, vérifie toutes les conditions pour qu'un mouvement soit correct, l'effectue sur
//le chessboard logique, puis retourne "true" ou "false" au UI pour que ce dernier sache si il doit déplacer les pièces
//sur l'échiquier QT
bool ChessBoardLog::movePiece(int oldX, int oldY, int newX, int newY) {
    //S'assure que l'on essaye pas de déplacer une pièce sur sa propre case
    if(oldX == newX && oldY == newY)
        return false;

    //Si l'on sélectionne une pièce de la bonne couleur (c'est à leur tour de jouer)
    if((whitesTurn && chessboard[oldY][oldX]->color_ == Color::WHITE) || (!whitesTurn && chessboard[oldY][oldX]->color_ == Color::BLACK)) {
        //Si le mouvement n'est pas possible pour la pièce, alors on retourne false
        if (!chessboard[oldY][oldX]->moveIsValid(newX, newY))
            return false;

        //Si le mouvement est valide mais qu'il y a des pièces dans le chemin, on retourne false
        if (!isPathClear(oldX, oldY, newX, newY))
            return false;

        //Appelle les fonctions de logique des tours vues plus haut
        if(whiteIsChecked && whitesTurn)
            turnLogicWhenChecked(oldX, oldY, newX, newY);
        else if(blackIsChecked && !whitesTurn)
            turnLogicWhenChecked(oldX, oldY, newX, newY);
        else
            turnLogicNormal(oldX, oldY, newX, newY);

        printWhenMoveIsDone(oldX, oldY, newX, newY);
        return moveDoneIndicatorForUi;
    }
    return false;
}

//Vérifie tous les mouvements possibles d'un pièce afin de les afficher en vert sur le chessboard QT
void ChessBoardLog::checkPossibleMovesForUI(int oldX, int oldY) {
    int newY, newX;
    vectorPossiblePiece.clear();
    //Ajoute toutes les positions possibles dans le vecteur
    if (auto pion = dynamic_cast<pieceLogic::Pawn *>(chessboard[oldY][oldX].get()); pion != nullptr) {
        vectorPossiblePiece = pion->calculatePossiblePositionsForUI();
    } else {
        vectorPossiblePiece = chessboard[oldY][oldX]->calculatePossibleAttackPositions();
    }

    //Retire les positions qui sont bloquées par une pièce dans le chemin
    int i = 0;
    while (i < vectorPossiblePiece.size()) {
        newY = vectorPossiblePiece[i].first;
        newX = vectorPossiblePiece[i].second;
        if (!isPathClear(oldX, oldY, newX, newY))
            vectorPossiblePiece.erase(vectorPossiblePiece.begin() + i);
        else
            i++;
    }
}

//Vérifie si les rois sont en échec en loopant à travers toutes les pièces de l'échiquier
void ChessBoardLog::checkForCheck() {
    int newX, newY, oldX, oldY;
    for(int a = 0; a < 8; a++) {
        for(int b = 0; b < 8; b++) {
            if(chessboard[a][b] == nullptr)
                continue;

            oldX = chessboard[a][b] -> actualX;
            oldY = chessboard[a][b] -> actualY;

            //Regarde toutes les positions que la pièce peut attaquer, en prenant en compte les collisions
            vectorForCheck = chessboard[oldY][oldX]->calculatePossibleAttackPositions();
            int j = 0;
            while (j < vectorForCheck.size()) {
                newY = vectorForCheck[j].first;
                newX = vectorForCheck[j].second;
                if(!isPathClear(oldX, oldY, newX, newY)) {
                    vectorForCheck.erase(vectorForCheck.begin() + j);
                } else {
                    j++;
                }
            }

            //Loop à travers toutes les positions attaquables et trouve si une est populée par un roi, ce qui le met en échec
            for(int i = 0; i < vectorForCheck.size(); i++) {
                newY = vectorForCheck[i].first;
                newX = vectorForCheck[i].second;

                if(dynamic_cast<pieceLogic::King*>(chessboard[newY][newX].get()) == nullptr)
                    continue;
                if(chessboard[newY][newX] -> color_ == chessboard[oldY][oldX] -> color_)
                    continue;

                if(chessboard[newY][newX] -> color_ == Color::WHITE) {
                    whiteIsChecked = true;
                } else {
                    blackIsChecked = true;
                }
            }
        }
    }
}

//Tue une pièce à une coordonnée spécifique sur le board
void ChessBoardLog::killPiece(int actualX, int actualY) {
    cout << "Killing piece at (" << actualX << "," << actualY << ")" << endl;
    chessboard[actualY][actualX].reset();
}

// vérifie si il y a une autre pièce sur le chemin de celui avec les coordonnées oldX et oldY
bool ChessBoardLog::isPathClear(int oldX, int oldY, int newX, int newY) {
    //Détermine la direction du mouvement
    Direction dir;
    if (oldX == newX)
        dir = VERTICAL;
    else if (oldY == newY)
        dir = HORIZONTAL;
    else
        dir = DIAGONAL;

    //Gère le mouvement du cavalier (différent car peut sauter par dessus des pièces)
    if (dynamic_cast<pieceLogic::Knight *>(chessboard[oldY][oldX].get()) != nullptr) {
        if (chessboard[newY][newX].get() == nullptr)
            return true;
        else if (chessboard[newY][newX]->color_ == chessboard[oldY][oldX]->color_)
            return false;
        else {
            return true;
        }
    }

    //Vérifie le mouvement du pion (différent à cause des prises en diagonale)
    if (dynamic_cast<pieceLogic::Pawn *>(chessboard[oldY][oldX].get()) != nullptr) {
        if (dir == DIAGONAL) {
            if (chessboard[newY][newX].get() == nullptr)
                return false;
            else if (chessboard[newY][newX]->color_ == chessboard[oldY][oldX]->color_)
                return false;
            else {
                return true;
            }
        } else {
            if (newY > oldY) {
                for (int i = newY; i > oldY; i--) {
                    if (chessboard[i][newX].get() != nullptr)
                        return false;
                }
            } else if (newY < oldY) {
                for (int i = newY; i < oldY; i++) {
                    if (chessboard[i][newX].get() != nullptr)
                        return false;
                }
            }
            return true;
        }
    }

    switch (dir) {
        case HORIZONTAL:
            //Vérifie que tout le chemin (sauf la case de destination) est clear
            if (newX > oldX) {
                for (int i = newX - 1; i > oldX; i--) {
                    if (chessboard[newY][i].get() != nullptr)
                        return false;
                }
            } else if (newX < oldX) {
                for (int i = newX + 1; i < oldX; i++) {
                    if (chessboard[newY][i].get() != nullptr)
                        return false;
                }
            }

            //Vérifie si la case de destination est clear OU si il y a une pièce adverse dessus
            if (chessboard[newY][newX].get() != nullptr) {
                if (chessboard[newY][newX]->color_ != chessboard[oldY][oldX]->color_) {
                    return true;
                }
                return false;
            }
            return true;
            break;
        case VERTICAL:
            //Vérifie que tout le chemin (sauf la case de destination) est clear
            if (newY > oldY) {
                for (int i = newY - 1; i > oldY; i--) {
                    if (chessboard[i][newX].get() != nullptr)
                        return false;
                }
            } else if (newY < oldY) {
                for (int i = newY + 1; i < oldY; i++) {
                    if (chessboard[i][newX].get() != nullptr)
                        return false;
                }
            }

            //Vérifie si la case de destination est clear OU si il y a une pièce adverse dessus
            if (chessboard[newY][newX].get() != nullptr) {
                if (chessboard[newY][newX]->color_ != chessboard[oldY][oldX]->color_) {
                    return true;
                }
                return false;
            }
            return true;
            break;
        case DIAGONAL:
            //Vérifie que tout le chemin (sauf la case de destination) est clear
            int hor, ver;
            if (newX > oldX) {
                if (newY > oldY) {
                    hor = oldX + 1;
                    ver = oldY + 1;
                    while (hor != newX || ver != newY) {
                        if (chessboard[ver][hor].get() != nullptr)
                            return false;
                        hor++;
                        ver++;
                    }
                } else {
                    hor = oldX + 1;
                    ver = oldY - 1;
                    while (hor != newX || ver != newY) {
                        if (chessboard[ver][hor].get() != nullptr)
                            return false;
                        hor++;
                        ver--;
                    }
                }
            } else {
                if (newY > oldY) {
                    hor = oldX - 1;
                    ver = oldY + 1;
                    while (hor != newX || ver != newY) {
                        if (chessboard[ver][hor].get() != nullptr)
                            return false;
                        hor--;
                        ver++;
                    }
                } else {
                    hor = oldX - 1;
                    ver = oldY - 1;
                    while (hor != newX || ver != newY) {
                        if (chessboard[ver][hor].get() != nullptr)
                            return false;
                        hor--;
                        ver--;
                    }
                }
            }

            //Vérifie si la case de destination est clear OU si il y a une pièce adverse dessus
            if (chessboard[newY][newX].get() != nullptr) {
                if (chessboard[newY][newX]->color_ != chessboard[oldY][oldX]->color_) {
                    return true;
                }
                return false;
            }
            return true;
            break;
    }
}