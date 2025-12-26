#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_6266893198231237979);
void live_err_fun(double *nom_x, double *delta_x, double *out_2556696738617185850);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_6026804354882225494);
void live_H_mod_fun(double *state, double *out_9172097458523039436);
void live_f_fun(double *state, double dt, double *out_6347583497580092832);
void live_F_fun(double *state, double dt, double *out_5083381771866625158);
void live_h_4(double *state, double *unused, double *out_5235185666751532562);
void live_H_4(double *state, double *unused, double *out_1851372745047718404);
void live_h_9(double *state, double *unused, double *out_2388176640729125203);
void live_H_9(double *state, double *unused, double *out_1610183098418127759);
void live_h_10(double *state, double *unused, double *out_7588760419434127912);
void live_H_10(double *state, double *unused, double *out_9119916348562345627);
void live_h_12(double *state, double *unused, double *out_3997380577892493688);
void live_H_12(double *state, double *unused, double *out_3168083662984243391);
void live_h_35(double *state, double *unused, double *out_3820371934705095865);
void live_H_35(double *state, double *unused, double *out_1515289312324888972);
void live_h_32(double *state, double *unused, double *out_5859554445355791964);
void live_H_32(double *state, double *unused, double *out_1646454097265629441);
void live_h_13(double *state, double *unused, double *out_269158530397702062);
void live_H_13(double *state, double *unused, double *out_5352583280434267736);
void live_h_14(double *state, double *unused, double *out_2388176640729125203);
void live_H_14(double *state, double *unused, double *out_1610183098418127759);
void live_h_33(double *state, double *unused, double *out_961704079123598542);
void live_H_33(double *state, double *unused, double *out_4665846316963746576);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}