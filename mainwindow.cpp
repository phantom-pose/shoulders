#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_leftShoulder = new Shoulder(true);
    m_rightShoulder = new Shoulder(false);
}

MainWindow::~MainWindow()
{
    delete m_leftShoulder;
    delete m_rightShoulder;
}
