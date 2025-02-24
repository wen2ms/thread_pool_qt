#ifndef MYTASK_H
#define MYTASK_H

#include <QThread>
#include <QVector>

class RandomGeneration : public QObject {
    Q_OBJECT
  public:
    explicit RandomGeneration(QObject *parent = nullptr);
    
    void working(int numbers_count);

  signals:
    void send_random_numbers(QVector<int> random_nubmers);
};

class BubbleSort : public QObject {
    Q_OBJECT
  public:
    explicit BubbleSort(QObject *parent = nullptr);
    
    void working(QVector<int> random_numbers);

  signals:
    void send_sorted_numbers(QVector<int> sorted_nubmers);
};

class QuickSort : public QObject {
    Q_OBJECT
  public:
    explicit QuickSort(QObject *parent = nullptr);
    
    void working(QVector<int> random_numbers);
    
  signals:
    void send_sorted_numbers(QVector<int> sorted_nubmers);
    
  private:
    void quick_sort(QVector<int>& sorted_numbers, int left, int right);
};
#endif  // MYTASK_H
