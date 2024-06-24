/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: COM2DOFDetailed.c
 *
 * Code generated for Simulink model 'COM2DOFDetailed'.
 *
 * Model version                  : 29.2
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Mon May 27 11:48:43 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "COM2DOFDetailed.hxx"

/* External inputs (root inport signals with default storage) */
ExtU_COM2DOFDetailed_T COM2DOFDetailed_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_COM2DOFDetailed_T COM2DOFDetailed_Y;

/* Real-time model */
static RT_MODEL_COM2DOFDetailed_T COM2DOFDetailed_M_;
RT_MODEL_COM2DOFDetailed_T *const COM2DOFDetailed_M = &COM2DOFDetailed_M_;

/* Model step function */
void COM2DOFDetailed_step(void)
{
  /* Outport: '<Root>/dx' incorporates:
   *  Inport: '<Root>/x'
   *  MATLAB Function: '<S1>/sim2dof'
   */
  COM2DOFDetailed_Y.dx[0] = COM2DOFDetailed_U.x[0];
  COM2DOFDetailed_Y.dx[1] = COM2DOFDetailed_U.x[1];
  COM2DOFDetailed_Y.dx[2] = COM2DOFDetailed_U.x[2];
  COM2DOFDetailed_Y.dx[3] = COM2DOFDetailed_U.x[3];
}

/* Model initialize function */
void COM2DOFDetailed_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void COM2DOFDetailed_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
