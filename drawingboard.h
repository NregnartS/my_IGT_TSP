#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QHBoxLayout>
#include <unit.h>

namespace Ui {
class drawingBoard;
}

class drawingBoard:public QWidget
{
    Q_OBJECT
public:
    explicit drawingBoard(QWidget *parent = nullptr);

    virtual ~drawingBoard(){};

    drawingBoard(const QPainterPath &tp);

    void paintEvent(QPaintEvent*);

    QPainterPath getPath();

    void setPath(const QPainterPath &tp);

    void setUV(double v){this->u.setValue(v);}

private:
    Ui::drawingBoard *ui;
    QPainterPath path;
    Unit u;
    QLabel *valueLabel;
    QHBoxLayout *layout;
};

#endif // DRAWINGBOARD_H
