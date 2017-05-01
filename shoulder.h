#pragma once
#include <memory>

char constexpr LEFT_FILENAME[]  = "cut/female/left_shoulder";
char constexpr RIGHT_FILENAME[] = "cut/female/right_shoulder";
int constexpr SIZE_X_LEFT = 46,
              SIZE_Y_LEFT = 81,
              SIZE_Z_LEFT = 23;
int constexpr SIZE_X_RIGHT = 48,
              SIZE_Y_RIGHT = 81,
              SIZE_Z_RIGHT = 23;

class Size
{
public:
    Size(Size * s): m_x{s->X()}, m_y{s->Y()}, m_z{s->Z()}
    {
        delete s;
    }

    Size(int x,int y,int z): m_x{x}, m_y{y}, m_z{z}
    {}
    int const & X() const { return m_x; };
    int const & Y() const { return m_y; };
    int const & Z() const { return m_z; };
private:
    int const m_x;
    int const m_y;
    int const m_z;
};

class Shoulder
{
public:
    Shoulder(bool l);
    ~Shoulder();
    int const & X() const { return m_size->X(); };
    int const & Y() const { return m_size->Y(); };
    int const & Z() const { return m_size->Z(); };

private:
    int*** m_data;
    bool const m_left;
    std::shared_ptr<Size> m_size;
};
