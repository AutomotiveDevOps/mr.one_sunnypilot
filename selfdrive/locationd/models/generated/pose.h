#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5045866649768905313);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8605282873688095256);
void pose_H_mod_fun(double *state, double *out_1951764618460370916);
void pose_f_fun(double *state, double dt, double *out_9131418681283073727);
void pose_F_fun(double *state, double dt, double *out_7332136968328018376);
void pose_h_4(double *state, double *unused, double *out_2574344235091918444);
void pose_H_4(double *state, double *unused, double *out_5723571828304278488);
void pose_h_10(double *state, double *unused, double *out_6588171587677358326);
void pose_H_10(double *state, double *unused, double *out_8713079387063064920);
void pose_h_13(double *state, double *unused, double *out_5152739096252851195);
void pose_H_13(double *state, double *unused, double *out_8935845653636611289);
void pose_h_14(double *state, double *unused, double *out_4540428471259618960);
void pose_H_14(double *state, double *unused, double *out_2640783396008906192);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}