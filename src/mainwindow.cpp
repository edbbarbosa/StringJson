#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    layout = new QVBoxLayout(centralWidget);
    QHBoxLayout *hbox = new QHBoxLayout;
    layout->addLayout(hbox);

    entry = new QLineEdit;
    QPushButton *button = new QPushButton("Add");
    hbox->addWidget(entry);
    hbox->addWidget(button);

    connect(button, &QPushButton::clicked, this, [this]() {
        addLabel(entry->text());
    });

    setCentralWidget(centralWidget);

    json json;
    QStringList texts = json.readJson();

    for(const QString &text : texts){
        createRow(text);
    }

}

MainWindow::~MainWindow() {}

void MainWindow::createRow(const QString &text){
    QHBoxLayout *hbox = new QHBoxLayout;
    layout->addLayout(hbox);
    QPushButton *removeButton = new QPushButton("Remove");
    QLabel *label = new QLabel(text);
    label->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);

    hbox->addWidget(label);
    hbox->addWidget(removeButton);

    json json;
    QObject::connect(removeButton, &QPushButton::clicked,
        this, [this, json, text, hbox, label, removeButton] mutable {
        if(json.removeText(text)){
            hbox->removeWidget(label);
            hbox->removeWidget(removeButton);
            label->deleteLater();
            removeButton->deleteLater();
            hbox->deleteLater();
        }
    });
}

void MainWindow::addLabel(QString text){
    json json;
    if(json.saveJson(text)){
        createRow(text);
    }
}


