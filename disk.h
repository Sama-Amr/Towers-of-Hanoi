#ifndef DISK_H
#define DISK_H
#include <QLabel>
#include <QImage>
#include "tower.h"

class Disk
{
public:
    QLabel* label;
    Disk(int order, QLabel* label, QLabel* towerLabel);
    void animate(int x, int y);
    float getWidth();
    float getHeight();
    float getX();
    float getY();
    bool operator<(const Disk& other);
    bool done;
    void move(int x, int y);
private:
    int order;
    float width;
    float height;
    float x;
    float y;
    bool reached;
    QImage myImage;
};

#endif // DISK_H
