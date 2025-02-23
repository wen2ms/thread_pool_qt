#include "mythread.h"

#include <QElapsedTimer>
#include <QDebug>
#include <QRandomGenerator>

RandomGeneration::RandomGeneration(QObject *parent) : QThread{parent} {}

void RandomGeneration::recv_numbers_count(int numbers_count) {
    numbers_count_ = numbers_count;
}

void RandomGeneration::run() {
    qDebug() << "The thread addree of random generatiion:" << QThread::currentThread();
    
    QVector<int> random_numbers;
    
    QElapsedTimer generation_timer;
    
    generation_timer.start();
    
    for (int i = 0; i < numbers_count_; ++i) {
        random_numbers.push_back(QRandomGenerator::global()->bounded(100000));
    }
    
    qDebug() << "Total time to generate" << numbers_count_ << "random numbers:" << generation_timer.elapsed();
    
    emit send_random_numbers(random_numbers);
}

BubbleSort::BubbleSort(QObject *parent) : QThread{parent} {}

void BubbleSort::recv_random_numbers(const QVector<int>& random_numbers) {
    sorted_numbers_ = random_numbers;
}

void BubbleSort::run() {
    qDebug() << "The thread addree of bubble sort:" << QThread::currentThread();
    
    QElapsedTimer sort_timer;
    
    sort_timer.start();
    
    int temp_value;
    for (int i = 0; i < sorted_numbers_.size(); ++i) {
        for (int j = 0; j < sorted_numbers_.size() - i -1; ++j) {
            if (sorted_numbers_[j] > sorted_numbers_[j + 1]) {
                temp_value = sorted_numbers_[j];
                sorted_numbers_[j] = sorted_numbers_[j + 1];
                sorted_numbers_[j + 1] = temp_value;
            }
        }
    }
    
    qDebug() << "Total time to bubble sort:" << sort_timer.elapsed();
    
    emit send_sorted_numbers(sorted_numbers_);
}
