#pragma once

#include <QMainWindow>
#include <QLayout>
#include "shoulderpaintarea.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QGridLayout * Layout() { return m_gridLayout; }
    ShoulderPaintArea * GetLeft() { return m_leftShoulderArea; }
    ShoulderPaintArea * GetRight() { return m_rightShoulderArea; }

private:
    QWidget * m_centralWidget;
    QGridLayout * m_gridLayout;
    ShoulderPaintArea * m_leftShoulderArea;
    ShoulderPaintArea * m_rightShoulderArea;
};
