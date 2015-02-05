#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::on_getTableButton_released()
{
    ui->tableWidget->setRowCount(ui->spinBox->text().toInt());
    ui->tableWidget->setColumnCount(ui->spinBox->text().toInt());
}

void MainWindow::markCell(int i, int j)
{
    if(ui->tableWidget->item(i, j) == NULL)
        ui->tableWidget->setItem(i, j, new QTableWidgetItem("X"));
    else
        ui->tableWidget->setItem(i, j, NULL);
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open Image"), "~/", tr("Text Files (*.txt *.c *.cpp)"));
    ui->fileName->setText(fileName);
    QFile input(fileName);
    if(input.open(QIODevice::ReadOnly))
    {
        QByteArray t =  input.readAll();
        QString text(t);
        ui->plainTextEdit->setPlainText(text);
    }
    else
    {
       ui->statusBar->showMessage("Unable to open file for reading.");
    }
}

void MainWindow::calcCC()
{
    int P = 0;
    if(ui->tabWidget->currentIndex() == 0)
    {
        int count = ui->tableWidget->rowCount();
        if(count == 0)
            P = -1;
        else
        {
            for(int i = 0; i < count; i++)
            {
                int itemCount = 0;
                for(int j = 0; j < count; j++)
                {
                    if(ui->tableWidget->item(i, j) != NULL)
                        itemCount++;
                }
                if(itemCount > 1)
                    P++;
            }
        }
    }
    else
    {
        if(ui->plainTextEdit->toPlainText().isEmpty())
            P = -1;
        else
        {
            QString text = ui->plainTextEdit->toPlainText();
            P += text.count("if");
            P += text.count("while");
            P += text.count("switch");
            P += text.count("for");
        }
    }

    ui->result->setText(tr("The Cyclomatic Complexity of the given program is %1").arg(P + 1));
}

MainWindow::~MainWindow()
{
    delete ui;
}
