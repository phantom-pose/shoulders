#pragma once

#include <QWidget>
#include <QPushButton>
#include <shoulderpaintarea.h>

int constexpr TOP_BORDER = 10;
int constexpr H_BORDER = 15;
int constexpr RIGHT_AREA_BORDER = H_BORDER;
int constexpr LEFT_AREA_BORDER = RIGHT_AREA_BORDER + SCALE*SIZE_X_VOXEL*SIZE_X_RIGHT + H_BORDER;
int constexpr BUTTON_HEIGHT = 30;
int constexpr BUTTON_WIDTH = 100;

class ShoulderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShoulderWidget(bool l, QWidget *parent = 0);
    ~ShoulderWidget();

    int X() const { return SCALE * SIZE_X_VOXEL * m_paintArea->X(); };
    int Z() const { return (SCALE * SIZE_Z_VOXEL * m_paintArea->Z() + 5*TOP_BORDER + 2*BUTTON_HEIGHT); };
    int PaintX() const { return SCALE * SIZE_X_VOXEL * m_paintArea->X(); };
    int PaintZ() const { return SCALE * SIZE_Z_VOXEL * m_paintArea->Z(); };

private slots:
    void SliceBack();
    void SliceForward();
    void VoxelXBack();
    void VoxelXForward();

private:
    ShoulderPaintArea * m_paintArea;
    QPushButton * m_backButton;
    QPushButton * m_forwardButton;
    QPushButton * m_bezierDecXButton;
    QPushButton * m_bezierIncXButton;
};

