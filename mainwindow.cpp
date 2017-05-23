#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_centralWidget = new QWidget(this);
    this->setCentralWidget( m_centralWidget );
    m_layout = new QHBoxLayout( m_centralWidget );
    m_leftShoulder = new ShoulderWidget(true);
    m_rightShoulder = new ShoulderWidget(false);
    m_layout->addWidget(m_rightShoulder);
    m_layout->addWidget(m_leftShoulder);
    setFixedSize(FULL_WIDTH,
                 m_leftShoulder->Z() > m_rightShoulder->Z() ?
                     m_leftShoulder->Z()
                   :
                     m_rightShoulder->Z());
}

MainWindow::~MainWindow()
{}
