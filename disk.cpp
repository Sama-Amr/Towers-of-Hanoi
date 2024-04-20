#include "disk.h"
#include <QTimer>

Disk::Disk(int order, QLabel* label, QLabel* towerLabel)
{
    this->label = label;
    myImage.load(":/disk.png");
    this->order = order;
    height = 20;
    width = 100 - (order-1)*10;

    // Get the tower's position
    int towerX = towerLabel->x();
    int towerY = towerLabel->y();

    // Set the coordinates based on the tower's position
    x = towerX - 0.5*width;
    y = towerY - (order-1)*(height);

    this->label->setPixmap(QPixmap::fromImage(myImage));
    this->label->resize(width, height);
    this->label->setScaledContents(true);
    this->label->move(x, y);
}



void Disk::move(int x, int y)
{
    this->label->move(x, y);
    this->x = x;
    this->y = y;
}
void Disk::animate(int x, int y)
{
    this->reached = false;
    QTimer* timer = new QTimer();
    QFrame::connect(timer, &QTimer::timeout, [this, x, y, timer]() {
        if (!this->reached && this->y > 10) {
            this->y -= 1;
        } else if (this->x < x) {
            this->x += 1;
            this->reached = true;
        } else if (this->x > x) {
            this->x -= 1;
            this->reached = true;
        }else if (this->y < y) {
            this->y += 1;
        }

        move(static_cast<int>(this->x), static_cast<int>(this->y));

        if (this->x == x && this->y == y) {
            move(x, y);
            this->done = true;
            timer->stop();
            timer->deleteLater();
        }
    });

        timer->start(1);

}


float Disk::getWidth(){
    return width;
}
float Disk::getHeight(){
    return height;
}
float Disk::getX(){
    return x;
}
float Disk::getY(){
    return y;
}

bool Disk::operator<(const Disk& other)
{
    return this->order > other.order;
}
