#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class GameModeSelectWindow : public QDialog
{
Q_OBJECT

public:
    explicit GameModeSelectWindow(QWidget *parent = nullptr);
    int getSelectedGameMode() const;

private:
    QRadioButton *gameMode1Button;
    QRadioButton *gameMode2Button;
    QPushButton *playButton;
};

#endif

