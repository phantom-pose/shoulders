#pragma once

#include <QWidget>
#include <QPushButton>
#include "shoulderpaintarea.h"

int constexpr TOP_BORDER = 10;
int constexpr H_BORDER = 15;
int constexpr BUTTON_HEIGHT = 30;
int constexpr BUTTON_WIDTH = 100;
int constexpr V_BUTTON_WIDTH = 50;

class ShoulderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShoulderWidget(bool l, QWidget *parent = 0);
    ~ShoulderWidget();

    int DataX() const { return m_paintArea->X(); }
    int DataY() const { return m_paintArea->Y(); }
    int DataZ() const { return m_paintArea->Z(); }
    int *** GetData() const { return m_paintArea->GetData(); }

    int PaintX() const { return SCALE * SIZE_X_VOXEL * m_paintArea->X(); }
    int PaintZ() const { return SCALE * SIZE_Z_VOXEL * m_paintArea->Z(); }
    int X() const { return PaintX() + 2*H_BORDER + V_BUTTON_WIDTH; }
    int Z() const { return (PaintZ() + 5*TOP_BORDER + 2*BUTTON_HEIGHT); }

private slots:
    void SliceBack();
    void SliceForward();
    void VoxelXBack();
    void VoxelXForward();
    void VoxelZBack();
    void VoxelZForward();

private:
    ShoulderPaintArea * m_paintArea;
    QPushButton * m_backButton;
    QPushButton * m_forwardButton;
    QPushButton * m_bezierDecXButton;
    QPushButton * m_bezierIncXButton;
    QPushButton * m_bezierDecZButton;
    QPushButton * m_bezierIncZButton;
};

