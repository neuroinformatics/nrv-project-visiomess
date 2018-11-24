# by Y.Kamiyama
proc drawgraph(xoff,ax,t,gNa,gCa,gK,gKA) {
# gNa
origin(xoff,200);
scale("N","F","N","F",0,40,-0.01,0.12,1);
graph(gNa,t,0,0,1,3.5);
if ( ax==1) {
axis(1,1,"Y","Y",4,0,1,10,0.05,0);
}
label("I",49,35,5,0,"gNa",1);
frame();
# gCa
origin(xoff,150);
scale("N","F","N","F",0,40,-0.01,0.12,1);
graph(gCa,t,0,0,1,3.5);
if ( ax==1) {
axis(1,1,"Y","Y",4,0,1,10,0.05,0);
}
label("I",49,35,5,0,"gCa",1);
frame();
# gK
origin(xoff,100);
scale("N","F","N","F",0,40,-0.01,0.12,1);
graph(gK,t,0,0,1,3.5);
if ( ax==1) {
axis(1,1,"Y","Y",4,0,1,10,0.05,0);
}
label("I",49,35,5,0,"gK",1);
frame();
# gKA
origin(xoff,50);
scale("N","F","N","F",0,40,-0.01,0.12,1);
graph(gKA,t,0,0,1,3.5);
if ( ax==1) {
axis(1,1,"XY","XY",4,0,1,10,0.05,0);
}
if ( ax==0) {
axis(1,1,"X","X",4,0,1,10,0.05,0);
}
label("I",49,35,5,0,"gA",1);
frame();
}
#
#
#
wopen(1,"A4",0,2);
size(50,40);
#
scalar xoff,ax;
series t,gNa,gCa,gK,gKA;
#  
# unix("./rgc-markov vc01.in vc01.out");
x=text2buffer("vc01.out");
t=cut(x[0],0,length(x[0])-2);
gNa=cut(x[3],0,length(x[0])-2);
gCa=cut(x[4],0,length(x[0])-2);
gK=cut(x[5],0,length(x[0])-2);
gKA=cut(x[6],0,length(x[0])-2);
xoff=20;
ax=1;
drawgraph(xoff,ax,t,gNa,gCa,gK,gKA);
#
#
# unix("./rgc-markov vc02.in vc02.out");
x=text2buffer("vc02.out");
t=cut(x[0],0,length(x[0])-2);
gNa=cut(x[3],0,length(x[0])-2);
gCa=cut(x[4],0,length(x[0])-2);
gK=cut(x[5],0,length(x[0])-2);
gKA=cut(x[6],0,length(x[0])-2);
xoff=75;
ax=0;
drawgraph(xoff,ax,t,gNa,gCa,gK,gKA);
#
#
# unix("./rgc-markov vc03.in vc03.out");
x=text2buffer("vc03.out");
t=cut(x[0],0,length(x[0])-2);
gNa=cut(x[3],0,length(x[0])-2);
gCa=cut(x[4],0,length(x[0])-2);
gK=cut(x[5],0,length(x[0])-2);
gKA=cut(x[6],0,length(x[0])-2);
xoff=130;
ax=0;
drawgraph(xoff,ax,t,gNa,gCa,gK,gKA);
# unix("./rgc-markov vc04.in vc04.out");
# unix("./rgc-markov vc05.in vc05.out");
