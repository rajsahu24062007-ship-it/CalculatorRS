#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <cctype>

using namespace std;

// --- ANSI Color Codes for UI Styling ---
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string TEXT_MUTED = "\033[90m";
const string CYAN = "\033[38;5;51m";      // Accent color
const string AMBER = "\033[38;5;214m";     // Equals button / Eval
const string ROSE = "\033[38;5;197m";      // AC button
const string PURPLE = "\033[38;5;135m";    // Calculus buttons
const string EMERALD = "\033[38;5;48m";    // Matrices
const string BLUE = "\033[38;5;33m";       // Space button
const string BG_DARK = "\033[48;5;234m";   // Panel background
const string BG_BTN = "\033[48;5;236m";    // Standard button

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// --- ANSI Escape Codes for Colors ---
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string TEXT_WHITE = "\033[37m";
const string TEXT_BLACK = "\033[30m";

// Button Background Colors (matching the screenshots)
const string BG_NUM    = "\033[48;5;236m";  // Dark Grey (7, 8, 9)
const string BG_FUNC   = "\033[48;5;24m";   // Medium Blue (sin, cos, log)
const string BG_OP     = "\033[48;5;26m";   // Brighter Blue (+, -, *, /)
const string BG_ROSE   = "\033[48;5;197m";  // Pink/Rose (AC)
const string BG_AMBER  = "\033[48;5;214m";  // Yellow/Amber (=)
const string BG_PURPLE = "\033[48;5;54m";   // Purple (Def Integral, Pi)
const string BG_DARK   = "\033[48;5;234m";  // Very Dark (Backspace)

// Helper function to print a perfectly centered, colored button block
void printBtn(string label, string colorCode, int width = 9) {
    // Calculate padding to center the text
    // Note: Unicode characters (like π, √) can mess with string length in C++, 
    // but this basic padding works for most standard terminals.
    int labelLen = 0;
    for(char c : label) { if((c & 0xC0) != 0x80) labelLen++; } // Rough UTF-8 length count
    
    int padLeft = (width - labelLen) / 2;
    int padRight = width - labelLen - padLeft;
    
    cout << colorCode << (padLeft > 0 ? string(padLeft, ' ') : "") 
         << label 
         << (padRight > 0 ? string(padRight, ' ') : "") << RESET << " ";
}

// ==========================================
// 1. STANDARD CALCULATOR (7-Column Layout)
// ==========================================
void drawStandardCalculator() {
    cout << "\n--- STANDARD CALCULATOR KEYPAD ---\n\n";
    
    // Row 1
    printBtn("sin", BG_FUNC); printBtn("cos", BG_FUNC); printBtn("tan", BG_FUNC);
    printBtn("AC", BG_ROSE + BOLD); printBtn("<-", BG_DARK); printBtn("%", BG_OP); printBtn("=", BG_AMBER + TEXT_BLACK + BOLD);
    cout << "\n\n";

    // Row 2
    printBtn("sin⁻¹", BG_FUNC); printBtn("cos⁻¹", BG_FUNC); printBtn("tan⁻¹", BG_FUNC);
    printBtn("7", BG_NUM); printBtn("8", BG_NUM); printBtn("9", BG_NUM); printBtn("÷", BG_OP);
    cout << "\n\n";

    // Row 3
    printBtn("log₁₀", BG_FUNC); printBtn("log₂", BG_FUNC); printBtn("ln", BG_FUNC);
    printBtn("4", BG_NUM); printBtn("5", BG_NUM); printBtn("6", BG_NUM); printBtn("×", BG_OP);
    cout << "\n\n";

    // Row 4
    printBtn("x²", BG_FUNC); printBtn("x³", BG_FUNC); printBtn("xʸ", BG_FUNC);
    printBtn("1", BG_NUM); printBtn("2", BG_NUM); printBtn("3", BG_NUM); printBtn("-", BG_OP);
    cout << "\n\n";

    // Row 5
    printBtn("n!", BG_FUNC); printBtn("(", BG_FUNC); printBtn(")", BG_FUNC);
    printBtn("π", BG_NUM); printBtn("0", BG_NUM); printBtn(".", BG_NUM + BOLD); printBtn("+", BG_OP);
    cout << "\n\n";

    // Row 6
    printBtn("√x", BG_FUNC); printBtn("ʸ√x", BG_FUNC); printBtn("|x|", BG_FUNC);
    printBtn("^", BG_NUM); printBtn("e", BG_NUM); printBtn(",", BG_NUM); printBtn("Δ", BG_OP);
    cout << "\n\n";
}

// ==========================================
// 2. CUSTOM FORMULA (8-Column Layout)
// ==========================================
void drawCustomFormula() {
    cout << "\n--- CUSTOM FORMULA KEYPAD ---\n\n";

    // Row 1
    printBtn("7", BG_NUM); printBtn("8", BG_NUM); printBtn("9", BG_NUM); printBtn("÷", BG_OP);
    printBtn("sin", BG_FUNC); printBtn("cos", BG_FUNC); printBtn("tan", BG_FUNC); printBtn("DEG/RAD", BG_FUNC);
    cout << "\n\n";

    // Row 2
    printBtn("4", BG_NUM); printBtn("5", BG_NUM); printBtn("6", BG_NUM); printBtn("×", BG_OP);
    printBtn("sin⁻¹", BG_FUNC); printBtn("cos⁻¹", BG_FUNC); printBtn("tan⁻¹", BG_FUNC); printBtn("π", BG_FUNC);
    cout << "\n\n";

    // Row 3
    printBtn("1", BG_NUM); printBtn("2", BG_NUM); printBtn("3", BG_NUM); printBtn("-", BG_OP);
    printBtn("log", BG_FUNC); printBtn("ln", BG_FUNC); printBtn("10ˣ", BG_FUNC); printBtn("eˣ", BG_FUNC);
    cout << "\n\n";

    // Row 4
    printBtn("±", BG_NUM); printBtn("0", BG_NUM); printBtn(".", BG_NUM + BOLD); printBtn("+", BG_OP);
    printBtn("x²", BG_FUNC); printBtn("x³", BG_FUNC); printBtn("xʸ", BG_FUNC); printBtn("√x", BG_FUNC);
    cout << "\n\n";

    // Row 5 (Purple Accents)
    printBtn("Def ∫", BG_PURPLE + BOLD); printBtn("d²/dx²", BG_PURPLE + BOLD); printBtn("Π", BG_PURPLE + BOLD); 
    printBtn("³√x", BG_FUNC); printBtn("ʸ√x", BG_FUNC); printBtn("1/x", BG_FUNC); printBtn("|x|", BG_FUNC); printBtn("∞", BG_FUNC);
    cout << "\n\n";

    // Row 6
    printBtn("∫", BG_FUNC); printBtn("d/dx", BG_FUNC); printBtn("lim", BG_FUNC); printBtn("Σ", BG_FUNC);
    printBtn("n!", BG_FUNC); printBtn("(", BG_FUNC); printBtn(")", BG_FUNC); printBtn(",", BG_FUNC);
    cout << "\n\n";

    // Row 7
    printBtn("nCr", BG_FUNC); printBtn("nPr", BG_FUNC); printBtn("log₂", BG_FUNC); printBtn("i", BG_FUNC);
    printBtn("A⁻¹", BG_FUNC); printBtn("Aᵀ", BG_FUNC); printBtn("det(A)", BG_FUNC); printBtn("Δ", BG_FUNC);
    cout << "\n\n";

    // Row 8
    printBtn("x", BG_FUNC); printBtn("y", BG_FUNC); printBtn("z", BG_FUNC); printBtn("a", BG_FUNC);
    printBtn("b", BG_FUNC); printBtn("c", BG_FUNC); printBtn("e", BG_FUNC); printBtn("α", BG_FUNC);
    cout << "\n\n";

    // Row 9 (Greek Alphabet Bottom)
    printBtn("β", BG_FUNC); printBtn("θ", BG_FUNC); printBtn("λ", BG_FUNC); printBtn("μ", BG_FUNC);
    printBtn("σ", BG_FUNC); printBtn("ω", BG_FUNC); printBtn("γ", BG_FUNC); printBtn("ϕ", BG_FUNC);
    cout << "\n\n";
}

int main() {
    // Draw the two UIs
    drawStandardCalculator();
    cout << "Press Enter to see the Custom Formula layout...";
    cin.get();
    drawCustomFormula();

    return 0;
}


// ==========================================
// HISTORY MANAGER
// ==========================================
struct HistoryEntry {
    string tool, expression, result;
};

class HistoryManager {
private:
    vector<HistoryEntry> history;
public:
    void add(string t, string e, string r) {
        history.push_back({t, e, r});
    }
    void display() {
        cout << BOLD << CYAN << "\n--- Global History ---\n" << RESET;
        if (history.empty()) {
            cout << TEXT_MUTED << "No calculations performed yet.\n" << RESET;
            return;
        }
        for (auto it = history.rbegin(); it != history.rend(); ++it) {
            cout << BOLD << "[" << it->tool << "] " << RESET 
                 << it->expression << BOLD << AMBER << " = " << it->result << RESET << "\n";
        }
        cout << "\n";
    }
    void clear() {
        history.clear();
        cout << ROSE << BOLD << "All history cleared.\n" << RESET;
    }
};


// ANSI Color Codes for the Keypad
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string BLACK_TEXT = "\033[30m";
const string WHITE_TEXT = "\033[37m";

// Background Colors based on your HTML image
const string BG_NORMAL = "\033[48;5;236m";   // Standard buttons (7, 8, 9, etc.)
const string BG_SLATE = "\033[48;5;239m";    // fa-delete-left (Back) button
const string BG_ROSE = "\033[48;5;197m";     // AC (Clear) button
const string BG_BLUE = "\033[48;5;27m";      // Space/NL button
const string BG_AMBER = "\033[48;5;214m";    // Compute (=) button

// Helper function to print a formatted, colored button block
void printButton(string label, string colorCode, int width = 8) {
    int padLeft = (width - label.length()) / 2;
    int padRight = width - label.length() - padLeft;
    cout << colorCode << string(padLeft, ' ') << label << string(padRight, ' ') << RESET << "  ";
}

void drawInfoTheoryKeypad() {
    cout << "\n";
    // Row 1: 7, 8, 9, AC
    printButton("7", BG_NORMAL + WHITE_TEXT);
    printButton("8", BG_NORMAL + WHITE_TEXT);
    printButton("9", BG_NORMAL + WHITE_TEXT);
    printButton("AC", BG_ROSE + WHITE_TEXT + BOLD);
    cout << "\n\n";

    // Row 2: 4, 5, 6, Back (<-)
    printButton("4", BG_NORMAL + WHITE_TEXT);
    printButton("5", BG_NORMAL + WHITE_TEXT);
    printButton("6", BG_NORMAL + WHITE_TEXT);
    printButton("<-", BG_SLATE + WHITE_TEXT); 
    cout << "\n\n";

    // Row 3: 1, 2, 3, Space (Newline)
    printButton("1", BG_NORMAL + WHITE_TEXT);
    printButton("2", BG_NORMAL + WHITE_TEXT);
    printButton("3", BG_NORMAL + WHITE_TEXT);
    printButton("Space", BG_BLUE + WHITE_TEXT + BOLD);
    cout << "\n\n";

    // Row 4: 0, ., ,, = (Compute)
    printButton("0", BG_NORMAL + WHITE_TEXT);
    printButton(".", BG_NORMAL + WHITE_TEXT + BOLD);
    printButton(",", BG_NORMAL + WHITE_TEXT);
    printButton("=", BG_AMBER + BLACK_TEXT + BOLD);
    cout << "\n\n";
}

void handleInfoTheoryInput() {
    string matrixInput = "";
    char key;
    bool computing = false;

    while (!computing) {
        drawInfoTheoryKeypad(); // Draw the UI
        cout << "Current Matrix Data: \n" << matrixInput << "\n";
        cout << "Press a key (or '=' to compute): ";
        cin >> key;

        // This acts exactly like your HTML onclick="" events
        switch (key) {
            // Equivalent to onclick="itKey('...')"
            case '7': case '8': case '9':
            case '4': case '5': case '6':
            case '1': case '2': case '3':
            case '0': case ',':
                matrixInput += key; 
                break;
                
            // Equivalent to onclick="itDecimal()"
            case '.':
                if (matrixInput.empty() || isspace(matrixInput.back())) {
                    matrixInput += "0."; // Smart decimal prepend
                } else {
                    matrixInput += ".";
                }
                break;

            // Space (represented by 's' or '_') equivalent to onclick="itKey('\n')"
            case 's': 
            case '_':
                matrixInput += "\n";
                break;

            // Equivalent to onclick="itClear()"
            case 'c': 
            case 'C':
                matrixInput = "";
                break;

            // Equivalent to onclick="computeInfoTheory()"
            case '=':
                computing = true;
                // Call your computeInfoTheory(matrixInput) function here
                cout << "\nComputing Matrix...\n";
                break;

            default:
                cout << "Invalid key.\n";
                break;
        }
    }
}


// ==========================================
// MATH ENGINE
// ==========================================
class MathEngine {
private:
    static int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return 3;
        return 0;
    }

    static double applyOp(double a, double b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': 
                if (b == 0) throw runtime_error("Division by zero");
                return a / b;
            case '^': return pow(a, b);
            default: return 0;
        }
    }

public:
    static double evaluate(string tokens, map<string, double> variables = {}) {
        stack<double> values;
        stack<char> ops;

        for (size_t i = 0; i < tokens.length(); i++) {
            if (isspace(tokens[i])) continue;
            
            if (isalpha(tokens[i])) {
                string varName = "";
                while (i < tokens.length() && isalpha(tokens[i])) {
                    varName += tokens[i++];
                }
                i--;
                values.push(variables[varName]);
            }
            else if (isdigit(tokens[i]) || tokens[i] == '.') {
                string numStr = "";
                while (i < tokens.length() && (isdigit(tokens[i]) || tokens[i] == '.')) {
                    numStr += tokens[i++];
                }
                values.push(stod(numStr));
                i--;
            }
            else if (tokens[i] == '(') {
                ops.push(tokens[i]);
            }
            else if (tokens[i] == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    double val2 = values.top(); values.pop();
                    double val1 = values.top(); values.pop();
                    char op = ops.top(); ops.pop();
                    values.push(applyOp(val1, val2, op));
                }
                if (!ops.empty()) ops.pop();
            }
            else {
                while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {
                    double val2 = values.top(); values.pop();
                    double val1 = values.top(); values.pop();
                    char op = ops.top(); ops.pop();
                    values.push(applyOp(val1, val2, op));
                }
                ops.push(tokens[i]);
            }
        }

        while (!ops.empty()) {
            double val2 = values.top(); values.pop();
            double val1 = values.top(); values.pop();
            char op = ops.top(); ops.pop();
            values.push(applyOp(val1, val2, op));
        }

        return values.empty() ? 0 : values.top();
    }
};

// ==========================================
// UI HELPER
// ==========================================
void printHeader(string title) {
    cout << BG_DARK << CYAN << BOLD << "\n======================================================\n";
    cout << "  " << title << "\n";
    cout << "======================================================\n" << RESET;
}

// ==========================================
// MODULES
// ==========================================
void runStandardCalculator(HistoryManager& hist) {
    printHeader("STANDARD CALCULATOR");
    cout << TEXT_MUTED << "Supported: +, -, *, /, ^, ( )\n" << RESET;
    cout << "Enter expression: ";
    string expr;
    cin >> ws; getline(cin, expr);
    
    try {
        double res = MathEngine::evaluate(expr);
        cout << BOLD << AMBER << "\nResult: = " << res << "\n" << RESET;
        hist.add("Calculator", expr, to_string(res));
    } catch (const exception& e) {
        cout << ROSE << "Error: " << e.what() << "\n" << RESET;
    }
}

void runCustomFormula(HistoryManager& hist) {
    printHeader("CUSTOM FORMULA ENGINE");
    cout << "Enter formula (e.g., a+b^2-c): ";
    string formula;
    cin >> ws; getline(cin, formula);
    
    map<string, double> vars;
    string varName = "";
    for (char c : formula) {
        if (isalpha(c)) varName += c;
        else if (varName != "") {
            vars[varName] = 0;
            varName = "";
        }
    }
    if (varName != "") vars[varName] = 0;

    if (!vars.empty()) cout << "\n" << CYAN << "--- Variable Inputs ---" << RESET << "\n";
    for (auto const& [key, val] : vars) {
        cout << key << " = ";
        cin >> vars[key];
    }

    try {
        double res = MathEngine::evaluate(formula, vars);
        cout << BOLD << AMBER << "\nResult: = " << res << "\n" << RESET;
        hist.add("Formula", formula, to_string(res));
    } catch (const exception& e) {
        cout << ROSE << "Error: " << e.what() << "\n" << RESET;
    }
}

// Entropy Structures
struct Symbol { string name; double p; string code = ""; };
struct HuffNode {
    double p; string sym; HuffNode *left, *right;
    HuffNode(double prob, string s) : p(prob), sym(s), left(nullptr), right(nullptr) {}
};
struct CompareNode { bool operator()(HuffNode* const& n1, HuffNode* const& n2) { return n1->p > n2->p; } };

void shannonFanoRec(vector<Symbol>& syms, int start, int end) {
    if (start >= end) return;
    if (start == end - 1) { syms[start].code += "0"; syms[end].code += "1"; return; }
    double total = 0; for (int i = start; i <= end; ++i) total += syms[i].p;
    double sum = 0, minDiff = total; int split = start;
    for (int i = start; i < end; ++i) {
        sum += syms[i].p;
        double diff = abs(total - 2 * sum);
        if (diff < minDiff) { minDiff = diff; split = i; }
    }
    for (int i = start; i <= split; ++i) syms[i].code += "0";
    for (int i = split + 1; i <= end; ++i) syms[i].code += "1";
    shannonFanoRec(syms, start, split);
    shannonFanoRec(syms, split + 1, end);
}

void generateHuffman(HuffNode* root, string str, map<string, string>& huffmanCodes) {
    if (!root) return;
    if (root->sym != "") huffmanCodes[root->sym] = str;
    generateHuffman(root->left, str + "0", huffmanCodes);
    generateHuffman(root->right, str + "1", huffmanCodes);
}

void runEntropy(HistoryManager& hist) {
    printHeader("ENTROPY & SOURCE CODING");
    int n;
    cout << "Number of probabilities: ";
    cin >> n;
    vector<Symbol> syms(n);
    double sum = 0;
    
    cout << "Enter " << n << " probabilities separated by space:\n";
    for (int i = 0; i < n; ++i) {
        syms[i].name = "x" + to_string(i + 1);
        cin >> syms[i].p;
        sum += syms[i].p;
    }
    if (abs(sum - 1.0) > 0.001) for (int i = 0; i < n; ++i) syms[i].p /= sum;

    double hBits = 0.0, maxH = log2(n);
    for (auto& s : syms) if (s.p > 0) hBits -= s.p * log2(s.p);
    
    // Shannon-Fano
    vector<Symbol> sfSyms = syms;
    sort(sfSyms.begin(), sfSyms.end(), [](const Symbol& a, const Symbol& b) { return a.p > b.p; });
    shannonFanoRec(sfSyms, 0, sfSyms.size() - 1);
    
    // Huffman
    priority_queue<HuffNode*, vector<HuffNode*>, CompareNode> pq;
    for (auto& s : syms) pq.push(new HuffNode(s.p, s.name));
    while (pq.size() > 1) {
        HuffNode *left = pq.top(); pq.pop();
        HuffNode *right = pq.top(); pq.pop();
        HuffNode *top = new HuffNode(left->p + right->p, "");
        top->left = left; top->right = right;
        pq.push(top);
    }
    map<string, string> huffCodes;
    generateHuffman(pq.top(), "", huffCodes);

    cout << fixed << setprecision(4);
    cout << CYAN << "\nENTROPY H(X): " << BOLD << hBits << " b" << RESET << "\n";
    cout << CYAN << "MAX ENTROPY:  " << BOLD << maxH << " b" << RESET << "\n\n";

    cout << BG_DARK << " Sym | P(x)   | Shannon-Fano   | Huffman        " << RESET << "\n";
    cout << TEXT_MUTED << "------------------------------------------------" << RESET << "\n";
    for (auto& s : sfSyms) {
        cout << " " << setw(4) << left << s.name 
             << "| " << s.p << " | "
             << CYAN << setw(15) << s.code << RESET 
             << "| " << PURPLE << huffCodes[s.name] << RESET << "\n";
    }
    
    stringstream ss; ss << fixed << setprecision(4) << hBits << " b";
    hist.add("Entropy", "Probabilities Evaluated", ss.str());
}

void runProgrammer(HistoryManager& hist) {
    printHeader("PROGRAMMER");
    long long decVal;
    cout << "Enter Decimal value: ";
    cin >> decVal;
    
    cout << "\n";
    cout << CYAN << "HEX: " << BOLD << hex << uppercase << decVal << dec << RESET << "\n";
    cout << AMBER << "DEC: " << BOLD << decVal << RESET << "\n";
    cout << EMERALD << "OCT: " << BOLD << oct << decVal << dec << RESET << "\n";
    cout << BLUE << "BIN: " << BOLD << bitset<32>(decVal) << RESET << "\n";
    
    stringstream ss; ss << hex << uppercase << decVal;
    hist.add("Programmer", "DEC: " + to_string(decVal), "HEX: " + ss.str());
}

// ==========================================
// MAIN LOOP
// ==========================================
int main() {
    HistoryManager history;
    int choice;

    do {
        cout << BG_DARK << CYAN << BOLD << "\n======================================================\n";
        cout << "                RAJ'S CALCULATOR (C++)\n";
        cout << "======================================================\n" << RESET;
        
        cout << " " << CYAN << "[1]" << RESET << " Calculator\n";
        cout << " " << PURPLE << "[2]" << RESET << " Custom Formula\n";
        cout << " " << EMERALD << "[3]" << RESET << " Entropy & Source Coding\n";
        cout << " " << BLUE << "[4]" << RESET << " Programmer\n";
        cout << " " << TEXT_MUTED << "[5]" << RESET << " View History\n";
        cout << " " << ROSE << "[0]" << RESET << " Exit\n";
        cout << "\nSelect view: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: runStandardCalculator(history); break;
            case 2: runCustomFormula(history); break;
            case 3: runEntropy(history); break;
            case 4: runProgrammer(history); break;
            case 5: history.display(); break;
            case 0: cout << "\nShutting down...\n"; break;
            default: cout << ROSE << "Invalid choice.\n" << RESET;
        }
    } while (choice != 0);

    return 0;
}