/* $VisiomeSS-Revision: 1.2 $ $VisiomeSS-Date: 2003/10/24 07:21:08 $
   File:
     ICa_double_compute.sl
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

nasgn("ICa");
nmake();


hold            =@@@NUMBER:-60@@@;
clamp_time      =@@@NUMBER:2.3@@@; #(sec)
sim_time        =@@@NUMBER:10@@@;
cal_time        =@@@NUMBER:0.0001@@@;
store_time      =@@@NUMBER:0.01@@@;
interval        =@@@NUMBER:3.3@@@;

series ICa;     nout(ICa,"HC",0,3,"ICa")
series Ca;      nout(Ca,"HC",0,3,"Ca")
series Input;   nout(Input,"HC",0,2)

i=0;
for(stim=-60;stim<60;stim+=10){
### voltate stimulus
tmp=(0~(sim_time/cal_time))*0+hold;
tmp2=fill(tmp,1/cal_time,(1+clamp_time)/cal_time,stim);
input=fill(tmp2,(1+interval)/cal_time,(1+interval+clamp_time)/cal_time,0);
undef(tmp);undef(tmp2);

nstim("HC",0,"B",input);
ntime(sim_time,cal_time,store_time)

ncal();
DATA="ICa_double.dat"; $DATA:[i]=ICa;
DATA="Ca_double.dat"; $DATA:[i]=Ca;
DATA="ICa_double_stim.dat"; $DATA:[i]=Input;
i++;
}
#
# Draw Graph
#
inline("ICa_double.sl");
