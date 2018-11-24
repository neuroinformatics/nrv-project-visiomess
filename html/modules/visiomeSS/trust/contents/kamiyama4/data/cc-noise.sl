# by Y.Kamiyama
#
#
# local procedures
#
proc raster(indat,outdat,th) {
for ( n=0; n<length(indat); n++ ) {
outdat:[n]=0;
if ( indat:[n] > th ){ 
    outdat:[n]=1;
  }
}
for ( n=length(outdat)-1; n>0; n-- ) {
if ( outdat:[n-1]==1 && outdat:[n]==1 ){
  outdat:[n]=0;
}	
}}

proc axisfor34(ltime) {
origin(20,20);
size(80,5);
scale("N","F","N","F",0,ltime,0.8,1.2);
axis(1,1,"X","X",4,0,1,250,0.5,1);
origin(110,20);
axis(1,1,"X","X",4,0,1,250,0.5,1);
#
origin(20,80);
size(80,80)
scale("N","F","N","F",0,ltime,-70,30);
axis(1,1,"Y","Y",4,0,1,100,25,1);
label("I",85,82,4,0,"Stochastic Model",2);
}

proc deterministic(ltime) {
#
series xde,tde,Vde,dde, Vdde; 
#
# unix("./rgc-deterministic det-noise.in det-noise.out");
xde=text2buffer("det-noise.out");
tde=cut(xde[0],1,length(xde[0])-2);
Vde=cut(xde[2],1,length(xde[0])-2);
#
# unix("./rgc-deterministic det-DC.in det-DC.out");
#
dde=text2buffer("det-DC.out");
Vdde=cut(dde[2],1,length(xde[0])-2);
#
origin(20,170);
scale("N","F","N","F",0,ltime,-70,30);
graph(Vdde,tde,0,0,0,1,3.5);
axis(1,1,"Y","Y",4,0,1,100,25,1);
label("I",85,82,4,0,"Deterministic Model",2);
#
origin(110,170);
graph(Vde,tde,0,0,0,1,3.5);
}
#
# main
#
series x,t,V;
series d,Vd;
series Rn,Rd;
series xde,tde,Vde;
series dde,Vdde; 

string dfile,param;

deviation=0.010;

yorg=20;
ltime=1500.0;
cheight=0.010;

wopen(1,"A4",0,2);
for ( i=0; i<2; i++ ) {
for ( j=0; j<10; j++ ) {
#
dfile="cc"+i+j+".out";
#
# Gaussian input
#
param="./rgc-markov noise.in"+" "+dfile
# unix(param);
#
x=text2buffer(dfile);
t=cut(x[0],1,length(x[0])-2);
V=cut(x[2],1,length(x[0])-2);
#
raster(V,Rn,15.0);
#
dfile="dc"+i+j+".out";
#
# DC input
#
param="./rgc-markov dc.in"+" "+dfile;
# unix(param);
#
d=text2buffer(dfile);
Vd=cut(d[2],1,length(x[0])-2);
#
raster(Vd,Rd,15.0);
#
size(80,80);
scale("N","F","N","F",0,ltime,-70,30);
origin(110,80);
graph(V,t,0,0,0,1,3.5);
#
origin(20,80)
graph(Vd,t,0,0,0,1,3.5);
#
# raster plot
#
origin(20,yorg);
size(80,3);
scale("N","F","N","F",0,ltime,0.9,1.1);
graph(Rd,t,0,3,0,1,3,5);
origin(110,yorg);
graph(Rn,t,0,3,0,1,3,5);
yorg=yorg+2.5;
#
# draw axes once
#
if ( dfile=="dc00.out" ) {
#
# draw input current
origin(20,260);
size(80,25);
scale("N","F","N","F",0,ltime,-0.2,3.2);
graph(d[1],t,0,0,0,1,3.5);
axis(1,1,"Y","Y",4,0,1,100,1.0,1);
#
origin(110,260);
graph(x[1],t,0,0,0,1,3.5);
#
origin(20,5);
param="sigma:"+deviation+"  tau_s:2.0  radius:6.25um  C.mean:"+cheight;
label("I",0,0,4,0,param,0);
#
axisfor34(ltime);
#
deterministic(ltime);
} # endif
} # endfor 
} # endfor
