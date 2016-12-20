#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>
#include <QVector>

#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class Processing_thread : public QThread
{
    Q_OBJECT

private:
    int Proton_energy;

    QVector <QVector <double> > Result;

protected:
    void run ();

signals:
    void Calculation_done();

public:
    void Set_energy (int E)
    {
        Proton_energy = E;
    }

     Processing_thread (void)
    {
        Proton_energy = 0;
    }

    QVector < QVector <double> > Get_Result (void)
    {
        return Result;
    }
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Processing_thread Thread;

    QMovie *movie;

    QPen blackDotPen;

private slots:
    void on_pushButton_clicked();

    void replot ();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
