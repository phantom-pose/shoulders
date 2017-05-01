#pragma once

#include <QMainWindow>
#include <QCloseEvent>
#include "shoulder.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Shoulder * m_leftShoulder;
    Shoulder * m_rightShoulder;
};
