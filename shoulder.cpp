#include "shoulder.h"

using namespace std;

Shoulder::Shoulder(bool l): m_left{l}
{
    if (m_left)
    {
        m_size = make_shared<Size>(new Size(SIZE_X_LEFT, SIZE_Y_LEFT, SIZE_Z_LEFT));
    }
    else
    {
        m_size = make_shared<Size>(new Size(SIZE_X_RIGHT, SIZE_Y_RIGHT, SIZE_Z_RIGHT));
    }

    m_data = new int**[Z()];
    for (int k = 0; k < Z(); k++)
    {
        m_data[k] = new int*[Y()];
        for (int j = 0; j < Y(); j++)
        {
            m_data[k][j] = new int[X()];
        }
    }
    ifstream dataFile;
    string line;
    dataFile.open(m_left ? LEFT_FILENAME : RIGHT_FILENAME);
    if (dataFile.is_open())
    {
        string delimiter = " ";
        size_t pos = 0;
        string token;
        int iz, iy, ix, t = 0;
        while (getline(dataFile, line))
        {
            while ((pos = line.find(delimiter)) != string::npos)
            {
                iz = t / (X()*Y());
                iy = (t % (X()*Y())) / X();
                ix = (t % (X()*Y())) % X();
                token = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                m_data[iz][iy][ix] = atoi(token.c_str());
                t++;
            }
            iz = t / (X()*Y());
            iy = (t % (X()*Y())) / X();
            ix = (t % (X()*Y())) % X();
            m_data[iz][iy][ix] = atoi(line.c_str());
            t++;
        }
    }
    dataFile.close();
}

Shoulder::~Shoulder()
{
    for (int k = 0; k < Z(); k++)
    {
        for (int j = 0; j < Y(); j++)
        {
            delete m_data[k][j];
        }
        delete m_data[k];
    }
    delete m_data;
}

int ** Shoulder::GetSlice(int number) const
{
    int ** slice = new int*[Z()];
    for (int iz = 0; iz < Z(); iz++)
    {
        slice[iz] = new int[X()];
        for (int ix = 0; ix < X(); ix++)
        {
            slice[iz][ix] = m_data[iz][number][ix];
        }
    }
    return slice;
}

vector<DecCoords2D*> Shoulder::GetBezierLine(double alpha, int x, int z) const
{
    vector<DecCoords2D*> line;
    line.reserve(BEZIER_LENGTH);
    for (int it = 0; it < BEZIER_LENGTH; it++)
    {
        line.push_back(FindPoint(alpha, static_cast<float>(it)/BEZIER_LENGTH,
                             X()*SIZE_X_VOXEL, Z()*SIZE_Z_VOXEL,
                             x*SIZE_X_VOXEL, z*SIZE_Z_VOXEL));
    }
    return line;
}
