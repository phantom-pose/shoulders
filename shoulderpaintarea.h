#pragma once

#include <QWidget>
#include <QPainter>
#include "shoulder.h"

int constexpr SCALE = 2;
int constexpr TOP_BORDER = 5;
int constexpr RIGHT_AREA_BORDER = 10;
int constexpr LEFT_AREA_BORDER = RIGHT_AREA_BORDER + SCALE*SIZE_X_VOXEL*SIZE_X_RIGHT + 10;
int constexpr FULL_WIDTH = LEFT_AREA_BORDER + SCALE*SIZE_X_VOXEL*SIZE_X_LEFT + 10;

class ShoulderPaintArea : public QWidget
{
    Q_OBJECT

public:
    explicit ShoulderPaintArea(bool l, QWidget *parent = 0);
    ~ShoulderPaintArea();
    virtual void paintEvent(QPaintEvent * event);
    void IncSlice();

    int const & X() const { return m_shoulder->X(); };
    int const & Y() const { return m_shoulder->Y(); };
    int const & Z() const { return m_shoulder->Z(); };

private:
    Shoulder * m_shoulder;
    int m_nSlice = 40;
};
