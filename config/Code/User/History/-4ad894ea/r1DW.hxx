/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CoM3DOFDetailed.h
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

#ifndef CoM3DOFDetailed_h_
#define CoM3DOFDetailed_h_
#ifndef CoM3DOFDetailed_COMMON_INCLUDES_
#define CoM3DOFDetailed_COMMON_INCLUDES_
#include "rtwtypes.hxx"
#endif                                 /* CoM3DOFDetailed_COMMON_INCLUDES_ */

#include "CoM3DOFDetailed_types.hxx"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T x[6];                         /* '<Root>/x' */
  real_T grav[3];                      /* '<Root>/grav' */
  real_T DL[2];                        /* '<Root>/DL' */
  real_T rho;                          /* '<Root>/rho' */
  real_T mu;                           /* '<Root>/mu' */
} ExtU_CoM3DOFDetailed_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T x_dot;                        /* '<Root>/x_dot' */
  real_T inVarOut;                     /* '<Root>/inVarOut' */
} ExtY_CoM3DOFDetailed_T;

/* Real-time Model Data Structure */
struct tag_RTM_CoM3DOFDetailed_T {
  const char_T * volatile errorStatus;
};

/* External inputs (root inport signals with default storage) */
extern ExtU_CoM3DOFDetailed_T CoM3DOFDetailed_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_CoM3DOFDetailed_T CoM3DOFDetailed_Y;

/* Model entry point functions */
extern void CoM3DOFDetailed_initialize(void);
extern void CoM3DOFDetailed_step(void);
extern void CoM3DOFDetailed_terminate(void);

/* Real-time Model object */
extern RT_MODEL_CoM3DOFDetailed_T *const CoM3DOFDetailed_M;

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
 * hilite_system('Sim3DOFDetailed/CoM3DOFDetailed')    - opens subsystem Sim3DOFDetailed/CoM3DOFDetailed
 * hilite_system('Sim3DOFDetailed/CoM3DOFDetailed/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Sim3DOFDetailed'
 * '<S1>'   : 'Sim3DOFDetailed/CoM3DOFDetailed'
 * '<S2>'   : 'Sim3DOFDetailed/CoM3DOFDetailed/MATLAB Function'
 */
#endif                                 /* CoM3DOFDetailed_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
