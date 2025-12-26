#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_5045866649768905313) {
   out_5045866649768905313[0] = delta_x[0] + nom_x[0];
   out_5045866649768905313[1] = delta_x[1] + nom_x[1];
   out_5045866649768905313[2] = delta_x[2] + nom_x[2];
   out_5045866649768905313[3] = delta_x[3] + nom_x[3];
   out_5045866649768905313[4] = delta_x[4] + nom_x[4];
   out_5045866649768905313[5] = delta_x[5] + nom_x[5];
   out_5045866649768905313[6] = delta_x[6] + nom_x[6];
   out_5045866649768905313[7] = delta_x[7] + nom_x[7];
   out_5045866649768905313[8] = delta_x[8] + nom_x[8];
   out_5045866649768905313[9] = delta_x[9] + nom_x[9];
   out_5045866649768905313[10] = delta_x[10] + nom_x[10];
   out_5045866649768905313[11] = delta_x[11] + nom_x[11];
   out_5045866649768905313[12] = delta_x[12] + nom_x[12];
   out_5045866649768905313[13] = delta_x[13] + nom_x[13];
   out_5045866649768905313[14] = delta_x[14] + nom_x[14];
   out_5045866649768905313[15] = delta_x[15] + nom_x[15];
   out_5045866649768905313[16] = delta_x[16] + nom_x[16];
   out_5045866649768905313[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8605282873688095256) {
   out_8605282873688095256[0] = -nom_x[0] + true_x[0];
   out_8605282873688095256[1] = -nom_x[1] + true_x[1];
   out_8605282873688095256[2] = -nom_x[2] + true_x[2];
   out_8605282873688095256[3] = -nom_x[3] + true_x[3];
   out_8605282873688095256[4] = -nom_x[4] + true_x[4];
   out_8605282873688095256[5] = -nom_x[5] + true_x[5];
   out_8605282873688095256[6] = -nom_x[6] + true_x[6];
   out_8605282873688095256[7] = -nom_x[7] + true_x[7];
   out_8605282873688095256[8] = -nom_x[8] + true_x[8];
   out_8605282873688095256[9] = -nom_x[9] + true_x[9];
   out_8605282873688095256[10] = -nom_x[10] + true_x[10];
   out_8605282873688095256[11] = -nom_x[11] + true_x[11];
   out_8605282873688095256[12] = -nom_x[12] + true_x[12];
   out_8605282873688095256[13] = -nom_x[13] + true_x[13];
   out_8605282873688095256[14] = -nom_x[14] + true_x[14];
   out_8605282873688095256[15] = -nom_x[15] + true_x[15];
   out_8605282873688095256[16] = -nom_x[16] + true_x[16];
   out_8605282873688095256[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_1951764618460370916) {
   out_1951764618460370916[0] = 1.0;
   out_1951764618460370916[1] = 0.0;
   out_1951764618460370916[2] = 0.0;
   out_1951764618460370916[3] = 0.0;
   out_1951764618460370916[4] = 0.0;
   out_1951764618460370916[5] = 0.0;
   out_1951764618460370916[6] = 0.0;
   out_1951764618460370916[7] = 0.0;
   out_1951764618460370916[8] = 0.0;
   out_1951764618460370916[9] = 0.0;
   out_1951764618460370916[10] = 0.0;
   out_1951764618460370916[11] = 0.0;
   out_1951764618460370916[12] = 0.0;
   out_1951764618460370916[13] = 0.0;
   out_1951764618460370916[14] = 0.0;
   out_1951764618460370916[15] = 0.0;
   out_1951764618460370916[16] = 0.0;
   out_1951764618460370916[17] = 0.0;
   out_1951764618460370916[18] = 0.0;
   out_1951764618460370916[19] = 1.0;
   out_1951764618460370916[20] = 0.0;
   out_1951764618460370916[21] = 0.0;
   out_1951764618460370916[22] = 0.0;
   out_1951764618460370916[23] = 0.0;
   out_1951764618460370916[24] = 0.0;
   out_1951764618460370916[25] = 0.0;
   out_1951764618460370916[26] = 0.0;
   out_1951764618460370916[27] = 0.0;
   out_1951764618460370916[28] = 0.0;
   out_1951764618460370916[29] = 0.0;
   out_1951764618460370916[30] = 0.0;
   out_1951764618460370916[31] = 0.0;
   out_1951764618460370916[32] = 0.0;
   out_1951764618460370916[33] = 0.0;
   out_1951764618460370916[34] = 0.0;
   out_1951764618460370916[35] = 0.0;
   out_1951764618460370916[36] = 0.0;
   out_1951764618460370916[37] = 0.0;
   out_1951764618460370916[38] = 1.0;
   out_1951764618460370916[39] = 0.0;
   out_1951764618460370916[40] = 0.0;
   out_1951764618460370916[41] = 0.0;
   out_1951764618460370916[42] = 0.0;
   out_1951764618460370916[43] = 0.0;
   out_1951764618460370916[44] = 0.0;
   out_1951764618460370916[45] = 0.0;
   out_1951764618460370916[46] = 0.0;
   out_1951764618460370916[47] = 0.0;
   out_1951764618460370916[48] = 0.0;
   out_1951764618460370916[49] = 0.0;
   out_1951764618460370916[50] = 0.0;
   out_1951764618460370916[51] = 0.0;
   out_1951764618460370916[52] = 0.0;
   out_1951764618460370916[53] = 0.0;
   out_1951764618460370916[54] = 0.0;
   out_1951764618460370916[55] = 0.0;
   out_1951764618460370916[56] = 0.0;
   out_1951764618460370916[57] = 1.0;
   out_1951764618460370916[58] = 0.0;
   out_1951764618460370916[59] = 0.0;
   out_1951764618460370916[60] = 0.0;
   out_1951764618460370916[61] = 0.0;
   out_1951764618460370916[62] = 0.0;
   out_1951764618460370916[63] = 0.0;
   out_1951764618460370916[64] = 0.0;
   out_1951764618460370916[65] = 0.0;
   out_1951764618460370916[66] = 0.0;
   out_1951764618460370916[67] = 0.0;
   out_1951764618460370916[68] = 0.0;
   out_1951764618460370916[69] = 0.0;
   out_1951764618460370916[70] = 0.0;
   out_1951764618460370916[71] = 0.0;
   out_1951764618460370916[72] = 0.0;
   out_1951764618460370916[73] = 0.0;
   out_1951764618460370916[74] = 0.0;
   out_1951764618460370916[75] = 0.0;
   out_1951764618460370916[76] = 1.0;
   out_1951764618460370916[77] = 0.0;
   out_1951764618460370916[78] = 0.0;
   out_1951764618460370916[79] = 0.0;
   out_1951764618460370916[80] = 0.0;
   out_1951764618460370916[81] = 0.0;
   out_1951764618460370916[82] = 0.0;
   out_1951764618460370916[83] = 0.0;
   out_1951764618460370916[84] = 0.0;
   out_1951764618460370916[85] = 0.0;
   out_1951764618460370916[86] = 0.0;
   out_1951764618460370916[87] = 0.0;
   out_1951764618460370916[88] = 0.0;
   out_1951764618460370916[89] = 0.0;
   out_1951764618460370916[90] = 0.0;
   out_1951764618460370916[91] = 0.0;
   out_1951764618460370916[92] = 0.0;
   out_1951764618460370916[93] = 0.0;
   out_1951764618460370916[94] = 0.0;
   out_1951764618460370916[95] = 1.0;
   out_1951764618460370916[96] = 0.0;
   out_1951764618460370916[97] = 0.0;
   out_1951764618460370916[98] = 0.0;
   out_1951764618460370916[99] = 0.0;
   out_1951764618460370916[100] = 0.0;
   out_1951764618460370916[101] = 0.0;
   out_1951764618460370916[102] = 0.0;
   out_1951764618460370916[103] = 0.0;
   out_1951764618460370916[104] = 0.0;
   out_1951764618460370916[105] = 0.0;
   out_1951764618460370916[106] = 0.0;
   out_1951764618460370916[107] = 0.0;
   out_1951764618460370916[108] = 0.0;
   out_1951764618460370916[109] = 0.0;
   out_1951764618460370916[110] = 0.0;
   out_1951764618460370916[111] = 0.0;
   out_1951764618460370916[112] = 0.0;
   out_1951764618460370916[113] = 0.0;
   out_1951764618460370916[114] = 1.0;
   out_1951764618460370916[115] = 0.0;
   out_1951764618460370916[116] = 0.0;
   out_1951764618460370916[117] = 0.0;
   out_1951764618460370916[118] = 0.0;
   out_1951764618460370916[119] = 0.0;
   out_1951764618460370916[120] = 0.0;
   out_1951764618460370916[121] = 0.0;
   out_1951764618460370916[122] = 0.0;
   out_1951764618460370916[123] = 0.0;
   out_1951764618460370916[124] = 0.0;
   out_1951764618460370916[125] = 0.0;
   out_1951764618460370916[126] = 0.0;
   out_1951764618460370916[127] = 0.0;
   out_1951764618460370916[128] = 0.0;
   out_1951764618460370916[129] = 0.0;
   out_1951764618460370916[130] = 0.0;
   out_1951764618460370916[131] = 0.0;
   out_1951764618460370916[132] = 0.0;
   out_1951764618460370916[133] = 1.0;
   out_1951764618460370916[134] = 0.0;
   out_1951764618460370916[135] = 0.0;
   out_1951764618460370916[136] = 0.0;
   out_1951764618460370916[137] = 0.0;
   out_1951764618460370916[138] = 0.0;
   out_1951764618460370916[139] = 0.0;
   out_1951764618460370916[140] = 0.0;
   out_1951764618460370916[141] = 0.0;
   out_1951764618460370916[142] = 0.0;
   out_1951764618460370916[143] = 0.0;
   out_1951764618460370916[144] = 0.0;
   out_1951764618460370916[145] = 0.0;
   out_1951764618460370916[146] = 0.0;
   out_1951764618460370916[147] = 0.0;
   out_1951764618460370916[148] = 0.0;
   out_1951764618460370916[149] = 0.0;
   out_1951764618460370916[150] = 0.0;
   out_1951764618460370916[151] = 0.0;
   out_1951764618460370916[152] = 1.0;
   out_1951764618460370916[153] = 0.0;
   out_1951764618460370916[154] = 0.0;
   out_1951764618460370916[155] = 0.0;
   out_1951764618460370916[156] = 0.0;
   out_1951764618460370916[157] = 0.0;
   out_1951764618460370916[158] = 0.0;
   out_1951764618460370916[159] = 0.0;
   out_1951764618460370916[160] = 0.0;
   out_1951764618460370916[161] = 0.0;
   out_1951764618460370916[162] = 0.0;
   out_1951764618460370916[163] = 0.0;
   out_1951764618460370916[164] = 0.0;
   out_1951764618460370916[165] = 0.0;
   out_1951764618460370916[166] = 0.0;
   out_1951764618460370916[167] = 0.0;
   out_1951764618460370916[168] = 0.0;
   out_1951764618460370916[169] = 0.0;
   out_1951764618460370916[170] = 0.0;
   out_1951764618460370916[171] = 1.0;
   out_1951764618460370916[172] = 0.0;
   out_1951764618460370916[173] = 0.0;
   out_1951764618460370916[174] = 0.0;
   out_1951764618460370916[175] = 0.0;
   out_1951764618460370916[176] = 0.0;
   out_1951764618460370916[177] = 0.0;
   out_1951764618460370916[178] = 0.0;
   out_1951764618460370916[179] = 0.0;
   out_1951764618460370916[180] = 0.0;
   out_1951764618460370916[181] = 0.0;
   out_1951764618460370916[182] = 0.0;
   out_1951764618460370916[183] = 0.0;
   out_1951764618460370916[184] = 0.0;
   out_1951764618460370916[185] = 0.0;
   out_1951764618460370916[186] = 0.0;
   out_1951764618460370916[187] = 0.0;
   out_1951764618460370916[188] = 0.0;
   out_1951764618460370916[189] = 0.0;
   out_1951764618460370916[190] = 1.0;
   out_1951764618460370916[191] = 0.0;
   out_1951764618460370916[192] = 0.0;
   out_1951764618460370916[193] = 0.0;
   out_1951764618460370916[194] = 0.0;
   out_1951764618460370916[195] = 0.0;
   out_1951764618460370916[196] = 0.0;
   out_1951764618460370916[197] = 0.0;
   out_1951764618460370916[198] = 0.0;
   out_1951764618460370916[199] = 0.0;
   out_1951764618460370916[200] = 0.0;
   out_1951764618460370916[201] = 0.0;
   out_1951764618460370916[202] = 0.0;
   out_1951764618460370916[203] = 0.0;
   out_1951764618460370916[204] = 0.0;
   out_1951764618460370916[205] = 0.0;
   out_1951764618460370916[206] = 0.0;
   out_1951764618460370916[207] = 0.0;
   out_1951764618460370916[208] = 0.0;
   out_1951764618460370916[209] = 1.0;
   out_1951764618460370916[210] = 0.0;
   out_1951764618460370916[211] = 0.0;
   out_1951764618460370916[212] = 0.0;
   out_1951764618460370916[213] = 0.0;
   out_1951764618460370916[214] = 0.0;
   out_1951764618460370916[215] = 0.0;
   out_1951764618460370916[216] = 0.0;
   out_1951764618460370916[217] = 0.0;
   out_1951764618460370916[218] = 0.0;
   out_1951764618460370916[219] = 0.0;
   out_1951764618460370916[220] = 0.0;
   out_1951764618460370916[221] = 0.0;
   out_1951764618460370916[222] = 0.0;
   out_1951764618460370916[223] = 0.0;
   out_1951764618460370916[224] = 0.0;
   out_1951764618460370916[225] = 0.0;
   out_1951764618460370916[226] = 0.0;
   out_1951764618460370916[227] = 0.0;
   out_1951764618460370916[228] = 1.0;
   out_1951764618460370916[229] = 0.0;
   out_1951764618460370916[230] = 0.0;
   out_1951764618460370916[231] = 0.0;
   out_1951764618460370916[232] = 0.0;
   out_1951764618460370916[233] = 0.0;
   out_1951764618460370916[234] = 0.0;
   out_1951764618460370916[235] = 0.0;
   out_1951764618460370916[236] = 0.0;
   out_1951764618460370916[237] = 0.0;
   out_1951764618460370916[238] = 0.0;
   out_1951764618460370916[239] = 0.0;
   out_1951764618460370916[240] = 0.0;
   out_1951764618460370916[241] = 0.0;
   out_1951764618460370916[242] = 0.0;
   out_1951764618460370916[243] = 0.0;
   out_1951764618460370916[244] = 0.0;
   out_1951764618460370916[245] = 0.0;
   out_1951764618460370916[246] = 0.0;
   out_1951764618460370916[247] = 1.0;
   out_1951764618460370916[248] = 0.0;
   out_1951764618460370916[249] = 0.0;
   out_1951764618460370916[250] = 0.0;
   out_1951764618460370916[251] = 0.0;
   out_1951764618460370916[252] = 0.0;
   out_1951764618460370916[253] = 0.0;
   out_1951764618460370916[254] = 0.0;
   out_1951764618460370916[255] = 0.0;
   out_1951764618460370916[256] = 0.0;
   out_1951764618460370916[257] = 0.0;
   out_1951764618460370916[258] = 0.0;
   out_1951764618460370916[259] = 0.0;
   out_1951764618460370916[260] = 0.0;
   out_1951764618460370916[261] = 0.0;
   out_1951764618460370916[262] = 0.0;
   out_1951764618460370916[263] = 0.0;
   out_1951764618460370916[264] = 0.0;
   out_1951764618460370916[265] = 0.0;
   out_1951764618460370916[266] = 1.0;
   out_1951764618460370916[267] = 0.0;
   out_1951764618460370916[268] = 0.0;
   out_1951764618460370916[269] = 0.0;
   out_1951764618460370916[270] = 0.0;
   out_1951764618460370916[271] = 0.0;
   out_1951764618460370916[272] = 0.0;
   out_1951764618460370916[273] = 0.0;
   out_1951764618460370916[274] = 0.0;
   out_1951764618460370916[275] = 0.0;
   out_1951764618460370916[276] = 0.0;
   out_1951764618460370916[277] = 0.0;
   out_1951764618460370916[278] = 0.0;
   out_1951764618460370916[279] = 0.0;
   out_1951764618460370916[280] = 0.0;
   out_1951764618460370916[281] = 0.0;
   out_1951764618460370916[282] = 0.0;
   out_1951764618460370916[283] = 0.0;
   out_1951764618460370916[284] = 0.0;
   out_1951764618460370916[285] = 1.0;
   out_1951764618460370916[286] = 0.0;
   out_1951764618460370916[287] = 0.0;
   out_1951764618460370916[288] = 0.0;
   out_1951764618460370916[289] = 0.0;
   out_1951764618460370916[290] = 0.0;
   out_1951764618460370916[291] = 0.0;
   out_1951764618460370916[292] = 0.0;
   out_1951764618460370916[293] = 0.0;
   out_1951764618460370916[294] = 0.0;
   out_1951764618460370916[295] = 0.0;
   out_1951764618460370916[296] = 0.0;
   out_1951764618460370916[297] = 0.0;
   out_1951764618460370916[298] = 0.0;
   out_1951764618460370916[299] = 0.0;
   out_1951764618460370916[300] = 0.0;
   out_1951764618460370916[301] = 0.0;
   out_1951764618460370916[302] = 0.0;
   out_1951764618460370916[303] = 0.0;
   out_1951764618460370916[304] = 1.0;
   out_1951764618460370916[305] = 0.0;
   out_1951764618460370916[306] = 0.0;
   out_1951764618460370916[307] = 0.0;
   out_1951764618460370916[308] = 0.0;
   out_1951764618460370916[309] = 0.0;
   out_1951764618460370916[310] = 0.0;
   out_1951764618460370916[311] = 0.0;
   out_1951764618460370916[312] = 0.0;
   out_1951764618460370916[313] = 0.0;
   out_1951764618460370916[314] = 0.0;
   out_1951764618460370916[315] = 0.0;
   out_1951764618460370916[316] = 0.0;
   out_1951764618460370916[317] = 0.0;
   out_1951764618460370916[318] = 0.0;
   out_1951764618460370916[319] = 0.0;
   out_1951764618460370916[320] = 0.0;
   out_1951764618460370916[321] = 0.0;
   out_1951764618460370916[322] = 0.0;
   out_1951764618460370916[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_9131418681283073727) {
   out_9131418681283073727[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_9131418681283073727[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_9131418681283073727[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_9131418681283073727[3] = dt*state[12] + state[3];
   out_9131418681283073727[4] = dt*state[13] + state[4];
   out_9131418681283073727[5] = dt*state[14] + state[5];
   out_9131418681283073727[6] = state[6];
   out_9131418681283073727[7] = state[7];
   out_9131418681283073727[8] = state[8];
   out_9131418681283073727[9] = state[9];
   out_9131418681283073727[10] = state[10];
   out_9131418681283073727[11] = state[11];
   out_9131418681283073727[12] = state[12];
   out_9131418681283073727[13] = state[13];
   out_9131418681283073727[14] = state[14];
   out_9131418681283073727[15] = state[15];
   out_9131418681283073727[16] = state[16];
   out_9131418681283073727[17] = state[17];
}
void F_fun(double *state, double dt, double *out_7332136968328018376) {
   out_7332136968328018376[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7332136968328018376[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7332136968328018376[2] = 0;
   out_7332136968328018376[3] = 0;
   out_7332136968328018376[4] = 0;
   out_7332136968328018376[5] = 0;
   out_7332136968328018376[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7332136968328018376[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7332136968328018376[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7332136968328018376[9] = 0;
   out_7332136968328018376[10] = 0;
   out_7332136968328018376[11] = 0;
   out_7332136968328018376[12] = 0;
   out_7332136968328018376[13] = 0;
   out_7332136968328018376[14] = 0;
   out_7332136968328018376[15] = 0;
   out_7332136968328018376[16] = 0;
   out_7332136968328018376[17] = 0;
   out_7332136968328018376[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7332136968328018376[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7332136968328018376[20] = 0;
   out_7332136968328018376[21] = 0;
   out_7332136968328018376[22] = 0;
   out_7332136968328018376[23] = 0;
   out_7332136968328018376[24] = 0;
   out_7332136968328018376[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7332136968328018376[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7332136968328018376[27] = 0;
   out_7332136968328018376[28] = 0;
   out_7332136968328018376[29] = 0;
   out_7332136968328018376[30] = 0;
   out_7332136968328018376[31] = 0;
   out_7332136968328018376[32] = 0;
   out_7332136968328018376[33] = 0;
   out_7332136968328018376[34] = 0;
   out_7332136968328018376[35] = 0;
   out_7332136968328018376[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7332136968328018376[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7332136968328018376[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7332136968328018376[39] = 0;
   out_7332136968328018376[40] = 0;
   out_7332136968328018376[41] = 0;
   out_7332136968328018376[42] = 0;
   out_7332136968328018376[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7332136968328018376[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7332136968328018376[45] = 0;
   out_7332136968328018376[46] = 0;
   out_7332136968328018376[47] = 0;
   out_7332136968328018376[48] = 0;
   out_7332136968328018376[49] = 0;
   out_7332136968328018376[50] = 0;
   out_7332136968328018376[51] = 0;
   out_7332136968328018376[52] = 0;
   out_7332136968328018376[53] = 0;
   out_7332136968328018376[54] = 0;
   out_7332136968328018376[55] = 0;
   out_7332136968328018376[56] = 0;
   out_7332136968328018376[57] = 1;
   out_7332136968328018376[58] = 0;
   out_7332136968328018376[59] = 0;
   out_7332136968328018376[60] = 0;
   out_7332136968328018376[61] = 0;
   out_7332136968328018376[62] = 0;
   out_7332136968328018376[63] = 0;
   out_7332136968328018376[64] = 0;
   out_7332136968328018376[65] = 0;
   out_7332136968328018376[66] = dt;
   out_7332136968328018376[67] = 0;
   out_7332136968328018376[68] = 0;
   out_7332136968328018376[69] = 0;
   out_7332136968328018376[70] = 0;
   out_7332136968328018376[71] = 0;
   out_7332136968328018376[72] = 0;
   out_7332136968328018376[73] = 0;
   out_7332136968328018376[74] = 0;
   out_7332136968328018376[75] = 0;
   out_7332136968328018376[76] = 1;
   out_7332136968328018376[77] = 0;
   out_7332136968328018376[78] = 0;
   out_7332136968328018376[79] = 0;
   out_7332136968328018376[80] = 0;
   out_7332136968328018376[81] = 0;
   out_7332136968328018376[82] = 0;
   out_7332136968328018376[83] = 0;
   out_7332136968328018376[84] = 0;
   out_7332136968328018376[85] = dt;
   out_7332136968328018376[86] = 0;
   out_7332136968328018376[87] = 0;
   out_7332136968328018376[88] = 0;
   out_7332136968328018376[89] = 0;
   out_7332136968328018376[90] = 0;
   out_7332136968328018376[91] = 0;
   out_7332136968328018376[92] = 0;
   out_7332136968328018376[93] = 0;
   out_7332136968328018376[94] = 0;
   out_7332136968328018376[95] = 1;
   out_7332136968328018376[96] = 0;
   out_7332136968328018376[97] = 0;
   out_7332136968328018376[98] = 0;
   out_7332136968328018376[99] = 0;
   out_7332136968328018376[100] = 0;
   out_7332136968328018376[101] = 0;
   out_7332136968328018376[102] = 0;
   out_7332136968328018376[103] = 0;
   out_7332136968328018376[104] = dt;
   out_7332136968328018376[105] = 0;
   out_7332136968328018376[106] = 0;
   out_7332136968328018376[107] = 0;
   out_7332136968328018376[108] = 0;
   out_7332136968328018376[109] = 0;
   out_7332136968328018376[110] = 0;
   out_7332136968328018376[111] = 0;
   out_7332136968328018376[112] = 0;
   out_7332136968328018376[113] = 0;
   out_7332136968328018376[114] = 1;
   out_7332136968328018376[115] = 0;
   out_7332136968328018376[116] = 0;
   out_7332136968328018376[117] = 0;
   out_7332136968328018376[118] = 0;
   out_7332136968328018376[119] = 0;
   out_7332136968328018376[120] = 0;
   out_7332136968328018376[121] = 0;
   out_7332136968328018376[122] = 0;
   out_7332136968328018376[123] = 0;
   out_7332136968328018376[124] = 0;
   out_7332136968328018376[125] = 0;
   out_7332136968328018376[126] = 0;
   out_7332136968328018376[127] = 0;
   out_7332136968328018376[128] = 0;
   out_7332136968328018376[129] = 0;
   out_7332136968328018376[130] = 0;
   out_7332136968328018376[131] = 0;
   out_7332136968328018376[132] = 0;
   out_7332136968328018376[133] = 1;
   out_7332136968328018376[134] = 0;
   out_7332136968328018376[135] = 0;
   out_7332136968328018376[136] = 0;
   out_7332136968328018376[137] = 0;
   out_7332136968328018376[138] = 0;
   out_7332136968328018376[139] = 0;
   out_7332136968328018376[140] = 0;
   out_7332136968328018376[141] = 0;
   out_7332136968328018376[142] = 0;
   out_7332136968328018376[143] = 0;
   out_7332136968328018376[144] = 0;
   out_7332136968328018376[145] = 0;
   out_7332136968328018376[146] = 0;
   out_7332136968328018376[147] = 0;
   out_7332136968328018376[148] = 0;
   out_7332136968328018376[149] = 0;
   out_7332136968328018376[150] = 0;
   out_7332136968328018376[151] = 0;
   out_7332136968328018376[152] = 1;
   out_7332136968328018376[153] = 0;
   out_7332136968328018376[154] = 0;
   out_7332136968328018376[155] = 0;
   out_7332136968328018376[156] = 0;
   out_7332136968328018376[157] = 0;
   out_7332136968328018376[158] = 0;
   out_7332136968328018376[159] = 0;
   out_7332136968328018376[160] = 0;
   out_7332136968328018376[161] = 0;
   out_7332136968328018376[162] = 0;
   out_7332136968328018376[163] = 0;
   out_7332136968328018376[164] = 0;
   out_7332136968328018376[165] = 0;
   out_7332136968328018376[166] = 0;
   out_7332136968328018376[167] = 0;
   out_7332136968328018376[168] = 0;
   out_7332136968328018376[169] = 0;
   out_7332136968328018376[170] = 0;
   out_7332136968328018376[171] = 1;
   out_7332136968328018376[172] = 0;
   out_7332136968328018376[173] = 0;
   out_7332136968328018376[174] = 0;
   out_7332136968328018376[175] = 0;
   out_7332136968328018376[176] = 0;
   out_7332136968328018376[177] = 0;
   out_7332136968328018376[178] = 0;
   out_7332136968328018376[179] = 0;
   out_7332136968328018376[180] = 0;
   out_7332136968328018376[181] = 0;
   out_7332136968328018376[182] = 0;
   out_7332136968328018376[183] = 0;
   out_7332136968328018376[184] = 0;
   out_7332136968328018376[185] = 0;
   out_7332136968328018376[186] = 0;
   out_7332136968328018376[187] = 0;
   out_7332136968328018376[188] = 0;
   out_7332136968328018376[189] = 0;
   out_7332136968328018376[190] = 1;
   out_7332136968328018376[191] = 0;
   out_7332136968328018376[192] = 0;
   out_7332136968328018376[193] = 0;
   out_7332136968328018376[194] = 0;
   out_7332136968328018376[195] = 0;
   out_7332136968328018376[196] = 0;
   out_7332136968328018376[197] = 0;
   out_7332136968328018376[198] = 0;
   out_7332136968328018376[199] = 0;
   out_7332136968328018376[200] = 0;
   out_7332136968328018376[201] = 0;
   out_7332136968328018376[202] = 0;
   out_7332136968328018376[203] = 0;
   out_7332136968328018376[204] = 0;
   out_7332136968328018376[205] = 0;
   out_7332136968328018376[206] = 0;
   out_7332136968328018376[207] = 0;
   out_7332136968328018376[208] = 0;
   out_7332136968328018376[209] = 1;
   out_7332136968328018376[210] = 0;
   out_7332136968328018376[211] = 0;
   out_7332136968328018376[212] = 0;
   out_7332136968328018376[213] = 0;
   out_7332136968328018376[214] = 0;
   out_7332136968328018376[215] = 0;
   out_7332136968328018376[216] = 0;
   out_7332136968328018376[217] = 0;
   out_7332136968328018376[218] = 0;
   out_7332136968328018376[219] = 0;
   out_7332136968328018376[220] = 0;
   out_7332136968328018376[221] = 0;
   out_7332136968328018376[222] = 0;
   out_7332136968328018376[223] = 0;
   out_7332136968328018376[224] = 0;
   out_7332136968328018376[225] = 0;
   out_7332136968328018376[226] = 0;
   out_7332136968328018376[227] = 0;
   out_7332136968328018376[228] = 1;
   out_7332136968328018376[229] = 0;
   out_7332136968328018376[230] = 0;
   out_7332136968328018376[231] = 0;
   out_7332136968328018376[232] = 0;
   out_7332136968328018376[233] = 0;
   out_7332136968328018376[234] = 0;
   out_7332136968328018376[235] = 0;
   out_7332136968328018376[236] = 0;
   out_7332136968328018376[237] = 0;
   out_7332136968328018376[238] = 0;
   out_7332136968328018376[239] = 0;
   out_7332136968328018376[240] = 0;
   out_7332136968328018376[241] = 0;
   out_7332136968328018376[242] = 0;
   out_7332136968328018376[243] = 0;
   out_7332136968328018376[244] = 0;
   out_7332136968328018376[245] = 0;
   out_7332136968328018376[246] = 0;
   out_7332136968328018376[247] = 1;
   out_7332136968328018376[248] = 0;
   out_7332136968328018376[249] = 0;
   out_7332136968328018376[250] = 0;
   out_7332136968328018376[251] = 0;
   out_7332136968328018376[252] = 0;
   out_7332136968328018376[253] = 0;
   out_7332136968328018376[254] = 0;
   out_7332136968328018376[255] = 0;
   out_7332136968328018376[256] = 0;
   out_7332136968328018376[257] = 0;
   out_7332136968328018376[258] = 0;
   out_7332136968328018376[259] = 0;
   out_7332136968328018376[260] = 0;
   out_7332136968328018376[261] = 0;
   out_7332136968328018376[262] = 0;
   out_7332136968328018376[263] = 0;
   out_7332136968328018376[264] = 0;
   out_7332136968328018376[265] = 0;
   out_7332136968328018376[266] = 1;
   out_7332136968328018376[267] = 0;
   out_7332136968328018376[268] = 0;
   out_7332136968328018376[269] = 0;
   out_7332136968328018376[270] = 0;
   out_7332136968328018376[271] = 0;
   out_7332136968328018376[272] = 0;
   out_7332136968328018376[273] = 0;
   out_7332136968328018376[274] = 0;
   out_7332136968328018376[275] = 0;
   out_7332136968328018376[276] = 0;
   out_7332136968328018376[277] = 0;
   out_7332136968328018376[278] = 0;
   out_7332136968328018376[279] = 0;
   out_7332136968328018376[280] = 0;
   out_7332136968328018376[281] = 0;
   out_7332136968328018376[282] = 0;
   out_7332136968328018376[283] = 0;
   out_7332136968328018376[284] = 0;
   out_7332136968328018376[285] = 1;
   out_7332136968328018376[286] = 0;
   out_7332136968328018376[287] = 0;
   out_7332136968328018376[288] = 0;
   out_7332136968328018376[289] = 0;
   out_7332136968328018376[290] = 0;
   out_7332136968328018376[291] = 0;
   out_7332136968328018376[292] = 0;
   out_7332136968328018376[293] = 0;
   out_7332136968328018376[294] = 0;
   out_7332136968328018376[295] = 0;
   out_7332136968328018376[296] = 0;
   out_7332136968328018376[297] = 0;
   out_7332136968328018376[298] = 0;
   out_7332136968328018376[299] = 0;
   out_7332136968328018376[300] = 0;
   out_7332136968328018376[301] = 0;
   out_7332136968328018376[302] = 0;
   out_7332136968328018376[303] = 0;
   out_7332136968328018376[304] = 1;
   out_7332136968328018376[305] = 0;
   out_7332136968328018376[306] = 0;
   out_7332136968328018376[307] = 0;
   out_7332136968328018376[308] = 0;
   out_7332136968328018376[309] = 0;
   out_7332136968328018376[310] = 0;
   out_7332136968328018376[311] = 0;
   out_7332136968328018376[312] = 0;
   out_7332136968328018376[313] = 0;
   out_7332136968328018376[314] = 0;
   out_7332136968328018376[315] = 0;
   out_7332136968328018376[316] = 0;
   out_7332136968328018376[317] = 0;
   out_7332136968328018376[318] = 0;
   out_7332136968328018376[319] = 0;
   out_7332136968328018376[320] = 0;
   out_7332136968328018376[321] = 0;
   out_7332136968328018376[322] = 0;
   out_7332136968328018376[323] = 1;
}
void h_4(double *state, double *unused, double *out_2574344235091918444) {
   out_2574344235091918444[0] = state[6] + state[9];
   out_2574344235091918444[1] = state[7] + state[10];
   out_2574344235091918444[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5723571828304278488) {
   out_5723571828304278488[0] = 0;
   out_5723571828304278488[1] = 0;
   out_5723571828304278488[2] = 0;
   out_5723571828304278488[3] = 0;
   out_5723571828304278488[4] = 0;
   out_5723571828304278488[5] = 0;
   out_5723571828304278488[6] = 1;
   out_5723571828304278488[7] = 0;
   out_5723571828304278488[8] = 0;
   out_5723571828304278488[9] = 1;
   out_5723571828304278488[10] = 0;
   out_5723571828304278488[11] = 0;
   out_5723571828304278488[12] = 0;
   out_5723571828304278488[13] = 0;
   out_5723571828304278488[14] = 0;
   out_5723571828304278488[15] = 0;
   out_5723571828304278488[16] = 0;
   out_5723571828304278488[17] = 0;
   out_5723571828304278488[18] = 0;
   out_5723571828304278488[19] = 0;
   out_5723571828304278488[20] = 0;
   out_5723571828304278488[21] = 0;
   out_5723571828304278488[22] = 0;
   out_5723571828304278488[23] = 0;
   out_5723571828304278488[24] = 0;
   out_5723571828304278488[25] = 1;
   out_5723571828304278488[26] = 0;
   out_5723571828304278488[27] = 0;
   out_5723571828304278488[28] = 1;
   out_5723571828304278488[29] = 0;
   out_5723571828304278488[30] = 0;
   out_5723571828304278488[31] = 0;
   out_5723571828304278488[32] = 0;
   out_5723571828304278488[33] = 0;
   out_5723571828304278488[34] = 0;
   out_5723571828304278488[35] = 0;
   out_5723571828304278488[36] = 0;
   out_5723571828304278488[37] = 0;
   out_5723571828304278488[38] = 0;
   out_5723571828304278488[39] = 0;
   out_5723571828304278488[40] = 0;
   out_5723571828304278488[41] = 0;
   out_5723571828304278488[42] = 0;
   out_5723571828304278488[43] = 0;
   out_5723571828304278488[44] = 1;
   out_5723571828304278488[45] = 0;
   out_5723571828304278488[46] = 0;
   out_5723571828304278488[47] = 1;
   out_5723571828304278488[48] = 0;
   out_5723571828304278488[49] = 0;
   out_5723571828304278488[50] = 0;
   out_5723571828304278488[51] = 0;
   out_5723571828304278488[52] = 0;
   out_5723571828304278488[53] = 0;
}
void h_10(double *state, double *unused, double *out_6588171587677358326) {
   out_6588171587677358326[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_6588171587677358326[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_6588171587677358326[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8713079387063064920) {
   out_8713079387063064920[0] = 0;
   out_8713079387063064920[1] = 9.8100000000000005*cos(state[1]);
   out_8713079387063064920[2] = 0;
   out_8713079387063064920[3] = 0;
   out_8713079387063064920[4] = -state[8];
   out_8713079387063064920[5] = state[7];
   out_8713079387063064920[6] = 0;
   out_8713079387063064920[7] = state[5];
   out_8713079387063064920[8] = -state[4];
   out_8713079387063064920[9] = 0;
   out_8713079387063064920[10] = 0;
   out_8713079387063064920[11] = 0;
   out_8713079387063064920[12] = 1;
   out_8713079387063064920[13] = 0;
   out_8713079387063064920[14] = 0;
   out_8713079387063064920[15] = 1;
   out_8713079387063064920[16] = 0;
   out_8713079387063064920[17] = 0;
   out_8713079387063064920[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8713079387063064920[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8713079387063064920[20] = 0;
   out_8713079387063064920[21] = state[8];
   out_8713079387063064920[22] = 0;
   out_8713079387063064920[23] = -state[6];
   out_8713079387063064920[24] = -state[5];
   out_8713079387063064920[25] = 0;
   out_8713079387063064920[26] = state[3];
   out_8713079387063064920[27] = 0;
   out_8713079387063064920[28] = 0;
   out_8713079387063064920[29] = 0;
   out_8713079387063064920[30] = 0;
   out_8713079387063064920[31] = 1;
   out_8713079387063064920[32] = 0;
   out_8713079387063064920[33] = 0;
   out_8713079387063064920[34] = 1;
   out_8713079387063064920[35] = 0;
   out_8713079387063064920[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8713079387063064920[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8713079387063064920[38] = 0;
   out_8713079387063064920[39] = -state[7];
   out_8713079387063064920[40] = state[6];
   out_8713079387063064920[41] = 0;
   out_8713079387063064920[42] = state[4];
   out_8713079387063064920[43] = -state[3];
   out_8713079387063064920[44] = 0;
   out_8713079387063064920[45] = 0;
   out_8713079387063064920[46] = 0;
   out_8713079387063064920[47] = 0;
   out_8713079387063064920[48] = 0;
   out_8713079387063064920[49] = 0;
   out_8713079387063064920[50] = 1;
   out_8713079387063064920[51] = 0;
   out_8713079387063064920[52] = 0;
   out_8713079387063064920[53] = 1;
}
void h_13(double *state, double *unused, double *out_5152739096252851195) {
   out_5152739096252851195[0] = state[3];
   out_5152739096252851195[1] = state[4];
   out_5152739096252851195[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8935845653636611289) {
   out_8935845653636611289[0] = 0;
   out_8935845653636611289[1] = 0;
   out_8935845653636611289[2] = 0;
   out_8935845653636611289[3] = 1;
   out_8935845653636611289[4] = 0;
   out_8935845653636611289[5] = 0;
   out_8935845653636611289[6] = 0;
   out_8935845653636611289[7] = 0;
   out_8935845653636611289[8] = 0;
   out_8935845653636611289[9] = 0;
   out_8935845653636611289[10] = 0;
   out_8935845653636611289[11] = 0;
   out_8935845653636611289[12] = 0;
   out_8935845653636611289[13] = 0;
   out_8935845653636611289[14] = 0;
   out_8935845653636611289[15] = 0;
   out_8935845653636611289[16] = 0;
   out_8935845653636611289[17] = 0;
   out_8935845653636611289[18] = 0;
   out_8935845653636611289[19] = 0;
   out_8935845653636611289[20] = 0;
   out_8935845653636611289[21] = 0;
   out_8935845653636611289[22] = 1;
   out_8935845653636611289[23] = 0;
   out_8935845653636611289[24] = 0;
   out_8935845653636611289[25] = 0;
   out_8935845653636611289[26] = 0;
   out_8935845653636611289[27] = 0;
   out_8935845653636611289[28] = 0;
   out_8935845653636611289[29] = 0;
   out_8935845653636611289[30] = 0;
   out_8935845653636611289[31] = 0;
   out_8935845653636611289[32] = 0;
   out_8935845653636611289[33] = 0;
   out_8935845653636611289[34] = 0;
   out_8935845653636611289[35] = 0;
   out_8935845653636611289[36] = 0;
   out_8935845653636611289[37] = 0;
   out_8935845653636611289[38] = 0;
   out_8935845653636611289[39] = 0;
   out_8935845653636611289[40] = 0;
   out_8935845653636611289[41] = 1;
   out_8935845653636611289[42] = 0;
   out_8935845653636611289[43] = 0;
   out_8935845653636611289[44] = 0;
   out_8935845653636611289[45] = 0;
   out_8935845653636611289[46] = 0;
   out_8935845653636611289[47] = 0;
   out_8935845653636611289[48] = 0;
   out_8935845653636611289[49] = 0;
   out_8935845653636611289[50] = 0;
   out_8935845653636611289[51] = 0;
   out_8935845653636611289[52] = 0;
   out_8935845653636611289[53] = 0;
}
void h_14(double *state, double *unused, double *out_4540428471259618960) {
   out_4540428471259618960[0] = state[6];
   out_4540428471259618960[1] = state[7];
   out_4540428471259618960[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2640783396008906192) {
   out_2640783396008906192[0] = 0;
   out_2640783396008906192[1] = 0;
   out_2640783396008906192[2] = 0;
   out_2640783396008906192[3] = 0;
   out_2640783396008906192[4] = 0;
   out_2640783396008906192[5] = 0;
   out_2640783396008906192[6] = 1;
   out_2640783396008906192[7] = 0;
   out_2640783396008906192[8] = 0;
   out_2640783396008906192[9] = 0;
   out_2640783396008906192[10] = 0;
   out_2640783396008906192[11] = 0;
   out_2640783396008906192[12] = 0;
   out_2640783396008906192[13] = 0;
   out_2640783396008906192[14] = 0;
   out_2640783396008906192[15] = 0;
   out_2640783396008906192[16] = 0;
   out_2640783396008906192[17] = 0;
   out_2640783396008906192[18] = 0;
   out_2640783396008906192[19] = 0;
   out_2640783396008906192[20] = 0;
   out_2640783396008906192[21] = 0;
   out_2640783396008906192[22] = 0;
   out_2640783396008906192[23] = 0;
   out_2640783396008906192[24] = 0;
   out_2640783396008906192[25] = 1;
   out_2640783396008906192[26] = 0;
   out_2640783396008906192[27] = 0;
   out_2640783396008906192[28] = 0;
   out_2640783396008906192[29] = 0;
   out_2640783396008906192[30] = 0;
   out_2640783396008906192[31] = 0;
   out_2640783396008906192[32] = 0;
   out_2640783396008906192[33] = 0;
   out_2640783396008906192[34] = 0;
   out_2640783396008906192[35] = 0;
   out_2640783396008906192[36] = 0;
   out_2640783396008906192[37] = 0;
   out_2640783396008906192[38] = 0;
   out_2640783396008906192[39] = 0;
   out_2640783396008906192[40] = 0;
   out_2640783396008906192[41] = 0;
   out_2640783396008906192[42] = 0;
   out_2640783396008906192[43] = 0;
   out_2640783396008906192[44] = 1;
   out_2640783396008906192[45] = 0;
   out_2640783396008906192[46] = 0;
   out_2640783396008906192[47] = 0;
   out_2640783396008906192[48] = 0;
   out_2640783396008906192[49] = 0;
   out_2640783396008906192[50] = 0;
   out_2640783396008906192[51] = 0;
   out_2640783396008906192[52] = 0;
   out_2640783396008906192[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_5045866649768905313) {
  err_fun(nom_x, delta_x, out_5045866649768905313);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8605282873688095256) {
  inv_err_fun(nom_x, true_x, out_8605282873688095256);
}
void pose_H_mod_fun(double *state, double *out_1951764618460370916) {
  H_mod_fun(state, out_1951764618460370916);
}
void pose_f_fun(double *state, double dt, double *out_9131418681283073727) {
  f_fun(state,  dt, out_9131418681283073727);
}
void pose_F_fun(double *state, double dt, double *out_7332136968328018376) {
  F_fun(state,  dt, out_7332136968328018376);
}
void pose_h_4(double *state, double *unused, double *out_2574344235091918444) {
  h_4(state, unused, out_2574344235091918444);
}
void pose_H_4(double *state, double *unused, double *out_5723571828304278488) {
  H_4(state, unused, out_5723571828304278488);
}
void pose_h_10(double *state, double *unused, double *out_6588171587677358326) {
  h_10(state, unused, out_6588171587677358326);
}
void pose_H_10(double *state, double *unused, double *out_8713079387063064920) {
  H_10(state, unused, out_8713079387063064920);
}
void pose_h_13(double *state, double *unused, double *out_5152739096252851195) {
  h_13(state, unused, out_5152739096252851195);
}
void pose_H_13(double *state, double *unused, double *out_8935845653636611289) {
  H_13(state, unused, out_8935845653636611289);
}
void pose_h_14(double *state, double *unused, double *out_4540428471259618960) {
  h_14(state, unused, out_4540428471259618960);
}
void pose_H_14(double *state, double *unused, double *out_2640783396008906192) {
  H_14(state, unused, out_2640783396008906192);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
