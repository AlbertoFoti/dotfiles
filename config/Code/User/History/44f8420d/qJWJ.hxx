/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: LkupTable1000_private.h
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

#ifndef LkupTable1000_private_h_
#define LkupTable1000_private_h_
#include "rtwtypes.hxx"
#include "LkupTable1000_types.hxx"
#include "LkupTable1000.hxx"

void BINARYSEARCH_real_T(uint32_T *piLeft, uint32_T *piRght, real_T u, const
  real_T *pData, uint32_T iHi);
void LookUp_real_T_real_T(real_T *pY, const real_T *pYData, real_T u, const
  real_T *pUData, uint32_T iHi);

#endif                                 /* LkupTable1000_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
