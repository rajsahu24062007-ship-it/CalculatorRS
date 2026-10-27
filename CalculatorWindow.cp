#include "CalculatorWindow.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <map>

constexpr double PI_VAL = 3.14159265358979323846;
constexpr double E_VAL  = 2.71828182845904523536;

CalculatorWindow::CalculatorWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
    setWindowTitle("Swapnil's Calculator - Information Theory & Code Lab");
    setFixedSize(700, 680);
}

void CalculatorWindow::setupUi() {
    auto *centralWidget = new QWidget(this);
    auto *rootLayout = new QVBoxLayout(centralWidget);
    rootLayout->setContentsMargins(18, 18, 18, 18);
    rootLayout->setSpacing(12);

    // Header with Logo and Title
    auto *headerLayout = new QHBoxLayout();
    
    auto *logoLabel = new QLabel("Ω", this);
    logoLabel->setObjectName("brandLogo");
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel->setFixedSize(42, 42);

    auto *titleLayout = new QVBoxLayout();
    titleLayout->setSpacing(2);
    auto *titleText = new QLabel("Swapnil's Calculator", this);
    titleText->setObjectName("brandTitle");
    auto *subtitleText = new QLabel("Information Theory & Code Lab", this);
    subtitleText->setObjectName("brandSubtitle");
    titleLayout->addWidget(titleText);
    titleLayout->addWidget(subtitleText);

    headerLayout->addWidget(logoLabel);
    headerLayout->addLayout(titleLayout);
    headerLayout->addStretch();

    // Tabs
    auto *tabWidget = new QTabWidget(this);
    tabWidget->addTab(createScientificTab(), "Scientific Calc");
    tabWidget->addTab(createEntropyTab(), "ƒ Entropy Suite");

    rootLayout->addLayout(headerLayout);
    rootLayout->addWidget(tabWidget);
    setCentralWidget(centralWidget);

    // Modern Neon Dark Styling
    setStyleSheet(R"(
        QMainWindow, QWidget {
            background-color: #080d19;
            color: #f8fafc;
            font-family: 'Segoe UI', Arial, sans-serif;
            font-size: 13px;
        }
        #brandLogo {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #06b6d4, stop:1 #3b82f6);
            color: #ffffff;
            font-size: 22px;
            font-weight: bold;
            border-radius: 10px;
        }
        #brandTitle {
            font-size: 17px;
            font-weight: bold;
            color: #ffffff;
        }
        #brandSubtitle {
            font-size: 12px;
            color: #8292ab;
        }
        QTabWidget::pane {
            border: 1px solid #1f2d47;
            background: #0e1626;
            border-radius: 14px;
            padding: 10px;
        }
        QTabBar::tab {
            background: #141e33;
            color: #8292ab;
            font-weight: bold;
            padding: 8px 18px;
            margin-right: 4px;
            border-top-left-radius: 8px;
            border-top-right-radius: 8px;
        }
        QTabBar::tab:selected {
            background: #1f2d47;
            color: #06b6d4;
            border-bottom: 2px solid #06b6d4;
        }
        QLineEdit {
            background-color: #09101c;
            border: 1px solid #1f2d47;
            border-radius: 8px;
            padding: 8px 12px;
            color: #ffffff;
            font-size: 14px;
        }
        QLineEdit:focus {
            border: 1px solid #06b6d4;
        }
        QPushButton {
            background-color: #141e33;
            border: 1px solid #1f2d47;
            border-radius: 8px;
            color: #f8fafc;
            font-weight: 600;
            font-size: 14px;
            min-height: 42px;
        }
        QPushButton:hover { background-color: #1e2c47; }
        QPushButton:pressed { background-color: #253759; }
        QPushButton[type="op"] {
            background-color: #1b2640;
            color: #06b6d4;
            font-size: 16px;
        }
        QPushButton[type="danger"] {
            background-color: rgba(244, 63, 94, 0.15);
            color: #f43f5e;
            border: 1px solid rgba(244, 63, 94, 0.3);
        }
        QPushButton[type="danger"]:hover {
            background-color: rgba(244, 63, 94, 0.25);
        }
        QPushButton[type="equals"] {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #06b6d4, stop:1 #3b82f6);
            color: #ffffff;
            font-weight: bold;
            border: none;
        }
        QPushButton[type="degPill"] {
            background: rgba(6, 182, 212, 0.15);
            border: 1px solid rgba(6, 182, 212, 0.4);
            color: #06b6d4;
            font-size: 11px;
            font-weight: bold;
            border-radius: 6px;
            min-height: 22px;
            max-height: 22px;
            padding: 2px 10px;
        }
        QGroupBox {
            border: 1px solid #1f2d47;
            border-radius: 10px;
            margin-top: 10px;
            padding-top: 10px;
            font-weight: bold;
            color: #06b6d4;
        }
    )");
}

QWidget* CalculatorWindow::createScientificTab() {
    auto *widget = new QWidget(this);
    auto *layout = new QVBoxLayout(widget);
    layout->setSpacing(10);

    // Screen Box
    auto *screenFrame = new QFrame(this);
    screenFrame->setStyleSheet("background-color: #09101c; border: 1px solid #1f2d47; border-radius: 12px;");
    auto *screenLayout = new QVBoxLayout(screenFrame);
    screenLayout->setContentsMargins(14, 8, 14, 8);

    // Status bar inside screen
    auto *topStatusLayout = new QHBoxLayout();
    degRadToggleBtn = new QPushButton("• DEG", this);
    degRadToggleBtn->setProperty("type", "degPill");
    connect(degRadToggleBtn, &QPushButton::clicked, this, &CalculatorWindow::onToggleAngleUnit);

    statusLabel = new QLabel("Ready", this);
    statusLabel->setStyleSheet("color: #8292ab; font-size: 11px; font-style: italic;");
    
    topStatusLayout->addWidget(degRadToggleBtn);
    topStatusLayout->addStretch();
    topStatusLayout->addWidget(statusLabel);

    historyLabel = new QLabel("", this);
    historyLabel->setAlignment(Qt::AlignRight);
    historyLabel->setStyleSheet("color: #8292ab; font-size: 14px; min-height: 18px; border: none;");

    displayLabel = new QLabel("0", this);
    displayLabel->setAlignment(Qt::AlignRight);
    displayLabel->setStyleSheet("color: #ffffff; font-size: 32px; font-weight: bold; min-height: 44px; border: none;");

    screenLayout->addLayout(topStatusLayout);
    screenLayout->addWidget(historyLabel);
    screenLayout->addWidget(displayLabel);
    layout->addWidget(screenFrame);

    // Keypad Grid (7 columns layout)
    auto *grid = new QGridLayout();
    grid->setSpacing(6);

    // Row 1: sin, cos, tan, AC, DEL, (, )
    grid->addWidget(createButton("sin"), 0, 0);
    grid->addWidget(createButton("cos"), 0, 1);
    grid->addWidget(createButton("tan"), 0, 2);
    grid->addWidget(createButton("AC", "danger"), 0, 3);
    grid->addWidget(createButton("DEL", "danger"), 0, 4);
    grid->addWidget(createButton("(", "op"), 0, 5);
    grid->addWidget(createButton(")", "op"), 0, 6);

    // Row 2: cosec, sec, cot, 7, 8, 9, /
    grid->addWidget(createButton("cosec"), 1, 0);
    grid->addWidget(createButton("sec"), 1, 1);
    grid->addWidget(createButton("cot"), 1, 2);
    grid->addWidget(createButton("7"), 1, 3);
    grid->addWidget(createButton("8"), 1, 4);
    grid->addWidget(createButton("9"), 1, 5);
    grid->addWidget(createButton("/", "op"), 1, 6);

    // Row 3: ln, log10, log2, 4, 5, 6, *
    grid->addWidget(createButton("ln"), 2, 0);
    grid->addWidget(createButton("log10"), 2, 1);
    grid->addWidget(createButton("log2"), 2, 2);
    grid->addWidget(createButton("4"), 2, 3);
    grid->addWidget(createButton("5"), 2, 4);
    grid->addWidget(createButton("6"), 2, 5);
    grid->addWidget(createButton("*", "op"), 2, 6);

    // Row 4: x², xʸ, √x, 1, 2, 3, -
    grid->addWidget(createButton("x²"), 3, 0);
    grid->addWidget(createButton("xʸ", "op"), 3, 1);
    grid->addWidget(createButton("√x"), 3, 2);
    grid->addWidget(createButton("1"), 3, 3);
    grid->addWidget(createButton("2"), 3, 4);
    grid->addWidget(createButton("3"), 3, 5);
    grid->addWidget(createButton("-", "op"), 3, 6);

    // Row 5: π, e, 1/x, ±, 0, ., +
    grid->addWidget(createButton("π"), 4, 0);
    grid->addWidget(createButton("e"), 4, 1);
    grid->addWidget(createButton("1/x"), 4, 2);
    grid->addWidget(createButton("±"), 4, 3);
    grid->addWidget(createButton("0"), 4, 4);
    grid->addWidget(createButton("."), 4, 5);
    grid->addWidget(createButton("+", "op"), 4, 6);

    // Row 6: |x|, %, = (Calculate spanning 5 columns)
    grid->addWidget(createButton("|x|"), 5, 0);
    grid->addWidget(createButton("%", "op"), 5, 1);
    auto *equalsBtn = createButton("= (Calculate)", "equals");
    grid->addWidget(equalsBtn, 5, 2, 1, 5);

    layout->addLayout(grid);
    return widget;
}

QWidget* CalculatorWindow::createEntropyTab() {
    auto *widget = new QWidget(this);
    auto *layout = new QVBoxLayout(widget);
    layout->setSpacing(14);

    // Section 1: Probability Distribution
    auto *probTitle = new QLabel("<b>Shannon Entropy H(X) from Probabilities</b>", this);
    probTitle->setStyleSheet("color: #06b6d4; font-size: 14px;");
    auto *probSub = new QLabel("Enter discrete probabilities or frequencies (e.g. 0.5, 0.25, 0.25 or 1, 1, 2):", this);
    probSub->setStyleSheet("color: #8292ab;");

    probInput = new QLineEdit("0.5, 0.25, 0.25", this);
    auto *calcProbBtn = new QPushButton("Compute Information Entropy", this);
    calcProbBtn->setProperty("type", "equals");
    connect(calcProbBtn, &QPushButton::clicked, this, &CalculatorWindow::onComputeProbEntropy);

    auto *probGrid = new QGridLayout();
    probBitsLabel = new QLabel("--", this);
    probNatsLabel = new QLabel("--", this);
    probMaxLabel  = new QLabel("--", this);
    probEffLabel  = new QLabel("--", this);

    auto styleStat = [](QLabel *l) {
        l->setStyleSheet("color: #06b6d4; font-size: 15px; font-weight: bold; background: #09101c; border: 1px solid #1f2d47; border-radius: 6px; padding: 6px;");
        l->setAlignment(Qt::AlignCenter);
    };
    styleStat(probBitsLabel); styleStat(probNatsLabel); styleStat(probMaxLabel); styleStat(probEffLabel);

    probGrid->addWidget(new QLabel("Entropy H(X) [bits]:"), 0, 0); probGrid->addWidget(probBitsLabel, 0, 1);
    probGrid->addWidget(new QLabel("Entropy [nats]:"), 0, 2);       probGrid->addWidget(probNatsLabel, 0, 3);
    probGrid->addWidget(new QLabel("Max Entropy:"), 1, 0);          probGrid->addWidget(probMaxLabel, 1, 1);
    probGrid->addWidget(new QLabel("Efficiency:"), 1, 2);           probGrid->addWidget(probEffLabel, 1, 3);

    layout->addWidget(probTitle);
    layout->addWidget(probSub);
    layout->addWidget(probInput);
    layout->addWidget(calcProbBtn);
    layout->addLayout(probGrid);

    layout->addSpacing(10);

    // Section 2: Symbol & Text Entropy
    auto *textTitle = new QLabel("<b>Symbol & Text Entropy Lab</b>", this);
    textTitle->setStyleSheet("color: #06b6d4; font-size: 14px;");
    auto *textSub = new QLabel("Calculate bits-per-symbol information and unique alphabet metrics from raw text:", this);
    textSub->setStyleSheet("color: #8292ab;");

    stringInput = new QLineEdit("Swapnil Information Lab", this);
    auto *calcStrBtn = new QPushButton("Analyze String Entropy", this);
    calcStrBtn->setProperty("type", "equals");
    connect(calcStrBtn, &QPushButton::clicked, this, &CalculatorWindow::onComputeStringEntropy);

    auto *strGrid = new QGridLayout();
    strRateLabel     = new QLabel("--", this);
    strTotalLabel    = new QLabel("--", this);
    strAlphabetLabel = new QLabel("--", this);

    styleStat(strRateLabel); styleStat(strTotalLabel); styleStat(strAlphabetLabel);

    strGrid->addWidget(new QLabel("Bits / Character:"), 0, 0); strGrid->addWidget(strRateLabel, 0, 1);
    strGrid->addWidget(new QLabel("Total Information:"), 0, 2); strGrid->addWidget(strTotalLabel, 0, 3);
    strGrid->addWidget(new QLabel("Alphabet Size:"), 1, 0);    strGrid->addWidget(strAlphabetLabel, 1, 1);

    layout->addWidget(textTitle);
    layout->addWidget(textSub);
    layout->addWidget(stringInput);
    layout->addWidget(calcStrBtn);
    layout->addLayout(strGrid);

    layout->addStretch();

    // Run startup calculation
    onComputeProbEntropy();
    onComputeStringEntropy();

    return widget;
}

QPushButton* CalculatorWindow::createButton(const QString &text, const QString &type) {
    auto *btn = new QPushButton(text, this);
    btn->setProperty("type", type);

    if (text == "AC") connect(btn, &QPushButton::clicked, this, &CalculatorWindow::onClearAll);
    else if (text == "DEL") connect(btn, &QPushButton::clicked, this, &CalculatorWindow::onBackspace);
    else if (text == "±") connect(btn, &QPushButton::clicked, this, &CalculatorWindow::onToggleSign);
    else if (text == "= (Calculate)") connect(btn, &QPushButton::clicked, this, &CalculatorWindow::onEqualsClicked);
    else if (text == "+" || text == "-" || text == "*" || text == "/" || text == "%" || text == "xʸ") {
        connect(btn, &QPushButton::clicked, this, &CalculatorWindow::onOperatorClicked);
    } else if (text == "sin" || text == "cos" || text == "tan" || text == "cosec" || 
               text == "sec" || text == "cot" || text == "ln"  || text == "log10" || 
               text == "log2" || text == "√x" || text == "x²" || text == "1/x" || 
               text == "|x|" || text == "π" || text == "e") {
        connect(btn, &QPushButton::clicked, this, &CalculatorWindow::onFunctionClicked);
    } else {
        connect(btn, &QPushButton::clicked, this, &CalculatorWindow::onDigitClicked);
    }

    return btn;
}

void CalculatorWindow::onDigitClicked() {
    auto *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    QString txt = btn->text();

    if (resetDisplayOnNextInput) {
        currentInput = (txt == ".") ? "0." : txt;
        resetDisplayOnNextInput = false;
    } else {
        if (txt == "." && currentInput.contains(".")) return;
        if (currentInput == "0" && txt != ".") currentInput = txt;
        else currentInput += txt;
    }
    displayLabel->setText(currentInput);
    statusLabel->setText("Calculating...");
}

void CalculatorWindow::onClearAll() {
    currentInput = "0";
    pendingOperator = "";
    storedOperand = 0.0;
    historyLabel->setText("");
    displayLabel->setText("0");
    statusLabel->setText("Ready");
    resetDisplayOnNextInput = false;
}

void CalculatorWindow::onBackspace() {
    if (currentInput.length() > 1) {
        currentInput.chop(1);
    } else {
        currentInput = "0";
    }
    displayLabel->setText(currentInput);
}

void CalculatorWindow::onToggleSign() {
    double val = currentInput.toDouble();
    if (val != 0.0) {
        val = -val;
        currentInput = QString::number(val, 'g', 10);
        displayLabel->setText(currentInput);
    }
}

void CalculatorWindow::onToggleAngleUnit() {
    isDegreeMode = !isDegreeMode;
    degRadToggleBtn->setText(isDegreeMode ? "• DEG" : "• RAD");
    statusLabel->setText(isDegreeMode ? "Degree Mode" : "Radian Mode");
}

double CalculatorWindow::toRadians(double value) const {
    return isDegreeMode ? (value * PI_VAL / 180.0) : value;
}

void CalculatorWindow::onFunctionClicked() {
    auto *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    QString fn = btn->text();

    if (fn == "π") {
        currentInput = QString::number(PI_VAL, 'g', 10);
        displayLabel->setText(currentInput);
        resetDisplayOnNextInput = true;
        return;
    }
    if (fn == "e") {
        currentInput = QString::number(E_VAL, 'g', 10);
        displayLabel->setText(currentInput);
        resetDisplayOnNextInput = true;
        return;
    }

    double val = currentInput.toDouble();
    double res = 0.0;
    bool error = false;

    if (fn == "sin") res = std::sin(toRadians(val));
    else if (fn == "cos") res = std::cos(toRadians(val));
    else if (fn == "tan") res = std::tan(toRadians(val));
    else if (fn == "cosec") {
        double s = std::sin(toRadians(val));
        if (std::abs(s) < 1e-15) error = true; else res = 1.0 / s;
    }
    else if (fn == "sec") {
        double c = std::cos(toRadians(val));
        if (std::abs(c) < 1e-15) error = true; else res = 1.0 / c;
    }
    else if (fn == "cot") {
        double s = std::sin(toRadians(val));
        double c = std::cos(toRadians(val));
        if (std::abs(s) < 1e-15) error = true; else res = c / s;
    }
    else if (fn == "ln") {
        if (val <= 0) error = true; else res = std::log(val);
    }
    else if (fn == "log10") {
        if (val <= 0) error = true; else res = std::log10(val);
    }
    else if (fn == "log2") {
        if (val <= 0) error = true; else res = std::log2(val);
    }
    else if (fn == "√x") {
        if (val < 0) error = true; else res = std::sqrt(val);
    }
    else if (fn == "x²") res = std::pow(val, 2);
    else if (fn == "1/x") {
        if (std::abs(val) < 1e-15) error = true; else res = 1.0 / val;
    }
    else if (fn == "|x|") res = std::abs(val);

    historyLabel->setText(QString("%1(%2)").arg(fn).arg(currentInput));
    if (error) {
        displayLabel->setText("Error");
        currentInput = "0";
    } else {
        currentInput = QString::number(res, 'g', 10);
        displayLabel->setText(currentInput);
    }
    resetDisplayOnNextInput = true;
    statusLabel->setText("Done");
}

void CalculatorWindow::onOperatorClicked() {
    auto *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    QString op = btn->text();

    storedOperand = currentInput.toDouble();
    pendingOperator = (op == "xʸ") ? "^" : op;
    historyLabel->setText(QString("%1 %2").arg(currentInput).arg(pendingOperator));
    resetDisplayOnNextInput = true;
    statusLabel->setText("Operator set");
}

void CalculatorWindow::onEqualsClicked() {
    if (pendingOperator.isEmpty()) return;

    double secondOperand = currentInput.toDouble();
    double result = 0.0;
    bool error = false;

    if (pendingOperator == "+") result = storedOperand + secondOperand;
    else if (pendingOperator == "-") result = storedOperand - secondOperand;
    else if (pendingOperator == "*") result = storedOperand * secondOperand;
    else if (pendingOperator == "/") {
        if (secondOperand == 0.0) error = true;
        else result = storedOperand / secondOperand;
    }
    else if (pendingOperator == "^") result = std::pow(storedOperand, secondOperand);
    else if (pendingOperator == "%") result = std::fmod(storedOperand, secondOperand);

    historyLabel->setText(QString("%1 %2 %3 =").arg(storedOperand).arg(pendingOperator).arg(secondOperand));
    if (error) {
        displayLabel->setText("Error");
        currentInput = "0";
    } else {
        currentInput = QString::number(result, 'g', 10);
        displayLabel->setText(currentInput);
    }

    pendingOperator = "";
    resetDisplayOnNextInput = true;
    statusLabel->setText("Ready");
}

// Information Theory Engine
double CalculatorWindow::calculateShannonEntropy(const std::vector<double> &probs) const {
    double h = 0.0;
    for (double p : probs) {
        if (p > 0.0) h -= p * std::log2(p);
    }
    return h;
}

void CalculatorWindow::onComputeProbEntropy() {
    QString raw = probInput->text();
    QStringList tokens = raw.split(QRegExp("[, ]+"), Qt::SkipEmptyParts);
    std::vector<double> values;
    double sum = 0.0;

    for (const QString &t : tokens) {
        bool ok = false;
        double v = t.toDouble(&ok);
        if (ok && v >= 0.0) {
            values.push_back(v);
            sum += v;
        }
    }

    if (values.empty() || sum <= 0.0) {
        probBitsLabel->setText("Invalid input");
        return;
    }

    std::vector<double> probs;
    for (double v : values) probs.push_back(v / sum);

    double h_bits = calculateShannonEntropy(probs);
    double h_nats = h_bits * std::log(2.0);
    double h_max = std::log2(static_cast<double>(probs.size()));
    double eff = (h_max > 0.0) ? (h_bits / h_max) * 100.0 : 100.0;

    probBitsLabel->setText(QString::number(h_bits, 'f', 4) + " bits");
    probNatsLabel->setText(QString::number(h_nats, 'f', 4) + " nats");
    probMaxLabel->setText(QString::number(h_max, 'f', 4) + " bits");
    probEffLabel->setText(QString::number(eff, 'f', 1) + "%");
}

void CalculatorWindow::onComputeStringEntropy() {
    QString text = stringInput->text();
    if (text.isEmpty()) {
        strRateLabel->setText("0 bits");
        strTotalLabel->setText("0 bits");
        strAlphabetLabel->setText("0");
        return;
    }

    std::map<QChar, int> freq;
    for (const QChar &ch : text) freq[ch]++;

    double totalChars = static_cast<double>(text.length());
    std::vector<double> probs;
    for (const auto &[ch, count] : freq) {
        probs.push_back(static_cast<double>(count) / totalChars);
    }

    double h = calculateShannonEntropy(probs);
    double totalBits = h * totalChars;

    strRateLabel->setText(QString::number(h, 'f', 4) + " bits/char");
    strTotalLabel->setText(QString::number(totalBits, 'f', 1) + " bits");
    strAlphabetLabel->setText(QString::number(freq.size()));
}