/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CoM3DOFDetailed.c
 *
 * Code generated for Simulink model 'CoM3DOFDetailed'.
 *
 * Model version                  : 30.6
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed May 15 21:29:39 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CoM3DOFDetailed.hxx"

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
  /* Outport: '<Root>/x_dot' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  CoM3DOFDetailed_Y.x_dot = 1.0;

  /* Outport: '<Root>/inVarOut' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  CoM3DOFDetailed_Y.inVarOut = 0.0;
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
