#include "fuzzy_controller/fuzzy_controller.h"

static float mfTriang(float x, float a, float b, float c) {
  float out;

  if (x < a) {
    out = 0;
  } else if ((x >= a) && (x <= b)) {
    out = (x - a) / (b - a);
  } else if ((x >= b) && (x <= c)) {
    out = (c - x) / (c - b);
  } else {
    out = 0;
  }

  return out;
}

static float mfTrap(float x, float a, float b, float c, float d) {
  float out;

  if (x < a) {
    out = 0;
  } else if ((x >= a) && (x <= b)) {
    if (a == b) {
      out = 1;
    } else {
      out = (x - a) / (b - a);
    }
  } else if ((x >= b) && (x <= c)) {
    out = 1;
  } else if ((x >= c) && (x <= d)) {
    if (c == d) {
      out = 1;
    } else {
      out = (d - x) / (d - c);
    }
  } else {
    out = 0;
  }

  return out;
}

float run_fuzzy(float x1, float x2) {
  float out;
  float r[15]; // 15 value beta <=> 15 rule
  Error e;
  Error_dot e_dot;
  U_dot u_dot;

  // calculate anpha 1 (0->1)
  e.NB = mfTrap(x1, -2, -1, -0.22, -0.17);
  e.NS = mfTriang(x1, -0.22, -0.11, 0.001);
  e.ZE = mfTriang(x1, -0.11, 0, 0.11);
  e.PS = mfTriang(x1, 0.001, 0.11, 0.22);
  e.PB = mfTrap(x1, 0.17, 0.22, 1, 2);

  // calculate anpha 2 (0->1)
  e_dot.NE = mfTrap(x2, -2, -1, -0.22, -0.17);
  e_dot.ZE = mfTriang(x2, -0.4, 0, 0.4);
  e_dot.PO = mfTrap(x2, 0.17, 0.22, 1, 2);

  // calculate beta (0->1) base on MAX-MIN, "and" => MIN
  // e - e_dot - u_dot

  // NB-NE-NB
  r[0] = min(e.NB, e_dot.NE);
  // NB-ZE-NM
  r[1] = min(e.NB, e_dot.ZE);
  // NB-PO-NS
  r[2] = min(e.NB, e_dot.PO);
  // NS-NE-NM
  r[3] = min(e.NS, e_dot.NE);
  // NS-ZE-NS
  r[4] = min(e.NS, e_dot.ZE);
  // NS-PO-ZE
  r[5] = min(e.NS, e_dot.PO);
  // ZE-NE-NS
  r[6] = min(e.ZE, e_dot.NE);
  // ZE-ZE-ZE
  r[7] = min(e.ZE, e_dot.ZE);
  // ZE-PO-PS
  r[8] = min(e.ZE, e_dot.PO);
  // PS-NE-ZE
  r[9] = min(e.PS, e_dot.NE);
  // PS-ZE-PS
  r[10] = min(e.PS, e_dot.ZE);
  // PS-PO-PM
  r[11] = min(e.PS, e_dot.PO);
  // PB-NE-PS
  r[12] = min(e.PB, e_dot.NE);
  // PB-ZE-PM
  r[13] = min(e.PB, e_dot.ZE);
  // PB-PO-PB
  r[14] = min(e.PB, e_dot.PO);

  // Sugeno fuzzy system
  u_dot.NB = r[0];
  u_dot.NM = max(r[1], r[3]);
  u_dot.NS = max(max(r[2], r[4]), r[6]);
  u_dot.ZE = max(max(r[5], r[7]), r[9]);
  u_dot.PS = max(max(r[8], r[10]), r[12]);
  u_dot.PM = max(r[11], r[13]);
  u_dot.PB = r[14];

  // weighted average defuzzification method
  float sum_beta;
  float sum_beta_y;
  sum_beta = u_dot.NB + u_dot.NM + u_dot.NS + u_dot.ZE + u_dot.PS + u_dot.PM + u_dot.PB;
  sum_beta_y = -0.95 * u_dot.NB + -0.8 * u_dot.NM + -0.4 * u_dot.NS + 0 * u_dot.ZE + 0.4 * u_dot.PS + 0.8 * u_dot.PM + 0.95 * u_dot.PB;
  out = sum_beta_y / sum_beta;
  return out;
}