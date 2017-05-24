#include "shoulderwidget.h"

ShoulderWidget::ShoulderWidget(bool l, QWidget *parent) :
    QWidget(parent)
{
    m_paintArea = new ShoulderPaintArea(l, this);
    if (m_paintArea->Left()) {
        m_paintArea->move(0,0);
    } else {
        m_paintArea->move(V_BUTTON_WIDTH + 2*H_BORDER,0);
    }
    m_paintArea->resize(PaintX(),PaintZ());
    m_backButton = new QPushButton("Slice back", this);
    m_backButton->resize(BUTTON_WIDTH,BUTTON_HEIGHT);
    m_forwardButton = new QPushButton("Slice forward", this);
    m_forwardButton->resize(BUTTON_WIDTH,BUTTON_HEIGHT);
    if (m_paintArea->Left())
    {
        m_backButton->move(0,PaintZ() + TOP_BORDER);
        m_forwardButton->move(PaintX() - BUTTON_WIDTH, PaintZ() + TOP_BORDER);
    }
    else
    {
        m_backButton->move(2*H_BORDER + V_BUTTON_WIDTH,PaintZ() + TOP_BORDER);
        m_forwardButton->move(2*H_BORDER + V_BUTTON_WIDTH + PaintX() - BUTTON_WIDTH, PaintZ() + TOP_BORDER);
    }
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
        m_bezierIncXButton->move(2*H_BORDER + V_BUTTON_WIDTH,PaintZ() + 2*TOP_BORDER + BUTTON_HEIGHT);
        m_bezierDecXButton->move(2*H_BORDER + V_BUTTON_WIDTH + PaintX() - BUTTON_WIDTH, PaintZ() + 2*TOP_BORDER + BUTTON_HEIGHT);
    }
    connect(m_bezierDecXButton, SIGNAL (released()), this, SLOT (VoxelXBack()));
    connect(m_bezierIncXButton, SIGNAL (released()), this, SLOT (VoxelXForward()));
    m_bezierDecZButton = new QPushButton("Bottom", this);
    m_bezierDecZButton->resize(V_BUTTON_WIDTH, BUTTON_HEIGHT);
    m_bezierIncZButton = new QPushButton("Top", this);
    m_bezierIncZButton->resize(V_BUTTON_WIDTH, BUTTON_HEIGHT);
    if (m_paintArea->Left())
    {
        m_bezierDecZButton->move(PaintX() + H_BORDER, PaintZ() - BUTTON_HEIGHT);
        m_bezierIncZButton->move(PaintX() + H_BORDER, 0);
    }
    else
    {
        m_bezierDecZButton->move(H_BORDER, PaintZ() - BUTTON_HEIGHT);
        m_bezierIncZButton->move(H_BORDER, 0);
    }
    connect(m_bezierDecZButton, SIGNAL (released()), this, SLOT (VoxelZBack()));
    connect(m_bezierIncZButton, SIGNAL (released()), this, SLOT (VoxelZForward()));
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

void ShoulderWidget::VoxelZBack()
{
    m_paintArea->DecFocusZ();
}

void ShoulderWidget::VoxelZForward()
{
    m_paintArea->IncFocusZ();
}
