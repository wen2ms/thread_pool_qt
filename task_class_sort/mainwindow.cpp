#include "mainwindow.h"

#include <QThread>

#include "./ui_mainwindow.h"
#include "mytask.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    
    QThread* random_generation_thread = new QThread;
    QThread* bubble_sort_thread = new QThread;
    QThread* quick_sort_thread = new QThread; 
    
    RandomGeneration* random_generation = new RandomGeneration;
    
    BubbleSort* bubble_sort = new BubbleSort;
    QuickSort* quick_sort = new QuickSort;
    
    random_generation->moveToThread(random_generation_thread);
    bubble_sort->moveToThread(bubble_sort_thread);
    quick_sort->moveToThread(quick_sort_thread);
    
    connect(this, &MainWindow::start_generate_number, random_generation, &RandomGeneration::working);
    
    connect(ui->start_button, &QPushButton::clicked, this, [=]() {
        emit start_generate_number(10000);
        
        random_generation_thread->start();        
    });
    
    connect(random_generation, &RandomGeneration::send_random_numbers, bubble_sort, &BubbleSort::working);
    connect(random_generation, &RandomGeneration::send_random_numbers, quick_sort, &QuickSort::working);
    
    connect(random_generation, &RandomGeneration::send_random_numbers, this, [=](const QVector<int>& random_numbers) {
        bubble_sort_thread->start();
        quick_sort_thread->start();
        
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
}

MainWindow::~MainWindow() {
    delete ui;
}
