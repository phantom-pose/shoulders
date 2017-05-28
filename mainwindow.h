#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QPushButton>
#include <fstream>
#include "shoulderpaintarea.h"
#include "shoulder.h"
#include "shoulderwidget.h"

int constexpr FULL_WIDTH = SCALE*SIZE_X_VOXEL*SIZE_X_RIGHT + 4*H_BORDER
        + 2*V_BUTTON_WIDTH + SCALE*SIZE_X_VOXEL*SIZE_X_LEFT + BUTTON_WIDTH + 40;
char constexpr ALPHA_RES_RIGHT_FILENAME[]  = "res/ar";
char constexpr ALPHA_RES_LEFT_FILENAME[] = "res/al";
char constexpr T_RES_RIGHT_FILENAME[]  = "res/tr";
char constexpr T_RES_LEFT_FILENAME[] = "res/tl";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void Calculate();

private:
    QWidget * m_centralWidget;
    QLayout * m_layout;
    ShoulderWidget * m_leftShoulder;
    ShoulderWidget * m_rightShoulder;

    void CalcAndDumpShoulder(int xsize, int zsize,
                             char const afilename[], char const tfilename[]);
};
