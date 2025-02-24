#include "mytask.h"

#include <QElapsedTimer>
#include <QDebug>
#include <QRandomGenerator>

RandomGeneration::RandomGeneration(QObject *parent) : QObject{parent} {}

void RandomGeneration::working(int numbers_count) {
    qDebug() << "The thread addree of random generatiion:" << QThread::currentThread();
    
    QVector<int> random_numbers;
    
    QElapsedTimer generation_timer;
    
    generation_timer.start();
    
    for (int i = 0; i < numbers_count; ++i) {
        random_numbers.push_back(QRandomGenerator::global()->bounded(100000));
    }
    
    qDebug() << "Total time to generate" << numbers_count << "random numbers:" << generation_timer.elapsed() << "ms";
    
    emit send_random_numbers(random_numbers);
}

BubbleSort::BubbleSort(QObject *parent) : QObject{parent} {}

void BubbleSort::working(QVector<int> random_numbers) {
    qDebug() << "The thread addree of bubble sort:" << QThread::currentThread();
    
    QElapsedTimer sort_timer;
    
    sort_timer.start();
    
    int temp_value;
    for (int i = 0; i < random_numbers.size(); ++i) {
        for (int j = 0; j < random_numbers.size() - i -1; ++j) {
            if (random_numbers[j] > random_numbers[j + 1]) {
                temp_value = random_numbers[j];
                random_numbers[j] = random_numbers[j + 1];
                random_numbers[j + 1] = temp_value;
            }
        }
    }
    
    qDebug() << "Total time to bubble sort:" << sort_timer.elapsed() << "ms";
    
    emit send_sorted_numbers(random_numbers);
}

QuickSort::QuickSort(QObject *parent) : QObject{parent} {}

void QuickSort::working(QVector<int> random_numbers) {
    qDebug() << "The thread addree of quick sort:" << QThread::currentThread();
    
    QElapsedTimer sort_timer;
    
    sort_timer.start();
    
    quick_sort(random_numbers, 0, random_numbers.size() - 1);
    
    qDebug() << "Total time to quick sort:" << sort_timer.elapsed() << "ms";
    
    emit send_sorted_numbers(random_numbers);
}

void QuickSort::quick_sort(QVector<int>& sorted_numbers, int left, int right) {
    if (left < right) {
        int i = left, j = right;
        
        int x = sorted_numbers[left];
        while (i < j) {
            while (i < j && sorted_numbers[j] >= x) {
                j--;
            }
            
            if (i < j) {
                sorted_numbers[i++] = sorted_numbers[j];
            }
            
            while (i < j && sorted_numbers[i] < x) {
                i++;
            }
            
            if (i < j) {
                sorted_numbers[j--] = sorted_numbers[i];
            }
        }
        
        sorted_numbers[i] = x;
        
        quick_sort(sorted_numbers, left, i - 1);
        quick_sort(sorted_numbers, i + 1, right);
    }
}
