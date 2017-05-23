#include "shoulderpaintarea.h"

ShoulderPaintArea::ShoulderPaintArea(bool l, QWidget *parent) :
    QWidget(parent)
{
    m_shoulder = new Shoulder(l);
    setGeometry(0, 0,
                SCALE*SIZE_X_VOXEL*X() + 1, SCALE*SIZE_Z_VOXEL*Z() + 1);
}

ShoulderPaintArea::~ShoulderPaintArea()
{
    delete m_shoulder;
}

void ShoulderPaintArea::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
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

void ShoulderPaintArea::DecSlice() {
    if (m_nSlice > 0) {
        m_nSlice--;
        this->update();
    }
}

void ShoulderPaintArea::IncSlice() {
    if (m_nSlice < m_shoulder->Y() - 1) {
        m_nSlice++;
        this->update();
    }
}
