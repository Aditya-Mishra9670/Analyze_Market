#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QDate>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MarketData {
public:
    QDate date;
    double open;
    double high;
    double low;
    double close;
    double adjClose;
    double volume;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_analyzeButton_clicked();
    void on_browseButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<MarketData> marketData;

    // Add this line to declare selectedCSVPath as a member variable
    QString selectedCSVPath;

    void loadCSV(const QString &filePath);
    void calculateStatistics(double &mean, double &variance, double &median, double &mode);
    void plotChart(const QVector<double> &dailyMeans);
};

#endif // MAINWINDOW_H
