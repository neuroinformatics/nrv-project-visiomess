/*****************************************************************************

 Bee Vision  - Simulation Program of Compound Eye Vision -

 ----------------------------------------------------------------------------
 
 初期化関係の関数 

********************************************** (c) Hidetoshi Ikeno **********/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "beeVision.h"

extern compound_eye rightEye[NUM_CE], leftEye[NUM_CE];
extern VPL1cell     rightVPL1[NUM_VPL1], leftVPL1[NUM_VPL1];
extern VPL2cell     rightVPL2[NUM_VPL2], leftVPL2[NUM_VPL2];

extern parameters   beeParam;
extern target figure[N_FIGURE];

/*****************************************************************************

  出力ファイルの消去
 ---------------------------------------------------------------------------
   ./TIFF/bothEyeXY.tif
   ./TIFF/bothEyeYZ.tif
   ./TIFF/leftEyeXZ.tif
   ./TIFF/rightEyeXZ.tif

   ./TIFF/bothVPL1.tif
   ./TIFF/bothVPL2.tif

*****************************************************************************/

void rmFiles() {
  system( "rm ./TIFF/bothEyeXY.tif" );
  system( "rm ./TIFF/bothEyeYZ.tif" );
  system( "rm ./TIFF/leftEyeXZ.tif" );
  system( "rm ./TIFF/rightEyeXZ.tif" );
  system( "rm ./TIFF/bothEyeXZ.tif" );
  system( "rm ./TIFF/greyBothEyeXZ.tif" );
  system( "rm ./TIFF/greyRightEyeXZ.tif" );
  system( "rm ./TIFF/greyLeftEyeXZ.tif" );

  system( "rm ./TIFF/bothVPL1.tif" );
  system( "rm ./TIFF/bothVPL2.*.tif" );
}

/*****************************************************************************

  beeVsion.confの読み込み
 ---------------------------------------------------------------------------
  headR: ミツバチ頭部の半径

  flightAngle: 飛翔角度

  figCenter: 提示図形の中心座標
  figCenter: 図形の提示角度

*****************************************************************************/

void readConfig() {
  char  line[256];
  char  *pline, *keyword, *value;
  FILE  *fp;
  double a;
  int    figNum;

  fp = fopen( "beeVision.conf", "r" );

  while ( 1 ) {
    if ( fgets( line, 256, fp ) == NULL ) break;

    // 先頭が#の場合、途中に=がない行を読み飛ばす
    if ( line[0] == '#' ) continue;
    if ( strstr( line, "=" ) == NULL ) continue;

    // #以降はコメントとする
    if ( !(strstr( line, "#" ) == NULL) ) {
      pline = strtok( line, "#" );
      strcpy( line, pline );
    }

    keyword = strtok( line, "=" );

    // ミツバチの幾何学パラメータ

    if ( !(strstr( keyword, "headR" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.headR );
       printf( "headR: %lf\n", beeParam.headR );
    }

    if ( !(strstr( keyword, "maxVC" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.maxVC );
       printf( "maxVC: %lf\n", beeParam.maxVC );
    }
    if ( !(strstr( keyword, "minVC" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.minVC );
       printf( "minVC: %lf\n", beeParam.minVC );
    }

    if ( !(strstr( keyword, "venPh" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.venPh );
       printf( "venPh: %lf\n", beeParam.venPh );
    }

    if ( !(strstr( keyword, "dorPh" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.dorPh );
       printf( "dorPh: %lf\n", beeParam.dorPh );
    }

    if ( !(strstr( keyword, "stepPh" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.stepPh );
       printf( "stepPh: %lf\n", beeParam.stepPh );
    }

    if ( !(strstr( keyword, "venLimit" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.venLimit );
       printf( "venLimit: %lf\n", beeParam.venLimit );
    }
    if ( !(strstr( keyword, "dorLimit" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.dorLimit );
       printf( "dorLimit: %lf\n", beeParam.dorLimit );
    }

    // 個眼水平方向のパラメータ

    if ( !(strstr( keyword, "frontTh" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.frontTh );
       printf( "frontTh: %lf\n", beeParam.frontTh );
    }
    if ( !(strstr( keyword, "rearTh" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.rearTh );
       printf( "rearTh: %lf\n", beeParam.rearTh );
    }
    beeParam.thW2 = (beeParam.frontTh - beeParam.rearTh)/2.; 
    beeParam.centerTh = beeParam.rearTh + beeParam.thW2;

    if ( !(strstr( keyword, "stepTh" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.stepTh );
       printf( "stepTh: %lf\n", beeParam.stepTh );
    }

// initEye3()で使用する

    if ( !(strstr( keyword, "xPostMax" ) == NULL) ) {
       value = strtok( NULL, "," );
       sscanf( value, "%lf", &beeParam.xPostMax );
       printf( "xPostMax: %lf\n", beeParam.xPostMax );
    }

    if ( !(strstr( keyword, "xAntMax" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.xAntMax );
       printf( "xAntMax: %lf\n", beeParam.xAntMax );
    }

    if ( !(strstr( keyword, "rotAng" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.rotAng );
       printf( "rotMax: %lf\n", beeParam.rotAng );
    }

    if ( !(strstr( keyword, "rotXoff" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.rotXoff );
       printf( "rotXoff: %lf\n", beeParam.rotXoff );
    }

    if ( !(strstr( keyword, "rotYoff" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.rotYoff );
       printf( "rotYoff: %lf\n", beeParam.rotYoff );
    }

    // 個眼の視野角度

    if ( !(strstr( keyword, "omDeg" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.omDeg );
       printf( "omDeg: %lf\n", beeParam.omDeg );
    }

    // 個眼最大視野角

    if ( !(strstr( keyword, "omVenMax" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.omVenMax );
       printf( "omVenMax: %lf\n", beeParam.omVenMax );
    }
    if ( !(strstr( keyword, "omDorMax" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.omDorMax );
       printf( "omDorMax: %lf\n", beeParam.omDorMax );
    }

    if ( !(strstr( keyword, "omFrMax" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.omFrMax );
       printf( "omFrMax: %lf\n", beeParam.omFrMax );
    }
    if ( !(strstr( keyword, "omReMax" ) == NULL) ) {
       value = strtok( NULL, "," ); sscanf( value, "%lf", &beeParam.omReMax );
       printf( "omReMax: %lf\n", beeParam.omReMax );
    }

    // 個眼の受容野を表すガウス関数の係数

    if ( !(strstr( keyword, "omRFcoef" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.omRFcoef );
       printf( "omRFcoef: %lf\n", beeParam.omRFcoef );
    }

    // 個眼の応答を規格化するときの係数

    if ( !(strstr( keyword, "sigCoef" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.sigCoef );
       printf( "sigCoef: %lf\n", beeParam.sigCoef );
    }

    // 飛翔角度

    if ( !(strstr( keyword, "flightAngle" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.flightAngle );
       printf( "flightAngle: %lf\n", beeParam.flightAngle );
    }

    // VPL1: 画像情報処理層細胞数の設定

    if ( !(strstr( keyword, "numOfVPL1" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%d", &beeParam.numOfVPL1 );
       printf( "numOfVPL1: %d\n", beeParam.numOfVPL1 );
    }

    // VPL1: 画像処理層細胞の最小受容野角度

    if ( !(strstr( keyword, "VPL1rf_min" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.VPL1rf_min );
       printf( "VPL1rf_min: %lf\n", beeParam.VPL1rf_min );
    }

    //VPL1: 画像処理層細胞の最大受容野角度

    if ( !(strstr( keyword, "VPL1rf_max" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.VPL1rf_max );
       printf( "VPL1rf_max: %lf\n", beeParam.VPL1rf_max );
    }

    // VPL2: 画像情報処理層細胞数の設定

    if ( !(strstr( keyword, "numOfVPL2" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%d", &beeParam.numOfVPL2 );
       printf( "numOfVPL2: %d\n", beeParam.numOfVPL2 );
    }

    // VPL2: 画像処理層細胞の最小受容野角度

    if ( !(strstr( keyword, "VPL2rf_min" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.VPL2rf_min );
       printf( "VPL2rf_min: %lf\n", beeParam.VPL2rf_min );
    }

    // VPL2: 画像処理層細胞の最大受容野角度

    if ( !(strstr( keyword, "VPL2rf_max" ) == NULL) ) {
       value = strtok( NULL, "," ); 
       sscanf( value, "%lf", &beeParam.VPL2rf_max );
       printf( "VPL2rf_max: %lf\n", beeParam.VPL2rf_max );
    }

    /***************** 図形の読み込み **************************************/ 

    // 図形の中心座標を読み込み

    if ( !(strstr( keyword, "figNumber" ) == NULL) ) {
      value = strtok( NULL, "," ); sscanf( value, "%d", &figNum );
    }

    // 図形の中心座標を読み込み

    if ( !(strstr( keyword, "figCenter" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%lf", &figure[figNum].centerX );
      value = strtok( NULL, "," ); 
              sscanf( value, "%lf", &figure[figNum].centerY );
      value = strtok( NULL, "," ); 
              sscanf( value, "%lf", &figure[figNum].centerZ );
      printf( "figCenter: %lf, %lf, %lf\n",
              figure[figNum].centerX, 
              figure[figNum].centerY, 
              figure[figNum].centerZ );
    }

    // 図形の提示角度を読み込み

    if ( !(strstr( keyword, "figAngle" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%lf", &figure[figNum].angleX );
      value = strtok( NULL, "," ); 
              sscanf( value, "%lf", &figure[figNum].angleY );
      printf( "figAngle: %lf, %lf\n",
              figure[figNum].angleX, figure[figNum].angleY );
    }

    // 図形を形成するドット数を読み込み

    if ( !(strstr( keyword, "figDotX" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%d", &figure[figNum].dotX );
      printf( "figDotX: %d\n", figure[figNum].dotX );
    }
    if ( !(strstr( keyword, "figDotY" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%d", &figure[figNum].dotY );
      printf( "figDotY: %d\n", figure[figNum].dotY );
    }

    // 図形を形成するドットサイズを読み込み

    if ( !(strstr( keyword, "figDotD" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%lf", &figure[figNum].dotDiam );
      printf( "figDotD: %lf\n", figure[figNum].dotDiam );
    }

    // 図形パターン -1: pgm file, 0: +, 1: X, 2: ●

    if ( !(strstr( keyword, "figPattern" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%d", &figure[figNum].pattern );
      printf( "figPatten: %d\n", figure[figNum].pattern );
    }

    // 図形を提示するか、しないか  1: 提示する、0: 提示しない、

    if ( !(strstr( keyword, "figShow" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%d", &figure[figNum].show );
      printf( "figShow: %d\n", figure[figNum].show );
    }

    // 図形のカラー  1, -1をとりあえず使用する

    if ( !(strstr( keyword, "figColor" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%d", &figure[figNum].color );
      printf( "figColor: %d\n", figure[figNum].color );
    }

    // 図形ファイル名

    if ( !(strstr( keyword, "figFile" ) == NULL) ) {
      value = strtok( NULL, "," ); 
              sscanf( value, "%s", &figure[figNum].fileName );
      printf( "figFile: %s\n", figure[figNum].fileName );
    }

  }
  fclose( fp );

  beeParam.numOfFig = figNum+1;  
}

/*****************************************************************************

 複眼の初期化
 ---------------------------------------------------------------------------
 initEye()を使用するときはbeeVision.conf.base.1を用いる

*****************************************************************************/

int initEye() {
  int    i, p_flag;
  double ph, th; 
  double ven_len, dor_len, c_ven, c_dor;
  double front_th, rear_th, x, w;

  ven_len = beeParam.venPh - beeParam.venLimit;      // 腹側狭部の角度
  dor_len = beeParam.dorPh - beeParam.dorLimit;      // 背側狭部の角度
  c_ven = ven_len/((beeParam.thW2)*(beeParam.thW2));
  c_dor = dor_len/((beeParam.thW2)*(beeParam.thW2));

  i = 0;
  p_flag = 0;

  // 腹側(ventral)の複眼を配置

  for ( ph = beeParam.venPh; ph > 0; ph -= beeParam.stepPh ) {
    if ( ph < beeParam.venLimit ) {
      front_th = beeParam.frontTh; rear_th = beeParam.rearTh;
    } else {
      x = beeParam.venPh - ph; 
      w = sqrt( x/c_ven );
      front_th = beeParam.centerTh + w; rear_th = beeParam.centerTh - w; 
    }
    for ( th = rear_th+p_flag*beeParam.stepTh; 
          th < front_th; 
          th += 2.*beeParam.stepTh ) {
      leftEye[i].r  = beeParam.maxVC;
      rightEye[i].r = beeParam.maxVC;

      leftEye[i].th = th * TO_RAD;          // 水平方向角度
      leftEye[i].ph = -ph * TO_RAD;         // 垂直方向角度
      leftEye[i].br = 0.;                      // 明るさ

      rightEye[i].th = th * TO_RAD;         // 水平方向角度
      rightEye[i].ph = -ph * TO_RAD;        // 垂直方向角度
      rightEye[i].br = 0.;                     // 明るさ

      leftEye[i].z = leftEye[i].r * sin( leftEye[i].ph );
      leftEye[i].x = leftEye[i].r * cos( leftEye[i].ph )
                    * sin( leftEye[i].th );
      leftEye[i].y = leftEye[i].r * cos( leftEye[i].ph )
                    * cos( leftEye[i].th );

      rightEye[i].z = rightEye[i].r * sin( rightEye[i].ph );
      rightEye[i].x = rightEye[i].r * cos( rightEye[i].ph )
                    * sin( rightEye[i].th );
      rightEye[i].y = -rightEye[i].r * cos( rightEye[i].ph )
                    * cos( rightEye[i].th );

      leftEye[i].alpha = ( -beeParam.omReMax 
          + (beeParam.omFrMax+beeParam.omReMax)*(th-beeParam.rearTh)
            /(beeParam.frontTh-beeParam.rearTh)
        ) * TO_RAD;
      leftEye[i].beta = -beeParam.omVenMax * ph/beeParam.venPh * TO_RAD;

      if ( leftEye[i].alpha < 0. ) {
	rightEye[i].alpha = -M_PI - leftEye[i].alpha;
      } else {
        rightEye[i].alpha =  M_PI - leftEye[i].alpha;
      }
      rightEye[i].beta = leftEye[i].beta;

      /*
      printf( "om(%d): %lf, %lf, %lf, %lf\n",  
             i, leftEye[i].alpha*TO_DEG,   leftEye[i].beta*TO_DEG,
                rightEye[i].alpha*TO_DEG,  rightEye[i].beta*TO_DEG );
      */

      i++;
    }
    if ( p_flag == 0 ) p_flag = 1; else p_flag = 0;
  }

  // 背側(dorsal)の複眼を配置

  for ( ph = 0; ph < beeParam.dorPh; ph += beeParam.stepPh ) {
    if ( ph < beeParam.dorLimit ) {
      front_th = beeParam.frontTh; rear_th = beeParam.rearTh;
    } else {
      x = beeParam.dorPh - ph; 
      w = sqrt( x/c_dor );
      front_th = beeParam.centerTh + w; rear_th = beeParam.centerTh - w; 
    }
    for ( th = rear_th+p_flag*beeParam.stepTh; 
          th < front_th; 
          th += 2.*beeParam.stepTh ) {
      leftEye[i].r  = beeParam.maxVC;
      rightEye[i].r = beeParam.maxVC;

      leftEye[i].th = th * TO_RAD; 
      leftEye[i].ph = ph * TO_RAD;
      leftEye[i].br = 0.; 

      rightEye[i].th = th * TO_RAD;         // 水平方向角度
      rightEye[i].ph = ph * TO_RAD;         // 垂直方向角度
      rightEye[i].br = 0.;                     // 明るさ

      leftEye[i].z = leftEye[i].r * sin( leftEye[i].ph );
      leftEye[i].x = leftEye[i].r * cos( leftEye[i].ph )
                    * sin( leftEye[i].th );
      leftEye[i].y = leftEye[i].r * cos( leftEye[i].ph )
                    * cos( leftEye[i].th );

      rightEye[i].z = rightEye[i].r * sin( rightEye[i].ph );
      rightEye[i].x = rightEye[i].r * cos( rightEye[i].ph )
                    * sin( rightEye[i].th );
      rightEye[i].y = -rightEye[i].r * cos( rightEye[i].ph )
                    * cos( rightEye[i].th );

      leftEye[i].alpha = ( -beeParam.omReMax 
          + (beeParam.omFrMax+beeParam.omReMax)*(th-beeParam.rearTh)
            /(beeParam.frontTh-beeParam.rearTh)
        ) * TO_RAD;
      leftEye[i].beta = beeParam.omDorMax * ph/beeParam.dorPh * TO_RAD;

      if ( leftEye[i].alpha < 0. ) {
	rightEye[i].alpha = -M_PI - leftEye[i].alpha;
      } else {
        rightEye[i].alpha =  M_PI - leftEye[i].alpha;
      }
      rightEye[i].beta = leftEye[i].beta;

      /*
      printf( "om(%d): %lf, %lf, %lf, %lf\n",  
             i, leftEye[i].alpha*TO_DEG,  leftEye[i].beta*TO_DEG,
                rightEye[i].alpha*TO_DEG, rightEye[i].beta*TO_DEG );
      */

      i++;
    }
    if ( p_flag == 0 ) p_flag = 1; else p_flag = 0;
  }

  beeParam.numOfOM = i;
  printf( "number of compound eyes: %d\n", beeParam.numOfOM );

  return 0;
}

/*****************************************************************************

 複眼の初期化 2
 ---------------------------------------------------------------------------
 initEye2()を使用するときはbeeVision.conf.base.2を用いる

*****************************************************************************/

double calcOmFrMax( double ph ) {
  double y, x;

  x = -ph/10. + 6.;
  y = -0.0004 * pow( x, 6 ) + 0.0161 * pow( x, 5 ) - 0.2359 * pow( x, 4 )
    +  1.8472 * pow( x, 3 ) - 7.5935 * x * x + 12.858 * x + 12.827;
  y = y + 90.;

  return y;
}

// 複眼端の水平方向角度を計算する

double calcFrontTh( double ph ) {
  double y, x;

  if ( ph > 0. ) {
      y = beeParam.frontTh + 45.*(ph/50.)*(ph/50.);
  } else {
      x = ph/5. + 11.;
      y = -0.0006 * pow( x, 4 ) + 0.0172 * pow( x, 3 )
          -0.1779 * x * x + 0.8148 * x - 0.6364;
      y = y/0.9655 * beeParam.frontTh;
  }

  return  y;
}

double calcRearTh( double ph ) {
  double y, x;

  if ( ph > 0. ) {
      y = beeParam.rearTh - 40.*(ph/50.)*(ph/50.);
  } else {
      x = ph/5. + 11.;
      y = -0.0004 * pow( x, 4 ) + 0.0124 * pow( x, 3 )
          -0.1358 * x * x + 0.6974 * x - 0.5688;
      y = y/1.3 * (beeParam.rearTh);
  }

  return y;
}

// 複眼境界のY座標を求める

double compY( double ph ) {
  double x, y;

  x = ph/5. + 10.;
  y = -0.2021 * x * x + 3.5735 * x + 31.53;
  y = y/47.5 * beeParam.headR;

  return y;
}

// 複眼境界のZ座標を求める

double compZ( double ph ) {
  double x, y;

  if ( ph > 0. ) {
      x = ph/5. + 1.;
      y = -0.1629 * x * x + 4.7947 * x - 4.55;
      y = y/47.5 * beeParam.headR;
  } else {
      x = ph/5. + 10.;
      y = -0.0663 * x * x - 3.1617 * x + 38.042;
      y = -y/47.5 * beeParam.headR;
  }

  return y;
}

int initEye2() {
  int    i, p_flag;
  double ph, th; 
  double front_th, rear_th, x, w;
  double omFrMax;

  i = 0;
  p_flag = 0;

  // 腹側(ventral)の複眼を配置

  ph = beeParam.venPh;
  while ( ph > 0. ) {
    front_th = calcFrontTh( -ph );
    rear_th = calcRearTh( -ph );
    omFrMax = calcOmFrMax( -ph );

    th = rear_th + p_flag*beeParam.stepTh;
    while( th < front_th ) { 
      leftEye[i].th = th * TO_RAD;          // 水平方向角度
      leftEye[i].ph = -ph * TO_RAD;         // 垂直方向角度
      leftEye[i].br = 0.;                      // 明るさ

      rightEye[i].th = th * TO_RAD;         // 水平方向角度
      rightEye[i].ph = -ph * TO_RAD;        // 垂直方向角度
      rightEye[i].br = 0.;                     // 明るさ

      leftEye[i].z = compZ( -ph );
      leftEye[i].y = (compY( -ph )-1.0)*cos(th*TO_RAD) + 1.0;
      leftEye[i].x = (compY( -ph )-1.0)*sin( th*TO_RAD ) + 0.5;
      leftEye[i].r = sqrt( leftEye[i].x * leftEye[i].x +
			   leftEye[i].y * leftEye[i].y +  
			   leftEye[i].z * leftEye[i].z );  

      rightEye[i].z = compZ( -ph );
      rightEye[i].y = -(compY( -ph )-1.0)*cos(th*TO_RAD) - 1.0;
      rightEye[i].x = (compY( -ph )-1.0)*sin( th*TO_RAD ) + 0.5;
      rightEye[i].r = sqrt( rightEye[i].x * rightEye[i].x +
			    rightEye[i].y * rightEye[i].y +  
			    rightEye[i].z * rightEye[i].z );  

      if ( front_th != rear_th ) {
        leftEye[i].alpha = ( -beeParam.omReMax 
            + (omFrMax+beeParam.omReMax)*(th-rear_th)
              /(front_th-rear_th)
          ) * TO_RAD;
      } else {
	  leftEye[i].alpha = 25. * TO_RAD;
      }
      leftEye[i].beta = -beeParam.omVenMax * ph/beeParam.venPh * TO_RAD;

      if ( leftEye[i].alpha < 0. ) {
	rightEye[i].alpha = -M_PI - leftEye[i].alpha;
      } else {
        rightEye[i].alpha =  M_PI - leftEye[i].alpha;
      }
      rightEye[i].beta = leftEye[i].beta;

      /*
      printf( "om(%d): %lf, %lf, %lf, %lf\n",  
             i, leftEye[i].alpha*TO_DEG,   leftEye[i].beta*TO_DEG,
                rightEye[i].alpha*TO_DEG,  rightEye[i].beta*TO_DEG );
      */

      i++;

      th += 2.*beeParam.stepTh;
    }
    if ( p_flag == 0 ) p_flag = 1; else p_flag = 0;

    ph -= beeParam.stepPh;
  }

  // 背側(dorsal)の複眼を配置

  ph = 0.;
  while ( ph < beeParam.dorPh ) {
    front_th = calcFrontTh( ph );
    rear_th = calcRearTh( ph );
    omFrMax = calcOmFrMax( ph );

    th = rear_th + p_flag*beeParam.stepTh; 
    while ( th < front_th ) {
      leftEye[i].th = th * TO_RAD; 
      leftEye[i].ph = ph * TO_RAD;
      leftEye[i].br = 0.; 

      rightEye[i].th = th * TO_RAD;         // 水平方向角度
      rightEye[i].ph = ph * TO_RAD;         // 垂直方向角度
      rightEye[i].br = 0.;                     // 明るさ

      leftEye[i].z = compZ( ph );
      leftEye[i].y = (compY( ph )-1.0)*cos(th*TO_RAD) + 1.0;
      leftEye[i].x = (compY( ph )-1.0)*sin( th*TO_RAD ) + 0.5;
      leftEye[i].r = sqrt( leftEye[i].x * leftEye[i].x +
			   leftEye[i].y * leftEye[i].y +  
			   leftEye[i].z * leftEye[i].z );  


      rightEye[i].z = compZ( ph );
      rightEye[i].y = -(compY( ph )-1.0)*cos(th*TO_RAD) - 1.0;
      rightEye[i].x = (compY( ph )-1.0)*sin( th*TO_RAD ) + 0.5;
      rightEye[i].r = sqrt( rightEye[i].x * rightEye[i].x +
			    rightEye[i].y * rightEye[i].y +  
			    rightEye[i].z * rightEye[i].z );

      if ( front_th != rear_th ) {
        leftEye[i].alpha = ( -beeParam.omReMax 
            + (omFrMax+beeParam.omReMax)*(th-rear_th)
              /(front_th-rear_th)
          ) * TO_RAD;
      } else {
	  leftEye[i].alpha = 25. * TO_RAD;
      }

      leftEye[i].beta = beeParam.omDorMax * ph/beeParam.dorPh * TO_RAD;

      if ( leftEye[i].alpha < 0. ) {
	rightEye[i].alpha = -M_PI - leftEye[i].alpha;
      } else {
        rightEye[i].alpha =  M_PI - leftEye[i].alpha;
      }
      rightEye[i].beta = leftEye[i].beta;

      i++;

      th += 2.*beeParam.stepTh;
    }
    if ( p_flag == 0 ) p_flag = 1; else p_flag = 0;

    ph += beeParam.stepPh;
  }

  beeParam.numOfOM = i;
  printf( "number of compound eyes: %d\n", beeParam.numOfOM );

  return 0;
}

/*****************************************************************************

 複眼の初期化 3
 複眼形状を楕円で近似してモデル化した
 ---------------------------------------------------------------------------
 initEye3()を使用するときはbeeVision.conf.base.3を用いる

*****************************************************************************/

double rMapping( double ph ) {
  double x, f, rMax;

  x = ph/5. + 11.;
  f = -0.0008 * x * x + 0.0042 * x + 1.0509;
  rMax = beeParam.headR * f; 

  return rMax;
}

int initEye3() {
  int    i, p_flag;
  double ph, th; 
  double antTh, postTh, x, w;
  double omFrMax;

  double rMax, z, xPost, xAnt, y, zMax, r2;
  double rotA, xOff, yOff;

  i = 0;
  p_flag = 0;   // 個眼を互い違いに配置するためのふらぐ

  // 腹側(ventral)の複眼を配置

  ph = beeParam.venPh;   // Z方向の角度
  zMax = beeParam.headR * atan( -beeParam.venPh * TO_RAD ); // 最大のZの値 
  while ( ph > 0. ) {
    z = beeParam.headR * atan( -ph * TO_RAD ); 
    xPost = sqrt( beeParam.xPostMax * beeParam.xPostMax 
                  * (1. - (z*z)/(zMax*zMax))
                );
    xAnt  = sqrt( beeParam.xAntMax * beeParam.xAntMax 
                  * (1. - (z*z)/(zMax*zMax))
                );
    
    postTh = -tan( xPost/beeParam.headR ) * TO_DEG;  // 後方向の角度
    antTh = tan( xAnt/beeParam.headR ) * TO_DEG;  // 前方向の角度
    omFrMax = calcOmFrMax( -ph );   // 前方向の最大視線方向を求める

    rMax = rMapping( -ph );

    th = postTh + p_flag*beeParam.stepTh;
    while( th < antTh ) { 
      leftEye[i].ph = -ph * TO_RAD;         // 垂直方向角度
      leftEye[i].br = 0.;                      // 明るさ
     
      leftEye[i].z = rMax * sin( -ph * TO_RAD );
      leftEye[i].y = rMax * cos( -ph * TO_RAD ) * cos( th * TO_RAD );
      leftEye[i].x = rMax * cos( -ph * TO_RAD ) * sin( th * TO_RAD );

      // 回転させる

      rotA = beeParam.rotAng * TO_RAD;
      xOff = beeParam.rotXoff;
      yOff = beeParam.rotYoff;

      leftEye[i].y = (leftEye[i].y-yOff) * cos(rotA) 
	           - (leftEye[i].x-xOff) * sin(rotA) + yOff;
      leftEye[i].x = (leftEye[i].y-yOff) * sin(rotA)
                   + (leftEye[i].x-xOff) * cos(rotA) + xOff;

/*
      leftEye[i].r = sqrt( leftEye[i].x * leftEye[i].x +
           leftEye[i].y * leftEye[i].y +  
	   leftEye[i].z * leftEye[i].z );
      leftEye[i].th = atan( leftEye[i].x/(-leftEye[i].y) );
      leftEye[i].ph = atan( leftEye[i].z/(-leftEye[i].y) );
*/
      // 右目について

      rightEye[i].ph = -ph * TO_RAD;        // 垂直方向角度
      rightEye[i].br = 0.;                     // 明るさ

      rightEye[i].z = rMax * sin( -ph * TO_RAD );
      rightEye[i].y = -rMax * cos( -ph * TO_RAD ) * cos( th * TO_RAD );
      rightEye[i].x = rMax * cos( -ph * TO_RAD ) * sin( th * TO_RAD );

      // 回転させる

      rotA = -beeParam.rotAng * TO_RAD;
      xOff = beeParam.rotXoff;
      yOff = -beeParam.rotYoff;

      rightEye[i].y = (rightEye[i].y-yOff) * cos(rotA) 
                    - (rightEye[i].x-xOff) * sin(rotA) + yOff;
      rightEye[i].x = (rightEye[i].y-yOff) * sin(rotA)
                    + (rightEye[i].x-xOff) * cos(rotA) + xOff;

/*
      rightEye[i].r = sqrt( rightEye[i].x * rightEye[i].x +
			    rightEye[i].y * rightEye[i].y +  
			    rightEye[i].z * rightEye[i].z );  
*/

      // 視線を求める

      leftEye[i].alpha = ( -beeParam.omReMax  
            + (omFrMax+beeParam.omReMax)*(th-postTh)/(antTh-postTh)
           ) * TO_RAD;
      leftEye[i].beta = -beeParam.omVenMax * ph/beeParam.venPh * TO_RAD;

      if ( leftEye[i].alpha < 0. ) {
	rightEye[i].alpha = -M_PI - leftEye[i].alpha;
      } else {
        rightEye[i].alpha =  M_PI - leftEye[i].alpha;
      }
      rightEye[i].beta = leftEye[i].beta;

      i++;

      th += 2.*beeParam.stepTh;
    }
    if ( p_flag == 0 ) p_flag = 1; else p_flag = 0;

    ph -= beeParam.stepPh;
  }

  // 背側(dorsal)の複眼を配置

  ph = 0.;   // Z方向の角度
  zMax = beeParam.headR * atan( beeParam.dorPh * TO_RAD ); // 最大のZの値 
  while ( ph < beeParam.dorPh ) {
    z = beeParam.headR * atan( ph * TO_RAD ); 
    xPost = pow( beeParam.xPostMax * beeParam.xPostMax 
		 * beeParam.xPostMax * beeParam.xPostMax 
		 * (1. - (z*z)/(zMax*zMax)), 0.25 );
    xAnt  = pow( beeParam.xAntMax * beeParam.xAntMax
                 * beeParam.xAntMax * beeParam.xAntMax		 
		 * (1. - (z*z)/(zMax*zMax)), 0.25 );

    //   xAnt =  beeParam.xAntMax * (ph/50.+1.);

    postTh = -tan( xPost/beeParam.headR ) * TO_DEG;  // 後方向の角度
    antTh = tan( xAnt/beeParam.headR ) * TO_DEG;  // 前方向の角度
    omFrMax = calcOmFrMax( ph );   // 前方向の最大視線方向を求める

    rMax = rMapping( ph );

    th = postTh + p_flag*beeParam.stepTh;
    while( th < antTh ) { 
      leftEye[i].ph = ph * TO_RAD;         // 垂直方向角度
      leftEye[i].br = 0.;                      // 明るさ
     
      leftEye[i].z = rMax * sin( ph * TO_RAD );
      leftEye[i].y = rMax * cos( ph * TO_RAD ) * cos( th * TO_RAD );
      leftEye[i].x = rMax * cos( ph * TO_RAD ) * sin( th * TO_RAD );

      // 回転させる

      rotA = beeParam.rotAng * TO_RAD;
      xOff = beeParam.rotXoff;
      yOff = beeParam.rotYoff;

      leftEye[i].y = (leftEye[i].y-yOff) * cos(rotA) 
	           - (leftEye[i].x-xOff) * sin(rotA) + yOff;
      leftEye[i].x = (leftEye[i].y-yOff) * sin(rotA)
                   + (leftEye[i].x-xOff) * cos(rotA) + xOff;

/*
      leftEye[i].r = sqrt( leftEye[i].x * leftEye[i].x +
			   leftEye[i].y * leftEye[i].y +  
			   leftEye[i].z * leftEye[i].z );  
      leftEye[i].th = atan( leftEye[i].x/leftEye[i].y );
      leftEye[i].ph = atan( leftEye[i].z/leftEye[i].y );
*/

      // 右目について

      rightEye[i].ph = ph * TO_RAD;        // 垂直方向角度
      rightEye[i].br = 0.;                     // 明るさ

      rightEye[i].z = rMax * sin( ph * TO_RAD );
      rightEye[i].y = -rMax * cos( ph * TO_RAD ) * cos( th * TO_RAD );
      rightEye[i].x = rMax * cos( ph * TO_RAD ) * sin( th * TO_RAD );

      // 回転させる

      rotA = -beeParam.rotAng * TO_RAD;
      xOff = beeParam.rotXoff;
      yOff = -beeParam.rotYoff;

      rightEye[i].y = (rightEye[i].y-yOff) * cos(rotA) 
                    - (rightEye[i].x-xOff) * sin(rotA) + yOff;
      rightEye[i].x = (rightEye[i].y-yOff) * sin(rotA)
                    + (rightEye[i].x-xOff) * cos(rotA) + xOff;

/*
      rightEye[i].r = sqrt( rightEye[i].x * rightEye[i].x +
			    rightEye[i].y * rightEye[i].y +  
			    rightEye[i].z * rightEye[i].z );  
*/

      // 視線を求める

      leftEye[i].alpha = ( -beeParam.omReMax  
            + (omFrMax+beeParam.omReMax)*(th-postTh)/(antTh-postTh)
           ) * TO_RAD;
      leftEye[i].beta = beeParam.omVenMax * ph/beeParam.dorPh * TO_RAD;

      if ( leftEye[i].alpha < 0. ) {
	rightEye[i].alpha = -M_PI - leftEye[i].alpha;
      } else {
        rightEye[i].alpha =  M_PI - leftEye[i].alpha;
      }

      rightEye[i].beta = leftEye[i].beta;

      i++;

      th += 2.*beeParam.stepTh;
    }
    if ( p_flag == 0 ) p_flag = 1; else p_flag = 0;

    ph += beeParam.stepPh;
  }

  beeParam.numOfOM = i;
  printf( "number of compound eyes: %d\n", beeParam.numOfOM );

  return 0;
}


/*****************************************************************************

 画像処理層(VPL1)神経細胞の初期化
 ---------------------------------------------------------------------------

*****************************************************************************/

int initVPL1() {
  int    i, j, k, refOM;
  double degRF, radRF;
  double diffTh, diffPh, diffAngle;

  for ( i = 0; i < beeParam.numOfVPL1; i++ ) {

    // 左側

    leftVPL1[i].respMode = 0;
//    leftVPL1[i].RFtype = rand() % VPL1_RF_NUM;
    leftVPL1[i].RFtype = 0;
    leftVPL1[i].RFcoef = 0.;
    //    leftVPL1[i].RFcoef = VPL1_RF_COEF * (double)rand()/RAND_MAX * TO_RAD;

    // 基準となる個眼を決める（左側）

    refOM = rand() % beeParam.numOfOM;

    leftVPL1[i].x = leftEye[refOM].x;    
    leftVPL1[i].y = leftEye[refOM].y;    
    leftVPL1[i].z = leftEye[refOM].z;    

    leftVPL1[i].r  = leftEye[refOM].r;    
    leftVPL1[i].th = leftEye[refOM].th;    
    leftVPL1[i].ph = leftEye[refOM].ph;    

    leftVPL1[i].alpha = leftEye[refOM].alpha;    
    leftVPL1[i].beta  = leftEye[refOM].beta;    

    // 左側について受容野とつながっている個眼を設定

    //    radRF = beeParam.VPL1rf_max * TO_RAD;
    degRF = beeParam.VPL1rf_min 
          + (beeParam.VPL1rf_max-beeParam.VPL1rf_min) 
          * (double)rand()/RAND_MAX; 
    radRF = degRF * TO_RAD;
    leftVPL1[i].rfAngle = radRF;

    leftVPL1[i].rfAngle = beeParam.VPL1rf_min;

    k = 0;
    for ( j = 0; j < beeParam.numOfOM; j++ ) {
      diffTh = fabs( leftEye[j].alpha - leftVPL1[i].alpha );
      diffPh = fabs( leftEye[j].beta - leftVPL1[i].beta );
      diffAngle = sqrt( diffTh*diffTh + diffPh*diffPh );
  
      if ( diffAngle < radRF ) {
        leftVPL1[i].connectOM[k] = j; k++;
      }
    }
    leftVPL1[i].conNumOfOM = k;    
//    printf( "leftVPL1[%d]: %d, %d, %lf\n", i, k, 
//    leftVPL1[i].RFtype, leftVPL1[i].RFcoef  );

    // 右側

    rightVPL1[i].respMode = 0;
//    rightVPL1[i].RFtype = rand() % VPL1_RF_NUM;
    rightVPL1[i].RFtype = 0;
    rightVPL1[i].RFcoef = 0.;
    // rightVPL1[i].RFcoef = VPL1_RF_COEF * (double)rand()/RAND_MAX * TO_RAD;

    // 基準となる個眼を決める（右側）

//  左右対象にするときにはコメントにする
//    refOM = rand() % beeParam.numOfOM;

    rightVPL1[i].x = rightEye[refOM].x;    
    rightVPL1[i].y = rightEye[refOM].y;    
    rightVPL1[i].z = rightEye[refOM].z;    

    rightVPL1[i].r  = rightEye[refOM].r;    
    rightVPL1[i].th = rightEye[refOM].th;    
    rightVPL1[i].ph = rightEye[refOM].ph;    

    rightVPL1[i].alpha = rightEye[refOM].alpha;    
    rightVPL1[i].beta  = rightEye[refOM].beta;    

    // 右側について受容野とつながっている個眼を設定

    //    radRF = beeParam.VPL1rf_max * TO_RAD;
//  左右対象にするときにはコメントにする
//    degRF = beeParam.VPL1rf_min 
//          + (beeParam.VPL1rf_max-beeParam.VPL1rf_min) 
//          * (double)rand()/RAND_MAX; 
//    radRF = degRF * TO_RAD; 
    rightVPL1[i].rfAngle = radRF;

    k = 0;
    for ( j = 0; j < beeParam.numOfOM; j++ ) {
      diffTh = fabs( rightEye[j].alpha - rightVPL1[i].alpha );
      diffPh = fabs( rightEye[j].beta - rightVPL1[i].beta );
      diffAngle = sqrt( diffTh*diffTh + diffPh*diffPh );
  
      if ( diffAngle < radRF ) {
        rightVPL1[i].connectOM[k] = j; k++;
      }
    }
    rightVPL1[i].conNumOfOM = k;    
    //printf( "rightVPL1[%d]: %d\n", i, k );

  }

  return 0;
}

/*****************************************************************************

 画像処理層(VPL2)神経細胞の初期化
 ---------------------------------------------------------------------------

*****************************************************************************/

int initVPL2() {
  int    i, j, k, refVPL1;
  double degRF, radRF;
  double diffTh, diffPh, diffAngle;

  for ( i = 0; i < beeParam.numOfVPL2; i++ ) {

    // 左側

    leftVPL2[i].respMode = 0;
    leftVPL2[i].RFtype = rand() % VPL2_RF_NUM;
    //    leftVPL2[i].RFtype = 0;

    // 基準となる個眼を決める（左側）

    refVPL1 = rand() % beeParam.numOfVPL1;

    leftVPL2[i].x = leftVPL1[refVPL1].x;    
    leftVPL2[i].y = leftVPL1[refVPL1].y;    
    leftVPL2[i].z = leftVPL1[refVPL1].z;    

    leftVPL2[i].r  = leftVPL1[refVPL1].r;    
    leftVPL2[i].th = leftVPL1[refVPL1].th;    
    leftVPL2[i].ph = leftVPL1[refVPL1].ph;    

    leftVPL2[i].alpha = leftVPL1[refVPL1].alpha;    
    leftVPL2[i].beta  = leftVPL1[refVPL1].beta;    

    // 左側について受容野とつながっている個眼を設定

    degRF = beeParam.VPL2rf_min 
          + (beeParam.VPL2rf_max-beeParam.VPL2rf_min) 
          * (double)rand()/RAND_MAX; 
    radRF = degRF * TO_RAD; 
    leftVPL2[i].rfAngle = radRF;

    k = 0;
    for ( j = 0; j < beeParam.numOfVPL1; j++ ) {
      diffTh = fabs( leftVPL1[j].alpha - leftVPL2[i].alpha );
      diffPh = fabs( leftVPL1[j].beta - leftVPL2[i].beta );
      diffAngle = sqrt( diffTh*diffTh + diffPh*diffPh );
  
      if ( diffAngle < radRF ) {
        leftVPL2[i].connectVPL1[k] = j; k++;
      }
    }
    leftVPL2[i].conNumOfVPL1 = k;    
    //    printf( "leftVPL2[%d]: %d\n", i, k );

    // 右側

    rightVPL2[i].respMode = 0;

// 左右を一致させるときには左のRFtypeをコピーする 
//    rightVPL2[i].RFtype = rand() % VPL2_RF_NUM;
    rightVPL2[i].RFtype = leftVPL2[i].RFtype;

    // 基準となる個眼を決める（右側）

// 左右を一致させるときにはコメントにする
//    refVPL1 = rand() % beeParam.numOfVPL1;

    rightVPL2[i].x = rightVPL1[refVPL1].x;    
    rightVPL2[i].y = rightVPL1[refVPL1].y;    
    rightVPL2[i].z = rightVPL1[refVPL1].z;    

    rightVPL2[i].r  = rightVPL1[refVPL1].r;    
    rightVPL2[i].th = rightVPL1[refVPL1].th;    
    rightVPL2[i].ph = rightVPL1[refVPL1].ph;    

    rightVPL2[i].alpha = rightVPL1[refVPL1].alpha;    
    rightVPL2[i].beta  = rightVPL1[refVPL1].beta;    

    // 右側について受容野とつながっている個眼を設定

// 左右を一致させるときにはコメントにする
//    degRF = beeParam.VPL2rf_min 
//          + (beeParam.VPL2rf_max-beeParam.VPL2rf_min) 
//          * (double)rand()/RAND_MAX; 
//    radRF = degRF * TO_RAD; 
    rightVPL2[i].rfAngle = radRF;

    k = 0;
    for ( j = 0; j < beeParam.numOfVPL1; j++ ) {
      diffTh = fabs( rightVPL1[j].alpha - rightVPL2[i].alpha );
      diffPh = fabs( rightVPL1[j].beta - rightVPL2[i].beta );
      diffAngle = sqrt( diffTh*diffTh + diffPh*diffPh );
  
      if ( diffAngle < radRF ) {
        rightVPL2[i].connectVPL1[k] = j; k++;
      }
    }
    rightVPL2[i].conNumOfVPL1 = k;    
    // printf( "rightVPL2[%d]: %d\n", i, k );

  }
  return 0;
}

