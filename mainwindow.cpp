#include "mainwindow.h"
#include <thread>
#include <QLabel>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_centralWidget = new QWidget(this);
    this->setCentralWidget( m_centralWidget );
    m_layout = new QHBoxLayout( m_centralWidget );
    m_layout->setMargin(0);
    m_leftShoulder = new ShoulderWidget(true);
    m_rightShoulder = new ShoulderWidget(false);
    m_layout->addWidget(m_rightShoulder);
    m_layout->addWidget(m_leftShoulder);
    m_rightShoulder->resize(m_rightShoulder->X()+1, m_rightShoulder->Z()+1);
    QWidget * techArea = new QWidget(this);
    techArea->setFixedWidth(TECH_WIDGET_WIDTH);
    QPushButton * resultButton = new QPushButton("Calculate", techArea);
    m_layout->addWidget(techArea);
    resultButton->resize(BUTTON_WIDTH, BUTTON_HEIGHT);
    connect(resultButton, SIGNAL (released()), this, SLOT (Calculate()));
    setFixedSize(FULL_WIDTH,
                 m_leftShoulder->Z() > m_rightShoulder->Z() ?
                     m_leftShoulder->Z()
                   :
                     m_rightShoulder->Z());
}

MainWindow::~MainWindow()
{}

void MainWindow::Calculate()
{
    std::thread rightThread(&MainWindow::CalcAndDumpShoulder,
                           this,
                           m_rightShoulder->DataX(),
                           m_rightShoulder->DataZ(),
                           ALPHA_RES_RIGHT_FILENAME,
                           T_RES_RIGHT_FILENAME);
    std::thread leftThread(&MainWindow::CalcAndDumpShoulder,
                           this,
                           m_leftShoulder->DataX(),
                           m_leftShoulder->DataZ(),
                           ALPHA_RES_LEFT_FILENAME,
                           T_RES_LEFT_FILENAME);
    rightThread.join();
    leftThread.join();
}

void MainWindow::CalcAndDumpShoulder(int xsize, int zsize,
                                     char const afilename[], char const tfilename[])
{
    ofstream aout, tout;
    aout.open(afilename);
    tout.open(tfilename);
    BezierCoords2D * coords;
    for (int ix = 0; ix < xsize; ix++)
    {
        for (int iz = 0; iz < zsize; iz++) {
            coords = BezierCoords2D::FindAlpha(SIZE_X_VOXEL*xsize,
                                               SIZE_Z_VOXEL*zsize,
                                               SIZE_X_VOXEL*(ix+1),
                                               SIZE_Z_VOXEL*(iz+1));
            aout << coords->alpha() << " ";
            tout << coords->t() << " ";
            delete coords;
        }
        aout << "\n";
        tout << "\n";
    }
    aout.close();
    tout.close();
}
