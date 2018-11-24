#include <stdio.h>
#include <math.h>
#include <time.h>

/*========= define structure for the symbols, values and units============*/
struct sym{
     char name[80];
     double value;
     char unit[80];
};

main(int argc, char *argv[])
{
/*==========C program for Runge-Kutta calculation in work station ========*/
     struct sym s[3000];
     char flo[255];
     char flm[255];
     double x[3000];
     double o[50][510];
     double k[4][3000];
     double xc[3000];
     double xstt,xstp,calstp,outstp,instp_h,instp_6,xx;
     double ts0,ts1,tb0,tb1,mn,mx,amp,stt,stp,frq,t1,t2,BL,BI,dty,pw,t_on,t_off,tbi;
     int fnc,burst;
     int v[3000],o_v[3000];
     int n_data=1;
     int n_sym,n_outval,n_v;
     int n,i,nn,nm;
     long int e1,e2,n1,n2,n3,n4,n5;
     char w[80],ww[80];
     FILE *fp1, *fp2;
     time_t t;
     /**************** list of symbols and symbol number ******************/
     /*     x1:A = 1 molec.                x13:kA-1 = 6.65 /s!            */
     /*     x2:A* = 0 molec.               x14:kA-2 = 2.22e1 /s!          */
     /*     x3:A.2glu = 0 molec.           x15:kA-2d = 6.65e2 /s!         */
     /*     x4:A.glu = 0 molec.            x16:kA1 = 2.22e5 /M/s!         */
     /*     x5:Ad* = 0 molec.              x17:kA2 = 7.39e5 /M/s!         */
     /*     x6:Ad.2glu = 0 molec.          x18:kA2d = 2.22e7 /M/s!        */
     /*     x7:Ad.glu = 0 molec.           x19:kdA-1 = 4.4e-1 /s!         */
     /*     x8:a = 2.96e2 /s!              x20:kdA-2 = 4.4e-1 /s!         */
     /*     x9:ad = 2.96e2 /s!             x21:kdA-3 = 1.32e1 /s!         */
     /*     x10:b = 4e3 /s!                x22:kdA1 = 1.46 /s!            */
     /*     x11:bd = 2e3 /s!               x23:kdA2 = 1.46e1 /s!          */
     /*     x12:glu = 0 M!                 x24:kdA3 = 1.46e2 /s!          */
     /************** RK.TMP file read and initial file write **************/
     fp1=fopen("RK.TMP","r");
     fscanf(fp1, "%s", w);
     fclose(fp1);
     if (fp1=fopen(w, "r")){
	fscanf(fp1,"%s",flm);
	fscanf(fp1,"%s",flo);
	fp2=fopen(flo, "w");
        fputs("*V2\n",fp2);
	fprintf(fp2, "%s\n",flm);
	fscanf(fp1,"%d",&n_sym);
	fgets(w,80,fp1);
	/*..... read/write symbols, initial values, units .....*/
	for(n=1;n<=n_sym;n++){
	   fscanf(fp1, "%s %lf %s", s[n].name, &s[n].value, s[n].unit);
	   x[n]=s[n].value;
	   fprintf(fp2, "%s %12.5e %s\n", s[n].name, x[n], s[n].unit);
	}
	/*........................ end mark .....................*/
	fscanf(fp1, "%s", ww);
	fputs("* * *\n",fp2);
	/*.................. read stimulation condition .........*/
	fgets(w,80,fp1);
	fscanf(fp1,"%d",&fnc);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&mn);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&mx);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&amp);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&stt);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&stp);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&frq);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&t1);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&t2);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&BL);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&BI);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&dty);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&pw);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&t_on);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&t_off);
	fgets(w,80,fp1);
	fprintf(fp2,"%d,%12.5e,%12.5e,%12.5e,%12.5e,%12.5e,%12.5e,%12.5e,%12.5e,%12.5e,%12.5e,%12.5e,%12.5e,%12.5e,%12.5e\n",fnc,mn,mx,amp,stt,stp,frq,t1,t2,BL,BI,dty,pw,t_on,t_off);
	/*......... cal.start/cal.stop/cal.step/out.step ........*/
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&xstt);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&xstp);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&calstp);
	fgets(w,80,fp1);
	fscanf(fp1,"%lf",&outstp);
	fgets(w,80,fp1);
	fprintf(fp2,"%12.5e,%12.5e,%12.5e,%12.5e\n",xstt,xstp,calstp,outstp);
	/*................ read number of outval ...............*/
	fgets(w,80,fp1);
	fscanf(fp1,"%d",&n_outval);
	fgets(w,80,fp1);
        fgets(w,80,fp1);
	for(n=1;n<=n_outval;n++){
	   fscanf(fp1,"%d",&i);
	   fgets(w,80,fp1);
	   o_v[n]=i;
	   fprintf(fp2,"%d\n",o_v[n]);
	}
	fputs("*\n",fp2);
        fgets(w,80,fp1);
	/*.................. read output variable # .............*/
	fscanf(fp1,"%d",&n_v);
	fgets(w,80,fp1);
        fgets(w,80,fp1);
	for(n=1;n<=n_v;n++){
	   fscanf(fp1,"%d",&i);
	   fgets(w,80,fp1);
	   v[n]=i;
	}
	/*.................. close ..............................*/
	fclose(fp1);
	fclose(fp2);
     } else
	printf("open error\n");
     /********************** preparation for calculation ******************/
     instp_h=calstp/2;
     instp_6=calstp/6;
     /*....................... save initial values .......................*/
     for(n=1;n<=n_outval;n++)
	o[n][n_data]=x[o_v[n]];
     if(argc>=1){
	fp2=fopen(flo,"a");
	for(n=1;n<n_outval;n++)
	   fprintf(fp2,"%12.5e,",o[n][n_data]);
	fprintf(fp2,"%12.5e\n",o[n_outval][n_data]);
	fclose(fp2);
     }
     n_data++;
     /*************************** calculation *****************************/
     e1=(xstp+0.4*outstp-xstt)/outstp-1;
     e2=outstp/calstp-1;
     time(&t);
     /*....................... preparation for stimulation ...............*/
     x[12]=mn;
     ts0=stt;
     tb0=stt;
     burst=1;
     /*...................................................................*/
     printf("calculation started at %s\n", ctime(&t));
     for(n1=0;n1<=e1;n1++){
	xx=((double)n1)*outstp+calstp;
	for(n2=0;n2<=e2;n2++){
	   x[0]=((double)n2)*calstp+xx;
	   /*............. stimulation ............*/
	   if((x[0]>=stt) && (x[0]<=stp)){
		ts1=x[0]-ts0;
		tb1=x[0]-tb0;
		if(BL==0)
		   tb1=0;
                if(( burst == 1) && (tb1 <= BL)){
                   /*step*/
                   if(fnc==1)
                      x[12]=mx;
                   /*pulse*/
                   if(fnc==2){
                      if(ts1<=t_on)
                         x[12]=mx;
                      if((ts1>t_on) && (ts1<=pw))
                         x[12]=mn;
                      if(ts1>pw)
                         ts0=x[0];
                   }
                   /*2exp*/
                   if(fnc==3){
                      if(ts1>=pw){
                         ts0=x[0];
                         ts1=x[0]-ts0;
                      }
                      x[12]=amp*(1 - exp(-ts1 / t1)) * exp(-ts1 / t2) + mn;
                   }
                   /*ramp*/
                   if(fnc==4){
                      if(ts1>=pw){
                         ts0=x[0];
                         ts1=x[0]-ts0;
                      }
                      x[12]=mx*ts1/pw + mn;
                   }
                   /*alpha*/
                   if(fnc==5){
                      if(ts1>=pw){
                         ts0=x[0];
                         ts1=x[0]-ts0;
                      }
                      x[12]=amp*ts1*exp(-ts1 / t1) + mn;
                   }
                }
                else {
                   if(burst==1){
                      tb0=x[0];
                      burst=0;
                      x[12]=mn;
                   }
                   tbi=x[0]-tb0;
                   if((burst==0) && (tbi>BI)){
                      burst=1;
                      tb0=x[0];
                   }
                }
           }
           else {
              x[12]=mn;
           }
           /*...........pre-loop calculation..........*/
	   /*............. integration ............*/
	   for(n=1;n<=n_v;n++)
		xc[v[n]]=x[v[n]];
           k[0][1]= - x[16]*x[1]*x[12] + x[13]*x[4];
           k[0][4]=x[16]*x[1]*x[12] - x[13]*x[4] - x[17]*x[4]*x[12] + x[14]*x[3] - x[22]*x[4] + x[19]*x[7];
           k[0][3]=x[17]*x[4]*x[12] - x[14]*x[3] - x[8]*x[3] + x[10]*x[2] - x[23]*x[3] + x[20]*x[6];
           k[0][2]=x[8]*x[3] - x[10]*x[2] - x[24]*x[2] + x[21]*x[5];
           k[0][7]= - x[18]*x[7]*x[12] + x[15]*x[6] + x[22]*x[4] - x[19]*x[7];
           k[0][6]=x[18]*x[7]*x[12] - x[15]*x[6] - x[9]*x[6] + x[11]*x[5] + x[23]*x[3] - x[20]*x[6];
           k[0][5]=x[9]*x[6] - x[11]*x[5] + x[24]*x[2] - x[21]*x[5];
	   nn=1;
	   for(n3=1;n3<=3;n3++){
		if(n3==1)
		   nm=1;
		if(n3==2)
		   nm=0;
		if(n3==3){
		   nm=2;
		   nn=2;
		}
                x[0]=x[0]+instp_h*((double)nm);
		for(n4=1;n4<=n_v;n4++)
		   x[v[n4]]=xc[v[n4]]+k[n3-1][v[n4]]*instp_h*((double)nn);
                k[n3][1]= - x[16]*x[1]*x[12] + x[13]*x[4];
                k[n3][4]=x[16]*x[1]*x[12] - x[13]*x[4] - x[17]*x[4]*x[12] + x[14]*x[3] - x[22]*x[4] + x[19]*x[7];
                k[n3][3]=x[17]*x[4]*x[12] - x[14]*x[3] - x[8]*x[3] + x[10]*x[2] - x[23]*x[3] + x[20]*x[6];
                k[n3][2]=x[8]*x[3] - x[10]*x[2] - x[24]*x[2] + x[21]*x[5];
                k[n3][7]= - x[18]*x[7]*x[12] + x[15]*x[6] + x[22]*x[4] - x[19]*x[7];
                k[n3][6]=x[18]*x[7]*x[12] - x[15]*x[6] - x[9]*x[6] + x[11]*x[5] + x[23]*x[3] - x[20]*x[6];
                k[n3][5]=x[9]*x[6] - x[11]*x[5] + x[24]*x[2] - x[21]*x[5];
	   }
	   for(n5=1;n5<=n_v;n5++)
		x[v[n5]]=xc[v[n5]]+instp_6*(k[0][v[n5]]+2.0*(k[1][v[n5]]+k[2][v[n5]])+k[3][v[n5]]);
           /*...........post-loop calculation..........*/
	}
        /*........................ save values ...........................*/
        for(n=1;n<=n_outval;n++)
	   o[n][n_data]=x[o_v[n]];
	if(argc>=1){
	   fp2=fopen(flo,"a");
	      for(n=1;n<n_outval;n++)
		fprintf(fp2,"%12.5e,",o[n][n_data]);
	      fprintf(fp2,"%12.5e\n",o[n_outval][n_data]);
	   fclose(fp2);
        }
        n_data++;
	time(&t);
	printf("file=%s   step=%d / ",flo,n1+1);
	printf("%d   %s\n",e1+1,ctime(&t));
     }
     /*********************** write calculation results *******************/
     fp2=fopen(flo,"a");
     if(argc<1){
        for(n=1;n<=n_data-1;n++){
	   for(nn=1;nn<n_outval;nn++)
	      fprintf(fp2,"%12.5e,",o[nn][n]);
	   fprintf(fp2,"%12.5e\n",o[n_outval][n]);
        }
     }
     fputs("/*symbol values at the end of calculation*/\n",fp2);
     for(n=1;n<=n_sym;n++)
	fprintf(fp2,"%12.5e\n",x[n]);
     fclose(fp2);
     /*********************************************************************/
}
