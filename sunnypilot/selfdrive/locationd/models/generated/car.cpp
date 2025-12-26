#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_1495822306016943310) {
   out_1495822306016943310[0] = delta_x[0] + nom_x[0];
   out_1495822306016943310[1] = delta_x[1] + nom_x[1];
   out_1495822306016943310[2] = delta_x[2] + nom_x[2];
   out_1495822306016943310[3] = delta_x[3] + nom_x[3];
   out_1495822306016943310[4] = delta_x[4] + nom_x[4];
   out_1495822306016943310[5] = delta_x[5] + nom_x[5];
   out_1495822306016943310[6] = delta_x[6] + nom_x[6];
   out_1495822306016943310[7] = delta_x[7] + nom_x[7];
   out_1495822306016943310[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5346728418981959989) {
   out_5346728418981959989[0] = -nom_x[0] + true_x[0];
   out_5346728418981959989[1] = -nom_x[1] + true_x[1];
   out_5346728418981959989[2] = -nom_x[2] + true_x[2];
   out_5346728418981959989[3] = -nom_x[3] + true_x[3];
   out_5346728418981959989[4] = -nom_x[4] + true_x[4];
   out_5346728418981959989[5] = -nom_x[5] + true_x[5];
   out_5346728418981959989[6] = -nom_x[6] + true_x[6];
   out_5346728418981959989[7] = -nom_x[7] + true_x[7];
   out_5346728418981959989[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5298357770380346178) {
   out_5298357770380346178[0] = 1.0;
   out_5298357770380346178[1] = 0.0;
   out_5298357770380346178[2] = 0.0;
   out_5298357770380346178[3] = 0.0;
   out_5298357770380346178[4] = 0.0;
   out_5298357770380346178[5] = 0.0;
   out_5298357770380346178[6] = 0.0;
   out_5298357770380346178[7] = 0.0;
   out_5298357770380346178[8] = 0.0;
   out_5298357770380346178[9] = 0.0;
   out_5298357770380346178[10] = 1.0;
   out_5298357770380346178[11] = 0.0;
   out_5298357770380346178[12] = 0.0;
   out_5298357770380346178[13] = 0.0;
   out_5298357770380346178[14] = 0.0;
   out_5298357770380346178[15] = 0.0;
   out_5298357770380346178[16] = 0.0;
   out_5298357770380346178[17] = 0.0;
   out_5298357770380346178[18] = 0.0;
   out_5298357770380346178[19] = 0.0;
   out_5298357770380346178[20] = 1.0;
   out_5298357770380346178[21] = 0.0;
   out_5298357770380346178[22] = 0.0;
   out_5298357770380346178[23] = 0.0;
   out_5298357770380346178[24] = 0.0;
   out_5298357770380346178[25] = 0.0;
   out_5298357770380346178[26] = 0.0;
   out_5298357770380346178[27] = 0.0;
   out_5298357770380346178[28] = 0.0;
   out_5298357770380346178[29] = 0.0;
   out_5298357770380346178[30] = 1.0;
   out_5298357770380346178[31] = 0.0;
   out_5298357770380346178[32] = 0.0;
   out_5298357770380346178[33] = 0.0;
   out_5298357770380346178[34] = 0.0;
   out_5298357770380346178[35] = 0.0;
   out_5298357770380346178[36] = 0.0;
   out_5298357770380346178[37] = 0.0;
   out_5298357770380346178[38] = 0.0;
   out_5298357770380346178[39] = 0.0;
   out_5298357770380346178[40] = 1.0;
   out_5298357770380346178[41] = 0.0;
   out_5298357770380346178[42] = 0.0;
   out_5298357770380346178[43] = 0.0;
   out_5298357770380346178[44] = 0.0;
   out_5298357770380346178[45] = 0.0;
   out_5298357770380346178[46] = 0.0;
   out_5298357770380346178[47] = 0.0;
   out_5298357770380346178[48] = 0.0;
   out_5298357770380346178[49] = 0.0;
   out_5298357770380346178[50] = 1.0;
   out_5298357770380346178[51] = 0.0;
   out_5298357770380346178[52] = 0.0;
   out_5298357770380346178[53] = 0.0;
   out_5298357770380346178[54] = 0.0;
   out_5298357770380346178[55] = 0.0;
   out_5298357770380346178[56] = 0.0;
   out_5298357770380346178[57] = 0.0;
   out_5298357770380346178[58] = 0.0;
   out_5298357770380346178[59] = 0.0;
   out_5298357770380346178[60] = 1.0;
   out_5298357770380346178[61] = 0.0;
   out_5298357770380346178[62] = 0.0;
   out_5298357770380346178[63] = 0.0;
   out_5298357770380346178[64] = 0.0;
   out_5298357770380346178[65] = 0.0;
   out_5298357770380346178[66] = 0.0;
   out_5298357770380346178[67] = 0.0;
   out_5298357770380346178[68] = 0.0;
   out_5298357770380346178[69] = 0.0;
   out_5298357770380346178[70] = 1.0;
   out_5298357770380346178[71] = 0.0;
   out_5298357770380346178[72] = 0.0;
   out_5298357770380346178[73] = 0.0;
   out_5298357770380346178[74] = 0.0;
   out_5298357770380346178[75] = 0.0;
   out_5298357770380346178[76] = 0.0;
   out_5298357770380346178[77] = 0.0;
   out_5298357770380346178[78] = 0.0;
   out_5298357770380346178[79] = 0.0;
   out_5298357770380346178[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6819373762398369071) {
   out_6819373762398369071[0] = state[0];
   out_6819373762398369071[1] = state[1];
   out_6819373762398369071[2] = state[2];
   out_6819373762398369071[3] = state[3];
   out_6819373762398369071[4] = state[4];
   out_6819373762398369071[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6819373762398369071[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6819373762398369071[7] = state[7];
   out_6819373762398369071[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1597924601777556475) {
   out_1597924601777556475[0] = 1;
   out_1597924601777556475[1] = 0;
   out_1597924601777556475[2] = 0;
   out_1597924601777556475[3] = 0;
   out_1597924601777556475[4] = 0;
   out_1597924601777556475[5] = 0;
   out_1597924601777556475[6] = 0;
   out_1597924601777556475[7] = 0;
   out_1597924601777556475[8] = 0;
   out_1597924601777556475[9] = 0;
   out_1597924601777556475[10] = 1;
   out_1597924601777556475[11] = 0;
   out_1597924601777556475[12] = 0;
   out_1597924601777556475[13] = 0;
   out_1597924601777556475[14] = 0;
   out_1597924601777556475[15] = 0;
   out_1597924601777556475[16] = 0;
   out_1597924601777556475[17] = 0;
   out_1597924601777556475[18] = 0;
   out_1597924601777556475[19] = 0;
   out_1597924601777556475[20] = 1;
   out_1597924601777556475[21] = 0;
   out_1597924601777556475[22] = 0;
   out_1597924601777556475[23] = 0;
   out_1597924601777556475[24] = 0;
   out_1597924601777556475[25] = 0;
   out_1597924601777556475[26] = 0;
   out_1597924601777556475[27] = 0;
   out_1597924601777556475[28] = 0;
   out_1597924601777556475[29] = 0;
   out_1597924601777556475[30] = 1;
   out_1597924601777556475[31] = 0;
   out_1597924601777556475[32] = 0;
   out_1597924601777556475[33] = 0;
   out_1597924601777556475[34] = 0;
   out_1597924601777556475[35] = 0;
   out_1597924601777556475[36] = 0;
   out_1597924601777556475[37] = 0;
   out_1597924601777556475[38] = 0;
   out_1597924601777556475[39] = 0;
   out_1597924601777556475[40] = 1;
   out_1597924601777556475[41] = 0;
   out_1597924601777556475[42] = 0;
   out_1597924601777556475[43] = 0;
   out_1597924601777556475[44] = 0;
   out_1597924601777556475[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1597924601777556475[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1597924601777556475[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1597924601777556475[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1597924601777556475[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1597924601777556475[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1597924601777556475[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1597924601777556475[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1597924601777556475[53] = -9.8100000000000005*dt;
   out_1597924601777556475[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1597924601777556475[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1597924601777556475[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1597924601777556475[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1597924601777556475[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1597924601777556475[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1597924601777556475[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1597924601777556475[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1597924601777556475[62] = 0;
   out_1597924601777556475[63] = 0;
   out_1597924601777556475[64] = 0;
   out_1597924601777556475[65] = 0;
   out_1597924601777556475[66] = 0;
   out_1597924601777556475[67] = 0;
   out_1597924601777556475[68] = 0;
   out_1597924601777556475[69] = 0;
   out_1597924601777556475[70] = 1;
   out_1597924601777556475[71] = 0;
   out_1597924601777556475[72] = 0;
   out_1597924601777556475[73] = 0;
   out_1597924601777556475[74] = 0;
   out_1597924601777556475[75] = 0;
   out_1597924601777556475[76] = 0;
   out_1597924601777556475[77] = 0;
   out_1597924601777556475[78] = 0;
   out_1597924601777556475[79] = 0;
   out_1597924601777556475[80] = 1;
}
void h_25(double *state, double *unused, double *out_8763770437478898383) {
   out_8763770437478898383[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3955198077416968201) {
   out_3955198077416968201[0] = 0;
   out_3955198077416968201[1] = 0;
   out_3955198077416968201[2] = 0;
   out_3955198077416968201[3] = 0;
   out_3955198077416968201[4] = 0;
   out_3955198077416968201[5] = 0;
   out_3955198077416968201[6] = 1;
   out_3955198077416968201[7] = 0;
   out_3955198077416968201[8] = 0;
}
void h_24(double *state, double *unused, double *out_359344665282169121) {
   out_359344665282169121[0] = state[4];
   out_359344665282169121[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6180905861395836763) {
   out_6180905861395836763[0] = 0;
   out_6180905861395836763[1] = 0;
   out_6180905861395836763[2] = 0;
   out_6180905861395836763[3] = 0;
   out_6180905861395836763[4] = 1;
   out_6180905861395836763[5] = 0;
   out_6180905861395836763[6] = 0;
   out_6180905861395836763[7] = 0;
   out_6180905861395836763[8] = 0;
   out_6180905861395836763[9] = 0;
   out_6180905861395836763[10] = 0;
   out_6180905861395836763[11] = 0;
   out_6180905861395836763[12] = 0;
   out_6180905861395836763[13] = 0;
   out_6180905861395836763[14] = 1;
   out_6180905861395836763[15] = 0;
   out_6180905861395836763[16] = 0;
   out_6180905861395836763[17] = 0;
}
void h_30(double *state, double *unused, double *out_8618250613258243412) {
   out_8618250613258243412[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7574855654800966660) {
   out_7574855654800966660[0] = 0;
   out_7574855654800966660[1] = 0;
   out_7574855654800966660[2] = 0;
   out_7574855654800966660[3] = 0;
   out_7574855654800966660[4] = 1;
   out_7574855654800966660[5] = 0;
   out_7574855654800966660[6] = 0;
   out_7574855654800966660[7] = 0;
   out_7574855654800966660[8] = 0;
}
void h_26(double *state, double *unused, double *out_4826820192790462559) {
   out_4826820192790462559[0] = state[7];
}
void H_26(double *state, double *unused, double *out_213694758542911977) {
   out_213694758542911977[0] = 0;
   out_213694758542911977[1] = 0;
   out_213694758542911977[2] = 0;
   out_213694758542911977[3] = 0;
   out_213694758542911977[4] = 0;
   out_213694758542911977[5] = 0;
   out_213694758542911977[6] = 0;
   out_213694758542911977[7] = 1;
   out_213694758542911977[8] = 0;
}
void h_27(double *state, double *unused, double *out_3762097169818052738) {
   out_3762097169818052738[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8697125107108160045) {
   out_8697125107108160045[0] = 0;
   out_8697125107108160045[1] = 0;
   out_8697125107108160045[2] = 0;
   out_8697125107108160045[3] = 1;
   out_8697125107108160045[4] = 0;
   out_8697125107108160045[5] = 0;
   out_8697125107108160045[6] = 0;
   out_8697125107108160045[7] = 0;
   out_8697125107108160045[8] = 0;
}
void h_29(double *state, double *unused, double *out_7860400468097424602) {
   out_7860400468097424602[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7064624310486574476) {
   out_7064624310486574476[0] = 0;
   out_7064624310486574476[1] = 1;
   out_7064624310486574476[2] = 0;
   out_7064624310486574476[3] = 0;
   out_7064624310486574476[4] = 0;
   out_7064624310486574476[5] = 0;
   out_7064624310486574476[6] = 0;
   out_7064624310486574476[7] = 0;
   out_7064624310486574476[8] = 0;
}
void h_28(double *state, double *unused, double *out_4705607022719715173) {
   out_4705607022719715173[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1901363363169078438) {
   out_1901363363169078438[0] = 1;
   out_1901363363169078438[1] = 0;
   out_1901363363169078438[2] = 0;
   out_1901363363169078438[3] = 0;
   out_1901363363169078438[4] = 0;
   out_1901363363169078438[5] = 0;
   out_1901363363169078438[6] = 0;
   out_1901363363169078438[7] = 0;
   out_1901363363169078438[8] = 0;
}
void h_31(double *state, double *unused, double *out_1000505180658225942) {
   out_1000505180658225942[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3985844039293928629) {
   out_3985844039293928629[0] = 0;
   out_3985844039293928629[1] = 0;
   out_3985844039293928629[2] = 0;
   out_3985844039293928629[3] = 0;
   out_3985844039293928629[4] = 0;
   out_3985844039293928629[5] = 0;
   out_3985844039293928629[6] = 0;
   out_3985844039293928629[7] = 0;
   out_3985844039293928629[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_1495822306016943310) {
  err_fun(nom_x, delta_x, out_1495822306016943310);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5346728418981959989) {
  inv_err_fun(nom_x, true_x, out_5346728418981959989);
}
void car_H_mod_fun(double *state, double *out_5298357770380346178) {
  H_mod_fun(state, out_5298357770380346178);
}
void car_f_fun(double *state, double dt, double *out_6819373762398369071) {
  f_fun(state,  dt, out_6819373762398369071);
}
void car_F_fun(double *state, double dt, double *out_1597924601777556475) {
  F_fun(state,  dt, out_1597924601777556475);
}
void car_h_25(double *state, double *unused, double *out_8763770437478898383) {
  h_25(state, unused, out_8763770437478898383);
}
void car_H_25(double *state, double *unused, double *out_3955198077416968201) {
  H_25(state, unused, out_3955198077416968201);
}
void car_h_24(double *state, double *unused, double *out_359344665282169121) {
  h_24(state, unused, out_359344665282169121);
}
void car_H_24(double *state, double *unused, double *out_6180905861395836763) {
  H_24(state, unused, out_6180905861395836763);
}
void car_h_30(double *state, double *unused, double *out_8618250613258243412) {
  h_30(state, unused, out_8618250613258243412);
}
void car_H_30(double *state, double *unused, double *out_7574855654800966660) {
  H_30(state, unused, out_7574855654800966660);
}
void car_h_26(double *state, double *unused, double *out_4826820192790462559) {
  h_26(state, unused, out_4826820192790462559);
}
void car_H_26(double *state, double *unused, double *out_213694758542911977) {
  H_26(state, unused, out_213694758542911977);
}
void car_h_27(double *state, double *unused, double *out_3762097169818052738) {
  h_27(state, unused, out_3762097169818052738);
}
void car_H_27(double *state, double *unused, double *out_8697125107108160045) {
  H_27(state, unused, out_8697125107108160045);
}
void car_h_29(double *state, double *unused, double *out_7860400468097424602) {
  h_29(state, unused, out_7860400468097424602);
}
void car_H_29(double *state, double *unused, double *out_7064624310486574476) {
  H_29(state, unused, out_7064624310486574476);
}
void car_h_28(double *state, double *unused, double *out_4705607022719715173) {
  h_28(state, unused, out_4705607022719715173);
}
void car_H_28(double *state, double *unused, double *out_1901363363169078438) {
  H_28(state, unused, out_1901363363169078438);
}
void car_h_31(double *state, double *unused, double *out_1000505180658225942) {
  h_31(state, unused, out_1000505180658225942);
}
void car_H_31(double *state, double *unused, double *out_3985844039293928629) {
  H_31(state, unused, out_3985844039293928629);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
