/* ME2E CVS header (please see footer for a full file history)

Current file status:

$Id: $

$Name:  $

$State: Exp $

*/
#include "../GE_GNC.hxx"
#include "GE_Guidance.hxx"
using namespace GE_GNC_utils;

void GE_Guidance_class::GE_GUI_Read(void)
{
  {  
     E2E_ReadFile file("GEguidance", "DHS");
 
/*  (1.1) P_TCon Discrete Control simulation time [s] */
    file.readReal(&GUI.P_TCon);
/*  (1.2) - Dimension of lookup tables */ 
    file.readReal(GUI.P_LUT_Dim,2);
/*  (1.3) P_machInLkUp[GUI.P_LUT_Dim[0]]  mach input divisions for LUTs depending on mach */
    file.readReal(GUI.P_machInLkUp, GUI.P_LUT_Dim[0]);
/*  (1.4) P_cDtrimLkUp[GUI.P_LUT_Dim[0]] cD output divisions for LUT depending on mach */
    file.readReal(GUI.P_cDtrimLkUp, GUI.P_LUT_Dim[0]);
/*  (1.5) P_cLtrimLkUp[GUI.P_LUT_Dim[0]] cL output divisions for LUT depending on mach */
    file.readReal(GUI.P_cLtrimLkUp, GUI.P_LUT_Dim[0]);
/*  (1.6) P_cNtrimLkUp[GUI.P_LUT_Dim[0]] cN output divisions for LUT depending on mach */
    file.readReal(GUI.P_cNtrimLkUp, GUI.P_LUT_Dim[0]);
/*  (1.7) P_tauNtrimLkUp[GUI.P_LUT_Dim[0]] tauN output divisions for LUT depending on mach */
    file.readReal(GUI.P_tauNtrimLkUp, GUI.P_LUT_Dim[0]);
/*  (1.8) P_RinLkUp[GUI.P_LUT_Dim[1]] Radius input divisions for LUTs depending on Radius */ 
    file.readReal(GUI.P_RinLkUp, GUI.P_LUT_Dim[1]);
/*  (1.9) P_cSndLkUp[GUI.P_LUT_Dim[1]] Sound output divisions for LUT depending on Radius */
    file.readReal(GUI.P_cSndLkUp, GUI.P_LUT_Dim[1]);
/*  (1.10) P_rhoNomLkUp[GUI.P_LUT_Dim[1]] rho output divisions for LUT depending on Radius */
    file.readReal(GUI.P_rhoNomLkUp, GUI.P_LUT_Dim[1]);
/*  (1.11) P_HatmLkUpFilt[GUI.P_LUT_Dim[1]] Hatm output divisions for LUT depending on Radius */
    file.readReal(GUI.P_HatmLkUpFilt, GUI.P_LUT_Dim[1]);
  }
  {   
   E2E_ReadFile file("GEguidanceInit", "DHS");
     
/*  (1.1) Initial value of the estimated bank angle [rad] */
    file.readReal(&GUI.P_muGui0);  
/*  (1.2) Initial value of the estimated bank angular rate [rad/s] */
    file.readReal(&GUI.P_omgMuGui0);
  }  
  {
   E2E_ReadFile file("GEpathplannerLong", "DHS");
 
/*  (1.1) Dimension of Planned array of commanded bank angle */
    file.readReal(&GUI.P_MuDim);  
/*  (1.1) Planned command of the bank angle */
    file.readReal(GUI.P_uMuGuiRs, GUI.P_MuDim);  
/*  (1.2) Planned bank angle */
    file.readReal(GUI.P_MuGuiRs, GUI.P_MuDim);
/*  (1.3) Planned CoM state vector */
    file.readReal(GUI.P_xCoMGuiRs, GUI.P_MuDim, 6);
/*  (1.4) Planned gravity vector */
    file.readReal(GUI.P_gNEDGuiRs, GUI.P_MuDim, 3);
  }
  
}

void GE_Guidance_class::GE_GUI_Init(double *xMuGui)
{        
   GUI.D_CS  = 0; 					/* Current Step Nav Con loop*/
   GUI.D_xMuGui_prev[0]=GUI.P_muGui0;    		/* Initial Bank Angle */
   GUI.D_xMuGui_prev[1]=GUI.P_omgMuGui0; 		/* Initial Bank Omega */          

   xMuGui[0]=GUI.P_muGui0;
   xMuGui[1]=GUI.P_omgMuGui0; 

   /* init _prev data*/ 
   GUI.D_xMuGui_prev[0] = xMuGui[0];
   GUI.D_xMuGui_prev[1] = xMuGui[1];

   /* store initial guess */

   for (int i=0; i<6; i++)
   {  
     GUI.O_xCoMGui[i] = GUI.P_xCoMGuiRs[GUI.D_CS][i]; 						/* Output 1 of the Simulink schematic */
   }

   GUI.O_xMuGui[0] = xMuGui[0];
   GUI.O_xMuGui[1] = xMuGui[1];

}

void GE_Guidance_class::GE_GUI_Exec(double xCoMNav[6], double *xCoMGui, double *DragLift, double *RhoHatm, double *cNtauN, double *gNED, double *xMuGui, double *uMuGui)                                
        
{

int i,j;
double Vw, Radius, vSound, machNav;
    
 for (i=0; i<6; i++)
 {  
     xCoMGui[i] = GUI.P_xCoMGuiRs[GUI.D_CS][i]; 						/* Output 1 of the Simulink schematic */
 }
 *uMuGui = GUI.P_uMuGuiRs[GUI.D_CS];         							/* Output 2 of the Simulink schematic */
 
 xMuGui[0] = GUI.D_xMuGui_prev[0] + GUI.D_xMuGui_prev[1] + 0.5**uMuGui;  			/* Output 3 of the Simulink schematic */
 xMuGui[1] = GUI.D_xMuGui_prev[1] +*uMuGui;  							/* Output 3 of the Simulink schematic */ 
                                   
 //Vw = GUI.P_xCoMGuiRs[GUI.D_CS][3];
 //Radius = GUI.P_xCoMGuiRs[GUI.D_CS][0];
 
 Vw = xCoMNav[3];
 Radius = xCoMNav[0];

 vSound = lookup(GUI.P_RinLkUp, GUI.P_cSndLkUp, Radius, GUI.P_LUT_Dim[1]);

 machNav=Vw/vSound;
 DragLift[0] = lookup(GUI.P_machInLkUp, GUI.P_cDtrimLkUp, machNav, GUI.P_LUT_Dim[0]); 		/* Output 4 of the Simulink schematic */
 DragLift[1] = lookup(GUI.P_machInLkUp, GUI.P_cLtrimLkUp, machNav, GUI.P_LUT_Dim[0]); 		/* Output 4 of the Simulink schematic */ 
 RhoHatm[0] = lookup(GUI.P_RinLkUp, GUI.P_rhoNomLkUp, Radius, GUI.P_LUT_Dim[1]); 		/* Output 5 of the Simulink schematic */
 RhoHatm[1] = lookup(GUI.P_RinLkUp, GUI.P_HatmLkUpFilt, Radius, GUI.P_LUT_Dim[1]); 		/* Output 5 of the Simulink schematic */
 cNtauN[0] = lookup(GUI.P_machInLkUp, GUI.P_cNtrimLkUp, machNav, GUI.P_LUT_Dim[0]);  		/* Output 6 of the Simulink schematic */      
 cNtauN[1] = lookup(GUI.P_machInLkUp, GUI.P_tauNtrimLkUp, machNav, GUI.P_LUT_Dim[0]); 		/* Output 6 of the Simulink schematic */

 
 for (i=0; i<3; i++)
 {
     gNED[i] = GUI.P_gNEDGuiRs[GUI.D_CS][i]; 							/* Output 7 of the Simulink schematic */
 }
 
 for (i=0; i<6; i++)
 {  
     GUI.O_xCoMGui[i] = GUI.P_xCoMGuiRs[GUI.D_CS][i]; 						/* Output 1 of the Simulink schematic */
 }

 /* Store output data*/ 
 GUI.O_muGuiOut = GUI.P_MuGuiRs[GUI.D_CS];
 GUI.O_umuGuiOut = GUI.P_uMuGuiRs[GUI.D_CS];
 GUI.O_xMuGui[0] = xMuGui[0];
 GUI.O_xMuGui[1] = xMuGui[1];
 GUI.O_RhoHatm[0] = RhoHatm[0];
 GUI.O_RhoHatm[1] = RhoHatm[1];
 GUI.O_CDCL[0] = DragLift[0];
 GUI.O_CDCL[1] = DragLift[1];
 GUI.O_cNtauN[0] = cNtauN[0];
 GUI.O_cNtauN[1] = cNtauN[1];
 GUI.O_cSound = vSound;
 GUI.O_Mach = machNav;

 /* Update data*/ 
 GUI.D_xMuGui_prev[0] = xMuGui[0];
 GUI.D_xMuGui_prev[1] = xMuGui[1];
 
 GUI.D_CS = GUI.D_CS + 1;
 
   
}

void GE_Guidance_class::GE_GUI_Exit(void)
{
}

void GE_Guidance_class::GE_GUI_WriteDebugFile(E2E_PrintOutput *outfile)
{
    outfile->E2E_writeVar(GUI.O_muGuiOut, "rad");
    outfile->E2E_writeVar(GUI.O_umuGuiOut, "rad/s^2");
    outfile->E2E_writeVar(GUI.O_xMuGui, 2,"-");
    outfile->E2E_writeVar(GUI.O_xCoMGui,6, ""); 
    outfile->E2E_writeVar(GUI.O_RhoHatm,2, ""); 
    outfile->E2E_writeVar(GUI.O_CDCL,2, ""); 
    outfile->E2E_writeVar(GUI.O_cNtauN,2, ""); 
    outfile->E2E_writeVar(GUI.O_cSound,"m/s"); 
    outfile->E2E_writeVar(GUI.O_Mach,"");

//     outfile->E2E_writeVar(GUI.O_muSimNomOut, "m/s^2");    
}
/* ME2E CVS footer

Full file history:

$Log: $


*/

