/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: $

$Name:  $

$State: Exp $

*/
#ifndef GE_GNC_HXX
#define GE_GNC_HXX

#define DOUBLE double
#define CHAR char
#define INT32 int32_t

#include <cstdint>
#include <cmath>
//#include "GE_Guidance.hxx"
#include "Navigation/GE_Navigation.hxx"
//#include "GE_CoMControl.hxx"
//#include "GE_AttControl.hxx"

struct DHS_DM_INPUT_type;
struct DHS_DM_OUTPUT_type;

namespace GE_GNC_utils
{
// allocation function of the class found in MemHandling.cpp
double **dmatrix(int dim_i, int dim_j, double dinit);
double *dvector(int dim, double dinit);
int *ivector(int dim, int dinit);
void MyFree(void *a);
void MyFreeInt(int *a);

// Mathematical function of the class found in SPA_Matrix.cpp
void InvertMat3(double **x, double **invx);
void InvertMat2(double **x, double **invx);
void MultVByScl(double *x, double a, double *y, int N);
void MultMByScl(double **x, double a, double **y, int Nr, int Nc);
void MultVByScl3(double *x, double a, double *y);
void MultMByScl3(double **x, double a, double **y);
void AddV(double const *x1, double const *x2, double *y, int N);
void AddV3(double const *x1, double const *x2, double *y);
void CrossP3(double *x1, double *x2, double *y);
void DotPMV(double **m, double *x, double *dotP, int Nr, int Nc);
void DotPMV3(double **m, double *x, double *dotP);
void DotPMM(double **x1, double **x2, double **dotP, int Nr1, int Nc1, int Nr2,
            int Nc2);
void DotPMM3(double **x1, double **x2, double **dotP);
void AddM(double **x1, double **x2, double **y, int Nr, int Nc);
void AddM3(double **x1, double **x2, double **y);
void SaveVectIntoDatFile(double *x, int N, char *fileName);
void SaveMatIntoDatFile(double **m, int Nr, int Nc, char *fileName);
void NormalizeV4(double *q);
void CpVect(double *x1, double *x2, int N);
void SmoothStep(double *x, int N, double dir);
void QuatP(double *qa, double *qb, double *qOut, int conj);
void Quat2Rot(double *q, double **M);
void Rot2Quat(double **M, double *q);
void UpdateQuat(double *q, double *mu, double *qf, double minRate);
void QuatRot(double *v, double *q, double *y, char direction);
double *polcar(double **A, long int n);
double SatF(double *x, double min, double max);
double Sign(double x);
double Abs(double x);
double Sat(double x, double min, double max);
double Max(double *x, int N);
int Round2I(double x);
double lookup(double *xx, double *yy, double x, uint32_t N_PTS);
};

class GE_GNC_class
{
 private:
   // Sub class declaration
 
   //GE_Guidance_class GE_Gui;   
   GE_Navigation_class GE_Nav;
   //GE_CoMControl_class GE_Ccn;
   //GE_AttControl_class GE_Acn;

   // Class parameters:
   struct GNC_type
   {
      uint8_t BrmStatus_prev;
   } GNC;

 public:
   void GE_GNC_Read(void);
   void GE_GNC_Init(DHS_DM_INPUT_type *DhsInput, DHS_DM_OUTPUT_type *DhsOutput);
   void GE_GNC_Exec(DHS_DM_INPUT_type *DhsInput, DHS_DM_OUTPUT_type *DhsOutput);
   void GE_GNC_Exit(void);
   void GE_GNC_WriteDebugFile(E2E_PrintOutput *outfile);
};

#endif 


// GE_GNC_HXX
/* ME2E CVS footer

Full file history:

$Log: $


*/

