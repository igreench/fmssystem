#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->buttonWellcomeDemo, SIGNAL(clicked(bool)), this, SLOT(setPageMain()));
    connect(ui->buttonWellcomeExit, SIGNAL(clicked(bool)), this, SLOT(close()));

    connect(ui->buttonMainPlay, SIGNAL(clicked(bool)), this, SLOT(setPageGame()));
    connect(ui->buttonMainSettings, SIGNAL(clicked(bool)), this, SLOT(setPageSettings()));
    connect(ui->buttonMainStats, SIGNAL(clicked(bool)), this, SLOT(setPageStats()));
    connect(ui->buttonMainExit, SIGNAL(clicked(bool)), this, SLOT(setPageWellcome()));

    connect(ui->buttonSettingsBack, SIGNAL(clicked(bool)), this, SLOT(setPageMain()));
    connect(ui->buttonStatsBack, SIGNAL(clicked(bool)), this, SLOT(setPageMain()));
    connect(ui->buttonGameBack, SIGNAL(clicked(bool)), this, SLOT(setPageMain()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPageWellcome() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::setPageMain() {
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::setPageSettings() {
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::setPageStats() {
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::setPageGame() {
    ui->stackedWidget->setCurrentIndex(4);
}
