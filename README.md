
# 📈 Stock Data Analysis

A modern Qt-based desktop application for analyzing stock market data from CSV files.  
Easily upload your own CSV, view key statistics (mean, variance, median, mode), and visualize trends with interactive charts.

---

## ✨ Features

- **CSV Upload:** Select and analyze your own stock data files.
- **Automatic Validation:** Ensures your CSV matches the required structure and provides clear error messages if not.
- **Statistical Analysis:** Calculates mean, variance, median, and mode for your data.
- **Data Visualization:** Displays daily mean values in a dynamic chart.
- **User-Friendly Interface:** Simple, intuitive layout with clear feedback.

---

## 📄 CSV File Structure

> **Your CSV must use this exact structure:**

```
Date,Open,High,Low,Close,Adj Close,Volume
2024-01-01,150.0,151.0,149.0,150.5,150.3,1000000
2024-01-02,152.0,153.0,151.0,152.5,152.3,1100000
...
```

- The header **must match exactly** (including spaces and order).
- Each row represents a trading day.

If your file does not match, the app will show an error and display the required format.

---



## 🚀 Getting Started

### Prerequisites

- **Qt 5 or Qt 6** (with Widgets and Charts modules)
- **CMake** (recommended) or **qmake**
- A C++17 compatible compiler

### Build Instructions

#### Using CMake

```
git clone link_of_this_repo
cd stock-data-analysis
mkdir build && cd build
cmake ..
make
./Analyze_market
```

#### Using Qt Creator

1. Open `Analyze_market.pro` or `CMakeLists.txt` in Qt Creator.
2. Configure the project (select your Qt kit).
3. Build and run.

---

## 🛠️ Usage

1. **Click "Browse"** to select your CSV file.
2. **Verify** that the file path appears in the input box.
3. **Click "Analyze"** to compute statistics and view the chart.
4. If the file format is incorrect, an error message will guide you.

---

## 📁 Project Structure

```
.
├── main.cpp
├── mainwindow.h / .cpp
├── mainwindow.ui
├── CMakeLists.txt / Analyze_market.pro
├── README.md
└── (other source files)
```

---

## ❓ Troubleshooting

- **QFileDialog not found?**  
  Ensure you have the Qt Widgets module and your build system links against it.
- **App says "No file selected"?**  
  Make sure you have chosen a file using the Browse button.
- **CSV Format Error?**  
  Double-check your CSV header and column order.

---

## 📄 License

MIT License. See [LICENSE](LICENSE) for details.

---

## 🙏 Credits

- Developed by [Your Name]
- Uses [Qt](https://www.qt.io/) for UI and charting

---

## 🤝 Contributing

Pull requests and suggestions are welcome!  
Please fork the repository and submit a PR.

---

**Enjoy analyzing your stock data!**
```

---
