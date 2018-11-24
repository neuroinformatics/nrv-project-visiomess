/*****************************************************************************

Bee Vision  - Simulation Program of Compound Eye Vision -

 ----------------------------------------------------------------------------

出力関連の関数

********************************************** (c) Hidetoshi Ikeno **********/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "dislin.h"

#include "beeVision.h"

extern compound_eye rightEye[NUM_CE], leftEye[NUM_CE];
extern VPL1cell     rightVPL1[NUM_VPL1], leftVPL1[NUM_VPL1];
extern VPL2cell     rightVPL2[NUM_VPL2], leftVPL2[NUM_VPL2];

extern parameters   beeParam;

// 複眼に投影された画像情報を印刷

void printEye( int numOM ) {
  int    k;

  for ( k = 0; k < numOM; k++ ) {
    printf( "%lf, %lf, %lf\n", rightEye[k].x, rightEye[k].y, rightEye[k].br );
  }

}

// 複眼に投影された画像情報をプロット

//#define COLOR_FACT   0.0001               // カラー表示の係数
#define COLOR_FACT   100.               // カラー表示の係数
#define COLOR_OFF    125                // 0の時のカラー値

void plotLeftEyeXZ( char *disDevP, int numOM ) {
  int    k, color;
  float  x[NUM_CE], y[NUM_CE], z[NUM_CE];

  metafl( disDevP );
  if ( strcmp(disDevP, "xwin") ) { setfil( "./TIFF/leftEyeXZ.tif" ); }
  scrmod( "REVERS" );
  disini();

  axstyp( "cross" );
//  setvlt("grey"); 
  ax3len( 1500, 1500, 1500 );
  graf3( -2., 2., -2., 0.5, -2., 2., -2., 0.5, -1., 1., -1., 0.2 );

  for ( k = 0; k < numOM; k++ ) {
    x[k] = -leftEye[k].x;
    y[k] = leftEye[k].z;
    z[k] = leftEye[k].br;
  }

  curve3( x, y, z, numOM );

  // プロットした点を大きくする。

  for ( k = 0; k < numOM; k++ ) {
    color = ((int)(z[k]*COLOR_FACT)+COLOR_OFF);
//    if ( color > 255 ) color = 255;
//    if ( color < 0 ) color = 0;
    rlsec( x[k], y[k], 0., 0.02, 0., 360., color );
  }

  disfin();

}

void plotRightEyeXZ( char *disDevP, int numOM ) {
  int    k, color;
  float  x[NUM_CE], y[NUM_CE], z[NUM_CE];

  metafl( disDevP );
  if ( strcmp(disDevP, "xwin") ) { setfil( "./TIFF/rightEyeXZ.tif" ); }
  scrmod( "REVERS" );
  disini();

  axstyp( "cross" );
//  setvlt("grey"); 
  ax3len( 1500, 1500, 1500 );
  graf3( -2.,2., -2., 0.5, -2., 2., -2., 0.5, -1., 1., -1., 0.2 );

  for ( k = 0; k < numOM; k++ ) {
    x[k] = rightEye[k].x;
    y[k] = rightEye[k].z;
    z[k] = rightEye[k].br;
  }

  curve3( x, y, z, numOM );

  // プロットした点を大きくする。

  for ( k = 0; k < numOM; k++ ) {
    color = ((int)(z[k]*COLOR_FACT)+COLOR_OFF);
//    if ( color > 255 ) color = 255;
//    if ( color < 0 ) color = 0;
    rlsec( x[k], y[k], 0., 0.02, 0., 360., color );
  }

  disfin();

}

void plotBothEyeYZ( char *disDevP, int numOM ) {
  int    k, color;
  float  xR[NUM_CE], yR[NUM_CE], zR[NUM_CE];
  float  xL[NUM_CE], yL[NUM_CE], zL[NUM_CE];

  metafl( disDevP );
  if ( strcmp(disDevP, "xwin") ) { setfil( "./TIFF/bothEyeYZ.tif" ); }
  scrmod( "REVERS" );
  disini();

//  setvlt("grey"); 
  axstyp( "cross" );
  ax3len( 1500, 1500, 1500 );
  graf3( -2.5, 2.5, -2.5, 0.5, -2.5, 2.5, -2.5, 0.5, -1., 1., -1., 0.2 );

  // 左目

  for ( k = 0; k < numOM; k++ ) {
    xL[k] = leftEye[k].y;
    yL[k] = leftEye[k].z;
    zL[k] = leftEye[k].br;
  }

  // 右目

  for ( k = 0; k < numOM; k++ ) {
    xR[k] = rightEye[k].y;
    yR[k] = rightEye[k].z;
    zR[k] = rightEye[k].br;
  }

  curve3( xR, yR, zR, numOM );
  curve3( xL, yL, zL, numOM );

  // プロットした点を大きくする。

  // 左目

  for ( k = 0; k < numOM; k++ ) {
    color = ((int)(zL[k]*COLOR_FACT)+COLOR_OFF);
//    if ( color > 255 ) color = 255;
//    if ( color < 0 ) color = 0;
    rlsec( xL[k], yL[k], 0., 0.02, 0., 360., color );
  }

  // 右目

  for ( k = 0; k < numOM; k++ ) {
    color = ((int)(zR[k]*COLOR_FACT)+COLOR_OFF);
//    if ( color > 255 ) color = 255;
//    if ( color < 0 ) color = 0;
    rlsec( xR[k], yR[k], 0., 0.02, 0., 360., color );
  }

  disfin();

}

void plotBothEyeXY( char *disDevP, int numOM ) {
  int    k, color;
  float  xR[NUM_CE], yR[NUM_CE], zR[NUM_CE];
  float  xL[NUM_CE], yL[NUM_CE], zL[NUM_CE];

  metafl( disDevP );
  if ( strcmp(disDevP, "xwin") ) { setfil( "./TIFF/bothEyeXY.tif" ); }
  scrmod( "REVERS" );
  disini();

  axstyp( "cross" );
//  setvlt("grey"); 
  graf3( -2.5, 2.5, -2.5, 0.5, -2.5, 2.5, -2.5, 0.5, -1., 1., -1., 0.2 );

  // 左目

  for ( k = 0; k < numOM; k++ ) {
    xL[k] = leftEye[k].y;
    yL[k] = -leftEye[k].x;
    zL[k] = leftEye[k].br;
  }

  // 右目

  for ( k = 0; k < numOM; k++ ) {
    xR[k] = rightEye[k].y;
    yR[k] = -rightEye[k].x;
    zR[k] = rightEye[k].br;
  }

  curve3( xR, yR, zR, numOM );

  curve3( xL, yL, zL, numOM );

  // プロットした点を大きくする。

  // 左目

  for ( k = 0; k < numOM; k++ ) {
    color = ((int)(zL[k]*COLOR_FACT)+COLOR_OFF);
//    if ( color > 255 ) color = 255;
//    if ( color < 0 ) color = 0;
    rlsec( xL[k], yL[k], 0., 0.02, 0., 360., color );
  }

  // 右目

  for ( k = 0; k < numOM; k++ ) {
    color = ((int)(zR[k]*COLOR_FACT)+COLOR_OFF);
//    if ( color > 255 ) color = 255;
//    if ( color < 0 ) color = 0;
    rlsec( xR[k], yR[k], 0., 0.02, 0., 360., color );
  }


  disfin();

}

void plotBothEyeXZ( char *disDevP, int numOM ) {
  int    k, color;
  float  xR[NUM_CE], yR[NUM_CE], zR[NUM_CE];
  float  xL[NUM_CE], yL[NUM_CE], zL[NUM_CE];

  metafl( disDevP );
  if ( strcmp(disDevP, "xwin") ) { setfil( "./TIFF/bothEyeXZ.tif" ); }
  scrmod( "REVERS" );
  disini();

  setvlt("RAIN"); 
  graf3( -2.,2., -2., 0.5, -2., 2., -2., 0.5, -1., 1., -1., 0.2 );

  // 左側

  for ( k = 0; k < numOM; k++ ) {
    xL[k] = -leftEye[k].x + 1.;
    yL[k] = leftEye[k].z;
    zL[k] = leftEye[k].br;
  }

  // 右側

  for ( k = 0; k < numOM; k++ ) {
    xR[k] = rightEye[k].x - 1.;
    yR[k] = rightEye[k].z;
    zR[k] = rightEye[k].br;
  }

  curve3( xR, yR, zR, numOM );
  curve3( xL, yL, zL, numOM );

  // プロットした点を大きくする。

  // 左側

  for ( k = 0; k < numOM; k++ ) {
    color = ((int)(zL[k]*COLOR_FACT)+COLOR_OFF);
    if ( color > 255 ) color = 255;
    if ( color < 0 ) color = 0;
    rlsec( xL[k], yL[k], 0., 0.02, 0., 360., color );
  }

  // 右側

  for ( k = 0; k < numOM; k++ ) {
    color = ((int)(zR[k]*COLOR_FACT)+COLOR_OFF);
    if ( color > 255 ) color = 255;
    if ( color < 0 ) color = 0;
    rlsec( xR[k], yR[k], 0., 0.02, 0., 360., color );
  }

  disfin();
}

// 白黒で描画する

void greyPlotBothEyeXZ( char *disDevP, int numOM ) {
  int    k, color;
  float  xR[NUM_CE], yR[NUM_CE], zR[NUM_CE];
  float  xL[NUM_CE], yL[NUM_CE], zL[NUM_CE];

  metafl( disDevP );
  if ( strcmp(disDevP, "xwin") ) { setfil( "./TIFF/greyBothEyeXZ.tif" ); }
  scrmod( "REVERS" );
  disini();

  setvlt("GREY"); 
  graf3( -2.,2., -2., 0.5, -2., 2., -2., 0.5, -1., 1., -1., 0.2 );

  // 左側

  for ( k = 0; k < numOM; k++ ) {
    xL[k] = -leftEye[k].x + 1.;
    yL[k] = leftEye[k].z;
    zL[k] = leftEye[k].br;
  }

  // 右側

  for ( k = 0; k < numOM; k++ ) {
    xR[k] = rightEye[k].x - 1.;
    yR[k] = rightEye[k].z;
    zR[k] = rightEye[k].br;
  }

  curve3( xR, yR, zR, numOM );
  curve3( xL, yL, zL, numOM );

  // プロットした点を大きくする。

  // 左側

  for ( k = 0; k < numOM; k++ ) {
    color = ((int)(zL[k]*COLOR_FACT)+COLOR_OFF);
    if ( color > 255 ) color = 255;
    if ( color < 0 ) color = 0;
    rlsec( xL[k], yL[k], 0., 0.02, 0., 360., color );
  }

  // 右側

  for ( k = 0; k < numOM; k++ ) {
    color = ((int)(zR[k]*COLOR_FACT)+COLOR_OFF);
    if ( color > 255 ) color = 255;
    if ( color < 0 ) color = 0;
    rlsec( xR[k], yR[k], 0., 0.02, 0., 360., color );
  }

  disfin();
}

void greyPlotLeftEyeXZ( char *disDevP, int numOM ) {
  int    k, color;
  float  x[NUM_CE], y[NUM_CE], z[NUM_CE];

  metafl( disDevP );
  if ( strcmp(disDevP, "xwin") ) { setfil( "./TIFF/greyLeftEyeXZ.tif" ); }
  scrmod( "REVERS" );
  disini();

  axstyp( "cross" );
  setvlt("grey"); 
  ax3len( 1500, 1500, 1500 );
  graf3( -2., 2., -2., 0.5, -2., 2., -2., 0.5, -1., 1., -1., 0.2 );

  for ( k = 0; k < numOM; k++ ) {
    x[k] = -leftEye[k].x;
    y[k] = leftEye[k].z;
    z[k] = leftEye[k].br;
  }

  curve3( x, y, z, numOM );

  // プロットした点を大きくする。

  for ( k = 0; k < numOM; k++ ) {
    color = ((int)(z[k]*COLOR_FACT)+COLOR_OFF);
//    if ( color > 255 ) color = 255;
//    if ( color < 0 ) color = 0;
    rlsec( x[k], y[k], 0., 0.02, 0., 360., color );
  }

  disfin();

}

void greyPlotRightEyeXZ( char *disDevP, int numOM ) {
  int    k, color;
  float  x[NUM_CE], y[NUM_CE], z[NUM_CE];

  metafl( disDevP );
  if ( strcmp(disDevP, "xwin") ) { setfil( "./TIFF/greyRightEyeXZ.tif" ); }
  scrmod( "REVERS" );
  disini();

  axstyp( "cross" );
  setvlt("grey"); 
  ax3len( 1500, 1500, 1500 );
  graf3( -2.,2., -2., 0.5, -2., 2., -2., 0.5, -1., 1., -1., 0.2 );

  for ( k = 0; k < numOM; k++ ) {
    x[k] = rightEye[k].x;
    y[k] = rightEye[k].z;
    z[k] = rightEye[k].br;
  }

  curve3( x, y, z, numOM );

  // プロットした点を大きくする。
 
  for ( k = 0; k < numOM; k++ ) {
    color = ((int)(z[k]*COLOR_FACT)+COLOR_OFF);
//    if ( color > 255 ) color = 255;
//    if ( color < 0 ) color = 0;
    rlsec( x[k], y[k], 0., 0.02, 0., 360., color );
  }

  disfin();

}


/*

    VPL1

 */

#define VPL1_COLOR_FACT   100.       // カラー変更係数
#define VPL1_COLOR_OFF    125        // 0の時のカラー値

void plotBothVPL1( char *disDevP ) {
  int    k, color;
  float  xR[NUM_VPL1], yR[NUM_VPL1], zR[NUM_VPL1];
  float  xL[NUM_VPL1], yL[NUM_VPL1], zL[NUM_VPL1];

  metafl( disDevP );
  if ( strcmp(disDevP, "xwin") ) { setfil( "./TIFF/bothVPL1.tif" ); }
  scrmod( "REVERS" );
  disini();

  setvlt("RAIN"); 
  graf3( -2.,2., -2., 0.5, -2., 2., -2., 0.5, -1., 1., -1., 0.2 );

  // 左側

  for ( k = 0; k < beeParam.numOfVPL1; k++ ) {
    xL[k] = -leftVPL1[k].x + 1.;
    yL[k] = leftVPL1[k].z;
    zL[k] = leftVPL1[k].resp;
  }

  // 右側

  for ( k = 0; k < beeParam.numOfVPL1; k++ ) {
    xR[k] = rightVPL1[k].x - 1.;
    yR[k] = rightVPL1[k].z;
    zR[k] = rightVPL1[k].resp;
  }

  curve3( xR, yR, zR, beeParam.numOfVPL1 );
  curve3( xL, yL, zL, beeParam.numOfVPL1 );

  // プロットした点を大きくする。

  // 左側

  for ( k = 0; k < beeParam.numOfVPL1; k++ ) {
    color = ((int)(zL[k]*VPL1_COLOR_FACT)+VPL1_COLOR_OFF);
    if ( color > 255 ) color = 255;
    if ( color < 0 ) color = 0;
    rlsec( xL[k], yL[k], 0., 0.02, 0., 360., color );
  }

  // 右側

  for ( k = 0; k < beeParam.numOfVPL1; k++ ) {
    color = ((int)(zR[k]*VPL1_COLOR_FACT)+VPL1_COLOR_OFF);
    if ( color > 255 ) color = 255;
    if ( color < 0 ) color = 0;
    rlsec( xR[k], yR[k], 0., 0.02, 0., 360., color );
  }

  disfin();
}

#define VPL2_COLOR_FACT   10.       // カラー変更係数
#define VPL2_COLOR_OFF    125        // 0の時のカラー値

void plotBothVPL2( char *disDevP, int rfType ) {
  int    k, color, countR, countL;
  float  xR[NUM_VPL2], yR[NUM_VPL2], zR[NUM_VPL2];
  float  xL[NUM_VPL2], yL[NUM_VPL2], zL[NUM_VPL2];

  metafl( disDevP );
  if ( strcmp(disDevP, "xwin") ) { 
    switch ( rfType ) {
      case 0: { setfil( "./TIFF/bothVPL2.0.tif" ); break; }
      case 1: { setfil( "./TIFF/bothVPL2.1.tif" ); break; }
      case 2: { setfil( "./TIFF/bothVPL2.2.tif" ); break; }
      case 3: { setfil( "./TIFF/bothVPL2.3.tif" ); break; }
      case 4: { setfil( "./TIFF/bothVPL2.4.tif" ); break; }
    }
  }
  scrmod( "REVERS" );
  disini();
  setvlt("RAIN"); 
  graf3( -2.,2., -2., 0.5, -2., 2., -2., 0.5, -1., 1., -1., 0.2 );

  // 左側

  countL = 0;
  for ( k = 0; k < beeParam.numOfVPL2; k++ ) {
    xL[countL] = -leftVPL2[k].x + 1.;
    yL[countL] = leftVPL2[k].z;
    if ( rfType == leftVPL2[k].RFtype ) { 
      zL[countL] = leftVPL2[k].resp;
      countL++;
    }
  }

  // 右側

  countR = 0;
  for ( k = 0; k < beeParam.numOfVPL2; k++ ) {
    xR[countR] = rightVPL2[k].x - 1.;
    yR[countR] = rightVPL2[k].z;
    if ( rfType == rightVPL2[k].RFtype ) { 
      zR[countR] = rightVPL2[k].resp; 
      countR++;
    }
  }

  curve3( xL, yL, zL, countL );
  curve3( xR, yR, zR, countR );

  // プロットした点を大きくする。

  // 左側

  for ( k = 0; k < countL; k++ ) {
    color = ((int)(zL[k]*VPL2_COLOR_FACT)+VPL2_COLOR_OFF);
    if ( color >= 255 ) color = 255;
    if ( color <= 0 ) color = 0;
    rlsec( xL[k], yL[k], 0., 0.02, 0., 360., color );
  }

  // 右側

  for ( k = 0; k < countR; k++ ) {
    color = ((int)(zR[k]*VPL2_COLOR_FACT)+VPL2_COLOR_OFF);
    if ( color >= 255 ) color = 255;
    if ( color <= 0 ) color = 0;
    rlsec( xR[k], yR[k], 0., 0.02, 0., 360., color );
  }

  disfin();
}

/*****************************************************************************

  ファイル入出力

*****************************************************************************/

// 座標情報をファイルに出力する

void outToFileXYZ( char *outDir ) {
  int   k;
  FILE  *fp;
  char  outFile[256];
  char  format[256];

  strcpy( outFile, outDir );
  strcat( outFile, "/xyzEye.asc" );
  fp = fopen( outFile, "w" );

  for( k = 0; k < beeParam.numOfOM; k++ ) {
    fprintf( fp, "%d, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n", 
	   k, leftEye[k].x, leftEye[k].y, leftEye[k].z,
 	      leftEye[k].alpha, leftEye[k].beta,
              rightEye[k].x, rightEye[k].y, rightEye[k].z,
 	      rightEye[k].alpha, rightEye[k].beta );
  }

  fclose( fp );

  // 画像情報処理層VPL1

  strcpy( outFile, outDir );
  strcat( outFile, "/xyzVPL1.asc" );
  fp = fopen( outFile, "w" );

  strcpy( format, 
	  "%d, %lf, %lf, %lf, %d, %d, %lf, %lf, %lf, %d, %d,\n" );
  fp = fopen( outFile, "w" );
  for( k = 0; k < beeParam.numOfVPL1; k++ ) {
    fprintf( fp, format,
	   k, leftVPL1[k].x, leftVPL1[k].y, leftVPL1[k].z,
	      leftVPL1[k].respMode, leftVPL1[k].conNumOfOM, 
 	      rightVPL1[k].x, rightVPL1[k].y, rightVPL1[k].z, 
	      rightVPL1[k].respMode, rightVPL1[k].conNumOfOM );
  }
  fclose( fp );

  // 画像情報処理層VPL2

  strcpy( outFile, outDir );
  strcat( outFile, "/xyzVPL2.asc" );
  fp = fopen( outFile, "w" );

  strcpy( format, 
	  "%d, %lf, %lf, %lf, %d, %d, %lf, %lf, %lf, %d, %d\n" );
  fp = fopen( outFile, "w" );
  for( k = 0; k < beeParam.numOfVPL2; k++ ) {
    fprintf( fp, format,
	   k, leftVPL2[k].x, leftVPL2[k].y, leftVPL2[k].z,
	      leftVPL2[k].respMode, leftVPL2[k].RFtype, 
 	      rightVPL2[k].x, rightVPL2[k].y, rightVPL2[k].z, 
	      rightVPL2[k].respMode, rightVPL2[k].RFtype );
  }
  fclose( fp );

}

// 結果をファイルに出力

void outToFile( char *outDir ) {
  int   k;
  FILE  *fp;
  char  outFile[256];

  strcpy( outFile, outDir );
  strcat( outFile, "/Eye.asc" );
  fp = fopen( outFile, "w" );

  for( k = 0; k < beeParam.numOfOM; k++ ) {
    fprintf( fp, "%d, %lf, %lf\n", k, leftEye[k].br, rightEye[k].br );
  }

  fclose( fp );

  // 

  strcpy( outFile, outDir );
  strcat( outFile, "/VPL1.asc" );
  fp = fopen( outFile, "w" );

  for( k = 0; k < beeParam.numOfVPL1; k++ ) {
    fprintf( fp, "%d, %lf, %lf\n", k, leftVPL1[k].resp, rightVPL1[k].resp );
  }

  fclose( fp );

  // 

  strcpy( outFile, outDir );
  strcat( outFile, "/VPL2.asc" );
  fp = fopen( outFile, "w" );

  for( k = 0; k < beeParam.numOfVPL2; k++ ) {
    fprintf( fp, "%d, %lf, %d, %lf, %d\n", k, 
                 leftVPL2[k].resp, leftVPL2[k].RFtype,
                 rightVPL2[k].resp, rightVPL2[k].RFtype );
  }

  fclose( fp );

}

// 結果をファイルから読み込み

int inFromFile( char *dataFile ) {
  int     k;
  double  xR, yR, zR, brR;
  double  xL, yL, zL, brL;
  char    line[256];
  FILE    *fp;

  fp = fopen( dataFile, "r" );

  fgets( line, 256, fp );
  while ( 1 ) {
    fgets( line, 256, fp );
    if ( !strcmp(line, "</ommatidium>\n") ) break;
    sscanf( line, "%d, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n", 
	    &k, &xL, &yL, &zL, &brL, &xR, &yR, &zR, &brR );

    leftEye[k].x = xL;
    leftEye[k].y = yL;
    leftEye[k].z = zL;
    leftEye[k].br = brL;

    rightEye[k].x = xR;
    rightEye[k].y = yR;
    rightEye[k].z = zR;
    rightEye[k].br = brR;

  }
  fclose(fp);  

  return k;
}

