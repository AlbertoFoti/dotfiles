/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: COM2DOFDetailed.h
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

#ifndef COM2DOFDetailed_h_
#define COM2DOFDetailed_h_
#ifndef COM2DOFDetailed_COMMON_INCLUDES_
#define COM2DOFDetailed_COMMON_INCLUDES_
#include "rtwtypes.hxx"
#endif                                 /* COM2DOFDetailed_COMMON_INCLUDES_ */

#include "COM2DOFDetailed_types.hxx"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T x[4];                         /* '<Root>/x' */
  real_T mu;                           /* '<Root>/mu' */
  real_T DL[2];                        /* '<Root>/DL' */
  real_T rho;                          /* '<Root>/rho' */
} ExtU_COM2DOFDetailed_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T dx[4];                        /* '<Root>/dx' */
} ExtY_COM2DOFDetailed_T;

/* Real-time Model Data Structure */
struct tag_RTM_COM2DOFDetailed_T {
  const char_T * volatile errorStatus;
};

/* External inputs (root inport signals with default storage) */
extern ExtU_COM2DOFDetailed_T COM2DOFDetailed_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_COM2DOFDetailed_T COM2DOFDetailed_Y;

/* Model entry point functions */
extern void COM2DOFDetailed_initialize(void);
extern void COM2DOFDetailed_step(void);
extern void COM2DOFDetailed_terminate(void);

/* Real-time Model object */
extern RT_MODEL_COM2DOFDetailed_T *const COM2DOFDetailed_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('Sim2DOF_02/Sim2dof/COM2DOFDetailed')    - opens subsystem Sim2DOF_02/Sim2dof/COM2DOFDetailed
 * hilite_system('Sim2DOF_02/Sim2dof/COM2DOFDetailed/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Sim2DOF_02/Sim2dof'
 * '<S1>'   : 'Sim2DOF_02/Sim2dof/COM2DOFDetailed'
 * '<S2>'   : 'Sim2DOF_02/Sim2dof/COM2DOFDetailed/sim2dof'
 */
#endif                                 /* COM2DOFDetailed_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
