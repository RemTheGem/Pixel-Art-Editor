#include "PixelCanvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>

PixelCanvas::PixelCanvas(QWidget *parent)
    : QWidget(parent)
{

    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {
            pixels[y][x] = Qt::white;
        }
    }

    setMouseTracking(true);
}
void PixelCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {

            QRect rect(
                x * pixelSize,
                y * pixelSize,
                pixelSize,
                pixelSize
                );

            painter.fillRect(rect, pixels[y][x]);
            painter.drawRect(rect); // grid lines
        }
    }
}
void PixelCanvas::mousePressEvent(QMouseEvent *event)
{
    int x = event->position().x() / pixelSize;
    int y = event->position().y() / pixelSize;

    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize && Qt::white) {
        if(pixels[y][x] == Qt::white)
        pixels[y][x] = Qt::black;
        else
            pixels[y][x] = Qt::white;
        update();
    }

}