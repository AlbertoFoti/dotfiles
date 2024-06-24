/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MatrixInverse.h
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

#ifndef MatrixInverse_h_
#define MatrixInverse_h_
#ifndef MatrixInverse_COMMON_INCLUDES_
#define MatrixInverse_COMMON_INCLUDES_
#include "rtwtypes.hxx"
#include "math.h"
#endif                                 /* MatrixInverse_COMMON_INCLUDES_ */

#include "MatrixInverse_types.hxx"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T u[64];                        /* '<Root>/u' */
} ExtU_MatrixInverse_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T y[64];                        /* '<Root>/y' */
} ExtY_MatrixInverse_T;

/* Real-time Model Data Structure */
struct tag_RTM_MatrixInverse_T {
  const char_T * volatile errorStatus;
};

/* External inputs (root inport signals with default storage) */
extern ExtU_MatrixInverse_T MatrixInverse_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_MatrixInverse_T MatrixInverse_Y;

/* Model entry point functions */
extern void MatrixInverse_initialize(void);
extern void MatrixInverse_step(void);
extern void MatrixInverse_terminate(void);

/* Real-time Model object */
extern RT_MODEL_MatrixInverse_T *const MatrixInverse_M;

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
 * hilite_system('linearAlgebraSim/MatrixInverse')    - opens subsystem linearAlgebraSim/MatrixInverse
 * hilite_system('linearAlgebraSim/MatrixInverse/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'linearAlgebraSim'
 * '<S1>'   : 'linearAlgebraSim/MatrixInverse'
 * '<S2>'   : 'linearAlgebraSim/MatrixInverse/MATLAB Function'
 */
#endif                                 /* MatrixInverse_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
