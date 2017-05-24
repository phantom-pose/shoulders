#include "shoulderwidget.h"

ShoulderWidget::ShoulderWidget(bool l, QWidget *parent) :
    QWidget(parent)
{
    m_paintArea = new ShoulderPaintArea(l, this);
    m_backButton = new QPushButton("Slice back", this);
    m_backButton->move(0,PaintZ() + TOP_BORDER);
    m_backButton->resize(BUTTON_WIDTH,BUTTON_HEIGHT);
    m_forwardButton = new QPushButton("Slice forward", this);
    m_forwardButton->move(PaintX() - BUTTON_WIDTH, PaintZ() + TOP_BORDER);
    m_forwardButton->resize(BUTTON_WIDTH,BUTTON_HEIGHT);
    connect(m_backButton, SIGNAL (released()), this, SLOT (SliceBack()));
    connect(m_forwardButton, SIGNAL (released()), this, SLOT (SliceForward()));
    m_bezierDecXButton = new QPushButton("Voxel X dec", this);
    m_bezierDecXButton->resize(BUTTON_WIDTH,BUTTON_HEIGHT);
    m_bezierIncXButton = new QPushButton("Voxel X inc", this);
    m_bezierIncXButton->resize(BUTTON_WIDTH,BUTTON_HEIGHT);
    if (m_paintArea->Left())
    {
        m_bezierDecXButton->move(0,PaintZ() + 2*TOP_BORDER + BUTTON_HEIGHT);
        m_bezierIncXButton->move(PaintX() - BUTTON_WIDTH, PaintZ() + 2*TOP_BORDER + BUTTON_HEIGHT);
    }
    else
    {
        m_bezierIncXButton->move(0,PaintZ() + 2*TOP_BORDER + BUTTON_HEIGHT);
        m_bezierDecXButton->move(PaintX() - BUTTON_WIDTH, PaintZ() + 2*TOP_BORDER + BUTTON_HEIGHT);
    }
    connect(m_bezierDecXButton, SIGNAL (released()), this, SLOT (VoxelXBack()));
    connect(m_bezierIncXButton, SIGNAL (released()), this, SLOT (VoxelXForward()));
    setGeometry(0, 0,
                X() + 1, Z() + 1);
}

ShoulderWidget::~ShoulderWidget()
{
    delete m_paintArea;
}

void ShoulderWidget::SliceBack()
{
    m_paintArea->DecSlice();
}

void ShoulderWidget::SliceForward()
{
    m_paintArea->IncSlice();
}

void ShoulderWidget::VoxelXBack()
{
    m_paintArea->DecFocusX();
}

void ShoulderWidget::VoxelXForward()
{
    m_paintArea->IncFocusX();
}
