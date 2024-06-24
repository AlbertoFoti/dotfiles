/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: LinSysSolve.c
 *
 * Code generated for Simulink model 'LinSysSolve'.
 *
 * Model version                  : 29.30
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Tue May 28 13:49:53 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "LinSysSolve.hxx"
#include "rtwtypes.hxx"
#include <string.h>
#include <math.h>
#include "LinSysSolve_private.hxx"
#include "rt_nonfinite.hxx"

/* External inputs (root inport signals with default storage) */
ExtU_LinSysSolve_T LinSysSolve_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_LinSysSolve_T LinSysSolve_Y;

/* Real-time model */
static RT_MODEL_LinSysSolve_T LinSysSolve_M_;
RT_MODEL_LinSysSolve_T *const LinSysSolve_M = &LinSysSolve_M_;

/* Forward declaration for local functions */
static real_T LinSysSolve_xnrm2(int32_T n, const real_T x_data[], int32_T ix0);
static void LinSysSolve_xgeqp3(real_T A_data[], const int32_T A_size[2], real_T
  tau_data[], int32_T *tau_size, int32_T jpvt_data[], int32_T jpvt_size[2]);

/* Function for MATLAB Function: '<S1>/MATLAB Function' */
static real_T LinSysSolve_xnrm2(int32_T n, const real_T x_data[], int32_T ix0)
{
  real_T absxk;
  real_T scale;
  real_T t;
  real_T y;
  int32_T k;
  int32_T kend;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x_data[ix0 - 1]);
    } else {
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        absxk = fabs(x_data[k - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
}

real_T rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T a;
  real_T b;
  real_T y;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = sqrt(a * a + 1.0) * b;
  } else if (a > b) {
    b /= a;
    y = sqrt(b * b + 1.0) * a;
  } else if (rtIsNaN(b)) {
    y = (rtNaN);
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

/* Function for MATLAB Function: '<S1>/MATLAB Function' */
static void LinSysSolve_xgeqp3(real_T A_data[], const int32_T A_size[2], real_T
  tau_data[], int32_T *tau_size, int32_T jpvt_data[], int32_T jpvt_size[2])
{
  real_T vn1_data[6];
  real_T vn2_data[6];
  real_T work_data[6];
  real_T s;
  real_T smax;
  real_T temp2;
  int32_T b_ix;
  int32_T c_k;
  int32_T exitg1;
  int32_T ii;
  int32_T itemp;
  int32_T k;
  int32_T knt;
  int32_T l;
  int32_T m_tmp;
  int32_T minmana;
  int32_T mmi;
  int32_T n_tmp;
  int32_T nmi;
  int32_T pvt;
  int32_T temp_tmp;
  boolean_T exitg2;
  boolean_T guard1;
  m_tmp = A_size[0];
  n_tmp = A_size[1];
  if (A_size[0] <= A_size[1]) {
    minmana = A_size[0];
  } else {
    minmana = A_size[1];
  }

  *tau_size = minmana;
  if (minmana - 1 >= 0) {
    memset(&tau_data[0], 0, (uint32_T)minmana * sizeof(real_T));
  }

  guard1 = false;
  if ((A_size[0] == 0) || (A_size[1] == 0)) {
    guard1 = true;
  } else {
    if (A_size[0] <= A_size[1]) {
      itemp = A_size[0];
    } else {
      itemp = A_size[1];
    }

    if (itemp < 1) {
      guard1 = true;
    } else {
      jpvt_size[0] = 1;
      jpvt_size[1] = A_size[1];
      for (k = 0; k < n_tmp; k++) {
        jpvt_data[k] = k + 1;
      }

      if (minmana - 1 >= 0) {
        memset(&tau_data[0], 0, (uint32_T)minmana * sizeof(real_T));
      }

      for (minmana = 0; minmana < n_tmp; minmana++) {
        work_data[minmana] = 0.0;
        smax = LinSysSolve_xnrm2(m_tmp, A_data, minmana * m_tmp + 1);
        vn1_data[minmana] = smax;
        vn2_data[minmana] = smax;
      }

      if (A_size[0] <= A_size[1]) {
        k = A_size[0];
      } else {
        k = A_size[1];
      }

      for (minmana = 0; minmana < k; minmana++) {
        knt = minmana * m_tmp;
        ii = knt + minmana;
        nmi = n_tmp - minmana;
        mmi = m_tmp - minmana;
        if (nmi < 1) {
          pvt = -1;
        } else {
          pvt = 0;
          if (nmi > 1) {
            smax = fabs(vn1_data[minmana]);
            for (itemp = 2; itemp <= nmi; itemp++) {
              s = fabs(vn1_data[(minmana + itemp) - 1]);
              if (s > smax) {
                pvt = itemp - 1;
                smax = s;
              }
            }
          }
        }

        pvt += minmana;
        if (pvt != minmana) {
          b_ix = pvt * m_tmp;
          for (c_k = 0; c_k < m_tmp; c_k++) {
            temp_tmp = b_ix + c_k;
            smax = A_data[temp_tmp];
            itemp = knt + c_k;
            A_data[temp_tmp] = A_data[itemp];
            A_data[itemp] = smax;
          }

          itemp = jpvt_data[pvt];
          jpvt_data[pvt] = jpvt_data[minmana];
          jpvt_data[minmana] = itemp;
          vn1_data[pvt] = vn1_data[minmana];
          vn2_data[pvt] = vn2_data[minmana];
        }

        if (minmana + 1 < m_tmp) {
          s = A_data[ii];
          itemp = ii + 2;
          tau_data[minmana] = 0.0;
          if (mmi > 0) {
            smax = LinSysSolve_xnrm2(mmi - 1, A_data, ii + 2);
            if (smax != 0.0) {
              smax = rt_hypotd_snf(A_data[ii], smax);
              if (A_data[ii] >= 0.0) {
                smax = -smax;
              }

              if (fabs(smax) < 1.0020841800044864E-292) {
                knt = 0;
                pvt = ii + mmi;
                do {
                  knt++;
                  for (c_k = itemp; c_k <= pvt; c_k++) {
                    A_data[c_k - 1] *= 9.9792015476736E+291;
                  }

                  smax *= 9.9792015476736E+291;
                  s *= 9.9792015476736E+291;
                } while ((fabs(smax) < 1.0020841800044864E-292) && (knt < 20));

                smax = rt_hypotd_snf(s, LinSysSolve_xnrm2(mmi - 1, A_data, ii +
                  2));
                if (s >= 0.0) {
                  smax = -smax;
                }

                tau_data[minmana] = (smax - s) / smax;
                s = 1.0 / (s - smax);
                for (c_k = itemp; c_k <= pvt; c_k++) {
                  A_data[c_k - 1] *= s;
                }

                for (itemp = 0; itemp < knt; itemp++) {
                  smax *= 1.0020841800044864E-292;
                }

                s = smax;
              } else {
                tau_data[minmana] = (smax - A_data[ii]) / smax;
                s = 1.0 / (A_data[ii] - smax);
                pvt = ii + mmi;
                for (knt = itemp; knt <= pvt; knt++) {
                  A_data[knt - 1] *= s;
                }

                s = smax;
              }
            }
          }

          A_data[ii] = s;
        } else {
          tau_data[minmana] = 0.0;
        }

        if (minmana + 1 < n_tmp) {
          smax = A_data[ii];
          A_data[ii] = 1.0;
          knt = (ii + m_tmp) + 1;
          if (tau_data[minmana] != 0.0) {
            itemp = mmi - 1;
            pvt = (ii + mmi) - 1;
            while ((itemp + 1 > 0) && (A_data[pvt] == 0.0)) {
              itemp--;
              pvt--;
            }

            nmi--;
            exitg2 = false;
            while ((!exitg2) && (nmi > 0)) {
              pvt = (nmi - 1) * m_tmp + knt;
              c_k = pvt;
              do {
                exitg1 = 0;
                if (c_k <= pvt + itemp) {
                  if (A_data[c_k - 1] != 0.0) {
                    exitg1 = 1;
                  } else {
                    c_k++;
                  }
                } else {
                  nmi--;
                  exitg1 = 2;
                }
              } while (exitg1 == 0);

              if (exitg1 == 1) {
                exitg2 = true;
              }
            }

            nmi--;
          } else {
            itemp = -1;
            nmi = -1;
          }

          if (itemp + 1 > 0) {
            if (nmi + 1 != 0) {
              if (nmi >= 0) {
                memset(&work_data[0], 0, (uint32_T)(nmi + 1) * sizeof(real_T));
              }

              b_ix = 0;
              temp_tmp = m_tmp * nmi + knt;
              for (pvt = knt; m_tmp < 0 ? pvt >= temp_tmp : pvt <= temp_tmp; pvt
                   += m_tmp) {
                s = 0.0;
                l = pvt + itemp;
                for (c_k = pvt; c_k <= l; c_k++) {
                  s += A_data[(ii + c_k) - pvt] * A_data[c_k - 1];
                }

                work_data[b_ix] += s;
                b_ix++;
              }
            }

            if (!(-tau_data[minmana] == 0.0)) {
              for (pvt = 0; pvt <= nmi; pvt++) {
                s = work_data[pvt];
                if (s != 0.0) {
                  s *= -tau_data[minmana];
                  b_ix = itemp + knt;
                  for (c_k = knt; c_k <= b_ix; c_k++) {
                    A_data[c_k - 1] += A_data[(ii + c_k) - knt] * s;
                  }
                }

                knt += m_tmp;
              }
            }
          }

          A_data[ii] = smax;
        }

        for (ii = minmana + 2; ii <= n_tmp; ii++) {
          nmi = (ii - 1) * m_tmp + minmana;
          smax = vn1_data[ii - 1];
          if (smax != 0.0) {
            s = fabs(A_data[nmi]) / smax;
            s = 1.0 - s * s;
            if (s < 0.0) {
              s = 0.0;
            }

            temp2 = smax / vn2_data[ii - 1];
            temp2 = temp2 * temp2 * s;
            if (temp2 <= 1.4901161193847656E-8) {
              if (minmana + 1 < m_tmp) {
                smax = LinSysSolve_xnrm2(mmi - 1, A_data, nmi + 2);
                vn1_data[ii - 1] = smax;
                vn2_data[ii - 1] = smax;
              } else {
                vn1_data[ii - 1] = 0.0;
                vn2_data[ii - 1] = 0.0;
              }
            } else {
              vn1_data[ii - 1] = smax * sqrt(s);
            }
          }
        }
      }
    }
  }

  if (guard1) {
    jpvt_size[0] = 1;
    jpvt_size[1] = A_size[1];
    for (m_tmp = 0; m_tmp < n_tmp; m_tmp++) {
      jpvt_data[m_tmp] = m_tmp + 1;
    }
  }
}

/* Model step function */
void LinSysSolve_step(void)
{
  real_T A_data[36];
  real_T B_data[6];
  real_T b_B_data[6];
  real_T tau_data[6];
  real_T s;
  real_T wj;
  int32_T jpvt_data[6];
  int32_T A_size[2];
  int32_T jpvt_size[2];
  int32_T a;
  int32_T b_temp_tmp;
  int32_T e_k;
  int32_T f;
  int32_T i;
  int32_T ijA;
  int32_T jA;
  int32_T jj;
  int32_T jpvt_tmp;
  int32_T kAcol;
  int32_T maxmn;
  int32_T minmn;
  int32_T rankA;

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/size1'
   *  Inport: '<Root>/size2'
   */
  if (LinSysSolve_U.size1 < 1.0) {
    minmn = 0;
  } else {
    minmn = (int32_T)LinSysSolve_U.size1;
  }

  if (LinSysSolve_U.size2 < 1.0) {
    maxmn = 0;
  } else {
    maxmn = (int32_T)LinSysSolve_U.size2;
  }

  for (i = 0; i < 6; i++) {
    /* Outport: '<Root>/sol' incorporates:
     *  MATLAB Function: '<S1>/MATLAB Function'
     */
    LinSysSolve_Y.sol[i] = 0.0;
  }

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/m'
   *  Inport: '<Root>/size1'
   *  Inport: '<Root>/size2'
   *  Inport: '<Root>/v'
   *  Outport: '<Root>/sol'
   */
  if (LinSysSolve_U.size2 < 1.0) {
    f = 0;
  } else {
    f = (int32_T)LinSysSolve_U.size2;
  }

  if ((minmn == 0) || (maxmn == 0)) {
    if (maxmn - 1 >= 0) {
      memset(&b_B_data[0], 0, (uint32_T)maxmn * sizeof(real_T));
    }
  } else if ((int32_T)LinSysSolve_U.size1 == 0) {
    if (maxmn - 1 >= 0) {
      memset(&b_B_data[0], 0, (uint32_T)maxmn * sizeof(real_T));
    }
  } else if (minmn == maxmn) {
    if (minmn <= maxmn) {
      rankA = minmn;
    } else {
      rankA = maxmn;
    }

    if ((int32_T)LinSysSolve_U.size1 <= rankA) {
      rankA = (int32_T)LinSysSolve_U.size1;
    }

    for (a = 0; a < maxmn; a++) {
      for (i = 0; i < minmn; i++) {
        A_data[i + minmn * a] = LinSysSolve_U.m[6 * a + i];
      }
    }

    if (rankA < 1) {
      maxmn = 0;
    } else {
      maxmn = (uint8_T)(rankA - 1) + 1;
    }

    if (maxmn > 0) {
      jpvt_data[0] = 1;
      i = 1;
      for (kAcol = 2; kAcol <= maxmn; kAcol++) {
        i++;
        jpvt_data[kAcol - 1] = i;
      }
    }

    if (rankA >= 1) {
      if (rankA - 1 <= rankA) {
        maxmn = (uint8_T)(rankA - 1);
      } else {
        maxmn = (uint8_T)rankA;
      }

      for (i = 0; i < maxmn; i++) {
        kAcol = rankA - i;
        jj = (minmn + 1) * i;
        if (kAcol < 1) {
          a = -1;
        } else {
          a = 0;
          if (kAcol > 1) {
            wj = fabs(A_data[jj]);
            for (jpvt_tmp = 2; jpvt_tmp <= kAcol; jpvt_tmp++) {
              s = fabs(A_data[(jj + jpvt_tmp) - 1]);
              if (s > wj) {
                a = jpvt_tmp - 1;
                wj = s;
              }
            }
          }
        }

        if (A_data[jj + a] != 0.0) {
          if (a != 0) {
            jpvt_tmp = i + a;
            jpvt_data[i] = jpvt_tmp + 1;
            jA = (uint8_T)rankA;
            for (e_k = 0; e_k < jA; e_k++) {
              a = e_k * minmn;
              b_temp_tmp = a + i;
              wj = A_data[b_temp_tmp];
              a += jpvt_tmp;
              A_data[b_temp_tmp] = A_data[a];
              A_data[a] = wj;
            }
          }

          a = jj + kAcol;
          for (jpvt_tmp = jj + 2; jpvt_tmp <= a; jpvt_tmp++) {
            A_data[jpvt_tmp - 1] /= A_data[jj];
          }
        }

        a = kAcol - 2;
        jpvt_tmp = jj + minmn;
        jA = jpvt_tmp + 2;
        for (e_k = 0; e_k <= a; e_k++) {
          wj = A_data[e_k * minmn + jpvt_tmp];
          if (wj != 0.0) {
            b_temp_tmp = (kAcol + jA) - 2;
            for (ijA = jA; ijA <= b_temp_tmp; ijA++) {
              A_data[ijA - 1] += A_data[((jj + ijA) - jA) + 1] * -wj;
            }
          }

          jA += minmn;
        }
      }
    }

    i = (int32_T)LinSysSolve_U.size1;
    if (i - 1 >= 0) {
      memcpy(&b_B_data[0], &LinSysSolve_U.v[0], (uint32_T)i * sizeof(real_T));
    }

    for (maxmn = 0; maxmn <= rankA - 2; maxmn++) {
      i = jpvt_data[maxmn];
      if (maxmn + 1 != i) {
        wj = b_B_data[maxmn];
        b_B_data[maxmn] = b_B_data[i - 1];
        b_B_data[i - 1] = wj;
      }
    }

    maxmn = (uint8_T)rankA;
    for (i = 0; i < maxmn; i++) {
      kAcol = minmn * i;
      if (b_B_data[i] != 0.0) {
        for (jj = i + 2; jj <= rankA; jj++) {
          b_B_data[jj - 1] -= A_data[(jj + kAcol) - 1] * b_B_data[i];
        }
      }
    }

    for (maxmn = rankA; maxmn >= 1; maxmn--) {
      i = (maxmn - 1) * minmn;
      wj = b_B_data[maxmn - 1];
      if (wj != 0.0) {
        b_B_data[maxmn - 1] = wj / A_data[(maxmn + i) - 1];
        kAcol = (uint8_T)(maxmn - 1);
        for (jj = 0; jj < kAcol; jj++) {
          b_B_data[jj] -= A_data[jj + i] * b_B_data[maxmn - 1];
        }
      }
    }
  } else {
    i = (int32_T)LinSysSolve_U.size1;
    if (i - 1 >= 0) {
      memcpy(&B_data[0], &LinSysSolve_U.v[0], (uint32_T)i * sizeof(real_T));
    }

    A_size[0] = minmn;
    A_size[1] = maxmn;
    for (a = 0; a < maxmn; a++) {
      for (i = 0; i < minmn; i++) {
        A_data[i + minmn * a] = LinSysSolve_U.m[6 * a + i];
      }
    }

    LinSysSolve_xgeqp3(A_data, A_size, tau_data, &minmn, jpvt_data, jpvt_size);
    rankA = 0;
    if (A_size[0] < A_size[1]) {
      minmn = A_size[0];
      maxmn = A_size[1];
    } else {
      minmn = A_size[1];
      maxmn = A_size[0];
    }

    if (minmn > 0) {
      while ((rankA < minmn) && (!(fabs(A_data[A_size[0] * rankA + rankA]) <=
               2.2204460492503131E-15 * (real_T)maxmn * fabs(A_data[0])))) {
        rankA++;
      }
    }

    minmn = A_size[1];
    if (minmn - 1 >= 0) {
      memset(&b_B_data[0], 0, (uint32_T)minmn * sizeof(real_T));
    }

    if (A_size[0] <= A_size[1]) {
      minmn = A_size[0];
    } else {
      minmn = A_size[1];
    }

    for (maxmn = 0; maxmn < minmn; maxmn++) {
      i = A_size[0];
      if (tau_data[maxmn] != 0.0) {
        wj = B_data[maxmn];
        for (kAcol = maxmn + 2; kAcol <= i; kAcol++) {
          wj += A_data[(A_size[0] * maxmn + kAcol) - 1] * B_data[kAcol - 1];
        }

        wj *= tau_data[maxmn];
        if (wj != 0.0) {
          B_data[maxmn] -= wj;
          for (kAcol = maxmn + 2; kAcol <= i; kAcol++) {
            B_data[kAcol - 1] -= A_data[(A_size[0] * maxmn + kAcol) - 1] * wj;
          }
        }
      }
    }

    for (i = 0; i < rankA; i++) {
      b_B_data[jpvt_data[i] - 1] = B_data[i];
    }

    for (minmn = rankA; minmn >= 1; minmn--) {
      jpvt_tmp = jpvt_data[minmn - 1];
      i = (minmn - 1) * A_size[0];
      b_B_data[jpvt_tmp - 1] /= A_data[(minmn + i) - 1];
      for (maxmn = 0; maxmn <= minmn - 2; maxmn++) {
        a = jpvt_data[maxmn] - 1;
        b_B_data[a] -= b_B_data[jpvt_tmp - 1] * A_data[maxmn + i];
      }
    }
  }

  if (f - 1 >= 0) {
    memcpy(&LinSysSolve_Y.sol[0], &b_B_data[0], (uint32_T)f * sizeof(real_T));
  }
}

/* Model initialize function */
void LinSysSolve_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
}

/* Model terminate function */
void LinSysSolve_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
