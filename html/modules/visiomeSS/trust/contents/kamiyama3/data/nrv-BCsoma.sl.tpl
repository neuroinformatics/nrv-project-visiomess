/* $VisiomeSS-Revision: 1.7 $ $VisiomeSS-Date: 2003/10/24 07:25:17 $
   File: 
     nrv-BCsoma.sl
   Title:
     Retinal Bipolar Cell Model 
   Author: 
     Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
     Akito   Ishihara (ishihara@bpel.ics.tut.ac.jp)
   Reference Paper: 
     Usui, S., Ishihara, A., Kamiyama, Y. and Ishii, H. (1996),
     Ionic current model of bipolar cells in lower vertebrate
     retina, Vision Research, Vol.36, No.24, pp.4096-4076
*/
series mKv, hKv, C1, C2, OP1, OP2, OP3, mCa; 
series Ca_s, bCa_ls, bCa_hs, Ca_d, bCa_ld, bCa_hd, mKca, mA, hA;
series i_all, Vm;
series iv_051,iv_249, iv;

nassign("nrv-BCsoma");
npp();
nlink("-O2");

/* observable & output variables */
nout(mKv,"BC",0,3,"mKv");
nout(hKv,"BC",0,3,"hKv");
nout(C1,"BC",0,3,"C1");
nout(C2,"BC",0,3,"C2");
nout(OP1,"BC",0,3,"OP1");
nout(OP2,"BC",0,3,"OP2");
nout(OP3,"BC",0,3,"OP3");
nout(mCa,"BC",0,3,"mCa");
nout(Ca_s,"BC",0,3,"Ca_s");
nout(bCa_ls,"BC",0,3,"bCa_ls");
nout(bCa_hs,"BC",0,3,"bCa_hs");
nout(Ca_d,"BC",0,3,"Ca_d");
nout(bCa_ld,"BC",0,3,"bCa_ld");
nout(bCa_hd,"BC",0,3,"bCa_hd");
nout(mKca,"BC",0,3,"mKca");
nout(mA,"BC",0,3,"mA");
nout(hA,"BC",0,3,"hA");
nout(i_all,"BC",0,1);
nout(Vm,"BC",0,2);

numV=20;
Vh=@@@NUMBER:-30.0@@@;
Vc=(@@@NUMBER:-70@@@,@@@NUMBER:-60@@@,@@@NUMBER:-50@@@,@@@NUMBER:-40@@@,@@@NUMBER:-30@@@,@@@NUMBER:-20@@@,@@@NUMBER:-10@@@,@@@NUMBER:0@@@,@@@NUMBER:10@@@,@@@NUMBER:20@@@,@@@NUMBER:30@@@,@@@NUMBER:40@@@,@@@NUMBER:50@@@,@@@NUMBER:60@@@,@@@NUMBER:70@@@,@@@NUMBER:80@@@,@@@NUMBER:90@@@,@@@NUMBER:100@@@,@@@NUMBER:110@@@,@@@NUMBER:120@@@,@@@NUMBER:130@@@);
xtime=(0~500)*0.01

ninteg("R");
ginit();
wopen(1,"A4",0,2);
depax=0;hypax=0;

ntime(5.0,0.00001,0.01,0.1);

for (i=0; i<=numV; i++) {
  nstim("BC",0,"P",@@@NUMBER:0.5@@@,Vh,Vc:[i],@@@NUMBER:2.0@@@,@@@NUMBER:999.@@@);
  printf("Vh = %5.1f [mV]  Vc = %5.1f [mV]\n",Vh,Vc:[i]);
  ncal();
  iv_051:[i] =  get(i_all,find(xtime,0.51,1));
  iv_249:[i] =  get(i_all,find(xtime,2.49,1));
  iv:[i]     =  Vh + Vc:[i];
  if ( Vc:[i] > 0  ) {
     origin(20,110)
     size(80,10);
     scale("N","F","N","F",@@@NUMBER:0@@@,@@@NUMBER:5@@@,@@@NUMBER:-35@@@,@@@NUMBER:140@@@)
     graph(Vm,xtime,0,0,0,1,3.5);
     origin(20,140)
     size(80,50);
     scale("N","F","N","F",@@@NUMBER:0@@@,@@@NUMBER:5@@@,@@@NUMBER:-60@@@,@@@NUMBER:220@@@)
     if (depax==0) {
        label("I",0,-18,3,0,"Vh=-30",0);
        label("I",80,-28,3,0,"V=-20 to 100",1);
        title(1,"time[sec]","current[pA]");
        axis(1,1,"XY","XY",3.5,0,3,1,50,0);
        frame();
        depax=1;
     }
     graph(i_all,xtime,0,0,0,1,3.5);
  } else {
     origin(20,20)
     size(80,10);
     scale("N","F","N","F",@@@NUMBER:0@@@,@@@NUMBER:5@@@,@@@NUMBER:-100@@@,@@@NUMBER:-25@@@)
     graph(Vm,xtime,0,0,0,1,3.5);
     origin(20,50)
     size(80,50);
     scale("N","F","N","F",@@@NUMBER:0@@@,@@@NUMBER:5@@@,@@@NUMBER:-120@@@,@@@NUMBER:70@@@)
     if (hypax==0) {
        label("I",0,-18,3,0,"Vh=-30",0);
        label("I",80,-28,3,0,"V=-100 to -30",1);
        title(1,"time[sec]","current[pA]");
        axis(1,1,"XY","XY",3.5,0,3,1,50,0);
        frame();
        hypax=1;
     }
     graph(i_all,xtime,0,0,0,1,3.5);
  }
}

/* Draw I-V characteristics */
origin(120,20);
size(80,170);
scale("N","F","N","F",@@@NUMBER:-110@@@,@@@NUMBER:110@@@,@@@NUMBER:-110@@@,@@@NUMBER:210@@@);
graph(cut(iv_051,0,(find(iv,-30,1)-1)),cut(iv,0,(find(iv,-30,1)-1)),0,2,0,8,2);
graph(iv_249,iv,0,2,0,7,2);
title(1,"Membrane Potential[mV]","Current[pA]");
axis(1,1,"XY","XY",3.5,0,3,50,50,0);
draw("X",0);
draw("Y",0);
label("I",10,30,3.0,0,"2.49[s]");
label("I",2,53,3.0,0,"0.51[s]");
frame();
