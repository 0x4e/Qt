#ifndef PLOTTER
#define PLOTTER


#include <QtGui>
#include <QFrame>
#include <QImage>
#include <vector>
#include <QMap>


#define HORZ_DIVS_MAX 50 //12
#define MAX_SCREENSIZE 4096

#define PEAK_CLICK_MAX_H_DISTANCE 10 //Maximum horizontal distance of clicked point from peak
#define PEAK_CLICK_MAX_V_DISTANCE 20 //Maximum vertical distance of clicked point from peak
#define PEAK_H_TOLERANCE 2


class CPlotter : public QFrame
{
    Q_OBJECT

public:
    explicit CPlotter(QWidget *parent = 0);
    ~CPlotter();

    //QSize minimumSizeHint() const;
    //QSize sizeHint() const;

protected:
    //re-implemented widget event handlers
    void paintEvent(QPaintEvent *event);
    void wheelEvent( QWheelEvent * event );

private:
    QPixmap m_WaterfallPixmap;
    QPixmap m_2DPixmap;
};


#endif // PLOTTER

