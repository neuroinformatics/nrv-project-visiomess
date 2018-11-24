# Simulation script for hh01.mdl
#            2000/12/4 by H.Ikeno

# compile

nasgn( "hh" );
npp();
nlink( "-O3" );

# simulation

series	INa, IK, IL, mh[2], n, V, Iext;

ninteg( "F" );
ntime( @@@NUMBER:20@@@, @@@NUMBER:0.0005@@@, @@@NUMBER:0.05@@@ );
sam( @@@NUMBER:20000@@@ );

nout( INa, 0, "HH", 0, 3, INa );
nout(  IK, 0, "HH", 0, 3,  IK );
nout(  IL, 0, "HH", 0, 3,  IL );
nout(  mh, 0, "HH", 0, 3,   m );
nout(  mh, 1, "HH", 0, 3,   h );
nout(   n, 0, "HH", 0, 3,   n );

nout( V, 0, "HH", 0, 1 );
nout( Iext, 0, "HH", 0, 2 );
nstim( "HH", 0, "P", @@@NUMBER:1@@@, @@@NUMBER:0@@@, @@@NUMBER:1e-4@@@, @@@NUMBER:20@@@, @@@NUMBER:999@@@ );
ncal();

# graphic

wopen( 1, "A4", 0, 2 );
font( 6 );
lwidth( 3, 2 ); 

# stimuli

origin( 20, 265 );
size( 160, 10 ); 
scale( "N", "F", "N", "F", @@@NUMBER:0@@@, @@@NUMBER:20@@@, @@@NUMBER:0@@@, @@@NUMBER:1e-4@@@ );
graph( Iext, "T", 0, 0, 0, 1, 3, 5);

# voltage response

origin( 20, 180 );
size( 160, 80 ); 
scale( "N", "F", "N", "F", @@@NUMBER:0@@@, @@@NUMBER:20@@@, @@@NUMBER:-80@@@, @@@NUMBER:50@@@ );
graph( V, "T", 0, 0, 0, 1, 3,  5);
title( 1, "Time[msec]", "V[mV]" );
axis( 1, 1, "XY", "XY", 3.5, 0, 0, 0, 0, 0 );

# current response

origin( 20, 100 );
size( 160, 60 ); 
scale( "N", "F", "N", "F", @@@NUMBER:0@@@, @@@NUMBER:20@@@, @@@NUMBER:-1000@@@, @@@NUMBER:1000@@@ );

graph( IL, "T", 0, 0, 0, 1, 3,  5);
color( "cyan" );
graph( INa, "T", 0, 0, 0, 1, 3,  5);
color( "red" );
graph( IK, "T", 0, 0, 0, 1, 3,  5);
title( 1, "Time[msec]", "INa, IK, IL[nA]" );
axis( 1, 1, "XY", "XY", 3.5, 0, 0, 0, 0, 0 );

# m, h, n

origin( 20, 20 );
size( 160, 60 ); 
scale( "N", "F", "N", "F", @@@NUMBER:0@@@, @@@NUMBER:20@@@, @@@NUMBER:0@@@, @@@NUMBER:1@@@ );

color( "red" );
graph( mh[0], "T", 0, 0, 0, 1, 3,  5);
color( "green" );
graph( mh[1], "T", 0, 0, 0, 1, 3,  5);
color( "blue" );
graph( n, "T", 0, 0, 0, 1, 3,  5);
title( 1, "Time[msec]", "m, h, n" );
axis( 1, 1, "XY", "XY", 3.5, 0, 0, 0, 0, 0 );
