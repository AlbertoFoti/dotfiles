/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MatrixInverse.c
 *
 * Code generated for Simulink model 'MatrixInverse'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Fri May 24 21:32:34 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "MatrixInverse.hxx"
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
  real_T A[64];
  real_T s;
  real_T smax;
  int32_T c_j;
  int32_T d_k;
  int32_T i;
  int32_T ijA;
  int32_T jA;
  int32_T jj;
  int32_T kAcol;
  int8_T ipiv[8];
  int8_T p[8];
  int8_T ipiv_0;

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/u'
   */
  for (i = 0; i < 64; i++) {
    A[i] = MatrixInverse_U.u[i];
    MatrixInverse_Y.y[i] = 0.0;
  }

  for (c_j = 0; c_j < 8; c_j++) {
    ipiv[c_j] = (int8_T)(c_j + 1);
  }

  for (c_j = 0; c_j < 7; c_j++) {
    jj = c_j * 9;
    i = 8 - c_j;
    jA = 0;
    smax = fabs(A[jj]);
    for (d_k = 2; d_k <= i; d_k++) {
      s = fabs(A[(jj + d_k) - 1]);
      if (s > smax) {
        jA = d_k - 1;
        smax = s;
      }
    }

    if (A[jj + jA] != 0.0) {
      if (jA != 0) {
        i = c_j + jA;
        ipiv[c_j] = (int8_T)(i + 1);
        for (jA = 0; jA < 8; jA++) {
          kAcol = jA << 3;
          d_k = kAcol + c_j;
          smax = A[d_k];
          kAcol += i;
          A[d_k] = A[kAcol];
          A[kAcol] = smax;
        }
      }

      i = (jj - c_j) + 8;
      jA = (((((i - jj) - 1) / 2) << 1) + jj) + 2;
      d_k = jA - 2;
      for (kAcol = jj + 2; kAcol <= d_k; kAcol += 2) {
        tmp = _mm_loadu_pd(&A[kAcol - 1]);
        _mm_storeu_pd(&A[kAcol - 1], _mm_div_pd(tmp, _mm_set1_pd(A[jj])));
      }

      for (kAcol = jA; kAcol <= i; kAcol++) {
        A[kAcol - 1] /= A[jj];
      }
    }

    i = 6 - c_j;
    jA = jj + 10;
    for (d_k = 0; d_k <= i; d_k++) {
      smax = A[((d_k << 3) + jj) + 8];
      if (smax != 0.0) {
        kAcol = (jA - c_j) + 6;
        for (ijA = jA; ijA <= kAcol; ijA++) {
          A[ijA - 1] += A[((jj + ijA) - jA) + 1] * -smax;
        }
      }

      jA += 8;
    }
  }

  for (c_j = 0; c_j < 8; c_j++) {
    p[c_j] = (int8_T)(c_j + 1);
  }

  for (c_j = 0; c_j < 7; c_j++) {
    ipiv_0 = ipiv[c_j];
    if (ipiv_0 > c_j + 1) {
      jj = p[ipiv_0 - 1];
      p[ipiv_0 - 1] = p[c_j];
      p[c_j] = (int8_T)jj;
    }
  }

  for (jA = 0; jA < 8; jA++) {
    jj = (p[jA] - 1) << 3;
    MatrixInverse_Y.y[jA + jj] = 1.0;
    for (d_k = jA + 1; d_k < 9; d_k++) {
      c_j = (jj + d_k) - 1;
      if (MatrixInverse_Y.y[c_j] != 0.0) {
        for (i = d_k + 1; i < 9; i++) {
          kAcol = (jj + i) - 1;
          MatrixInverse_Y.y[kAcol] -= A[(((d_k - 1) << 3) + i) - 1] *
            MatrixInverse_Y.y[c_j];
        }
      }
    }
  }

  for (i = 0; i < 8; i++) {
    jA = i << 3;
    for (d_k = 7; d_k >= 0; d_k--) {
      kAcol = d_k << 3;
      c_j = d_k + jA;
      smax = MatrixInverse_Y.y[c_j];
      if (smax != 0.0) {
        MatrixInverse_Y.y[c_j] = smax / A[d_k + kAcol];
        for (ijA = 0; ijA < d_k; ijA++) {
          jj = ijA + jA;
          MatrixInverse_Y.y[jj] -= A[ijA + kAcol] * MatrixInverse_Y.y[c_j];
        }
      }
    }
  }

  /* End of MATLAB Function: '<S1>/MATLAB Function' */
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
