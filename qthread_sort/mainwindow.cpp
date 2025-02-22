#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "mythread.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    
    RandomGeneration* random_generation = new RandomGeneration;
    
    connect(this, &MainWindow::start_generate_number, random_generation, &RandomGeneration::recv_numbers_count);
    
    connect(ui->start_button, &QPushButton::clicked, this, [=]() {
        emit start_generate_number(10000);
        
        random_generation->start();        
    });
    
    connect(random_generation, &RandomGeneration::send_random_numbers, this, [=](const QVector<int>& random_numbers) {
        for (int i = 0; i < random_numbers.size(); ++i) {
            ui->random_list->addItem(QString::number(random_numbers.at(i)));
        }
    });
}

MainWindow::~MainWindow() {
    delete ui;
}
