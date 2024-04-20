#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tower.h"
#include "disk.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_resetButton_clicked();

    void on_numberOfDisks_valueChanged();

    void on_playButton_clicked();

    void on_previousButton_clicked();

    void on_nextButton_clicked();

    void on_checkBox_As_clicked();

    void on_checkBox_Bs_clicked();

    void on_checkBox_Cs_clicked();

    void on_checkBox_Ad_clicked();

    void on_checkBox_Bd_clicked();

    void on_checkBox_Cd_clicked();





private:
    Ui::MainWindow *ui;
    Tower *t1,*t2,*t3;
    int numberOfDisks;
    vector<Disk*> disks;
    void resetGame();
    vector<int> moveHistory;
    int index;

    QTimer *timer;

    char source;
    char destination;
    char auxillary;

    void solveHanoi(int disks, Tower* source, Tower* destination, Tower* auxilliary);
    void moveDisk(Tower* source, Tower* destination, bool addToHistory=true, bool animate=false);


    bool As=false;
    bool Bs=false;
    bool Cs=false;
    bool Ad=false;
    bool Bd=false;
    bool Cd=false;
};
#endif // MAINWINDOW_H
