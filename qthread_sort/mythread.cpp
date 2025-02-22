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
