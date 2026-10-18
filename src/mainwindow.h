#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QAction>
#include <QLineEdit>
#include "json.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QVBoxLayout *layout;
    QLineEdit *entry;
    void createRow(const QString &text);
    void addLabel(QString);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
