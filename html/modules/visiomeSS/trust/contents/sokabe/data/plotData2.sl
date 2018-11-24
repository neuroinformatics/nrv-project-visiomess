#
# Plot graph by SATELLITE
#               H.Ikeno 2003/08/27
#

# set parameter

string s;
param = text2buffer( "param2.mdl" );
s = "xmin = " + cut( param:[1], 2, 2 );
eval( s );
s = "xmax = " + cut( param:[2], 2, 2 );
eval( s );
s = "ymin = " + cut( param:[3], 2, 2 );
eval( s );
s = "ymax = " + cut( param:[4], 2, 2 );
eval( s );

# set plot data

series time, I[11];

x = text2buffer( "ex_data2.csv" );
time = cut( x[0], 0, 875 );
for ( i = 1; i < 12; i++ ) {
  I[i-1] = cut( x[i], 0, 875 );
}

string lbl[11];

lbl[0]  = "Vm = -104mV";
lbl[1]  = "Vm = -94mV";
lbl[2]  = "Vm = -84mV";
lbl[3]  = "Vm = -77mV";
lbl[4]  = "Vm = -68mV";
lbl[5]  = "Vm = -56mV";
lbl[6]  = "Vm = -43mV";
lbl[7]  = "Vm = +48mV";
lbl[8]  = "Vm = +54mV";
lbl[9]  = "Vm = +61mV";
lbl[10] = "Vm = +68mV";

# plot graph

wopen( 1, "A4", 0, 2 );

size( 150, 18 );
#scale( "N", "F", "N", "F", 0, 1500, -1., 1. );
scale( "N", "F", "N", "F", xmin, xmax, ymin, ymax );
for ( i = 0; i < 11; i++ ) {
  origin( 20, 250-i*22 );
  I[i] = dccut(I[i]);
  graph(I[i],time,0,0,0,1,3.5);
  label( "I", 154, 9, 4.5, 0, lbl[i] ); 
}
title( 1, "time (msec)", "current (pA)" );
axis(1,1,"XY","XY",4.5,0,0,0,1,0);


