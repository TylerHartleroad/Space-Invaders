#include "fleet.h"

Fleet::Fleet()
{
    width = columns * alienWidth + (columns - 1) * spacing;
    height = rows * alienHeight + (rows - 1) * spacing;
}


void Fleet::Update()
{
    if(delayCount >= moveDelay)
    {
        float newX = position.rx() + fleetDirection * (alienWidth + spacing);
        if(newX > width + alienWidth || newX < 0)
        {
            fleetDirection *= -1;
            position.setY(position.ry() + alienHeight + spacing);
        }
        else
        {
            position.setX(newX);
        }

        delayCount = 0;
    }
    else
    {
        delayCount++;
    }
}


void Fleet::Spawn()
{
    for(int i = 0; i < columns; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            aliens.push_back(QPoint(
                i * (alienWidth + spacing),
                j * (alienHeight + spacing)
            ));
        }
    }
}


void Fleet::Clear()
{
    aliens.clear();
}


QVector<QPoint>::iterator Fleet::AliensBegin()
{
    return aliens.begin();
}

QVector<QPoint>::iterator Fleet::AliensEnd()
{
    return aliens.end();
}

int Fleet::GetRows()
{
    return rows;
}

int Fleet::GetColumns()
{
    return columns;
}

float Fleet::GetWidth()
{
    return width;
}

float Fleet::GetHeight()
{
    return height;
}

float Fleet::GetAlienHeight()
{
    return alienHeight;
}

float Fleet::GetAlienWidth()
{
    return alienWidth;
}

QPoint Fleet::GetPosition()
{
    return position;
}
