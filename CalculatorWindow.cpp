#include "CalculatorWindow.h"
#include <cmath>
#include <stdexcept>
#include <numeric>
#include <QDir>
#include <QUrl>

#if !HAS_WEBENGINE
#include <QLabel>
#endif

// --- Entropy & Information Theory Calculations ---

double EntropyEngine::binaryEntropy(double p) {
    if (p < 0.0 || p > 1.0) throw std::out_of_range("p must be in [0, 1]");
    if (p == 0.0 || p == 1.0) return 0.0;
    return -(p * std::log2(p) + (1.0 - p) * std::log2(1.0 - p));
}

double EntropyEngine::shannonEntropy(const std::vector<double>& probs) {
    double h = 0.0;
    for (double p : probs) {
        if (p < 0.0 || p > 1.0) throw std::out_of_range("Probabilities must be in [0, 1]");
        if (p > 0.0) {
            h -= p * std::log2(p);
        }
    }
    return h;
}

double EntropyEngine::jointEntropy(const std::vector<std::vector<double>>& mat) {
    double h = 0.0;
    for (const auto& row : mat) {
        for (double p : row) {
            if (p > 0.0) h -= p * std::log2(p);
        }
    }
    return h;
}

double EntropyEngine::conditionalEntropy(const std::vector<std::vector<double>>& mat) {
    // H(Y|X) = H(X,Y) - H(X)
    double hXY = jointEntropy(mat);
    std::vector<double> pX;
    for (const auto& row : mat) {
        double sum = 0.0;
        for (double val : row) sum += val;
        pX.push_back(sum);
    }
    double hX = shannonEntropy(pX);
    return hXY - hX;
}

double EntropyEngine::mutualInformation(const std::vector<std::vector<double>>& mat) {
    // I(X;Y) = H(X) + H(Y) - H(X,Y)
    std::vector<double> pX(mat.size(), 0.0);
    std::vector<double> pY(mat[0].size(), 0.0);

    for (size_t i = 0; i < mat.size(); ++i) {
        for (size_t j = 0; j < mat[0].size(); ++j) {
            pX[i] += mat[i][j];
            pY[j] += mat[i][j];
        }
    }
    return shannonEntropy(pX) + shannonEntropy(pY) - jointEntropy(mat);
}

double EntropyEngine::klDivergence(const std::vector<double>& P, const std::vector<double>& Q) {
    if (P.size() != Q.size()) throw std::invalid_argument("Distributions must match in size");
    double dkl = 0.0;
    for (size_t i = 0; i < P.size(); ++i) {
        if (P[i] > 0.0) {
            if (Q[i] <= 0.0) throw std::domain_error("Q(i) must be > 0 when P(i) > 0");
            dkl += P[i] * std::log2(P[i] / Q[i]);
        }
    }
    return dkl;
}

// --- Window Lifecycle ---

CalculatorWindow::CalculatorWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Vaibhav's Calculator - Information Theory & Code Lab");
    resize(920, 840);

#if HAS_WEBENGINE
    webView = new QWebEngineView(this);
    QString htmlPath = QDir::current().filePath("index.html");
    webView->load(QUrl::fromLocalFile(htmlPath));
    setCentralWidget(webView);
#else
    QLabel *fallback = new QLabel("Open index.html directly in your browser or enable Qt WebEngine.", this);
    fallback->setAlignment(Qt::AlignCenter);
    fallback->setStyleSheet("background-color: #030712; color: #00f0ff; font-size: 16px; font-weight: bold;");
    setCentralWidget(fallback);
#endif
}

CalculatorWindow::~CalculatorWindow() = default;