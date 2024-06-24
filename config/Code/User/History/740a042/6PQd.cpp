/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: LkupTable20.c
 *
 * Code generated for Simulink model 'LkupTable20'.
 *
 * Model version                  : 30.11
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu May 16 16:31:51 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "LkupTable20.hxx"
#include "LkupTable20_private.hxx"
#include "rtwtypes.hxx"

/* External inputs (root inport signals with default storage) */
ExtU_LkupTable20_T LkupTable20_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_LkupTable20_T LkupTable20_Y;

/* Real-time model */
static RT_MODEL_LkupTable20_T LkupTable20_M_;
RT_MODEL_LkupTable20_T *const LkupTable20_M = &LkupTable20_M_;

/* Lookup Binary Search Utility BINARYSEARCH_real_T */
void BINARYSEARCH20_real_T(uint32_T *piLeft, uint32_T *piRght, real_T u, const
  real_T *pData, uint32_T iHi)
{
  /* Find the location of current input value in the data table. */
  *piLeft = 0U;
  *piRght = iHi;
  if (u <= pData[0] ) {
    /* Less than or equal to the smallest point in the table. */
    *piRght = 0U;
  } else if (u >= pData[iHi] ) {
    /* Greater than or equal to the largest point in the table. */
    *piLeft = iHi;
  } else {
    uint32_T i;

    /* Do a binary search. */
    while (( *piRght - *piLeft ) > 1U ) {
      /* Get the average of the left and right indices using to Floor rounding. */
      i = (*piLeft + *piRght) >> 1;

      /* Move either the right index or the left index so that */
      /*  LeftDataPoint <= CurrentValue < RightDataPoint */
      if (u < pData[i] ) {
        *piRght = i;
      } else {
        *piLeft = i;
      }
    }
  }
}

/* Lookup Utility LookUp_real_T_real_T */
void LookUp_real_T_real_T(real_T *pY, const real_T *pYData, real_T u, const
  real_T *pUData, uint32_T iHi)
{
  uint32_T iLeft;
  uint32_T iRght;
  BINARYSEARCH20_real_T( &(iLeft), &(iRght), u, pUData, iHi);

  {
    real_T lambda;
    if (pUData[iRght] > pUData[iLeft] ) {
      real_T num;
      real_T den;
      den = pUData[iRght];
      den -= pUData[iLeft];
      num = u;
      num -= pUData[iLeft];
      lambda = num / den;
    } else {
      lambda = 0.0;
    }

    {
      real_T yLeftCast;
      real_T yRghtCast;
      yLeftCast = pYData[iLeft];
      yRghtCast = pYData[iRght];
      yLeftCast += lambda * ( yRghtCast - yLeftCast );
      (*pY) = yLeftCast;
    }
  }
}

/* Model step function */
void LkupTable20_step(void)
{
  /* S-Function (sfix_look1_dyn): '<S1>/Lookup Table Dynamic' incorporates:
   *  Inport: '<Root>/data_in'
   *  Inport: '<Root>/lkup_in'
   *  Inport: '<Root>/lkup_out'
   *  Outport: '<Root>/data_out'
   */
  /* Dynamic Look-Up Table Block: '<S1>/Lookup Table Dynamic'
   * Input0  Data Type:  Floating Point real_T
   * Input1  Data Type:  Floating Point real_T
   * Input2  Data Type:  Floating Point real_T
   * Output0 Data Type:  Floating Point real_T
   * Lookup Method: Linear_Endpoint
   *
   */
  LookUp_real_T_real_T( &(LkupTable20_Y.data_out), &LkupTable20_U.lkup_out[0],
                       LkupTable20_U.data_in, &LkupTable20_U.lkup_in[0], 19U);
}

/* Model initialize function */
void LkupTable20_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void LkupTable20_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
