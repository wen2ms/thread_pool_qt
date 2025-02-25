#ifndef MYTASK_H
#define MYTASK_H

#include <QObject>
#include <QRunnable>
#include <QVector>

class RandomGeneration : public QObject, public QRunnable {
    Q_OBJECT
  public:
    explicit RandomGeneration(QObject *parent = nullptr);
    
    void run() override;
    
  public slots:
    void recv_numbers_count(int numbers_count);

  signals:
    void send_random_numbers(QVector<int> random_nubmers);
    
  private:
    int numbers_count_;
};

class BubbleSort : public QObject, public QRunnable {
    Q_OBJECT
  public:
    explicit BubbleSort(QObject *parent = nullptr);
    
    void run() override;
    
  public slots:
    void recv_random_numbers(const QVector<int>& random_numbers);
    
  signals:
    void send_sorted_numbers(QVector<int> sorted_nubmers);
    
  private:
    QVector<int> sorted_numbers_;
};

class QuickSort : public QObject, public QRunnable {
    Q_OBJECT
  public:
    explicit QuickSort(QObject *parent = nullptr);
    
    void run() override;
    
  public slots:
    void recv_random_numbers(const QVector<int>& random_numbers);
    
  signals:
    void send_sorted_numbers(QVector<int> sorted_nubmers);
    
  private:
    void quick_sort(QVector<int>& sorted_numbers, int left, int right);
    
    QVector<int> sorted_numbers_;
};
#endif  // MYTASK_H
