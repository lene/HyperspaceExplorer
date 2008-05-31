#include "Rotation.H"

namespace VecMath {

    const unsigned RotationAxes<3>::_axis[2][3] = {
        { 1, 0, 0 }, { 2, 2, 1}
    };

    const unsigned RotationAxes<4>::_axis[2][6] = {
        { 0, 0, 0, 1, 1, 2 }, { 1, 2, 3, 2, 3, 3 }
    };

    template <> Rotation<4>::operator Matrix<4>() const {
        Matrix<4> Rxy = Matrix<4> (0, 1, axis[0]), Rxz = Matrix<4> (0, 2, axis[1]),
                  Rxw = Matrix<4> (0, 3, axis[2]),  Ryz = Matrix<4> (1, 2, axis[3]),
                  Ryw = Matrix<4> (1, 3, axis[4]), Rzw = Matrix<4> (2, 3, axis[5]),
                  Rxyz = Rxy*Rxz, Rxwyz = Rxw*Ryz, Ryzw = Ryw*Rzw,
                  Rot = Rxyz*Rxwyz*Ryzw;

        return Rot;
    }

    template <> Rotation<3>::operator Matrix<3>() const {
        Matrix<3> Rx = Matrix<3> (1, 2, axis[0]), Ry = Matrix<3> (0, 2, axis[1]),
                  Rz = Matrix<3> (0, 1, axis[2]),
                  Rot = Rx*Ry*Rz;

        return Rot;
    }
}
