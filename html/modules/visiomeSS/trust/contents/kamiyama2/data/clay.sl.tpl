/* $VisiomeSS-Revision: 1.2 $ $VisiomeSS-Date: 2003/03/04 05:24:29 $
   File:
     clay.sl
   Title:
     Clay's modifiedl Hodgkin-Huxley Model
   Author:
     Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
   Reference Paper:
     Clay, J, R. (1998)
     Excitability of the Squid Gian Axon Revisited,
     Journal of Neurophysiology, Vol.80, pp.903-913
*/
nassign("clay");
npp();
nlink("-O2");

color( "red" );
lwidth( 3, 2 );

series n,C2,C3,C4,C5,I,I4,I5,O,Ks;
series INa,IK,IL; 
series V;

nout(V,"HH",0,1);
nout(n,"HH",0,3,"n"); 
nout(C2,"HH",0,3,"C2"); 
nout(C3,"HH",0,3,"C3"); 
nout(C4,"HH",0,3,"C4"); 
nout(C5,"HH",0,3,"C5"); 
nout(I,"HH",0,3,"I"); 
nout(I4,"HH",0,3,"I4"); 
nout(I5,"HH",0,3,"I5"); 
nout(O,"HH",0,3,"O"); 
nout(Ks,"HH",0,3,"Ks"); 
nout(INa,"HH",0,3,"INa"); 
nout(IK,"HH",0,3,"IK"); 
nout(IL,"HH",0,3,"IL"); 

npara("HH","V0",-59.476884);
npara("HH","n0",0.379878);
npara("HH","C20",0.161531);
npara("HH","C30",0.037980);
npara("HH","C40",0.008930);
npara("HH","C50",0.003653);
npara("HH","I0",0.001298);
npara("HH","I40",0.070581);
npara("HH","I50",0.028864);
npara("HH","O0",0.000165);
npara("HH","Ks0",10.004398);

/* I in pA/cm^2 */
nstim("HH",0,"P",@@@NUMBER:10@@@,@@@NUMBER:0@@@,@@@NUMBER:0.3@@@,@@@NUMBER:60@@@,@@@NUMBER:9999@@@);
ntime(100.0,0.01,0.05,0.1);
xtime=(0~2000)*0.05;
ninteg("F");
ncal();

scale("N","F","N","F",@@@NUMBER:0@@@,@@@NUMBER:100@@@,@@@NUMBER:-80@@@,@@@NUMBER:70@@@);
graph(V,xtime,0,0,0,1,3.5);
axis(1,1,"XY","XY",4,0,3,25,25,0);
frame();
/* Copyright 2003, KAMIYAMA Yoshimi */
/* $VisiomeSS-Author: kamiyama $ */
