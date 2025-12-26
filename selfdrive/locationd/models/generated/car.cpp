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
void err_fun(double *nom_x, double *delta_x, double *out_2065986197482277856) {
   out_2065986197482277856[0] = delta_x[0] + nom_x[0];
   out_2065986197482277856[1] = delta_x[1] + nom_x[1];
   out_2065986197482277856[2] = delta_x[2] + nom_x[2];
   out_2065986197482277856[3] = delta_x[3] + nom_x[3];
   out_2065986197482277856[4] = delta_x[4] + nom_x[4];
   out_2065986197482277856[5] = delta_x[5] + nom_x[5];
   out_2065986197482277856[6] = delta_x[6] + nom_x[6];
   out_2065986197482277856[7] = delta_x[7] + nom_x[7];
   out_2065986197482277856[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4660576742302856902) {
   out_4660576742302856902[0] = -nom_x[0] + true_x[0];
   out_4660576742302856902[1] = -nom_x[1] + true_x[1];
   out_4660576742302856902[2] = -nom_x[2] + true_x[2];
   out_4660576742302856902[3] = -nom_x[3] + true_x[3];
   out_4660576742302856902[4] = -nom_x[4] + true_x[4];
   out_4660576742302856902[5] = -nom_x[5] + true_x[5];
   out_4660576742302856902[6] = -nom_x[6] + true_x[6];
   out_4660576742302856902[7] = -nom_x[7] + true_x[7];
   out_4660576742302856902[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_110190372770704563) {
   out_110190372770704563[0] = 1.0;
   out_110190372770704563[1] = 0.0;
   out_110190372770704563[2] = 0.0;
   out_110190372770704563[3] = 0.0;
   out_110190372770704563[4] = 0.0;
   out_110190372770704563[5] = 0.0;
   out_110190372770704563[6] = 0.0;
   out_110190372770704563[7] = 0.0;
   out_110190372770704563[8] = 0.0;
   out_110190372770704563[9] = 0.0;
   out_110190372770704563[10] = 1.0;
   out_110190372770704563[11] = 0.0;
   out_110190372770704563[12] = 0.0;
   out_110190372770704563[13] = 0.0;
   out_110190372770704563[14] = 0.0;
   out_110190372770704563[15] = 0.0;
   out_110190372770704563[16] = 0.0;
   out_110190372770704563[17] = 0.0;
   out_110190372770704563[18] = 0.0;
   out_110190372770704563[19] = 0.0;
   out_110190372770704563[20] = 1.0;
   out_110190372770704563[21] = 0.0;
   out_110190372770704563[22] = 0.0;
   out_110190372770704563[23] = 0.0;
   out_110190372770704563[24] = 0.0;
   out_110190372770704563[25] = 0.0;
   out_110190372770704563[26] = 0.0;
   out_110190372770704563[27] = 0.0;
   out_110190372770704563[28] = 0.0;
   out_110190372770704563[29] = 0.0;
   out_110190372770704563[30] = 1.0;
   out_110190372770704563[31] = 0.0;
   out_110190372770704563[32] = 0.0;
   out_110190372770704563[33] = 0.0;
   out_110190372770704563[34] = 0.0;
   out_110190372770704563[35] = 0.0;
   out_110190372770704563[36] = 0.0;
   out_110190372770704563[37] = 0.0;
   out_110190372770704563[38] = 0.0;
   out_110190372770704563[39] = 0.0;
   out_110190372770704563[40] = 1.0;
   out_110190372770704563[41] = 0.0;
   out_110190372770704563[42] = 0.0;
   out_110190372770704563[43] = 0.0;
   out_110190372770704563[44] = 0.0;
   out_110190372770704563[45] = 0.0;
   out_110190372770704563[46] = 0.0;
   out_110190372770704563[47] = 0.0;
   out_110190372770704563[48] = 0.0;
   out_110190372770704563[49] = 0.0;
   out_110190372770704563[50] = 1.0;
   out_110190372770704563[51] = 0.0;
   out_110190372770704563[52] = 0.0;
   out_110190372770704563[53] = 0.0;
   out_110190372770704563[54] = 0.0;
   out_110190372770704563[55] = 0.0;
   out_110190372770704563[56] = 0.0;
   out_110190372770704563[57] = 0.0;
   out_110190372770704563[58] = 0.0;
   out_110190372770704563[59] = 0.0;
   out_110190372770704563[60] = 1.0;
   out_110190372770704563[61] = 0.0;
   out_110190372770704563[62] = 0.0;
   out_110190372770704563[63] = 0.0;
   out_110190372770704563[64] = 0.0;
   out_110190372770704563[65] = 0.0;
   out_110190372770704563[66] = 0.0;
   out_110190372770704563[67] = 0.0;
   out_110190372770704563[68] = 0.0;
   out_110190372770704563[69] = 0.0;
   out_110190372770704563[70] = 1.0;
   out_110190372770704563[71] = 0.0;
   out_110190372770704563[72] = 0.0;
   out_110190372770704563[73] = 0.0;
   out_110190372770704563[74] = 0.0;
   out_110190372770704563[75] = 0.0;
   out_110190372770704563[76] = 0.0;
   out_110190372770704563[77] = 0.0;
   out_110190372770704563[78] = 0.0;
   out_110190372770704563[79] = 0.0;
   out_110190372770704563[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3835132985482034285) {
   out_3835132985482034285[0] = state[0];
   out_3835132985482034285[1] = state[1];
   out_3835132985482034285[2] = state[2];
   out_3835132985482034285[3] = state[3];
   out_3835132985482034285[4] = state[4];
   out_3835132985482034285[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3835132985482034285[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3835132985482034285[7] = state[7];
   out_3835132985482034285[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3293171728534600208) {
   out_3293171728534600208[0] = 1;
   out_3293171728534600208[1] = 0;
   out_3293171728534600208[2] = 0;
   out_3293171728534600208[3] = 0;
   out_3293171728534600208[4] = 0;
   out_3293171728534600208[5] = 0;
   out_3293171728534600208[6] = 0;
   out_3293171728534600208[7] = 0;
   out_3293171728534600208[8] = 0;
   out_3293171728534600208[9] = 0;
   out_3293171728534600208[10] = 1;
   out_3293171728534600208[11] = 0;
   out_3293171728534600208[12] = 0;
   out_3293171728534600208[13] = 0;
   out_3293171728534600208[14] = 0;
   out_3293171728534600208[15] = 0;
   out_3293171728534600208[16] = 0;
   out_3293171728534600208[17] = 0;
   out_3293171728534600208[18] = 0;
   out_3293171728534600208[19] = 0;
   out_3293171728534600208[20] = 1;
   out_3293171728534600208[21] = 0;
   out_3293171728534600208[22] = 0;
   out_3293171728534600208[23] = 0;
   out_3293171728534600208[24] = 0;
   out_3293171728534600208[25] = 0;
   out_3293171728534600208[26] = 0;
   out_3293171728534600208[27] = 0;
   out_3293171728534600208[28] = 0;
   out_3293171728534600208[29] = 0;
   out_3293171728534600208[30] = 1;
   out_3293171728534600208[31] = 0;
   out_3293171728534600208[32] = 0;
   out_3293171728534600208[33] = 0;
   out_3293171728534600208[34] = 0;
   out_3293171728534600208[35] = 0;
   out_3293171728534600208[36] = 0;
   out_3293171728534600208[37] = 0;
   out_3293171728534600208[38] = 0;
   out_3293171728534600208[39] = 0;
   out_3293171728534600208[40] = 1;
   out_3293171728534600208[41] = 0;
   out_3293171728534600208[42] = 0;
   out_3293171728534600208[43] = 0;
   out_3293171728534600208[44] = 0;
   out_3293171728534600208[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3293171728534600208[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3293171728534600208[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3293171728534600208[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3293171728534600208[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3293171728534600208[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3293171728534600208[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3293171728534600208[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3293171728534600208[53] = -9.8100000000000005*dt;
   out_3293171728534600208[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3293171728534600208[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3293171728534600208[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3293171728534600208[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3293171728534600208[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3293171728534600208[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3293171728534600208[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3293171728534600208[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3293171728534600208[62] = 0;
   out_3293171728534600208[63] = 0;
   out_3293171728534600208[64] = 0;
   out_3293171728534600208[65] = 0;
   out_3293171728534600208[66] = 0;
   out_3293171728534600208[67] = 0;
   out_3293171728534600208[68] = 0;
   out_3293171728534600208[69] = 0;
   out_3293171728534600208[70] = 1;
   out_3293171728534600208[71] = 0;
   out_3293171728534600208[72] = 0;
   out_3293171728534600208[73] = 0;
   out_3293171728534600208[74] = 0;
   out_3293171728534600208[75] = 0;
   out_3293171728534600208[76] = 0;
   out_3293171728534600208[77] = 0;
   out_3293171728534600208[78] = 0;
   out_3293171728534600208[79] = 0;
   out_3293171728534600208[80] = 1;
}
void h_25(double *state, double *unused, double *out_9087532374714242093) {
   out_9087532374714242093[0] = state[6];
}
void H_25(double *state, double *unused, double *out_9082997853141532674) {
   out_9082997853141532674[0] = 0;
   out_9082997853141532674[1] = 0;
   out_9082997853141532674[2] = 0;
   out_9082997853141532674[3] = 0;
   out_9082997853141532674[4] = 0;
   out_9082997853141532674[5] = 0;
   out_9082997853141532674[6] = 1;
   out_9082997853141532674[7] = 0;
   out_9082997853141532674[8] = 0;
}
void h_24(double *state, double *unused, double *out_7439089857388481417) {
   out_7439089857388481417[0] = state[4];
   out_7439089857388481417[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7191096621562519376) {
   out_7191096621562519376[0] = 0;
   out_7191096621562519376[1] = 0;
   out_7191096621562519376[2] = 0;
   out_7191096621562519376[3] = 0;
   out_7191096621562519376[4] = 1;
   out_7191096621562519376[5] = 0;
   out_7191096621562519376[6] = 0;
   out_7191096621562519376[7] = 0;
   out_7191096621562519376[8] = 0;
   out_7191096621562519376[9] = 0;
   out_7191096621562519376[10] = 0;
   out_7191096621562519376[11] = 0;
   out_7191096621562519376[12] = 0;
   out_7191096621562519376[13] = 0;
   out_7191096621562519376[14] = 1;
   out_7191096621562519376[15] = 0;
   out_7191096621562519376[16] = 0;
   out_7191096621562519376[17] = 0;
}
void h_30(double *state, double *unused, double *out_7685567916563785125) {
   out_7685567916563785125[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2166307511649915919) {
   out_2166307511649915919[0] = 0;
   out_2166307511649915919[1] = 0;
   out_2166307511649915919[2] = 0;
   out_2166307511649915919[3] = 0;
   out_2166307511649915919[4] = 1;
   out_2166307511649915919[5] = 0;
   out_2166307511649915919[6] = 0;
   out_2166307511649915919[7] = 0;
   out_2166307511649915919[8] = 0;
}
void h_26(double *state, double *unused, double *out_8638347591774450497) {
   out_8638347591774450497[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5622242901693962718) {
   out_5622242901693962718[0] = 0;
   out_5622242901693962718[1] = 0;
   out_5622242901693962718[2] = 0;
   out_5622242901693962718[3] = 0;
   out_5622242901693962718[4] = 0;
   out_5622242901693962718[5] = 0;
   out_5622242901693962718[6] = 0;
   out_5622242901693962718[7] = 1;
   out_5622242901693962718[8] = 0;
}
void h_27(double *state, double *unused, double *out_2880374587233621038) {
   out_2880374587233621038[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4341070823450340830) {
   out_4341070823450340830[0] = 0;
   out_4341070823450340830[1] = 0;
   out_4341070823450340830[2] = 0;
   out_4341070823450340830[3] = 1;
   out_4341070823450340830[4] = 0;
   out_4341070823450340830[5] = 0;
   out_4341070823450340830[6] = 0;
   out_4341070823450340830[7] = 0;
   out_4341070823450340830[8] = 0;
}
void h_29(double *state, double *unused, double *out_6325940385554415297) {
   out_6325940385554415297[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6054433550319891863) {
   out_6054433550319891863[0] = 0;
   out_6054433550319891863[1] = 1;
   out_6054433550319891863[2] = 0;
   out_6054433550319891863[3] = 0;
   out_6054433550319891863[4] = 0;
   out_6054433550319891863[5] = 0;
   out_6054433550319891863[6] = 0;
   out_6054433550319891863[7] = 0;
   out_6054433550319891863[8] = 0;
}
void h_28(double *state, double *unused, double *out_67822483963767655) {
   out_67822483963767655[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7309911506320129179) {
   out_7309911506320129179[0] = 1;
   out_7309911506320129179[1] = 0;
   out_7309911506320129179[2] = 0;
   out_7309911506320129179[3] = 0;
   out_7309911506320129179[4] = 0;
   out_7309911506320129179[5] = 0;
   out_7309911506320129179[6] = 0;
   out_7309911506320129179[7] = 0;
   out_7309911506320129179[8] = 0;
}
void h_31(double *state, double *unused, double *out_3833154262444286410) {
   out_3833154262444286410[0] = state[8];
}
void H_31(double *state, double *unused, double *out_9052351891264572246) {
   out_9052351891264572246[0] = 0;
   out_9052351891264572246[1] = 0;
   out_9052351891264572246[2] = 0;
   out_9052351891264572246[3] = 0;
   out_9052351891264572246[4] = 0;
   out_9052351891264572246[5] = 0;
   out_9052351891264572246[6] = 0;
   out_9052351891264572246[7] = 0;
   out_9052351891264572246[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2065986197482277856) {
  err_fun(nom_x, delta_x, out_2065986197482277856);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4660576742302856902) {
  inv_err_fun(nom_x, true_x, out_4660576742302856902);
}
void car_H_mod_fun(double *state, double *out_110190372770704563) {
  H_mod_fun(state, out_110190372770704563);
}
void car_f_fun(double *state, double dt, double *out_3835132985482034285) {
  f_fun(state,  dt, out_3835132985482034285);
}
void car_F_fun(double *state, double dt, double *out_3293171728534600208) {
  F_fun(state,  dt, out_3293171728534600208);
}
void car_h_25(double *state, double *unused, double *out_9087532374714242093) {
  h_25(state, unused, out_9087532374714242093);
}
void car_H_25(double *state, double *unused, double *out_9082997853141532674) {
  H_25(state, unused, out_9082997853141532674);
}
void car_h_24(double *state, double *unused, double *out_7439089857388481417) {
  h_24(state, unused, out_7439089857388481417);
}
void car_H_24(double *state, double *unused, double *out_7191096621562519376) {
  H_24(state, unused, out_7191096621562519376);
}
void car_h_30(double *state, double *unused, double *out_7685567916563785125) {
  h_30(state, unused, out_7685567916563785125);
}
void car_H_30(double *state, double *unused, double *out_2166307511649915919) {
  H_30(state, unused, out_2166307511649915919);
}
void car_h_26(double *state, double *unused, double *out_8638347591774450497) {
  h_26(state, unused, out_8638347591774450497);
}
void car_H_26(double *state, double *unused, double *out_5622242901693962718) {
  H_26(state, unused, out_5622242901693962718);
}
void car_h_27(double *state, double *unused, double *out_2880374587233621038) {
  h_27(state, unused, out_2880374587233621038);
}
void car_H_27(double *state, double *unused, double *out_4341070823450340830) {
  H_27(state, unused, out_4341070823450340830);
}
void car_h_29(double *state, double *unused, double *out_6325940385554415297) {
  h_29(state, unused, out_6325940385554415297);
}
void car_H_29(double *state, double *unused, double *out_6054433550319891863) {
  H_29(state, unused, out_6054433550319891863);
}
void car_h_28(double *state, double *unused, double *out_67822483963767655) {
  h_28(state, unused, out_67822483963767655);
}
void car_H_28(double *state, double *unused, double *out_7309911506320129179) {
  H_28(state, unused, out_7309911506320129179);
}
void car_h_31(double *state, double *unused, double *out_3833154262444286410) {
  h_31(state, unused, out_3833154262444286410);
}
void car_H_31(double *state, double *unused, double *out_9052351891264572246) {
  H_31(state, unused, out_9052351891264572246);
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
