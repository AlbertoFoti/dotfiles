/*
 * CoM3DOFDetailed.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "CoM3DOFDetailed".
 *
 * Model version              : 30.6
 * Simulink Coder version : 24.1 (R2024a) 19-Nov-2023
 * C source code generated on : Wed May 15 21:19:56 2024
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CoM3DOFDetailed.hxx"
#include <string.h>
#include "rt_nonfinite.hxx"

/* External inputs (root inport signals with default storage) */
ExtU_CoM3DOFDetailed_T CoM3DOFDetailed_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_CoM3DOFDetailed_T CoM3DOFDetailed_Y;

/* Real-time model */
static RT_MODEL_CoM3DOFDetailed_T CoM3DOFDetailed_M_;
RT_MODEL_CoM3DOFDetailed_T *const CoM3DOFDetailed_M = &CoM3DOFDetailed_M_;

/* Model output function */
static void CoM3DOFDetailed_output(void)
{
  /* Outport: '<Root>/x_dot' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  /* MATLAB Function 'CoM3DOFDetailed/MATLAB Function': '<S2>:1' */
  /* '<S2>:1:22' */
  /* '<S2>:1:23' */
  CoM3DOFDetailed_Y.x_dot = 1.0;

  /* Outport: '<Root>/inVarOut' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  CoM3DOFDetailed_Y.inVarOut = 0.0;
}

/* Model update function */
static void CoM3DOFDetailed_update(void)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++CoM3DOFDetailed_M->Timing.clockTick0)) {
    ++CoM3DOFDetailed_M->Timing.clockTickH0;
  }

  CoM3DOFDetailed_M->Timing.t[0] = CoM3DOFDetailed_M->Timing.clockTick0 *
    CoM3DOFDetailed_M->Timing.stepSize0 + CoM3DOFDetailed_M->Timing.clockTickH0 *
    CoM3DOFDetailed_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
static void CoM3DOFDetailed_initialize(void)
{
}

/* Model terminate function */
static void CoM3DOFDetailed_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  CoM3DOFDetailed_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  CoM3DOFDetailed_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  CoM3DOFDetailed_initialize();
}

void MdlTerminate(void)
{
  CoM3DOFDetailed_terminate();
}

/* Registration function */
RT_MODEL_CoM3DOFDetailed_T *CoM3DOFDetailed(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)CoM3DOFDetailed_M, 0,
                sizeof(RT_MODEL_CoM3DOFDetailed_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = CoM3DOFDetailed_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "CoM3DOFDetailed_M points to
       static memory which is guaranteed to be non-NULL" */
    CoM3DOFDetailed_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    CoM3DOFDetailed_M->Timing.sampleTimes =
      (&CoM3DOFDetailed_M->Timing.sampleTimesArray[0]);
    CoM3DOFDetailed_M->Timing.offsetTimes =
      (&CoM3DOFDetailed_M->Timing.offsetTimesArray[0]);

    /* task periods */
    CoM3DOFDetailed_M->Timing.sampleTimes[0] = (1.0);

    /* task offsets */
    CoM3DOFDetailed_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(CoM3DOFDetailed_M, &CoM3DOFDetailed_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = CoM3DOFDetailed_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    CoM3DOFDetailed_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(CoM3DOFDetailed_M, 290.0);
  CoM3DOFDetailed_M->Timing.stepSize0 = 1.0;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    CoM3DOFDetailed_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(CoM3DOFDetailed_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(CoM3DOFDetailed_M->rtwLogInfo, (NULL));
    rtliSetLogT(CoM3DOFDetailed_M->rtwLogInfo, "tout");
    rtliSetLogX(CoM3DOFDetailed_M->rtwLogInfo, "");
    rtliSetLogXFinal(CoM3DOFDetailed_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(CoM3DOFDetailed_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(CoM3DOFDetailed_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(CoM3DOFDetailed_M->rtwLogInfo, 0);
    rtliSetLogDecimation(CoM3DOFDetailed_M->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &CoM3DOFDetailed_Y.x_dot,
        &CoM3DOFDetailed_Y.inVarOut
      };

      rtliSetLogYSignalPtrs(CoM3DOFDetailed_M->rtwLogInfo, ((LogSignalPtrsType)
        rt_LoggedOutputSignalPtrs));
    }

    {
      static int_T rt_LoggedOutputWidths[] = {
        1,
        1
      };

      static int_T rt_LoggedOutputNumDimensions[] = {
        1,
        1
      };

      static int_T rt_LoggedOutputDimensions[] = {
        1,
        1
      };

      static boolean_T rt_LoggedOutputIsVarDims[] = {
        0,
        0
      };

      static void* rt_LoggedCurrentSignalDimensions[] = {
        (NULL),
        (NULL)
      };

      static int_T rt_LoggedCurrentSignalDimensionsSize[] = {
        4,
        4
      };

      static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] = {
        SS_DOUBLE,
        SS_DOUBLE
      };

      static int_T rt_LoggedOutputComplexSignals[] = {
        0,
        0
      };

      static RTWPreprocessingFcnPtr rt_LoggingPreprocessingFcnPtrs[] = {
        (NULL),
        (NULL)
      };

      static const char_T *rt_LoggedOutputLabels[] = {
        "x_dot",
        "inVarOut" };

      static const char_T *rt_LoggedOutputBlockNames[] = {
        "CoM3DOFDetailed/x_dot",
        "CoM3DOFDetailed/inVarOut" };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] = {
        {
          2,
          rt_LoggedOutputWidths,
          rt_LoggedOutputNumDimensions,
          rt_LoggedOutputDimensions,
          rt_LoggedOutputIsVarDims,
          rt_LoggedCurrentSignalDimensions,
          rt_LoggedCurrentSignalDimensionsSize,
          rt_LoggedOutputDataTypeIds,
          rt_LoggedOutputComplexSignals,
          (NULL),
          rt_LoggingPreprocessingFcnPtrs,

          { rt_LoggedOutputLabels },
          (NULL),
          (NULL),
          (NULL),

          { rt_LoggedOutputBlockNames },

          { (NULL) },
          (NULL),
          rt_RTWLogDataTypeConvert
        }
      };

      rtliSetLogYSignalInfo(CoM3DOFDetailed_M->rtwLogInfo,
                            rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
      rt_LoggedCurrentSignalDimensions[1] = &rt_LoggedOutputWidths[1];
    }

    rtliSetLogY(CoM3DOFDetailed_M->rtwLogInfo, "yout");
  }

  CoM3DOFDetailed_M->solverInfoPtr = (&CoM3DOFDetailed_M->solverInfo);
  CoM3DOFDetailed_M->Timing.stepSize = (1.0);
  rtsiSetFixedStepSize(&CoM3DOFDetailed_M->solverInfo, 1.0);
  rtsiSetSolverMode(&CoM3DOFDetailed_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* parameters */
  CoM3DOFDetailed_M->defaultParam = ((real_T *)&CoM3DOFDetailed_P);

  /* external inputs */
  CoM3DOFDetailed_M->inputs = (((void*)&CoM3DOFDetailed_U));
  (void)memset(&CoM3DOFDetailed_U, 0, sizeof(ExtU_CoM3DOFDetailed_T));

  /* external outputs */
  CoM3DOFDetailed_M->outputs = (&CoM3DOFDetailed_Y);
  (void)memset(&CoM3DOFDetailed_Y, 0, sizeof(ExtY_CoM3DOFDetailed_T));

  /* Initialize Sizes */
  CoM3DOFDetailed_M->Sizes.numContStates = (0);/* Number of continuous states */
  CoM3DOFDetailed_M->Sizes.numY = (2); /* Number of model outputs */
  CoM3DOFDetailed_M->Sizes.numU = (13);/* Number of model inputs */
  CoM3DOFDetailed_M->Sizes.sysDirFeedThru = (1);/* The model is direct feedthrough */
  CoM3DOFDetailed_M->Sizes.numSampTimes = (1);/* Number of sample times */
  CoM3DOFDetailed_M->Sizes.numBlocks = (4);/* Number of blocks */
  CoM3DOFDetailed_M->Sizes.numBlockIO = (0);/* Number of block outputs */
  CoM3DOFDetailed_M->Sizes.numBlockPrms = (4);/* Sum of parameter "widths" */
  return CoM3DOFDetailed_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
