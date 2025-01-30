#include "chartview.h"


// Constructors
ChartView::ChartView(QWidget *parent) :
    QWidget(parent),
    model(nullptr)
{
        setMouseTracking(true);

}

// Methods
AbstractChartModel *ChartView::getModel() const
{
    return model;
}

void ChartView::setModel(AbstractChartModel * value)
{
    model = value;
    update();
}

int ChartView::getHorizontalScrollBarRange()
{
   return (model->getPointCount() - 1) * model->getDistanceBetweenPoints() + 2 * model->getPointsRadius()  - adjustedCurveRect.width() + 2  * horizontalMargin + 2 * model->getCurvesStartingMargin();
}

int ChartView::getHorizantalScrollBarPageStep()
{
    return contentsRect().width();
}

int ChartView::getHorizontalScrollBarSingleStep()
{
    return model->getDistanceBetweenPoints() * 0.8 ;
}

int ChartView::getVerticalScrollBarRange()
{
    return getDrawingArea(0).height() * rowsCount - contentsRect().height();
}

int ChartView::getVerticalScrollBarPageStep()
{
    return contentsRect().height();
}

int ChartView::getVerticalScrollBarSingleStep()
{
    return firstDrawingArea.height();
}

QPointF ChartView::getConvertedPoint(int chartIndex, int curveIndex, int pointIndex)
{
    return QPointF(getXcordinateOnView(chartIndex, pointIndex) , getYcordinateOnView(chartIndex, model->getPointY(chartIndex, curveIndex, pointIndex + startingIndex)));
}

int ChartView::getIndexFromCurserPosX(QRect rect, int curserX) const
{
    int adjustedCurserX(curserX - rect.x() - model->getCurvesStartingMargin() - horizontalMargin + startingPixel + model->getPointsRadius());

    if (adjustedCurserX < 0 || adjustedCurserX % model->getDistanceBetweenPoints() > model->getPointsRadius() * 2)
        return -1;

    int index (adjustedCurserX / model->getDistanceBetweenPoints() + startingIndex);

    if (index < model->getPointCount())
        return index;

    return -1;
}

float ChartView::getXcordinateOnView(int chartIndex, int index) const
{
    return  model->getDistanceBetweenPoints() * index + adjustedCurveRect.x() + horizontalMargin + model->getCurvesStartingMargin() - startingPixel;
}

QRect ChartView::getDrawingArea(int chartIndex) const
{
    return getChartArea(chartIndex).adjusted(model->getKeysColumnWidth() + model->getAxisColumnWidth(), 0, 0, 0);
}

QRect ChartView::getChartArea(int chartIndex) const
{
    int columnIndex(chartIndex % model->getChartColumCount());
    int rowIndex(chartIndex / model->getChartColumCount() - startingRowIndex);

    QRect chartArea (contentsRect().x() + columnIndex * contentsRect().width() / model->getChartColumCount() , contentsRect().y() + rowIndex * model->getChartHeight()  - startingRowPixel, contentsRect().width() / model->getChartColumCount(), model->getChartHeight());

    return chartArea;
}

int ChartView::getPointsCountInView() const
{
    return 1 + adjustedCurveRect.width() / model->getDistanceBetweenPoints();
}

float ChartView::getYcordinateOnRect(QRect actualChart, int chartIndex, float value) const
{
    float bY (actualChart.y() + actualChart.height() * (model->getMaxY(chartIndex) / (model->getMaxY(chartIndex) - model->getMinY(chartIndex))));
    float aY (-((actualChart.height() -verticalMargin * 2 - model->getPointsRadius() * 2) / (model->getMaxY(chartIndex) - model->getMinY(chartIndex))) );

    return  aY * value + bY;
}


float ChartView::getYcordinateOnView(int chartIndex, int value)
{
    float bY (adjustedCurveRect.y() + adjustedCurveRect.height() * (model->getMaxY(chartIndex) / (model->getMaxY(chartIndex) - model->getMinY(chartIndex))));
    float aY (-((adjustedCurveRect.height() -verticalMargin * 2 - model->getPointsRadius() * 2) / (model->getMaxY(chartIndex) - model->getMinY(chartIndex))) );

    return  aY * value + bY;
}

void ChartView::paintEvent(QPaintEvent * event)
{

    if (!model)
        return;

    firstDrawingArea = getDrawingArea(0);
    rowsCountOnView =  contentsRect().height() / model->getChartHeight() + 1;
    rowsCount = model->getChartCount() % model->getChartColumCount() == 0 ? model->getChartCount() / model->getChartColumCount() : model->getChartCount() / model->getChartColumCount() + 1;

    keysColumnWidth = model->getKeysColumnWidth();
    axisColumnWidth = model->getAxisColumnWidth();

    QPen pen;
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    scrollBareUpdate();

    int startingChartIndex (startingRowIndex * model->getChartColumCount());

    for (int chartIndex(startingChartIndex) ; chartIndex <= (rowsCountOnView + 1) * model->getChartColumCount() + startingChartIndex && chartIndex < model->getChartCount() ; chartIndex++)
    {
        adjustedCurveRect = getDrawingArea(chartIndex);
        QRect chartArea (getChartArea(chartIndex));

        QRect keysRect(chartArea);
        keysRect.setWidth(keysColumnWidth);

        QRect adjustedKeysRect(keysRect.adjusted(0, verticalMargin, 0, - verticalMargin));

        QRect axisRect(chartArea);
        axisRect.adjust(keysColumnWidth, 0, 0, 0);
        axisRect.setWidth(axisColumnWidth);
        QRect adjustedAxisRect(axisRect.adjusted(0, verticalMargin , 0, - verticalMargin));

        QRect curveRect (chartArea);
        curveRect.adjust(keysColumnWidth + axisColumnWidth, 0, 0, 0);

        pen.setColor(Qt::transparent);
        painter.setPen(pen);

        painter.setBrush(QBrush(model->getCurvesColumnBackgroundColor()));
        painter.drawRect(getDrawingArea(chartIndex));

        // Axe X
        pen.setWidth(model->getAxisWidth());
        pen.setColor(model->getAxisColor());
        painter.setPen(pen);
        painter.drawLine(QPointF(curveRect.x(), getYcordinateOnView(chartIndex, 0)), QPointF(curveRect.topRight().x(), getYcordinateOnView(chartIndex, 0)));

        for (int curveIndex(0) ; curveIndex < model->getCurvesCount(chartIndex) ; curveIndex++)
        {
            // Curve
            pen.setWidth(model->getCurvesWidth());
            pen.setColor(model->getCurveColor(chartIndex, curveIndex));
            painter.setPen(pen);

            for (int i(0) ; i < getPointsCountInView() && i + 1 + startingIndex < model->getPointCount() ; i++)
                painter.drawLine(getConvertedPoint(chartIndex, curveIndex, i), getConvertedPoint(chartIndex, curveIndex, i + 1));

            if (startingIndex > 0)
                painter.drawLine(getConvertedPoint(chartIndex, curveIndex, -1), getConvertedPoint(chartIndex, curveIndex, 0));

            int lastPointIndexOnCurve(getPointsCountInView());

            if (lastPointIndexOnCurve + startingIndex < model->getPointCount() - 1)
            {
                painter.drawLine(getConvertedPoint(chartIndex, curveIndex, lastPointIndexOnCurve), getConvertedPoint(chartIndex, curveIndex, lastPointIndexOnCurve + 1));
            }

            // Points
            pen.setWidth(0);
            for (int i(0) ; i <= getPointsCountInView() && i + startingIndex < model->getPointCount(); i++)
            {
                pen.setColor(model->getPointColor(chartIndex, curveIndex, i + startingIndex));
                painter.setBrush(model->getPointColor(chartIndex, curveIndex, i + startingIndex));
                painter.setPen(pen);
                painter.drawEllipse(getConvertedPoint(chartIndex, curveIndex, i ) , model->getPointsRadius(), model->getPointsRadius());
            }
        }

        // Keys
        pen.setColor(Qt::transparent);
        painter.setPen(pen);
        painter.setBrush(QBrush(model->getKeysColumnBackgroundColor()));
        painter.drawRect(keysRect);

        painter.setBrush(QBrush(model->getAxisColumnBackgroundColor()));
        painter.drawRect(axisRect);

        // Axe Y
        pen.setWidth(model->getAxisWidth());
        pen.setColor(model->getAxisColor());
        painter.setPen(pen);
        painter.drawLine(adjustedCurveRect.topLeft().x(), adjustedCurveRect.topLeft().y() + separatorWitdh / 2 , adjustedCurveRect.bottomLeft().x(), adjustedCurveRect.bottomLeft().y() - separatorWitdh / 2);

        // Separators
        pen.setWidth(separatorWitdh);
        pen.setColor(model->getSeparatorsBackgroundColor());
        painter.setPen(pen);
        painter.drawLine(chartArea.topRight(), chartArea.bottomRight());
        painter.drawLine(chartArea.bottomLeft(), chartArea.bottomRight());

        for (int curveIndex(0) ; curveIndex < model->getCurvesCount(chartIndex) ; curveIndex++)
        {
            // CurveName
            pen.setWidth(3);
            pen.setColor(model->getCurveColor(chartIndex, curveIndex));
            painter.setPen(pen);
            QFont font = painter.font();
            font.setPixelSize(model->getFontSize());
            painter.setFont(font);
            painter.drawText(adjustedKeysRect.adjusted(0, curveIndex * 20 ,0 , 0), Qt::AlignLeft , model->getCurveName(chartIndex, curveIndex));
        }
    }

    // Hide the empty charts
    int chartIndexToHide = model->getChartCount();
    while (startingChartIndex + (rowsCountOnView + 1) * model->getChartColumCount() > chartIndexToHide)
    {
        pen.setColor(model->getSeparatorsBackgroundColor());
        painter.setPen(pen);
        painter.setBrush(QBrush(model->getSeparatorsBackgroundColor()));
        painter.drawRect(getChartArea(chartIndexToHide));
        chartIndexToHide ++;
    }
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (! contentsRect().contains(event->pos()))
        return;

    QRect actualChart;
    int chartIndex;

    for (int i(0) ; i < model->getChartCount() ; i++)
    {
        if (getDrawingArea(i).contains(event->pos()))
        {
            actualChart = getDrawingArea(i);
            chartIndex = i;
            break;
        }
    }

    if (actualChart.isNull())
        return;

    QRect curserRect(event->x() - 10, event->y() - 10 , 20, 20);

    QStringList toolTips;

    int pointIndex = getIndexFromCurserPosX(actualChart, event->x());

    if (pointIndex != -1)
    {
        for (int curveIndex(0) ; curveIndex < model->getCurvesCount(chartIndex) ; curveIndex++)
        {
            if (abs(event->y() - getYcordinateOnRect(actualChart, chartIndex, model->getPointY(chartIndex, curveIndex, pointIndex))) <= model->getPointsRadius())
                toolTips.push_back(model->getTooltip(chartIndex, curveIndex, pointIndex));
        }
    }

    setToolTip(toolTips.join('\n'));
}

void ChartView::onDataChanged()
{
    update();
    scrollBareUpdate();
}

void ChartView::ensureVisible(int position)
{
    startingIndex = position / model->getDistanceBetweenPoints();

    if (startingIndex >= model->getPointCount())
        startingIndex = model->getPointCount()-1;

    startingPixel = position - startingIndex * model->getDistanceBetweenPoints();
    update();
}

void ChartView::ensureVerticalVisible(int position)
{
    startingRowIndex = position / firstDrawingArea.height();

    if (startingRowIndex >= rowsCount)
        startingRowIndex = rowsCount - 1;

    startingRowPixel = position - startingRowIndex * firstDrawingArea.height();
    update();
}

