/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CoM3DOFDetailed.c
 *
 * Code generated for Simulink model 'CoM3DOFDetailed'.
 *
 * Model version                  : 30.9
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu May 16 11:02:42 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CoM3DOFDetailed.hxx"
#include <math.h>
#include "rtwtypes.hxx"

/* External inputs (root inport signals with default storage) */
ExtU_CoM3DOFDetailed_T CoM3DOFDetailed_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_CoM3DOFDetailed_T CoM3DOFDetailed_Y;

/* Real-time model */
static RT_MODEL_CoM3DOFDetailed_T CoM3DOFDetailed_M_;
RT_MODEL_CoM3DOFDetailed_T *const CoM3DOFDetailed_M = &CoM3DOFDetailed_M_;

/* Model step function */
void CoM3DOFDetailed_step(void)
{
  real_T FD;
  real_T a_tmp;
  real_T d_a;
  real_T q;
  real_T x_dot_tmp;
  real_T x_dot_tmp_0;
  real_T x_dot_tmp_1;
  real_T x_dot_tmp_2;
  real_T x_dot_tmp_3;
  real_T x_dot_tmp_4;
  real_T x_dot_tmp_5;
  real_T x_dot_tmp_6;

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/DL'
   *  Inport: '<Root>/rho'
   *  Inport: '<Root>/x'
   */
  q = 0.5 * CoM3DOFDetailed_U.rho * (CoM3DOFDetailed_U.x[3] *
    CoM3DOFDetailed_U.x[3]);
  FD = q * 11.34 * CoM3DOFDetailed_U.DL[0];
  q = q * 11.34 * CoM3DOFDetailed_U.DL[1];
  a_tmp = CoM3DOFDetailed_U.x[3] / CoM3DOFDetailed_U.x[0];
  d_a = CoM3DOFDetailed_U.x[0] * 5.0239744E-9;
  x_dot_tmp = cos(CoM3DOFDetailed_U.x[4]);
  x_dot_tmp_0 = sin(CoM3DOFDetailed_U.x[5]);
  x_dot_tmp_1 = cos(CoM3DOFDetailed_U.x[5]);
  x_dot_tmp_2 = sin(CoM3DOFDetailed_U.x[4]);
  x_dot_tmp_3 = cos(CoM3DOFDetailed_U.x[2]);
  x_dot_tmp_4 = sin(CoM3DOFDetailed_U.x[2]);

  /* Outport: '<Root>/x_dot' incorporates:
   *  Inport: '<Root>/x'
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  CoM3DOFDetailed_Y.x_dot[0] = CoM3DOFDetailed_U.x[3] * x_dot_tmp_2;
  CoM3DOFDetailed_Y.x_dot[1] = CoM3DOFDetailed_U.x[3] / (CoM3DOFDetailed_U.x[0] *
    x_dot_tmp_3) * x_dot_tmp * x_dot_tmp_0;

  /* MATLAB Function: '<S1>/MATLAB Function' */
  x_dot_tmp_5 = a_tmp * x_dot_tmp;

  /* Outport: '<Root>/x_dot' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  CoM3DOFDetailed_Y.x_dot[2] = x_dot_tmp_5 * x_dot_tmp_1;

  /* MATLAB Function: '<S1>/MATLAB Function' */
  x_dot_tmp_6 = x_dot_tmp_4 * x_dot_tmp_1;

  /* Outport: '<Root>/x_dot' incorporates:
   *  Inport: '<Root>/grav'
   *  Inport: '<Root>/mu'
   *  Inport: '<Root>/x'
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  CoM3DOFDetailed_Y.x_dot[3] = (x_dot_tmp_2 * x_dot_tmp_3 - x_dot_tmp_6 *
    x_dot_tmp) * x_dot_tmp_3 * d_a + ((x_dot_tmp_1 * x_dot_tmp *
    CoM3DOFDetailed_U.grav[0] - x_dot_tmp_2 * CoM3DOFDetailed_U.grav[2]) +
    (a_tmp * 0.0 + 0.0005025125628140704 * -FD));
  CoM3DOFDetailed_Y.x_dot[4] = (((1.0 / CoM3DOFDetailed_U.x[3] * (q * cos
    (CoM3DOFDetailed_U.mu)) * 0.0005025125628140704 + x_dot_tmp_5) +
    -(x_dot_tmp_1 * x_dot_tmp_2 * CoM3DOFDetailed_U.grav[0] + x_dot_tmp *
      CoM3DOFDetailed_U.grav[2]) / CoM3DOFDetailed_U.x[3]) + x_dot_tmp_0 *
    x_dot_tmp_3 * 0.00014176) + (x_dot_tmp_6 * x_dot_tmp_2 + x_dot_tmp *
    x_dot_tmp_3) * (1.0 / CoM3DOFDetailed_U.x[3] * x_dot_tmp_3) * d_a;

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/x'
   */
  x_dot_tmp_2 = CoM3DOFDetailed_U.x[3] * x_dot_tmp;
  x_dot_tmp_5 = 1.0 / x_dot_tmp_2;

  /* Outport: '<Root>/x_dot' incorporates:
   *  Inport: '<Root>/grav'
   *  Inport: '<Root>/mu'
   *  Inport: '<Root>/x'
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  CoM3DOFDetailed_Y.x_dot[5] = (((q * sin(CoM3DOFDetailed_U.mu) * x_dot_tmp_5 *
    0.0005025125628140704 + x_dot_tmp * x_dot_tmp_0 * tan(CoM3DOFDetailed_U.x[2])
    * a_tmp) + -(x_dot_tmp_0 * CoM3DOFDetailed_U.grav[0]) / x_dot_tmp_2) +
    (x_dot_tmp_4 - x_dot_tmp_1 * x_dot_tmp_3 * tan(CoM3DOFDetailed_U.x[4])) *
    0.00014176) + x_dot_tmp_5 * x_dot_tmp_0 * x_dot_tmp_3 * x_dot_tmp_4 * d_a;

  /* Outport: '<Root>/inVarOut' incorporates:
   *  Inport: '<Root>/rho'
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  CoM3DOFDetailed_Y.inVarOut[0] = CoM3DOFDetailed_U.rho;
  CoM3DOFDetailed_Y.inVarOut[1] = FD;
  CoM3DOFDetailed_Y.inVarOut[2] = q;
}

/* Model initialize function */
void CoM3DOFDetailed_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void CoM3DOFDetailed_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
