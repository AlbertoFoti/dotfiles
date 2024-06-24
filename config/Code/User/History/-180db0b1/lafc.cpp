#include "GE_Grav01.hxx"
#include <cmath>

void GE_Grav01_class::GE_Grav_Init(void){}

void GE_Grav01_class::GE_Grav_Exec(const double xCoMNav[6], double gNED[3])
{

  double gg, sl, cl, rre, g[2];
  double P[4], JP[4], Q[4], JQ[4];
  double R,latitude;
  int jj;
  
  if (Grav.P_GRAVID==0)
  {
    gNED[0]=0;			/* north */
    gNED[1]=0;			/* east  */
    gNED[2]=0;			/* down	 */   
  }
   
  else
  {
   /* From the translation navigation the Radius and the latitude are considered.  longitude is not influencing the oblateness model */
    R	= xCoMNav[0]; 
    latitude = xCoMNav[2];

    gg	= Grav.P_MU/(R*R);

    g[0] = 1; 
    g[1] = 0;

     /* Zonal Harmonics */
    if (Grav.P_GRAVID>1)
    { 
      sl = sin(latitude);
      cl = cos(latitude);

      P[1] =1.-3.*sl*sl;
      JP[1]=3./2.*Grav.P_J2;
      Q[1] =2.*cl*sl;
      JQ[1]=3./2.*Grav.P_J2;

      P[2] =sl*(3.-5.*sl*sl);
      JP[2]=2.*Grav.P_J3;
      Q[2] =cl*(4.-5.*cl*cl);
      JQ[2]=3./2.*Grav.P_J3;

      P[3] =3.-30.*sl*sl+35.*sl*sl*sl*sl;
      JP[3]=-5./8.*Grav.P_J4;
      Q[3] =Q[1]*(4.-7.*cl*cl);
      JQ[3]=5./4.*Grav.P_J4;

      rre = Grav.P_REQ/R;

	 for (jj=1; jj<Grav.P_GRAVID; jj++)
	 {
		g[0]=g[0]+JP[jj]*pow(rre,(double)jj+1.)*P[jj];
		g[1]=g[1]+JQ[jj]*pow(rre,(double)jj+1.)*Q[jj];
	 }
    }

    g[0] = g[0]*gg;
    g[1] = g[1]*gg;

// #if 0
//     if (g[0]<=EPS) {g[0]=0.;}
//     if (g[1]<=EPS) {g[1]=0.;}
// #endif //0

    gNED[0]=g[1];	/* north */
    gNED[1]=0;		/* east  */
    gNED[2]=g[0];	/* down	 */

  }

/* Store gNED vector in output structure */
    for (int i=0;i<3;i++){
     Grav.O_gNED[i] = gNED[i];
  }

}