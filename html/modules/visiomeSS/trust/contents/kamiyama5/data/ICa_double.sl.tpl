/* $VisiomeSS-Revision: 1.3 $ $VisiomeSS-Date: 2003/10/24 07:21:08 $
   File:
     ICa_double.sl
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

wopen(1,"A4",0,2);
we();
lwidth(2,3);
font(7);
color("white","white");

t=(0~1500)/100

series tmpI, tmpI2, tmpV, tmpQ, tmpQ2;

hold            =-60;
clamp_time      =2.3; #(sec)
sim_time        =10;
cal_time        =0.0001;
store_time      =0.01;
interval        =3.3;

i=0;
for(stim=-60;stim<60;stim+=10){
DATA="ICa_double.dat"; ICa=$DATA:[i];
DATA="Ca_double.dat"; Ca=$DATA:[i];
DATA="ICa_double_stim.dat"; Input=$DATA:[i];

## Input
size(80,60);
origin(20,100);
scale("N","F","N","F",@@@NUMBER:0@@@,@@@NUMBER:10@@@,@@@NUMBER:-80@@@,@@@NUMBER:60@@@);
graph(Input,t,0,0,10,1,3.5);

## ICa
size(80,60);
origin(20,20);
scale("N","F","N","F",@@@NUMBER:0@@@,@@@NUMBER:10@@@,@@@NUMBER:-80@@@,@@@NUMBER:10@@@);
graph(ICa,t,0,0,10,1,3.5);

## Ca
size(80,60);
origin(120,20);
scale("N","F","N","F",@@@NUMBER:0@@@,@@@NUMBER:10@@@,@@@NUMBER:0@@@,@@@NUMBER:1@@@);
graph(Ca,t,0,0,10,1,3.5);

tmpQ:[i]=integ(cut(ICa,150,330));
tmpQ2:[i]=integ(cut(ICa,430,660));

tmpV:[i]=stim;
tmpI:[i]=ICa:[120];
tmpI2:[i]=ICa:[450];
i++;
}

## Input
size(80,60);
origin(20,100);
scale("N","F","N","F",@@@NUMBER:0@@@,@@@NUMBER:10@@@,@@@NUMBER:-80@@@,@@@NUMBER:60@@@);
title(1,"time [s]","command voltage [mV]");
axis(1,1,"XY","XY",5,0,3,0,0,0);
frame();
#origin(17,165);
#label(I,0,0,5,0,"C");

## ICa
size(80,60);
origin(20,20);
scale("N","F","N","F",@@@NUMBER:0@@@,@@@NUMBER:10@@@,@@@NUMBER:-80@@@,@@@NUMBER:10@@@);
title(1,"time [s]","calcium current [pA]");
axis(1,1,"XY","XY",5,0,3,0,0,0);
frame();
#origin(17,85);
#label(I,0,0,5,0,"A");

## Ca
size(80,60);
origin(120,20);
scale("N","F","N","F",@@@NUMBER:0@@@,@@@NUMBER:10@@@,@@@NUMBER:0@@@,@@@NUMBER:1@@@);
title(1,"time [s]","calcium concentration [uM]");
axis(1,1,"XY","XY",5,0,1,0,0,0);
frame();
#origin(117,85);
#label(I,0,0,5,0,"B");


size(80,60);
origin(120,100);
scale("N","F","N","F",@@@NUMBER:-70@@@,@@@NUMBER:70@@@,@@@NUMBER:-80@@@,@@@NUMBER:10@@@);
lwidth(1,1);
draw("X",0);
draw("Y",0);
lwidth(2,3);
color("white","white");
graph(tmpI,tmpV,0,2,0,7,3.0);
color("red","white");
graph(tmpI2,tmpV,0,2,0,7,3.0);
title(1,"voltage [mV]","current response [pA]");
axis(1,1,"XY","XY",5,0,3,0,0,0);
frame();
#origin(117,165);
#label(I,0,0,5,0,"D");

origin(20,180);
scale("N","F","N","F",0,1,0,1);
#graph(tmpI2/min(tmpI2),tmpI/min(tmpI),0,2,0,7,3.0);
graph(tmpQ2/min(tmpQ2),tmpQ/min(tmpQ),0,2,0,7,3.0);
title(1,"response to test pulse","response to pulse");
axis(1,1,"XY","XY",5,0,0,0,0,0);
frame();

