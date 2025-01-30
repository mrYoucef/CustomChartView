#include "abstractchartmodel.h"

// Constructors
AbstractChartModel::AbstractChartModel()
{

}

// Methods
float AbstractChartModel::getMinY(int chartIndex) const
{
    return -getMaxY(chartIndex);
}

QColor AbstractChartModel::getAxisColor() const
{
    return Qt::black;
}

int AbstractChartModel::getAxisWidth() const
{
    return 5;
}


QColor AbstractChartModel::getKeysColumnBackgroundColor() const
{
    return  Qt::white;
}

QColor AbstractChartModel::getAxisColumnBackgroundColor() const
{
    return  Qt::cyan;
}

QColor AbstractChartModel::getSeparatorsBackgroundColor() const
{
    return Qt::gray;
}

int AbstractChartModel::getChartCount() const
{
    return  1;
}

int AbstractChartModel::getChartColumCount() const
{
    return 1;
}

int AbstractChartModel::getChartHeight() const
{
    return 250;
}

float AbstractChartModel::getKeysColumnWidth() const
{
    int maxCurvesNamesSize = 0;
    QFont font;
    font.setPixelSize(getFontSize());
    QFontMetrics metric(font);

    for (int chartIndex(0) ; chartIndex < getChartCount() ; chartIndex++)
    {
        for (int i(0) ; i < getCurvesCount(chartIndex) ; i ++)
            if (maxCurvesNamesSize < metric.horizontalAdvance(getCurveName(chartIndex, i)))
                maxCurvesNamesSize = metric.horizontalAdvance(getCurveName(chartIndex, i));
    }

    return maxCurvesNamesSize;
}

float AbstractChartModel::getAxisColumnWidth() const
{
    return getAxisWidth() / 2;
}

QColor AbstractChartModel::getFontColor() const
{
    return Qt::black;
}

int AbstractChartModel::getFontSize() const
{
    return 20;
}

QColor AbstractChartModel::getCurvesColumnBackgroundColor() const
{
    return Qt::white;
}

QColor AbstractChartModel::getCurveColor(int chartIndex, int curveIndex) const
{
    return QColor((curveIndex * 133 + 50) % 256, (curveIndex * 55) % 256, (curveIndex * 75) % 256);
}

int AbstractChartModel::getCurvesWidth() const
{
    return 3;
}

int AbstractChartModel::getPointsRadius() const
{
    return 7;
}

int AbstractChartModel::getCurvesStartingMargin() const
{
    return getPointsRadius();
}
