#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QRegularExpression>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_getTableButton_released();
    void markCell(int, int);
    void openFile();
    void calcCC();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
