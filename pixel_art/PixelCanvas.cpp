#include "PixelCanvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QColorDialog>
#include <QImage>
#include <QFileDialog>
#include <QPoint>
#include <queue>
#include <QDebug>


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
            painter.drawRect(rect);
        }
    }
}
void PixelCanvas::mousePressEvent(QMouseEvent *event)
{
    isDrawing = true;

    int x = event->position().x() / pixelSize;
    int y = event->position().y() / pixelSize;

    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        switch(currentTool){
        case Tool::Brush:
            pixels[y][x] = currentColor;
            break;
        case Tool::Eraser:
            pixels[y][x] = Qt::white;
            break;
        case Tool::EyeDropper:
            currentColor = pixels[y][x];
            break;
        case Tool::Fill:
            floodFill(x, y);
            break;
        }
        update();
    }

}
void PixelCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (!isDrawing) return;

    int x = event->position().x() / pixelSize;
    int y = event->position().y() / pixelSize;

    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        switch(currentTool){
        case Tool::Brush:
            pixels[y][x] = currentColor;
            break;
        case Tool::Eraser:
            pixels[y][x] = Qt::white;
            break;
        case Tool::EyeDropper:
            break;
        case Tool::Fill:
            break;
        }
        update();
    }
}
void PixelCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    isDrawing = false;
}
void PixelCanvas::clear()
{
    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {
            pixels[y][x] = Qt::white;
        }
    }
    update();
}
void PixelCanvas::saveImage()
{
    QImage image(gridSize * pixelSize, gridSize * pixelSize, QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);

    for (int y = 0; y<gridSize; y++){
        for (int x = 0; x<gridSize; x++){
            QRect rect(
                x * pixelSize,
                y * pixelSize,
                pixelSize,
                pixelSize);
            painter.fillRect(rect, pixels[y][x]);
        }
    }
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save Image",
        "",
        "PNG Files (*.png)");
    if(!fileName.isEmpty()){
        if(!fileName.endsWith(".png")){
            fileName += ".png";
        }
        image.save(fileName);
    }
}
void PixelCanvas::setTool(Tool tool){
    currentTool = tool;
}
void PixelCanvas::floodFill(int startX, int startY){
    QColor target = pixels[startY][startX];
    QColor fill = currentColor;
    if(target == fill) return;
    std::queue<QPoint> q;
    q.push(QPoint(startX, startY));
    while (!q.empty()){
        QPoint p = q.front();
        q.pop();

        int x = p.x();
        int y = p.y();
        if (x >= 0 && x < gridSize && y >= 0 && y < gridSize){
            if(pixels[y][x] == target){
                pixels[y][x] = currentColor;
                q.push(QPoint(x+1, y));
                q.push(QPoint(x-1, y));
                q.push(QPoint(x, y+1));
                q.push(QPoint(x, y-1));
            }
        }


    }


}