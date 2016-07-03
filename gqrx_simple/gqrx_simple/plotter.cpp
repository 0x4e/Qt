#include "plotter.h"
#include <stdlib.h>
#include <cmath>
#include <QDebug>
#include <QtGlobal>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CPlotter::CPlotter(QWidget *parent) :
    QFrame(parent)
{

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_PaintOnScreen,false);
    setAutoFillBackground(false);
    setAttribute(Qt::WA_OpaquePaintEvent, false);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setMouseTracking(true);

    //setFftPlotColor(QColor(0xFF,0xFF,0xFF,0xFF));
    //QPoint LineBuf[MAX_SCREENSIZE];

    m_WaterfallPixmap = QPixmap(100,200);
    m_WaterfallPixmap.fill(Qt::red);



}

CPlotter::~CPlotter()
{
}

//Called by QT when Screen needs to be re-drawn
void CPlotter::paintEvent(QPaintEvent *event)
{
    QRect rect = event->rect();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.drawText(rect, Qt::AlignCenter,
                      "Data");
    painter.drawRect(rect);
    painter.drawPixmap(25, 0,m_WaterfallPixmap);
}

//////////////////////////////////////////////////////////////////////
// Called when a mouse wheel is turned
//////////////////////////////////////////////////////////////////////
void CPlotter::wheelEvent(QWheelEvent * event)
{
    qDebug() << event->pos();
}
