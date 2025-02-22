#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QVector>

class RandomGeneration : public QThread {
    Q_OBJECT
  public:
    explicit RandomGeneration(QObject *parent = nullptr);
    
  public slots:
    void recv_numbers_count(int numbers_count);
    
  protected:
    void run() override;

  signals:
    void send_random_numbers(QVector<int> random_nubmers);
    
  private:
    int numbers_count_;
};

#endif  // MYTHREAD_H
