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

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    static const int gridSize = 32;
    int pixelSize = 20;
    QColor currentColor = Qt::black;

    QColor pixels[gridSize][gridSize];
};

#endif // PIXELCANVAS_H