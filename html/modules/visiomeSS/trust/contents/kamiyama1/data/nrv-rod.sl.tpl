/* $VisiomeSS-Revision: 1.3 $ $VisiomeSS-Date: 2003/10/24 07:08:54 $
File: 
  nrv-rod.sl 
Title:
  Rod Photoreceptor Model 
Author: 
  Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
Reference Paper: 
  Kamiyama, Y., Ogura, T. and Usui, S. (1996),
  Ionic current model of the vertebrate rod photoreceptor,
  Vision Research, Vol.36, No.24, pp.4059-4068
*/
nassign("nrv-rod");
npp();
nlink("-O2");

series Ca, Cb, Rh, Rhi, T, PDE, cg;
series mCa, Ca_s, Cab_ls, Cab_hs;
series Ca_f, Cab_lf, Cab_hf;
series mKv, mKh, mKc, C1;
series C2, OP1, OP2, OP3;
series Iphoto, Ip2, Jphoto;
series ICa, ICl, IKv, IKc, Ih, Il;
series V;
series stim;

/* stimulus hight */
stim=(@@@NUMBER:0.03@@@, @@@NUMBER:0.1@@@, @@@NUMBER:0.3@@@, @@@NUMBER:1.0@@@, @@@NUMBER:3.0@@@, @@@NUMBER:10.0@@@, @@@NUMBER:30.0@@@);

/* observable & output variables */

nout(Ca,"Rod",0,3,"Ca");
nout(Cb,"Rod",0,3,"Cb");
nout(Rh,"Rod",0,3,"Rh");
nout(Rhi,"Rod",0,3,"Rhi");
nout(T,"Rod",0,3,"T");
nout(PDE,"Rod",0,3,"PDE");
nout(cg,"Rod",0,3,"cg");
nout(mCa,"Rod",0,3,"mCa");
nout(Ca_s,"Rod",0,3,"Ca_s");
nout(Cab_ls,"Rod",0,3,"Cab_ls");
nout(Cab_hs,"Rod",0,3,"Cab_hs");
nout(Ca_f,"Rod",0,3,"Ca_f");
nout(Cab_lf,"Rod",0,3,"Cab_lf");
nout(Cab_hf,"Rod",0,3,"Cab_hf");
nout(mKv,"Rod",0,3,"mKv");
nout(mKh,"Rod",0,3,"mKh");
nout(mKc,"Rod",0,3,"mKc");
nout(C1,"Rod",0,3,"C1");
nout(C2,"Rod",0,3,"C2");
nout(OP1,"Rod",0,3,"OP1");
nout(OP2,"Rod",0,3,"OP2");
nout(OP3,"Rod",0,3,"OP3");
nout(Ip2,"Rod",0,3,"Ip2");
nout(Iphoto,"Rod",0,3,"Iphoto");
nout(Jphoto,"Rod",0,3,"Jphoto");
nout(ICa,"Rod",0,3,"ICa");
nout(ICl,"Rod",0,3,"ICl");
nout(IKv,"Rod",0,3,"IKv");
nout(IKc,"Rod",0,3,"IKc");
nout(Ih,"Rod",0,3,"Ih");
nout(Il,"Rod",0,3,"Il");
nout(V,"Rod",0,1);

ntime(5.0,0.00001,0.01,0.1);
nsclist("O");
ninteg("F");
nsclist("S");
nsclist("T");

wopen(1,"A4",0,2);
ltype(1,1);
lwidth(2,2);
stime=(0~500)*0.01;
tmax=@@@NUMBER:5@@@;
imax=7;
for(i=0; i<=imax; i++) {

  nstim("Rod",0,"P",@@@NUMBER:1.0@@@,@@@NUMBER:0@@@,stim:[i],@@@NUMBER:0.05@@@,@@@NUMBER:999@@@);
  ncal();

/* plot graph */
  size(80,70);
  origin(20,110);
  scale("N","F","N","F",@@@NUMBER:0@@@,tmax,@@@NUMBER:-60@@@,@@@NUMBER:-30@@@);
  graph(V,stime,0,0,0,1,3.5);
  if (i==0) {
    title(1,"time[sec]","V[mV]");
    axis(1,1,"XY","XY",3.5,0,3,1,10,0);
    frame();
  }

  origin(20,190);
  scale("N","D","N","F",@@@NUMBER:-40@@@,@@@NUMBER:10@@@);
  graph(Ip2,stime,0,0,0,1,3.5);
  if (i==0) {
    title(1," ","Iphoto[pA]");
    axis(1,1,"Y","Y",3.5,0,3,2,10,0);
    frame();
  }

  size(80,38)
  origin(120,20);
  scale("N","D","N","F",@@@NUMBER:-4@@@,@@@NUMBER:14@@@);
  graph(Il,stime,0,0,0,1,3.5);
  if (i==0) {
    title(1,"time[sec]","Il[pA]");
    axis(1,1,"XY","XY",3.5,0,3,2,5,0);
    frame();
  }

  origin(120,60);
  scale("N","D","N","F",@@@NUMBER:-1@@@,@@@NUMBER:5@@@);
  graph(IKc,stime,0,0,0,1,3.5);
  if (i==0) {
    title(1," ","IKc[pA]");
    axis(1,1,"Y","Y",3.5,0,3,2,2,0);
    frame();
  }

  origin(120,100);
  scale("N","D","N","F",@@@NUMBER:-4@@@,@@@NUMBER:14@@@);
  graph(ICl,stime,0,0,0,1,3.5);
  if (i==0) {
    title(1," ","ICl(Ca)[pA]");
    axis(1,1,"Y","Y",3.5,0,2,0,5,0);
    frame();
  }

  origin(120,140);
  scale("N","D","N","F",@@@NUMBER:-2@@@,@@@NUMBER:12@@@);
  graph(IKv,stime,0,0,0,1,3.5);
  if (i==0) {
    title(1," ","IKv[pA]");
    axis(1,1,"Y","Y",3.5,0,3,2,5,0);
    frame();
  }

  origin(120,180);
  scale("N","D","N","F",@@@NUMBER:-18@@@,@@@NUMBER:4@@@);
  graph(Ih,stime,0,0,0,1,3.5);
  if (i==0) {
    title(1," ","Ih[pA]");
    axis(1,1,"Y","Y",3.5,0,3,2,5,0);
    frame();
  }

  origin(120,220);
  scale("N","D","N","F",@@@NUMBER:-12@@@,@@@NUMBER:2@@@);
  graph(ICa,stime,0,0,0,1,3.5);
  if (i==0) {
    title(1," ","ICa[pA]");
    axis(1,1,"Y","Y",3.5,0,3,2,5,0);
    frame();
  }

}
