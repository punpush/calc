#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>


#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);

private slots:
    void digitClicked();
    void dotClicked();
    void operatorClicked();
    void equalsClicked();
    void clearClicked();
    void backspaceClicked();

private:
    void applyOperator(double operand);
    void updateDisplay(const QString &text);

    QLineEdit *m_display {nullptr};

    QString m_pendingOperator;
    double m_accumulator {0.0};
    double m_memory {0.0};
    bool m_waitingForOperand {true};
};
