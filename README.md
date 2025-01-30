💡 Note:
This README was written with the help of ChatGPT—I couldn’t find the time, and honestly, it did a better job than I could anyway! 😄

# CustomChartView
The reason I created this widget is that Qt's built-in charting modules are part of the paid Qt Commercial edition. Since I wanted to create a fully functional charting system without the costs, I decided to implement my own module using Qt5. This gives you a powerful, open-source solution that integrates seamlessly with Qt!

# 🎨 ChartView Widget – Bring Your Data to Life!

Welcome to the ChartView Widget, where data meets art in a Qt5 application! 🌟 This README will guide you through crafting an abstract chart model, implementing it like a boss, and plugging it into the ChartView class for some widget magic. Let’s roll! 🚀

---

## 🏗️ Step 1: Create Your AbstractChartModel

We’re starting with the blueprint of all chart greatness: the `AbstractChartModel`. It’s like a contract for your data—you decide how your points, curves, columns, and charts behave by implementing some juicy virtual functions.

### Functions to Implement:

#### Points
- `getPointCount()`: How many points do you want?
- `getPointY()`: Where’s the Y-coordinate for a specific point?
- `getDistanceBetweenPoints()`: Are your points socially distancing?
- `getPointColor()`: How fancy do your points look? 🎨
- `getMaxY()`: The tallest point in your chart's world.
- `getMinY()`: The lowest point (because charts have bad days too).

#### Curves
- `getCurvesCount()`: How many curves in each chart?
- `getCurveName()`: Naming curves is serious business.
- `getCurveColor()`: What color is that curve today?
- `getCurvesWidth()`: The width of the curve, nice and thick or pencil-thin?
- `getTooltip()`: Hover hints—show off some info!
- `getPointsRadius()`: How big are your points?
- `getCurvesStartingMargin()`: Give your curves some breathing room.

#### Columns
- `getKeysColumnWidth()`: How wide is the key column?
- `getAxisColumnWidth()`: Ditto for the axis column.

#### Backgrounds
- `getKeysColumnBackgroundColor()`: Pretty up the key column!
- `getCurvesColumnBackgroundColor()`: Splash some color on the curves column!
- `getAxisColumnBackgroundColor()`: Even the axis column needs love.
- `getSeparatorsBackgroundColor()`: Keep those sections distinct.

#### Charts
- `getChartCount()`: How many charts are you drawing?
- `getChartColumnCount()`: Count those chart columns.
- `getChartHeight()`: Vertical vibes only.

### 🎯 Your Job:
Inherit from `AbstractChartModel` and implement these pure virtual functions in a derived class. You’re the boss—decide how the data is structured and behaves!

---

## 🎨 Step 2: The ChartView Widget

Time to feed your custom model into the `ChartView` class. It’s like matchmaking—your model is the data brain, and `ChartView` brings it to life on the canvas.

### Meet the ChartView Class:
- The `ChartView` is a subclass of `QWidget`, designed to render your chart beautifully.
- You plug in your `AbstractChartModel` and watch it paint the data like a pro artist.

### Key Members of ChartView:
- **Model**: The data source (`AbstractChartModel *model`) powering your charts.
- **Scroll Handling**: Keeps your data visible and scroll-friendly with starting indexes, pixel offsets, and scrollbar ranges.

### Cool Methods:
- **Painting**: `paintEvent(QPaintEvent *event)` is where the real magic happens—curves, points, and all your visual elements get painted here.
- **Mouse Events**: Use `mouseMoveEvent(QMouseEvent *event)` for interactivity (e.g., tooltips).
- **Scroll Visibility**: `ensureVisible()` makes sure specific points stay on screen.

### 🎯 Your Job:
1. Instantiate your `ChartView`.
2. Set your custom model using `setModel(AbstractChartModel *value)`.
3. Add it to your widget layout and enjoy!

---

## 🚀 Step 3: Putting It All Together

Here’s a quick guide to wiring it up:

1. **Create Your Model**: Implement a derived class from `AbstractChartModel` with all the required functions. Example:

    ```cpp
    class MyCustomModel : public AbstractChartModel {
        // Implement all those juicy virtual functions here
    };
    ```

2. **Set Up ChartView**: Create an instance of `ChartView` in your widget or main window:

    ```cpp
    ChartView *chartView = new ChartView();
    ```

3. **Plug In Your Model**: Feed your model to the `ChartView`:

    ```cpp
    MyCustomModel *model = new MyCustomModel();
    chartView->setModel(model);
    ```

4. **Display It Like a Champ**: Add the `ChartView` to your layout:

    ```cpp
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    setLayout(layout);
    ```

---

## 🖼️ The Final Result

You now have a fully functional, scrollable, interactive chart rendered beautifully in your Qt5 application. Your data never looked this good before! 🎉

---

## 🧩 Bonus Features:
- Add tooltips for interactivity.
- Customize colors, margins, and chart sizes to suit your style.

---

## ⚡ Real-Time Charting? Absolutely!

This isn’t just any ordinary chart—`ChartView` listens and reacts to data updates in real time! 🕒✨

Here’s how it works:
- Your data source (a custom `AbstractChartModel`) updates its data as new information arrives.
- When that happens, you call the `onDataChanged()` slot of `ChartView`, like so:

    ```cpp
    chartView->onDataChanged();
    ```

- The `onDataChanged()` slot springs into action and tells the `ChartView` to redraw itself with the new data. It’s instant, seamless, and perfect for live, real-time data visualization. 🎨✨

This makes `ChartView` perfect for use cases like:
- **Live Streaming Data**: Think stock prices, IoT sensor readings, or live performance metrics. 📈
- **Dynamic Updates**: Adapting your chart as users interact with the app.

---

## 🎯 How to Set It Up:
1. **Connect your custom `AbstractChartModel` to the `onDataChanged()` slot in `ChartView`:**

    ```cpp
    connect(yourModel, &YourCustomModel::dataChanged, chartView, &ChartView::onDataChanged);
    ```

2. **Emit the `dataChanged` signal from your model whenever new data arrives:**

    ```cpp
    emit dataChanged();
    ```

3. The `onDataChanged()` slot will handle the rest! Your chart will redraw itself, showing the latest and greatest data in real time.
