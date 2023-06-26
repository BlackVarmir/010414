#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::checkPasswords);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkPasswords()
{
    QString passwordsString = ui->lineEdit->text();
    QStringList passwords = passwordsString.split(",", Qt::SkipEmptyParts);

    QStringList validPasswords;

    foreach (const QString& password, passwords) {
        QString trimmedPassword = password.trimmed();  // Видаляємо пробіли з початку та кінця паролю

        if (validatePassword(trimmedPassword)) {
            validPasswords.append(trimmedPassword);
        }
    }

    if (!validPasswords.isEmpty()) {
        QString result = "Паролі, що відповідають критеріям:\n";
        result += validPasswords.join(", ");

        QMessageBox::information(this, "Результат", result);
    } else {
        QMessageBox::warning(this, "Результат", "Немає паролів, що відповідають критеріям");
    }
}



bool MainWindow::validatePassword(const QString& password) {
    if (password.length() < 4 || password.length() > 6) {
        return false;
    }

    if (!password.contains(QRegularExpression("[a-z]"))) {
        return false;
    }

    if (!password.contains(QRegularExpression("[0-9]"))) {
        return false;
    }

    if (!password.contains(QRegularExpression("[A-Z]"))) {
        return false;
    }

    if (!password.contains(QRegularExpression("[*#+@]"))) {
        return false;
    }

    if (password.contains(' ')) {
        return false;
    }

    return true;
}

