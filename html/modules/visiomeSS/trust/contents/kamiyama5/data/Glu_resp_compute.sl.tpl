/* $VisiomeSS-Revision: 1.2 $ $VisiomeSS-Date: 2003/10/24 07:21:08 $
   File:
     Glu_resp_compute.sl
   Title:
     Ionic Current Model of Fish Retinal Horizontal Cell
   Author:
     KAMIYAMA Yoshimi (kamiyama@ist.aichi-pu.ac.jp)
     AOYAMA Toshihiro (aoyama@brain.riken.go.jp)
   Reference Paper:
     Aoyama, T., Kamiyama, Y. and Usui. S. (2002)
     Simulation analysis of current-voltage relationship 
     of retinal horizontal cells
     The Transactions of the Institute of Electronics, Information
     and Communication Engineers, Vol.J85-D-II, 918-930
*/

nasgn("fishHC");
nmake();
ninteg("R");

series v;    nout(v,"HC",0,3,"V");
series Ca; nout(Ca,"HC",0,3,"Ca");

ntime(200,0.0001,0.1);

# Glutamate concentration (mM)
stims=(@@@NUMBER:0.001@@@, @@@NUMBER:0.003@@@, @@@NUMBER:0.005@@@, @@@NUMBER:0.008@@@, @@@NUMBER:0.01@@@, @@@NUMBER:0.03@@@, @@@NUMBER:0.1@@@, @@@NUMBER:0.3@@@, @@@NUMBER:1@@@);

#### control condition
for(i=0;i<index(stims);i++){
nstim("HC",0,"P", 1,0,stims:[i],100,1000);  # for Glutamate input
ncal();
$"control_V.dat":[i]=v;
$"control_Ca.dat":[i]=Ca;
}

####  without calcium store buffer (SB)
npara("HC",SB_t,0.0);
npara("HC",SB_init,0.0);

for(i=0;i<index(stims);i++){
nstim("HC",0,"P", 1,0,stims:[i],100,1000);  # for Glutamate input
ncal();
$"withoutSB_V.dat":[i]=v;
$"withoutSB_Ca.dat":[i]=Ca;
}

inline("Glu_resp.sl");
