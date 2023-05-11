#include "mainmenu.h"

GameModeSelectWindow::GameModeSelectWindow(QWidget *parent) :
        QDialog(parent),
        gameMode1Button(new QRadioButton("Mode \"Classique\"", this)),
        gameMode2Button(new QRadioButton("Mode \"Crazy Queen\"", this)),
        playButton(new QPushButton("Jouer!", this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *buttonsLayout = new QHBoxLayout;

    gameMode1Button->setChecked(true);

    buttonsLayout->addWidget(gameMode1Button);
    buttonsLayout->addWidget(gameMode2Button);

    mainLayout->addLayout(buttonsLayout);
    mainLayout->addWidget(playButton);

    setLayout(mainLayout);

    connect(playButton, &QPushButton::clicked, this, &GameModeSelectWindow::accept);
}

int GameModeSelectWindow::getSelectedGameMode() const
{
    if (gameMode1Button->isChecked()) {
        return 1;
    } else {
        return 2;
    }
}
