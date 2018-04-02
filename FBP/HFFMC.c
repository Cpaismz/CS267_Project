
/*

Copyright (c) 2006, Natural Resources Canada-Canadian Forest Service
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 the following conditions are met:
-Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
-Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer i
n the documentation and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE


 The Canadian Forest Service has gone through considerable testing to ensure that these
 computer functions duplicate the system as laid out in CFS Information Report 
"C.E. Van Wagner (1977) A method of computing fine fuel moisture content
 throughout the diurnal cycle. Canadian Forest Service, Petawawa Forest Experiment Station,
 Chalk River, Ont. Inf. Rep. PS-X-69"  however no guarantee is given as to the absolute accuracy of the code.
 
It has been modifed (2006) to reflect conversion to the FF scale and also to make
the rainfall absorption portion consistent with the FWI Systems FFMC calcualtions.
 
In addition it has been modified to fix TWO very minor accuracy issues
1) in the conversion between logbase 10 and natural log. Previously a constant
 2.303 was used as an approximation of ln(10),  the explicit form, log(10)
 is included.  (identified by KRA)

2) in conversion formula between FFMC and MC, which is used forwards and backwards on
each calcuation, has an accuracy issue which after a large number of calcuations can
systematically influence the results. IT is unlikely that the slightly bias introduced by this
accuracy issue is meaningful at all in the application of this hourly calcuation method to fire
management situations. While this small accuracy issue was identified only
during tests of a very large number of conversions betwen MC anbd FFMc in a version of the
program for sub-hourly FFMc calcuation, the more accutate conversaion factor has been included
in this version of the program for consistency.  147.2 has chanced to 147.27723
(the more accurate value seems to repeat 147.27722772277... though we have not extended our estimate
to try to demonstrate this to a large number of decimal places.

bmw/2006
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

float hourly_ffmc(float temp,float rh,float wind,float rain,float oldffmc);

main(int argc, char *argv[]){
  FILE *inp, *out;
  int err, year, mon, day, hour;
   float temp,rh,ws,rain,solrad,oldffmc,ffmc, time;
   
   if(argc!=4){
       printf(" ENTER >   HFFMC  <starting FFMC>  <input file>  <output file>\n\n");
       printf("INPUT FILE format must be space seperated and take the form\n");
       printf("YEAR  MONTH  DAY  HOUR  Temperature(C)  Relative_humitiy(%%)  Wind_speed(km/h)   Rainfall(mm)\n\n");
       exit(1);
   }
   
   inp=fopen(argv[2],"r");
   if(inp==NULL){printf("/n/n ***** FILE  %s  does not exist\n",argv[2]);exit(1);}
   out=fopen(argv[3],"w");
   
   oldffmc=atof(argv[1]);
   if(oldffmc>101 || oldffmc<0){ printf(" /n/n *****   FFMC must be between 0 and 101 \n"); exit(1);}

   err=fscanf(inp,"%d%d%d%d%f%f%f%f",&year,&mon,&day,&hour,&temp,&rh,&ws,&rain);
   while(err>=0){ 
     ffmc=hourly_ffmc(temp,rh,ws,rain,oldffmc);
     fprintf(out,"%4d %2d %2d %2d %5.1f %3.0f %5.1f %5.1f  %5.1f\n",year,mon,day,hour,temp,
             rh,ws,rain,ffmc); 
     oldffmc=ffmc;
     err=fscanf(inp,"%d%d%d%d%f%f%f%f",&year,&mon,&day,&hour,&temp,&rh,&ws,&rain);
  }

  printf("output has been written to %s\n",argv[3]); 
  fclose(inp);
  fclose(out);
}


float hourly_ffmc(float temp,float rh,float wind,float rain,float oldffmc)
/* this is the hourly ffmc routine given wx and previous ffmc */
{
  float rf=42.5,drf=0.0579;
  float mo,ed,ew,moew,moed,xm,a1,e,moe,xkd;
  mo=147.27723*(101-oldffmc)/(59.5+oldffmc);
  if(rain!=0)
   {
     if(mo>150) mo+= 0.0015*(mo-150)*(mo-150)*sqrt(rain)
               +rf*rain*exp(-100.0/(251-mo))*(1.0-exp(-6.93/rain));
       else mo+=rf*rain*exp(-100.0/(251-mo))*(1.0-exp(-6.93/rain)); 
     if(mo>250) mo=250;
   }
  ed=0.942*pow(rh,0.679)+(11.0*exp( (rh-100)/10.0))+0.18*(21.1-temp)*
     (1.0-1.0/exp(0.115*rh));
  moed=mo-ed;
  ew=0.618*pow(rh,0.753)+(10.0*exp((rh-100)/10.0))+0.18*(21.1-temp)*
     (1.0-1.0/exp(0.115*rh));
  moew=mo-ew;
  if (moed==0 || (moew>=0 && moed<0))
  {
    xm=mo;
    if(moed==0) e=ed;
    if(moew>=0) e=ew;
  }
  else
  {
    if( moed>0)
    {
      a1=rh/100;
      e=ed;
      moe=moed;
    }
    else
    {
      a1=(100.0-rh)/100.0;
      e=ew;
      moe=moew;
    }
   xkd=(0.424*(1-pow(a1,1.7))+(0.0694*sqrt(wind)*(1-pow(a1,8))));
   xkd=xkd*drf*exp(0.0365*temp);
   xm=e+moe*exp(-log(10.0)*xkd);
  }
  mo=xm;
  return ( 59.5*(250-xm)/(147.27723+xm) );
}
