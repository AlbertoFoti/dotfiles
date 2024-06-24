/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: LinSysSolve.h
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

#ifndef LinSysSolve_h_
#define LinSysSolve_h_
#ifndef LinSysSolve_COMMON_INCLUDES_
#define LinSysSolve_COMMON_INCLUDES_
#include "rtwtypes.hxx"
#endif                                 /* LinSysSolve_COMMON_INCLUDES_ */

#include "LinSysSolve_types.hxx"
#include "rtGetNaN.hxx"
#include "rt_nonfinite.hxx"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T m[36];                        /* '<Root>/m' */
  real_T v[6];                         /* '<Root>/v' */
  real_T size1;                        /* '<Root>/size1' */
  real_T size2;                        /* '<Root>/size2' */
} ExtU_LinSysSolve_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T sol[6];                       /* '<Root>/sol' */
} ExtY_LinSysSolve_T;

/* Real-time Model Data Structure */
struct tag_RTM_LinSysSolve_T {
  const char_T * volatile errorStatus;
};

/* External inputs (root inport signals with default storage) */
extern ExtU_LinSysSolve_T LinSysSolve_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_LinSysSolve_T LinSysSolve_Y;

/* Model entry point functions */
extern void LinSysSolve_initialize(void);
extern void LinSysSolve_step(void);
extern void LinSysSolve_terminate(void);

/* Real-time Model object */
extern RT_MODEL_LinSysSolve_T *const LinSysSolve_M;

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
 * hilite_system('Sim2DOF_02/LinSysSolve')    - opens subsystem Sim2DOF_02/LinSysSolve
 * hilite_system('Sim2DOF_02/LinSysSolve/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Sim2DOF_02'
 * '<S1>'   : 'Sim2DOF_02/LinSysSolve'
 * '<S2>'   : 'Sim2DOF_02/LinSysSolve/MATLAB Function'
 */
#endif                                 /* LinSysSolve_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
