#
# Plot graph by SATELLITE
#               H.Ikeno 2003/08/26
#

proc plotData ( c1, c2, sym ) {
  external x;
  series y[2], xip, yip;
  num_data = index( x[c1] );

  if ( c1 == 10 ) {
    y[0] = cut( x[c1], 2, num_data-6 );
    y[1] = cut( x[c2], 2, num_data-6 );
  } else if ( c1 == 12 ) {
    y[0] = cut( x[c1], 2, num_data-7 );
    y[1] = cut( x[c2], 2, num_data-7 );
  } else {
    y[0] = cut( x[c1], 0, num_data-2 );
    y[1] = cut( x[c2], 0, num_data-2 );
  }
  yip = spline( y[0], y[1], 50, xip );
  graph(y[1], y[0], 0, 1, 0, sym, 3.5);
  graph(yip, xip, 0, 0, 0, sym, 3.5);
}

# set parameter

string s;
param = text2buffer( "param1.mdl" );
s = "xmin = " + cut( param:[1], 2, 2 );
eval( s );
s = "xmax = " + cut( param:[2], 2, 2 );
eval( s );
s = "ymin = " + cut( param:[3], 2, 2 );
eval( s );
s = "ymax = " + cut( param:[4], 2, 2 );
eval( s );

# plot graph base

wopen( 1, "A4", 0, 2 );
size( 150, 150 );
origin( 30, 50 );
#scale( "N", "F", "N", "F", -150, 150, -1.5, 1.5 );
scale( "N", "F", "N", "F", xmin, xmax, ymin, ymax );

title( 1, "voltage (mV)", "current (pA)" );
axis(1,1,"XY","XY",5.5,0,0,0,0,0);
frame();
draw( "X", 0 );
draw( "Y", 0 );
	
# read data (ex_data1.csv)

#series y[2];

x = text2buffer( "ex_data1.csv" );
num_data = index( x[0] );

# 500mM K

#color( "white" );
plotData( 0, 1, 1 );

# 500mM K/Na

color( "green" );
plotData( 2, 3, 4 );

# 100mM K/Na

plotData( 4, 5, 2 );

# 50mM K/Na

plotData( 6, 7, 0 );

# 10mM K/Na

plotData( 8, 9, 7 );

# 500mM K/Li

color( "red" );
plotData( 10, 11, 1 );

# 50mM K/Li

plotData( 12, 13, 16);

