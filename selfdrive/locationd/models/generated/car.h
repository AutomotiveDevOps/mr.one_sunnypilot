#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_2065986197482277856);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4660576742302856902);
void car_H_mod_fun(double *state, double *out_110190372770704563);
void car_f_fun(double *state, double dt, double *out_3835132985482034285);
void car_F_fun(double *state, double dt, double *out_3293171728534600208);
void car_h_25(double *state, double *unused, double *out_9087532374714242093);
void car_H_25(double *state, double *unused, double *out_9082997853141532674);
void car_h_24(double *state, double *unused, double *out_7439089857388481417);
void car_H_24(double *state, double *unused, double *out_7191096621562519376);
void car_h_30(double *state, double *unused, double *out_7685567916563785125);
void car_H_30(double *state, double *unused, double *out_2166307511649915919);
void car_h_26(double *state, double *unused, double *out_8638347591774450497);
void car_H_26(double *state, double *unused, double *out_5622242901693962718);
void car_h_27(double *state, double *unused, double *out_2880374587233621038);
void car_H_27(double *state, double *unused, double *out_4341070823450340830);
void car_h_29(double *state, double *unused, double *out_6325940385554415297);
void car_H_29(double *state, double *unused, double *out_6054433550319891863);
void car_h_28(double *state, double *unused, double *out_67822483963767655);
void car_H_28(double *state, double *unused, double *out_7309911506320129179);
void car_h_31(double *state, double *unused, double *out_3833154262444286410);
void car_H_31(double *state, double *unused, double *out_9052351891264572246);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}