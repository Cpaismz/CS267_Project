/* this file give an example of loading the "inputs" structure
and calling the calucate routine
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
/*#include "C:/BMW/cffdrs/fbp/TESTSET/fbp5.0.h"*/
#include "FBP5.0.h"

void main(int argc, char *argv[]){

 static  inputs data, *dataptr=&data;
 static  fuel_coefs coef[18], *coef_ptr=&coef[0];
 static  main_outs mainout, *mainptr=&mainout;
 static  fire_struc head,flank,backs,*headptr=&head,*backptr=&backs,*flankptr=&flank;
 static  snd_outs sec,*sndptr=&sec;
 char a,element[10]="\0\0\0\0\0\0\0\0\0\0";
 int i,ii,err,count,m,d,testcase;
 float var[19],lbt, accn;
 int month[13]={ 0,31,59,90,120,151,181,212,243,273,304,334};

 FILE *inp, *out;
 if(argc!=3){
 printf("enter FBP-line  in-filename out-filename\n");
 printf(" in-filename has one line per fueltype the form:\n");
 printf("FuelType,mon,day,mon_minFMC,day_minFMC, Lat, Long,elev,FFMC,WS,WDIR,BUI,\n");
 printf("     PS,SAZ,PC,PDF,GFL,CUR,Elapsed_time\n\n\n");
 printf(" data must be comma seperated.\n\n ");
 exit(1);}

 setup_const(coef_ptr);   // set up the FBPFUNC contants
 inp=fopen(argv[1],"r");
 out=fopen(argv[2],"w");

 err=fscanf(inp,"%c",&a);
 printf("err=%d\n",err);
 ii=0;testcase=1;
 while(err>=0 && ii<100){
  /* this just reads thru the line and idenfified the                   appropriate variables
     that are seperated by comma's  FUELTYPE gets found in this         process and the
    rest get put into a simple array
  */
   for(count=0,i=0,ii=0;a!='\n' && ii<100 && err>=0;err=fscanf(inp,"%c",&a) ,ii++){
     if(a==','){
       element[i]='\0';element[i+1]='\0';
       if(count==0) {
         if(i==2)element[i]=' ';
         strncpy(data.fueltype,element,4); 
        /* *** FUELTYPE IS SET HERE    */
       }
       else if(i==0) {var[count]=-9;printf("count=%d\n",count);}
       else var[count]=atof(element);
       i=0;
       count++;
     }
     else{
       element[i]=a;
       i++;
     }
   }  /* end of for loop    we are at the end of a line now  */
   /*get the last element */
   printf("err=%d ii=%d\n",err,ii);
   a='1';
   element[i]='\0';element[i+1]='\0';

   if(i==0) var[count]=-9;
  var[count]=atof(element);
  if(err<0)break;

/* NOW ASSIGN THE NUMERICAL INPUT DATA INTO THE PROPER STRUCTURE TO PASS TO THE  calculate  FUNCTION  */

  data.ffmc=var[8];
  data.ws=var[9];  
  data.bui=var[11]; 
  data.lat=var[5];  /* latitude */
  data.lon=var[6];   /*longitude , whic should be positive in the western hemisphere*/

  data.waz=(int)(var[10]);  /* wind direction*/
   /* now ADD 180 DEGREES TO INPUT WIND DIRECTION..to get wind direction is going to---wind aszimulth*/
  data.waz+=180;if(data.waz>=360)data.waz-=360;

  data.ps=(int)(var[12]);  /* percent slope  */
  data.saz=(int)(var[13]); /* slope azimulth...directiuon up hill*/
  data.pc=(int)(var[14]);  /* percentage conifer of mixedwood stands  m1/m2*/
  data.pdf=(int)(var[15]); /* percent dead fir in m3/m4   */
  data.cur=(int)(var[17]); /* percent cure of grass o1 */
  data.gfl=var[16];        /* grass fuel load   */
  data.elev=(int)(var[7]); /* elevation...only used in the foliar moisture scheme */
  data.time=(int)(var[18]);  /* length of time you want spread calc for...this is only important if calculating distance of spread*/

  data.mon=(int)(var[1]);
  m=data.mon; d=(int)(var[2]);
  if(m!=0) data.jd=month[m-1]+d;
  else data.jd=0;

  m=(int)(var[3]); d=(int)(var[4]);   /* this is minimum foliar moisture date*/
  if(m>0) data.jd_min=month[m-1]+d;   /* only use it if it is EXPLICITLY specified*/
  else data.jd_min=0;                 /* which is RARE */       

  data.pattern=1;   /* point source ignition...so acceleration is included */

/*  HERE is the call to the FBP calculation routine  */
    calculate(dataptr,coef_ptr,mainptr,sndptr,headptr,flankptr,backptr);

/* now just simple output  */
    fprintf(out,"Test Case %1d\n\n",testcase);
    fprintf(out,"FT=%3s  FFMC=%3.1f  BUI=%3.1f  WS=%3.1f  WDIR=%1d  WAZ=%1d  GS=%1d  SAZ=%1d\n",
    data.fueltype,data.ffmc,data.bui,data.ws,(int)(var[10]),data.waz,data.ps,data.saz);

    fprintf(out,"LAT=%4.1f  LONG=%5.1f  ELEV=%4d JD=%1d  JD(FMCmin)=%1d   Elapsed_time=%1d\n",
    data.lat,data.lon,data.elev,data.jd,data.jd_min,data.time);
    fprintf(out,"PC=%1d   PDF=%1d   GFL=%4.2f   CUR=%1d\n\n",
      data.pc,data.pdf,data.gfl,data.cur);

    fprintf((out),"WSV=%5.3f  RAZ=%5.2f BE=%5.3f  SF=%5.3f ISI=%5.3f  FMC=%4.2f  JDmin=%1d\n",
    mainout.wsv,mainout.raz,mainout.be,mainout.sf,mainout.isi,mainout.fmc,mainout.jd_min);
    fprintf((out),"RSS=%5.3f SFC=%5.3f SFI=%4.2f CFC=%5.3f RSO=%5.3f CSI=%4.2f  TFC=%5.3f \n",
    mainout.rss,mainout.sfc,mainout.sfi, head.cfc,mainout.rso, mainout.csi,head.fc);

    accn=acceleration(dataptr,head.cfb);
    lbt=(sec.lb-1.0)*(1.0-exp(-accn*data.time)) +1.0;

    fprintf((out),"\nLB=%5.3f  LB(t)=%5.3f  AREA=%5.3f  PERIMETER=%4.2f  PGR=%5.3f\n"
    ,sec.lb,lbt,sec.area,sec.perm/1000.0,sec.pgr);
    fprintf((out),"Head : CFB=%5.3f  FD=%c ROS=%5.3f FI=%4.2f ROS(t)=%5.3f  D(t)=%5.3f\n"
    ,head.cfb,head.fd,head.ros,head.fi,head.rost, (head.dist));
   fprintf((out),"Flank: CFB=%5.3f  FD=%c ROS=%5.3f FI=%4.2f ROS(t)=%5.3f  D(t)=%5.3f\n"
    ,flank.cfb,flank.fd,flank.ros,flank.fi,flank.rost, flank.dist);
    fprintf((out),"Back : CFB=%5.3f  FD=%c ROS=%5.3f FI=%4.2f ROS(t)=%5.3f  D(t)=%5.3f\n"
    ,backs.cfb,backs.fd,backs.ros,backs.fi,backs.rost, backs.dist);

   fprintf(out,"\n\n==================================\n\n");

 err=fscanf(inp,"%c",&a);
 testcase++;
 }  /* the end of the big while that goes line by line */
 fclose(inp);
 fclose(out);
}
