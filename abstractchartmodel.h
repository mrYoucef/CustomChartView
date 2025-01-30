#ifndef ABSTRACTCHARTMODEL_H
#define ABSTRACTCHARTMODEL_H

#include <QColor>
#include <QPoint>
#include <QObject>
#include <QPainter>

class AbstractChartModel : public QObject
{
    Q_OBJECT

    // Constructors
    public:
        AbstractChartModel();

    // Methods
    public:

        // Points
        virtual int getPointCount() const = 0;
        virtual float getPointY(int chartIndex, int curveIndex, int pointIndex) const = 0;
        virtual int getDistanceBetweenPoints() const = 0;
        virtual QColor getPointColor(int chartIndex, int curveIndex, int pointIndex) const = 0;
        virtual float getMaxY(int chartIndex) const = 0;
        virtual float getMinY(int chartIndex) const;

        // Curves
        virtual int getCurvesCount(int chartIndex) const = 0;
        virtual QString getCurveName(int chartIndex, int curveIndex) const = 0;
        virtual QColor getCurveColor(int chartIndex, int curveIndex) const;
        virtual int getCurvesWidth() const;
        virtual QString getTooltip(int chartIndex, int curveIndex, int pointIndex) const = 0;
        virtual int getPointsRadius() const;
        virtual int getCurvesStartingMargin() const;
        virtual QColor getAxisColor() const;
        virtual int getAxisWidth() const;

        // Columns
        virtual float getKeysColumnWidth() const;
        virtual float getAxisColumnWidth() const;
        virtual QColor getFontColor() const;
        virtual int getFontSize() const;

        // Backgrounds
        virtual QColor getKeysColumnBackgroundColor() const;
        virtual QColor getCurvesColumnBackgroundColor() const;
        virtual QColor getAxisColumnBackgroundColor() const;
        virtual QColor getSeparatorsBackgroundColor() const;

        // Charts
        virtual int getChartCount() const;
        virtual int getChartColumCount() const;
        virtual int getChartHeight() const;


    // Signals
    signals:
        void dataChanged();

};

#endif // ABSTRACTCHARTMODEL_H
