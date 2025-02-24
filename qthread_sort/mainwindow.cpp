#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "mythread.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    
    RandomGeneration* random_generation = new RandomGeneration;
    
    BubbleSort* bubble_sort = new BubbleSort;
    QuickSort* quick_sort = new QuickSort;
    
    connect(this, &MainWindow::start_generate_number, random_generation, &RandomGeneration::recv_numbers_count);
    
    connect(ui->start_button, &QPushButton::clicked, this, [=]() {
        emit start_generate_number(10000);
        
        random_generation->start();        
    });
    
    connect(random_generation, &RandomGeneration::send_random_numbers, bubble_sort, &BubbleSort::recv_random_numbers);
    connect(random_generation, &RandomGeneration::send_random_numbers, quick_sort, &QuickSort::recv_random_numbers);
    
    connect(random_generation, &RandomGeneration::send_random_numbers, this, [=](const QVector<int>& random_numbers) {
        bubble_sort->start();
        quick_sort->start();
        
        for (int i = 0; i < random_numbers.size(); ++i) {
            ui->random_list->addItem(QString::number(random_numbers.at(i)));
        }
    });
    
    connect(bubble_sort, &BubbleSort::send_sorted_numbers, this, [=](const QVector<int>& sorted_numbers) {
        for (int i = 0; i < sorted_numbers.size(); ++i) {
            ui->bubble_sort_list->addItem(QString::number(sorted_numbers.at(i)));
        }
    });
    
    connect(quick_sort, &QuickSort::send_sorted_numbers, this, [=](const QVector<int>& sorted_numbers) {
        for (int i = 0; i < sorted_numbers.size(); ++i) {
            ui->quick_sort_list->addItem(QString::number(sorted_numbers.at(i)));
        }
    });

    connect(this, &MainWindow::destroyed, this, [=]() {
        random_generation->quit();
        random_generation->wait();
        random_generation->deleteLater();
        
        bubble_sort->quit();
        bubble_sort->wait();
        bubble_sort->deleteLater();
        
        quick_sort->quit();
        quick_sort->wait();
        quick_sort->deleteLater();
    });
}

MainWindow::~MainWindow() {
    delete ui;
}
