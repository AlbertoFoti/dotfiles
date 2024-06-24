/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MatrixInverse.c
 *
 * Code generated for Simulink model 'MatrixInverse'.
 *
 * Model version                  : 1.12
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Fri May 24 22:00:04 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "MatrixInverse.hxx"
#include <string.h>
#include <math.h>
#include <emmintrin.h>
#include "rtwtypes.hxx"

/* External inputs (root inport signals with default storage) */
ExtU_MatrixInverse_T MatrixInverse_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_MatrixInverse_T MatrixInverse_Y;

/* Real-time model */
static RT_MODEL_MatrixInverse_T MatrixInverse_M_;
RT_MODEL_MatrixInverse_T *const MatrixInverse_M = &MatrixInverse_M_;

/* Model step function */
void MatrixInverse_step(void)
{
  __m128d tmp;
  real_T A_data[64];
  real_T res_data[64];
  real_T s;
  real_T smax;
  int32_T ipiv_data[8];
  int32_T a;
  int32_T c_n;
  int32_T g_k;
  int32_T h_k;
  int32_T i;
  int32_T i_k;
  int32_T ijA;
  int32_T ipiv_size_idx_1;
  int32_T jA;
  int32_T jj;
  int32_T k;
  int32_T temp_tmp;
  int16_T p_data[8];
  int16_T p_tmp;
  boolean_T tmp_0;

  /* Outport: '<Root>/y' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  memset(&MatrixInverse_Y.y[0], 0, sizeof(real_T) << 6U);

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/NbrNom'
   *  Inport: '<Root>/u'
   *  Outport: '<Root>/y'
   */
  for (k = 0; k < 8; k++) {
    MatrixInverse_Y.y[k + (k << 3)] = 1.0;
  }

  if (MatrixInverse_U.NbrNom < 1.0) {
    k = 0;
    c_n = 0;
  } else {
    k = (int32_T)MatrixInverse_U.NbrNom;
    c_n = (int32_T)MatrixInverse_U.NbrNom;
  }

  tmp_0 = ((k == 0) || (c_n == 0));
  if (tmp_0) {
    for (a = 0; a < c_n; a++) {
      for (i = 0; i < k; i++) {
        res_data[i + k * a] = MatrixInverse_U.u[(a << 3) + i];
      }
    }
  } else {
    i = k * c_n;
    if (i - 1 >= 0) {
      memset(&res_data[0], 0, (uint32_T)i * sizeof(real_T));
    }

    for (a = 0; a < c_n; a++) {
      for (i = 0; i < k; i++) {
        A_data[i + k * a] = MatrixInverse_U.u[(a << 3) + i];
      }
    }

    if (k < 1) {
      c_n = 0;
    } else {
      c_n = (uint8_T)(k - 1) + 1;
    }

    ipiv_size_idx_1 = c_n;
    if (c_n > 0) {
      ipiv_data[0] = 1;
      i = 1;
      for (i_k = 2; i_k <= c_n; i_k++) {
        i++;
        ipiv_data[i_k - 1] = i;
      }
    }

    if (k < 1) {
      c_n = 0;
    } else {
      if (k - 1 <= k) {
        c_n = (uint8_T)(k - 1);
      } else {
        c_n = (uint8_T)k;
      }

      for (i = 0; i < c_n; i++) {
        i_k = k - i;
        jj = (k + 1) * i;
        if (i_k < 1) {
          a = -1;
        } else {
          a = 0;
          if (i_k > 1) {
            smax = fabs(A_data[jj]);
            for (g_k = 2; g_k <= i_k; g_k++) {
              s = fabs(A_data[(jj + g_k) - 1]);
              if (s > smax) {
                a = g_k - 1;
                smax = s;
              }
            }
          }
        }

        if (A_data[jj + a] != 0.0) {
          if (a != 0) {
            g_k = i + a;
            ipiv_data[i] = g_k + 1;
            jA = (uint8_T)k;
            for (h_k = 0; h_k < jA; h_k++) {
              a = h_k * k;
              temp_tmp = a + i;
              smax = A_data[temp_tmp];
              a += g_k;
              A_data[temp_tmp] = A_data[a];
              A_data[a] = smax;
            }
          }

          a = jj + i_k;
          g_k = (((((a - jj) - 1) / 2) << 1) + jj) + 2;
          jA = g_k - 2;
          for (h_k = jj + 2; h_k <= jA; h_k += 2) {
            tmp = _mm_loadu_pd(&A_data[h_k - 1]);
            _mm_storeu_pd(&A_data[h_k - 1], _mm_div_pd(tmp, _mm_set1_pd
              (A_data[jj])));
          }

          for (h_k = g_k; h_k <= a; h_k++) {
            A_data[h_k - 1] /= A_data[jj];
          }
        }

        a = i_k - 2;
        g_k = jj + k;
        jA = g_k + 2;
        for (h_k = 0; h_k <= a; h_k++) {
          smax = A_data[h_k * k + g_k];
          if (smax != 0.0) {
            temp_tmp = (i_k + jA) - 2;
            for (ijA = jA; ijA <= temp_tmp; ijA++) {
              A_data[ijA - 1] += A_data[((jj + ijA) - jA) + 1] * -smax;
            }
          }

          jA += k;
        }
      }

      c_n = (uint8_T)(k - 1) + 1;
    }

    if (c_n > 0) {
      p_data[0] = 1;
      i = 1;
      for (i_k = 2; i_k <= c_n; i_k++) {
        i++;
        p_data[i_k - 1] = (int16_T)i;
      }
    }

    for (i = 0; i < ipiv_size_idx_1; i++) {
      i_k = ipiv_data[i];
      if (i_k > i + 1) {
        jj = p_data[i_k - 1];
        p_data[i_k - 1] = p_data[i];
        p_data[i] = (int16_T)jj;
      }
    }

    c_n = (uint8_T)k;
    for (i_k = 0; i_k < c_n; i_k++) {
      p_tmp = p_data[i_k];
      ipiv_size_idx_1 = (p_tmp - 1) * k;
      res_data[i_k + ipiv_size_idx_1] = 1.0;
      for (a = i_k + 1; a <= k; a++) {
        jj = (p_tmp - 1) * k;
        if (res_data[(a + jj) - 1] != 0.0) {
          for (i = a + 1; i <= k; i++) {
            g_k = (i + ipiv_size_idx_1) - 1;
            res_data[g_k] -= A_data[((a - 1) * k + i) - 1] * res_data[(a + jj) -
              1];
          }
        }
      }
    }

    if ((k != 0) && (!tmp_0)) {
      for (i_k = 0; i_k < c_n; i_k++) {
        jj = k * i_k - 1;
        for (g_k = k; g_k >= 1; g_k--) {
          jA = (g_k - 1) * k;
          a = g_k + jj;
          smax = res_data[a];
          if (smax != 0.0) {
            res_data[a] = smax / A_data[(g_k + jA) - 1];
            h_k = (uint8_T)(g_k - 1);
            for (temp_tmp = 0; temp_tmp < h_k; temp_tmp++) {
              i = (temp_tmp + jj) + 1;
              res_data[i] -= A_data[temp_tmp + jA] * res_data[a];
            }
          }
        }
      }
    }
  }

  if (MatrixInverse_U.NbrNom < 1.0) {
    k = 0;
    c_n = 0;
  } else {
    k = (int32_T)MatrixInverse_U.NbrNom;
    c_n = (int32_T)MatrixInverse_U.NbrNom;
  }

  for (a = 0; a < c_n; a++) {
    for (i = 0; i < k; i++) {
      MatrixInverse_Y.y[i + (a << 3)] = res_data[k * a + i];
    }
  }
}

/* Model initialize function */
void MatrixInverse_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void MatrixInverse_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
