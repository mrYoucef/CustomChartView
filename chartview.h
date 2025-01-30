#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QPainter>
#include <QWidget>
#include <QDebug>
#include <QMouseEvent>

#include "abstractchartmodel.h"

class ChartView : public QWidget
{
    Q_OBJECT

    // Members
    private:
        AbstractChartModel * model;

        int startingIndex = 0;
        float startingPixel = 0;

        int startingRowIndex = 0;
        float startingRowPixel = 0;

        int rowsCount;
        int rowsCountOnView;

        float keysColumnWidth;
        float axisColumnWidth;

        int chartCount;
        QRect adjustedCurveRect;
        QRect firstDrawingArea;

        float verticalMargin = 10;
        float horizontalMargin = 10;
        int separatorWitdh = 4 ;


    // Constructors
    public:
        explicit ChartView(QWidget * parent = nullptr);

    // Methods
    public:
        AbstractChartModel * getModel() const;
        void setModel(AbstractChartModel *value);
        int getHorizontalScrollBarRange();
        int getHorizantalScrollBarPageStep();
        int getHorizontalScrollBarSingleStep();
        int getVerticalScrollBarRange();
        int getVerticalScrollBarPageStep();
        int getVerticalScrollBarSingleStep();

    private:
        QPointF getConvertedPoint(int chartIndex, int curveIndex, int pointIndex);
        int getIndexFromCurserPosX(QRect rect, int curserX) const;
        float getYcordinateOnView(int chartIndex, int value) ;
        float getXcordinateOnView(int chartIndex, int index) const;
        QRect getDrawingArea(int chartIndex) const;
        QRect getChartArea(int chartIndex) const;
        int getPointsCountInView() const;
        float getYcordinateOnRect(QRect actualChart, int chartIndex, float value) const;

    protected:
        void paintEvent(QPaintEvent * event) override;
        void mouseMoveEvent(QMouseEvent * event) override;

    // Slots
    public slots:
        void onDataChanged();
        void ensureVisible(int position);
        void ensureVerticalVisible(int position);

    // signals
    signals:
        void scrollBareUpdate();


};

#endif // CHARTVIEW_H
