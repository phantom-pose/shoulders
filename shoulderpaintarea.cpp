#include "shoulderpaintarea.h"

ShoulderPaintArea::ShoulderPaintArea(bool l, QWidget *parent) :
    QWidget(parent)
{
    m_shoulder = new Shoulder(l);
}

ShoulderPaintArea::~ShoulderPaintArea()
{
    delete m_shoulder;
}

void ShoulderPaintArea::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
    setGeometry(m_shoulder->Left() ? LEFT_AREA_BORDER : RIGHT_AREA_BORDER,
                TOP_BORDER,
                SCALE*SIZE_X_VOXEL*X() + 1, SCALE*SIZE_Z_VOXEL*Z() + 1);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(Pal);
    int ** slice = m_shoulder->GetSlice(m_nSlice);
    QPainter painter(this);
    for (int iz = 0; iz < Z(); iz++)
    {
        for (int ix = 0; ix < X(); ix++)
        {
            if (slice[iz][ix] != 0)
            {
                painter.drawRect(SCALE*SIZE_X_VOXEL*ix,
                                 SCALE*SIZE_Z_VOXEL*(Z() - (iz+1)),
                                 SCALE*SIZE_X_VOXEL, SCALE*SIZE_Z_VOXEL);
                painter.fillRect(SCALE*SIZE_X_VOXEL*ix,
                                 SCALE*SIZE_Z_VOXEL*(Z() - (iz+1)),
                                 SCALE*SIZE_X_VOXEL, SCALE*SIZE_Z_VOXEL,
                                 QColor(200, 200, 100, 127));
            }
        }
        delete slice[iz];
    }
    delete slice;
}
