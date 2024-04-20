#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTimer>
#include <cmath>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    t1 = new Tower(1,ui->tower1);
    t2 = new Tower(2,ui->tower2);
    t3 = new Tower(3,ui->tower3);
    resetGame();
}

MainWindow::~MainWindow()
{
    for(int i=disks.size()-1;i>=0;i--)
    {
        delete disks.at(i)->label;
        delete disks.at(i);
    }
    disks.clear();

    delete t1;
    delete t2;
    delete t3;

    delete ui;
}
void MainWindow::on_checkBox_As_clicked()
{
    if(Bs||Cs){
        return;
    }
    else{
        As=true;
        source='A';

    }
}

void MainWindow::on_checkBox_Bs_clicked(){
    if(As||Cs){
        return;
    }
    else{
        Bs=true;
        source='B';
    }
}

void MainWindow::on_checkBox_Cs_clicked()
{
    if(As||Bs){
        return;
    }
    else{
        Cs=true;
        source='C';
    }
}

void MainWindow::on_checkBox_Ad_clicked()
{
    if(Bd||Cd){
        return;
    }
    else{
        Ad=true;
        destination='A';
    }
}

void MainWindow::on_checkBox_Bd_clicked()
{
    if(Ad||Cd){
        return;
    }
    else{
        Bd=true;
        destination='B';
    }
}

void MainWindow::on_checkBox_Cd_clicked()
{
    if(Ad||Bd){
        return;
    }
    else{
        Cd=true;
        destination='C';

    }
}


void MainWindow::resetGame()
{
    for(int i=disks.size()-1;i>=0;i--)
    {
        delete disks.at(i)->label;
        delete disks.at(i);
    }
    disks.clear();
    t1->clear();
    t2->clear();
    t3->clear();

    numberOfDisks = ui->numberOfDisks->value();
    for(int i=1;i<=numberOfDisks;i++)
    {
        QLabel* newLabel = new QLabel(QString("disk_%1").arg(i), this);
        Disk* newDisk = new Disk(i,newLabel,'A');
        disks.push_back(newDisk);
        t1->addDisk(newDisk);
        newLabel->show();
    }
    ui->nextButton->setEnabled(false);
    ui->previousButton->setEnabled(false);

    ui->checkBox_As->setChecked(false);
    ui->checkBox_Ad->setChecked(false);
    ui->checkBox_Bs->setChecked(false);
    ui->checkBox_Bd->setChecked(false);
    ui->checkBox_Cs->setChecked(false);
    ui->checkBox_Cd->setChecked(false);

    As=false;
    Ad=false;
    Bs=false;
    Bd=false;
    Cs=false;
    Cd=false;
}




void MainWindow::on_resetButton_clicked()
{
    resetGame();
}


void MainWindow::on_numberOfDisks_valueChanged()
{
    resetGame();
}
void MainWindow::moveDisk(Tower* source, Tower* destination,bool addToHistory,bool animate)
{
    if (destination->canPushDisk(source->peekDisk()))
    {
        Disk* disk = source->popDisk();
        destination->pushDisk(disk,animate);
        if(addToHistory)
            moveHistory.push_back(source->getOrder()*10+destination->getOrder());
    }
}

void MainWindow::on_playButton_clicked()
{
    if(As && Cd){
        moveHistory.clear();
        solveHanoi(numberOfDisks,t1,t3,t2);
        index = moveHistory.size()-1;
        ui->previousButton->setEnabled(true);
        return;

    }
    if(As && Bd){
        moveHistory.clear();
        solveHanoi(numberOfDisks,t1,t2,t3);
        index = moveHistory.size()-1;
        ui->previousButton->setEnabled(true);
        return;
    }
    if(Bs && Ad){
        moveHistory.clear();
        solveHanoi(numberOfDisks,t2,t1,t3);
        index = moveHistory.size()-1;
        ui->previousButton->setEnabled(true);
        return;
    }
    if(Bs && Cd){
        moveHistory.clear();
        solveHanoi(numberOfDisks,t2,t3,t1);
        index = moveHistory.size()-1;
        ui->previousButton->setEnabled(true);
        return;
    }
    if(Cs && Ad){
        moveHistory.clear();
        solveHanoi(numberOfDisks,t3,t1,t2);
        index = moveHistory.size()-1;
        ui->previousButton->setEnabled(true);
        return;
    }
    if(Cs && Bd){
        moveHistory.clear();
        solveHanoi(numberOfDisks,t3,t2,t1);
        index = moveHistory.size()-1;
        ui->previousButton->setEnabled(true);
        return;
    }
    if(!As && !Bs && !Cs && !Ad && !Bd && !Cd){
        QMessageBox::information(this, "No Checkboxes Checked", "Please select a source and a destination");

    }


}

void MainWindow::solveHanoi(int disks, Tower* source, Tower* destination, Tower* auxiliary)
{
    if (disks == 1)
    {
        moveDisk(source, destination);
    }
    else
    {
        solveHanoi(disks - 1, source, auxiliary, destination);
        moveDisk(source, destination);
        solveHanoi(disks - 1, auxiliary, destination, source);
    }
}


void MainWindow::on_nextButton_clicked()
{
    int move = moveHistory.at(++index);
    int src = move/10;
    int dest = move%10;
    Tower* source = src==1?t1:src==2?t2:t3;
    Tower* destination = dest==1?t1:dest==2?t2:t3;
    this->moveDisk(source,destination,false,true);

    ui->previousButton->setEnabled(index!=-1);
    ui->nextButton->setEnabled(index!=moveHistory.size()-1);

}

void MainWindow::on_previousButton_clicked()
{
    int move = moveHistory.at(index--);
    int src = move/10;
    int dest = move%10;
    Tower* source = src==1?t1:src==2?t2:t3;
    Tower* destination = dest==1?t1:dest==2?t2:t3;
    this->moveDisk(destination,source,false,true);

    ui->previousButton->setEnabled(index!=-1);
    ui->nextButton->setEnabled(index!=moveHistory.size()-1);
}


