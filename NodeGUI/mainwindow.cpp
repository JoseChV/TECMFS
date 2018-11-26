#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include "ControllerNode.h"
#include <cstring>
#include <QTextStream>
#include <string>
#include "disknode.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Variables de las imagenes de los discos
    QPixmap diskEmpty("/home/kevinfgn/Qt Projects/NodeGUI/Images/diskEmpty.jpg");
    QPixmap disk1("/home/kevinfgn/Qt Projects/NodeGUI/Images/disk1.jpg");
    QPixmap disk2("/home/kevinfgn/Qt Projects/NodeGUI/Images/disk2.jpg");
    QPixmap disk3("/home/kevinfgn/Qt Projects/NodeGUI/Images/disk3.jpg");
    QPixmap disk4("/home/kevinfgn/Qt Projects/NodeGUI/Images/disk4.jpg");
    QPixmap disk5("/home/kevinfgn/Qt Projects/NodeGUI/Images/disk5.jpg");
    QFile disco1("/home/kevinfgn/Disk1");
    QFile disco2("/home/kevinfgn/Disk2");
    QFile disco3("/home/kevinfgn/Disk3");
    ui->setupUi(this);

    int label_1_w = ui->label1->width();
    int label_1_h =  ui->label1->height();
    int label_2_w = ui->label1->width();
    int label_2_h =  ui->label1->height();
    int label_3_w = ui->label1->width();
    int label_3_h =  ui->label1->height();

    ui->label1->setPixmap(disk2.scaled(label_1_w,label_1_h,Qt::KeepAspectRatio));


    ui->label2->setPixmap(disk2.scaled(label_2_w,label_2_h,Qt::KeepAspectRatio));


    ui->label3->setPixmap(disk2.scaled(label_3_w,label_3_h,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_clicked()
{
    //Se pasa de QString a String
    QString filename = QFileDialog::getOpenFileName(this,"Open a File","","Video File (*.*)");
    filename.remove(".mp4");
    string stringName = filename.toStdString();
    stringName.erase(0,34);
    QString newName = QString::fromStdString(stringName);
    ui->listWidget->addItem(newName);
    ui->listWidget->addItem(filename);
    char* name = (char*)stringName.c_str();
   // controller->saveToDiskNodes(name);
    controller->readFromDiskNodes(name);
}

void MainWindow::on_pushButton_2_clicked()
{

}
void MainWindow::on_pushButton_3_clicked()
{

}
