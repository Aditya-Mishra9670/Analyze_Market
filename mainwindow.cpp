#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QFileDialog>

#include <algorithm>
#include <cmath>
#include <map>
const QString expectedHeader = "Date,Open,High,Low,Close,Adj Close,Volume";
const QString requiredStructure = 
    "Date,Open,High,Low,Close,Adj Close,Volume\n"
    "2024-01-01,150.0,151.0,149.0,150.5,150.3,1000000\n"
    "2024-01-02,152.0,153.0,151.0,152.5,152.3,1100000";

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->analyzeButton, &QPushButton::clicked, this, &MainWindow::on_analyzeButton_clicked);
    connect(ui->browseButton, &QPushButton::clicked, this, &MainWindow::on_browseButton_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_browseButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select CSV File", "", "CSV Files (*.csv)");
    if (!filePath.isEmpty()) {
        selectedCSVPath = filePath;
        ui->fileLineEdit->setText(filePath); // Show path in UI
    }
}


void MainWindow::on_analyzeButton_clicked()
{
    QString path = selectedCSVPath;
    if (path.isEmpty()) {
        QMessageBox::warning(this, "No file selected", "Please select a CSV file first.");
        return;
    }

    loadCSV(path);

    double mean = 0, variance = 0, median = 0, mode = 0;
    calculateStatistics(mean, variance, median, mode);

    ui->meanLineEdit->setText(QString::number(mean));
    ui->varianceLineEdit->setText(QString::number(variance));
    ui->medianLineEdit->setText(QString::number(median));
    ui->modeLineEdit->setText(QString::number(mode));

    QVector<double> dailyMeans;
    for (const auto &entry : marketData) {
        dailyMeans.append((entry.open + entry.close) / 2.0);
    }

    plotChart(dailyMeans);
}

void MainWindow::loadCSV(const QString &filePath)
{
    marketData.clear();
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open file.");
        return;
    }

    QTextStream in(&file);
    QString headerline = in.readLine().trimmed();
    if (headerline != expectedHeader) {
        QMessageBox::warning(this, "Invalid File", "The CSV file does not match the expected structure:\n" + requiredStructure);
        file.close();
        return;
    }
    
    QString header = in.readLine();  // Skip header

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList tokens = line.split(',');

        if (tokens.size() != 7)
            continue;

        MarketData data;
        data.date = QDate::fromString(tokens[0], "yyyy-MM-dd");
        data.open = tokens[1].toDouble();
        data.high = tokens[2].toDouble();
        data.low = tokens[3].toDouble();
        data.close = tokens[4].toDouble();
        data.adjClose = tokens[5].toDouble();
        data.volume = tokens[6].toDouble();

        marketData.append(data);
    }

    file.close();
}

void MainWindow::calculateStatistics(double &mean, double &variance, double &median, double &mode)
{
    QVector<double> closes;
    for (const auto &entry : marketData)
        closes.append(entry.close);

    if (closes.isEmpty()) return;

    std::sort(closes.begin(), closes.end());
    double sum = std::accumulate(closes.begin(), closes.end(), 0.0);
    mean = sum / closes.size();

    variance = std::accumulate(closes.begin(), closes.end(), 0.0, [mean](double acc, double val) {
        return acc + (val - mean) * (val - mean);
    }) / closes.size();

    // Median
    if (closes.size() % 2 == 0)
        median = (closes[closes.size() / 2 - 1] + closes[closes.size() / 2]) / 2;
    else
        median = closes[closes.size() / 2];

    // Mode
    std::map<double, int> freq;
    for (double val : closes)
        freq[val]++;

    int maxFreq = 0;
    for (const auto &[val, count] : freq)
        if (count > maxFreq)
            maxFreq = count, mode = val;
}

void MainWindow::plotChart(const QVector<double> &dailyMeans)
{
    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < dailyMeans.size(); ++i)
        series->append(i, dailyMeans[i]);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Daily Average Mean (Open + Close / 2)");

    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Days");
    axisX->setLabelFormat("%d");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Average Price");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Replace the placeholder widget
    QLayoutItem *child;
    while ((child = ui->verticalLayout->takeAt(1)) != nullptr) {
        delete child->widget();
        delete child;
    }

    ui->verticalLayout->addWidget(chartView);
}
