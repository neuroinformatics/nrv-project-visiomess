/* $VisiomeSS-Revision: 1.2 $ $VisiomeSS-Date: 2003/03/04 05:24:29 $
   File:
     hh.sl
   Title:
     Hodgkin-Huxley Model
   Author:
     Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
   Reference Paper:
     Hodgkin, A. L. and Huxley, A. F. (1952),
     A quantitative description of membrane current and its
     application to conduction and excitation in nerve,
     Journal of Physiology, Vol.117, pp.500-544 
     Clay, J, R. (1998),
     Excitability of the Squid Gian Axon Revisited,
     Journal of Neurophysiology, Vol.80, pp.903-913
*/
nassign("hh");
npp();
nlink("-O2");

series m,h,n;
series gNa,gK,INa,IK,IL;
series V;

nout(V,"HH",0,1);
nout(gK,"HH",0,3,"gK");
nout(h,"HH",0,3,"h");
nout(m,"HH",0,3,"m");
nout(n,"HH",0,3,"n");
nout(gNa,"HH",0,3,"gNa");

/* I in uA/cm^2 */
nstim("HH",0,"P",@@@NUMBER:10@@@,@@@NUMBER:0@@@,@@@NUMBER:30.0@@@,@@@NUMBER:60@@@,@@@NUMBER:9999@@@);
ntime(100.0,0.01,0.05,0.1);
xtime=(0~2000)*0.05;
ninteg("F");
ncal();

color("green");
lwidth(3, 2);

scale("N","F","N","F",@@@NUMBER:0@@@,@@@NUMBER:100@@@,@@@NUMBER:-80@@@,@@@NUMBER:70@@@);
graph(V,xtime,0,0,0,1,3.5);
axis(1,1,"XY","XY",4,0,3,25,25,0);
frame();
/* Copyright 2003, KAMIYAMA Yoshimi */
/* $VisiomeSS-Author: kamiyama $ */
