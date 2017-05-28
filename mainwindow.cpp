#include "mainwindow.h"

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
    QPushButton * resultButton = new QPushButton("Calculate", this);
    m_layout->addWidget(resultButton);
    resultButton->setFixedSize(BUTTON_WIDTH, BUTTON_HEIGHT);
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
    ofstream aout, tout;
    aout.open(ALPHA_RES_RIGHT_FILENAME);
    tout.open(T_RES_RIGHT_FILENAME);
    CalcAndDumpShoulder(m_rightShoulder->DataX(), m_rightShoulder->DataZ(), aout, tout);
    aout.close();
    tout.close();

    aout.open(ALPHA_RES_LEFT_FILENAME);
    tout.open(T_RES_LEFT_FILENAME);
    CalcAndDumpShoulder(m_leftShoulder->DataX(), m_leftShoulder->DataZ(), aout, tout);
    aout.close();
    tout.close();
}

void MainWindow::CalcAndDumpShoulder(int xsize, int zsize, ofstream & afile, ofstream & tfile)
{
    BezierCoords2D * coords;
    for (int ix = 0; ix < xsize; ix++)
    {
        for (int iz = 0; iz < zsize; iz++) {
            coords = BezierCoords2D::FindAlpha(SIZE_X_VOXEL*xsize,
                                               SIZE_Z_VOXEL*zsize,
                                               SIZE_X_VOXEL*(ix+1),
                                               SIZE_Z_VOXEL*(iz+1));
            afile << coords->alpha() << " ";
            tfile << coords->t() << " ";
            delete coords;
        }
        afile << "\n";
        tfile << "\n";
    }
}
