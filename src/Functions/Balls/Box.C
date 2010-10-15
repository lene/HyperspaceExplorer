
#include "Box.H"
#include "Matrix.H"


double BoxBase::friction = 0.,
       BoxBase::max_t = 100.,
       BoxBase::elasticity = 1.,
       BoxBase::gravity = 0.;
bool BoxBase::sloppy = false;

double Box<2>::Xcam[];
Vec<2> Box<2>::vertices[];
Vec<2> Box<2>::vtrans[];
matrix<2> Box<2>::R;

double Box<3>::Xcam[];
Vec<3> Box<3>::vertices[];
Vec<3> Box<3>::vtrans[];
matrix<3> Box<3>::R;

double Box<4>::Xcam[];
Vec<4> Box<4>::vertices[];
Vec<4> Box<4>::vtrans[];
matrix<4> Box<4>::R;

double Box<5>::Xcam[];
Vec<5> Box<5>::vertices[];
Vec<5> Box<5>::vtrans[];
matrix<5> Box<5>::R;

double Box<6>::Xcam[];
Vec<6> Box<6>::vertices[];
Vec<6> Box<6>::vtrans[];
matrix<6> Box<6>::R;

double Box<7>::Xcam[];
Vec<7> Box<7>::vertices[];
Vec<7> Box<7>::vtrans[];
matrix<7> Box<7>::R;

double Box<8>::Xcam[];
Vec<8> Box<8>::vertices[];
Vec<8> Box<8>::vtrans[];
matrix<8> Box<8>::R;

double Box<9>::Xcam[];
Vec<9> Box<9>::vertices[];
Vec<9> Box<9>::vtrans[];
matrix<9> Box<9>::R;


BoxBase::BoxBase ():
    num_collisions (0), t (0.) { }


