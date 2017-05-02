#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_centralWidget = new QWidget(this);
    this->setCentralWidget( m_centralWidget );
    m_gridLayout = new QGridLayout( m_centralWidget );
    m_leftShoulderArea = new ShoulderPaintArea(true);
    m_rightShoulderArea = new ShoulderPaintArea(false);
    setFixedSize(FULL_WIDTH,
                 m_leftShoulderArea->Z() > m_rightShoulderArea->Z() ?
                     SCALE * SIZE_Z_VOXEL * m_leftShoulderArea->Z() + 2*TOP_BORDER
                   :
                     SCALE * SIZE_Z_VOXEL * m_rightShoulderArea->Z() + 2*TOP_BORDER);
}

MainWindow::~MainWindow()
{}
