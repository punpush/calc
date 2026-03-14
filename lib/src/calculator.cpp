#include <QVBoxLayout>
#include <QFont>
#include "calculator.h"

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    m_display = new QLineEdit(this);
    m_display->setReadOnly(true);
    m_display->setAlignment(Qt::AlignRight);

    auto font = m_display->font();
    font.setPointSize(20);
    m_display->setFont(font);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_display);

    auto *grid = new QGridLayout;
    mainLayout->addLayout(grid);

    QStringList digits = {"7","8","9","4","5","6","1","2","3","0"};
    QVector<QPushButton *> digitButtons;

    for (const auto &val : digits) {
        auto *button = new QPushButton(val, this);
        button->setMinimumSize(50, 50);
        connect(button, &QPushButton::clicked, this, &Calculator::digitClicked);
        digitButtons.push_back(button);
    }

    QStringList operators = {"÷", "×", "−", "+"};
    QVector<QPushButton *> operatorsButtons;
    for (const auto &op : operators) {
        auto *button = new QPushButton(op, this);
        button->setMinimumSize(50, 50);
        connect(button, &QPushButton::clicked, this, &Calculator::operatorClicked);
        operatorsButtons.push_back(button);
    }

    auto *equalButton = new QPushButton("=");
    equalButton->setMinimumSize(50, 50);
    equalButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    connect(equalButton, &QPushButton::clicked, this, &Calculator::equalsClicked);

    auto *dotButton = new QPushButton(".");
    dotButton->setMinimumSize(50, 50);
    connect(dotButton, &QPushButton::clicked, this, &Calculator::dotClicked);

    auto *clearButton = new QPushButton("C");
    clearButton->setMinimumSize(50, 50);
    connect(clearButton, &QPushButton::clicked, this, &Calculator::clearClicked);

    auto *backButton = new QPushButton("←");
    backButton->setMinimumSize(50, 50);
    connect(backButton, &QPushButton::clicked, this, &Calculator::backspaceClicked);

    int row = 0;
    grid->addWidget(clearButton, row, 0);
    grid->addWidget(backButton, row, 1);
    grid->addWidget(operatorsButtons[0], row, 2);
    grid->addWidget(operatorsButtons[1], row, 3);
    row++;

    grid->addWidget(digitButtons[0], row, 0);
    grid->addWidget(digitButtons[1], row, 1);
    grid->addWidget(digitButtons[2], row, 2);
    grid->addWidget(operatorsButtons[2], row, 3);
    row++;

    grid->addWidget(digitButtons[3], row, 0);
    grid->addWidget(digitButtons[4], row, 1);
    grid->addWidget(digitButtons[5], row, 2);
    grid->addWidget(operatorsButtons[3], row, 3);
    row++;

    grid->addWidget(digitButtons[6], row, 0);
    grid->addWidget(digitButtons[7], row, 1);
    grid->addWidget(digitButtons[8], row, 2);
    grid->addWidget(equalButton, row, 3, 2, 1);
    row++;

    grid->addWidget(digitButtons[9], row, 0, 1, 2);
    grid->addWidget(dotButton, row, 2);
}

void Calculator::updateDisplay(const QString &text)
{
    m_display->setText(text);
}

void Calculator::digitClicked()
{
    const auto *button = qobject_cast<QPushButton *>(sender());
    const auto &text = button->text();

    if (m_waitingForOperand) {
        updateDisplay(text);
        m_waitingForOperand = false;
    } else {
        updateDisplay(m_display->text() + text);
    }
}

void Calculator::dotClicked()
{
    const auto &text = m_display->text();
    if (!text.contains('.'))
        updateDisplay(text + ".");

    m_waitingForOperand = false;
}

void Calculator::clearClicked()
{
    m_accumulator = 0;
    m_pendingOperator.clear();
    m_waitingForOperand = true;
    updateDisplay("");
}

void Calculator::backspaceClicked()
{
    auto text = m_display->text();
    if (text.size() > 1)
        text.chop(1);
    else
        text = "";

    updateDisplay(text);
}

void Calculator::operatorClicked()
{
    const auto *button = qobject_cast<QPushButton*>(sender());
    const auto &op = button->text();
    const auto operand = m_display->text().toDouble();

    if (!m_pendingOperator.isEmpty() && !m_waitingForOperand)
        applyOperator(operand);
    else
        m_accumulator = operand;

    m_pendingOperator = op;
    m_waitingForOperand = true;
}

void Calculator::equalsClicked()
{
    auto operand = m_display->text().toDouble();
    applyOperator(operand);
    m_pendingOperator.clear();
    updateDisplay(QString::number(m_accumulator, 'g', 15));
    m_waitingForOperand = true;
}

void Calculator::applyOperator(double operand)
{
    if (m_pendingOperator == "+") {
        m_accumulator += operand;
    } else if (m_pendingOperator == "−") {
        m_accumulator -= operand;
    } else if (m_pendingOperator == "×") {
        m_accumulator *= operand;
    } else if (m_pendingOperator == "÷") {
        if (operand == 0)
            m_accumulator = 0;
        else
            m_accumulator /= operand;
    }
}
