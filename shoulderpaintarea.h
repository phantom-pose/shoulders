#pragma once

#include <QWidget>
#include <QPainter>
#include "shoulder.h"

int constexpr SCALE = 2;

class ShoulderPaintArea : public QWidget
{
    Q_OBJECT

public:
    explicit ShoulderPaintArea(bool l, QWidget *parent = 0);
    ~ShoulderPaintArea();
    virtual void paintEvent(QPaintEvent * event);
    void IncSlice();
    void DecSlice();
    void IncFocusX();
    void DecFocusX();
    void IncFocusZ();
    void DecFocusZ();

    int const & X() const { return m_shoulder->X(); }
    int const & Y() const { return m_shoulder->Y(); }
    int const & Z() const { return m_shoulder->Z(); }
    bool const & Left() const { return m_shoulder->Left(); }
    int *** GetData() const { return m_shoulder->GetData(); }

private:
    Shoulder * m_shoulder;
    int m_nSlice = 40;
    int m_focusX = 10;
    int m_focusZ = 10;
};
