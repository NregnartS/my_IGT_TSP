#include "drawingboard.h"

drawingBoard::drawingBoard(QWidget *parent)
    :QWidget(parent)
{
    this->resize(1000,700);
    this->setWindowTitle("IGT_TSP_Graph");
    this->valueLabel=new QLabel();
    this->layout=new QHBoxLayout();
    layout->addWidget(valueLabel,0,Qt::AlignLeft|Qt::AlignTop);
    setLayout(layout);
}

drawingBoard::drawingBoard(const QPainterPath &tp){
    this->setPath(tp);
}

void drawingBoard::setPath(const QPainterPath &tp){
    this->path=tp;
}

QPainterPath drawingBoard::getPath(){
    return this->path;
}

void drawingBoard::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPen pen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.setBrush(Qt::black);
    painter.drawPath(this->path);
    valueLabel->setText("¸ÃÂ·¾¶¾àÀëÎª£º"+QString::number(u.getValue(),10,6));
}
