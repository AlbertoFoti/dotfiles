/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: LkupTable1000.h
 *
 * Code generated for Simulink model 'LkupTable1000'.
 *
 * Model version                  : 30.11
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu May 16 16:32:00 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef LkupTable1000_h_
#define LkupTable1000_h_
#ifndef LkupTable1000_COMMON_INCLUDES_
#define LkupTable1000_COMMON_INCLUDES_
#include "rtwtypes.hxx"
#endif                                 /* LkupTable1000_COMMON_INCLUDES_ */

#include "LkupTable1000_types.hxx"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T data_in;                      /* '<Root>/data_in' */
  real_T lkup_in[1000];                /* '<Root>/lkup_in' */
  real_T lkup_out[1000];               /* '<Root>/lkup_out' */
} ExtU_LkupTable1000_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T data_out;                     /* '<Root>/data_out' */
} ExtY_LkupTable1000_T;

/* Real-time Model Data Structure */
struct tag_RTM_LkupTable1000_T {
  const char_T * volatile errorStatus;
};

/* External inputs (root inport signals with default storage) */
extern ExtU_LkupTable1000_T LkupTable1000_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_LkupTable1000_T LkupTable1000_Y;

/* Model entry point functions */
extern void LkupTable1000_initialize(void);
extern void LkupTable1000_step(void);
extern void LkupTable1000_terminate(void);

/* Real-time Model object */
extern RT_MODEL_LkupTable1000_T *const LkupTable1000_M;

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
 * hilite_system('Sim3DOFDetailed/LkupTable1000')    - opens subsystem Sim3DOFDetailed/LkupTable1000
 * hilite_system('Sim3DOFDetailed/LkupTable1000/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Sim3DOFDetailed'
 * '<S1>'   : 'Sim3DOFDetailed/LkupTable1000'
 */
#endif                                 /* LkupTable1000_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
