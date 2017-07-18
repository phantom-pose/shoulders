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
        delete [] slice[iz];
    }
    delete [] slice;
    if (Left())
    {
        painter.fillRect(SCALE*SIZE_X_VOXEL*(m_focusX-1),
                         SCALE*SIZE_Z_VOXEL*(Z() - m_focusZ),
                         SCALE*SIZE_X_VOXEL, SCALE*SIZE_Z_VOXEL,
                         QColor(200, 100, 100, 127));
    }
    else
    {
        painter.fillRect(SCALE*SIZE_X_VOXEL*(X() - m_focusX),
                         SCALE*SIZE_Z_VOXEL*(Z() - m_focusZ),
                         SCALE*SIZE_X_VOXEL, SCALE*SIZE_Z_VOXEL,
                         QColor(200, 100, 100, 127));
    }
    BezierCoords2D * coords = BezierCoords2D::FindAlpha(X()*SIZE_X_VOXEL,
                                                        Z()*SIZE_Z_VOXEL,
                                                        m_focusX*SIZE_X_VOXEL,
                                                        m_focusZ*SIZE_Z_VOXEL);
    double alpha = coords->alpha();
    delete coords;
    auto line = m_shoulder->GetBezierLine(alpha);
    auto from = line.front();
    for (auto &point : line)
    {
        if (m_shoulder->Left()) {
            painter.drawLine(
                        static_cast<int>(SCALE*from->x()),
                        static_cast<int>(SCALE*Z()*SIZE_Z_VOXEL - SCALE*from->z()),
                        static_cast<int>(SCALE*point->x()),
                        static_cast<int>(SCALE*Z()*SIZE_Z_VOXEL - SCALE*point->z())
                        );
        } else {
            painter.drawLine(
                        static_cast<int>(SCALE*X()*SIZE_X_VOXEL - SCALE*from->x()),
                        static_cast<int>(SCALE*Z()*SIZE_Z_VOXEL - SCALE*from->z()),
                        static_cast<int>(SCALE*X()*SIZE_X_VOXEL - SCALE*point->x()),
                        static_cast<int>(SCALE*Z()*SIZE_Z_VOXEL - SCALE*point->z())
                        );
        }
        from = point;
    }
    for (auto &point : line)
    {
        delete point;
    }
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

void ShoulderPaintArea::DecFocusX() {
    if (m_focusX > 0) {
        m_focusX--;
        this->update();
    }
}

void ShoulderPaintArea::IncFocusX() {
    if (m_focusX < m_shoulder->X()) {
        m_focusX++;
        this->update();
    }
}

void ShoulderPaintArea::DecFocusZ() {
    if (m_focusZ > 0) {
        m_focusZ--;
        this->update();
    }
}

void ShoulderPaintArea::IncFocusZ() {
    if (m_focusZ < m_shoulder->Z()) {
        m_focusZ++;
        this->update();
    }
}
