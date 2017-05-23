#pragma once

#include <QMainWindow>
#include <QLayout>
#include "shoulderpaintarea.h"
#include "shoulder.h"
#include "shoulderwidget.h"

int constexpr FULL_WIDTH = LEFT_AREA_BORDER + SCALE*SIZE_X_VOXEL*SIZE_X_LEFT + H_BORDER;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget * m_centralWidget;
    QLayout * m_layout;
    ShoulderWidget * m_leftShoulder;
    ShoulderWidget * m_rightShoulder;
};
