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

    enum class Tool {
        Brush,
        Eraser,
        EyeDropper,
        Fill
    };
    void setTool(Tool tool);
    void floodFill(int x, int y);
    void undo();
    void redo();

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
    struct CanvasState{
        QColor pixels[gridSize][gridSize];
    };
    Tool currentTool = Tool::Brush;
    CanvasState emptyState;
    CanvasState currentState;
    std::vector<CanvasState> undoStack;
    std::vector<CanvasState> redoStack;
    int maxUndo = 5;

};


#endif // PIXELCANVAS_H