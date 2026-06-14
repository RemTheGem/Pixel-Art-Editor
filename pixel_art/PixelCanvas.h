#ifndef PIXELCANVAS_H
#define PIXELCANVAS_H

#include <QWidget>
#include <QColor>
#include <QMouseEvent>
#include <QPaintEvent>

class PixelCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit PixelCanvas(QWidget *parent = nullptr);
    void setColor(const QColor &c) {currentColor = c;}
    void clear();
    void saveImage();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    static const int gridSize = 40;
    int pixelSize = 10;
    QColor currentColor = Qt::black;
    bool isDrawing = false;
    QColor pixels[gridSize][gridSize];
};

#endif // PIXELCANVAS_H