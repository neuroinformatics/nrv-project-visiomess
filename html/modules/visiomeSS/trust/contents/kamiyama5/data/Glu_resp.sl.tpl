/* $VisiomeSS-Revision: 1.3 $ $VisiomeSS-Date: 2003/10/24 07:21:08 $
   File:
     Glu_resp.sl
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

wopen(1,"A4",0, 2);
lwidth(2,3);
font(7);
color("white","white");

series Glus;
series Cas;
series Vs;

stims=(@@@NUMBER:1@@@, @@@NUMBER:3@@@, @@@NUMBER:10@@@, @@@NUMBER:30@@@, @@@NUMBER:100@@@, @@@NUMBER:300@@@, @@@NUMBER:1000@@@); /*uM*/

v=$"control_V.dat";
Ca=$"control_Ca.dat";

tmp=index(v);
t=(0~tmp:[1])*0.1

size(80,60);
origin(20,170);
frame();
scale("N","F","N","F",@@@NUMBER:-10@@@,@@@NUMBER:200@@@,@@@NUMBER:-80@@@,@@@NUMBER:0@@@);
for(i=0;i<index(stims);i++){
graph(v:[i],t,0,10,2,0,0);
}
title(1," ", "voltage (mV)");
axis(1,1,"XY","Y",5,0,3,100,20,0)

origin(20,100);
frame();
scale("N","F","N","F",@@@NUMBER:-10@@@,@@@NUMBER:200@@@,@@@NUMBER:-0.1@@@,@@@NUMBER:2@@@);
for(i=0;i<index(stims);i++){
graph(Ca:[i],t,0,10,2,0,0);
}
title(1,"time (sec)", "[Ca] (uM)");
axis(1,1,"XY","XY",5,0,1,100,0,0)

origin(110,170);
frame();
scale("N","F","N","F",@@@NUMBER:0.0008e3@@@,@@@NUMBER:1.5e3@@@,@@@NUMBER:-80@@@,@@@NUMBER:0@@@);
graph(v[900],stims,1,2,0,7,3.5);
title(1," ", " ");
axis(1,1,"XY","",5,0,0,0,20,0)

origin(110,100);
frame();
scale("N","F","N","F",@@@NUMBER:0.0008e3@@@,@@@NUMBER:1.5e3@@@,@@@NUMBER:-0.1@@@,@@@NUMBER:2.0@@@);
graph(Ca[900],stims,1,2,0,7,3.5);
title(1,"Glu (uM)", " ");
axis(1,1,"XY","X",5,0,0,0,0,0)

origin(5,160);
label("I",0,0,6,0,"B");
origin(5,230);
label("I",0,0,6,0,"A");

Ca_SB0=$"withoutSB_Ca.dat";

origin(20,20);
frame();
scale("N","F","N","F",@@@NUMBER:-10@@@,@@@NUMBER:200@@@,@@@NUMBER:-0.1@@@,@@@NUMBER:2@@@);
for(i=0;i<index(stims);i++){
graph(Ca_SB0:[i],t,0,10,2,0,0);
}
title(1,"time (sec)", "[Ca] (uM)");
axis(1,1,"XY","XY",5,0,1,100,0,0)

origin(110,20);
frame();
scale("N","F","N","F",@@@NUMBER:0.0008e3@@@,@@@NUMBER:1.5e3@@@,@@@NUMBER:-0.1@@@,@@@NUMBER:2.0@@@);
graph(Ca_SB0[900],stims,1,2,0,7,3.5);
title(1,"Glu (uM)", " ");
axis(1,1,"XY","X",5,0,0,0,0,0)

origin(5,80);
label("I",0,0,6,0,"C");
