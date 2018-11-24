/*****************************************************************************

 Bee Vision  - Simulation Program of Honeybee Compound Eye Vision -
            (c) Hidetoshi Ikeno/Himeji Institute of Technology

 ----------------------------------------------------------------------------

ディレクトリ
  ./ _____________        
     |__TIFF/___XY/       TIFF files of XY view
     |       |__XZleft/   TIFF files of XZ view (left eye)
     |       |__XZright/  TIFF files of XZ view (right eye)
     |       |__YZ/       TIFF files of YZ view
     |__Conf/             config files for simulation               
     |__Results/          results files
     |__Responses/        cell responses

コンパイル方法
  (i686)
  % make

実行方法
  % beeVision -b/-v number -plot/-noplot :
              -b : バッチでシミュレーションを実行
              -v : バージョンの表示
              number: シミュレーション系列におけるシーケンシャルナンバー
              -plot: イメージファイルを作成する
              -noplot: イメージファイルを作成しない

注意点
  (1) グラフィック表示には、DISLIN(http://www.linmpi.mpg.de/dislin)を使用
      あらかじめ、dislinをインストールしておく必要がある。
      beeVision21.cと同じディレクトリにdislin.hをおく。
  (2) 実行においては, beeVision.confファイルを読み込む。
  (3) Ver.3 より、beeVision.confでパラメータ及び刺激条件を設定するようにした。
      従って、Ver.2.*, Ver. 3.*ではbeeVision.confの構成が大きく異なる。

 ----------------------------------------------------------------------------

2001/09/08: Start Project
2001/09/10: Version 2.0       プログラムの基本部ができた。
2001/09/11: Version 2.1       視線ベクトル角度alpha, betaを追加。
2001/09/14: Version 2.2       一応満足いくレベルになった。
2001/09/15: Version 2.21      条件設定、バッチ処理機能を追加した。
2001/09/16: Version 2.22      左眼の角度設定に関するバグを修正。
2001/09/17: Version 2.23      個眼配置の方法を変更, 対象図形の明るさを-1〜1で
                              表せば、明るさに応じた画像が表示される。
2001/09/17: Version 2.24      実際の行動実験データに合わせるために、提示図形の
                              ドットピッチを0.5mmとし、直径45mmの円形図形を提示
                              するようにした。
2001/10/15: Version 2.25      提示図形のY軸についての回転に対する座標補正に
                              ついてのバグを修正。
                              画像ピクセルの明るさ=0の点は計算しない。
2001/10/13: Version 2.26      ミツバチ飛翔姿勢に基づく補正 fixFig()を追加。
2001/11/05: Version 2.30      leftEye, rightEyeの変数を変更
                              これまでとは左右の目が反対になる
                              (ミツバチを中心に左右を決めた)
2001/11/14: Version 2.31      個眼における照度は光源までの距離の２乗に反比例
                              するようにした。
                              通信学会論文誌用のパターン生成関数を入れた。
2001/11/16: Version 2.32      視線ベクトルに対する画像の傾きの影響を入れる
2001/11/26: Version 2.34      目標図形設定のバグを修正(バーの太さ)，
                              照度計算における単位変換を入れた
2002/01/23: Version 2.35      視野とドットの重なりの計算部分を修正
2002/05/01: Version 3.00      confファイルによるシミュレーション条件設定機能
                              を強化する
2003/01/14: Version 3.10      画像情報処理層の追加

********************************************** (c) Hidetoshi Ikeno **********/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "beeVision.h"

/*****************************************************************************

  共通パラメータ、目標変数の定義

 ----------------------------------------------------------------------------
  rightEye, leftEye: 左右複眼
  rightVPL1, leftVPL1: 左右VPL1層
  rightVPL1mem, leftVPL1mem: 一つ前の時刻の左右VPL1層
  rightVPL2, leftVPL2: 左右VPL2層

  beeParam: シミュレーション関連パラメータ
  figure: 目標図形

*****************************************************************************/

compound_eye  rightEye[NUM_CE],       leftEye[NUM_CE];

VPL1cell      rightVPL1[NUM_VPL1],    leftVPL1[NUM_VPL1];
double        rightVPL1mem[VPL1_MEM][NUM_VPL1]; 
double        leftVPL1mem[VPL1_MEM][NUM_VPL1];

VPL2cell      rightVPL2[NUM_VPL2],    leftVPL2[NUM_VPL2];

parameters   beeParam;
target       figure[N_FIGURE];

/******************************************************************************

 関数プロトタイプの定義

 ----------------------------------------------------------------------------

******************************************************************************/

// 複眼データの設定: init.c

extern void rmFiles();
extern void readConfig();
extern void initEye();
extern void initEye2();
extern void initEye3();
extern void initVPL1();
extern void initVPL2();

// 提示画像の設定: figure.c

extern void initFig( int );
extern void initFigPlus( int );
extern void initFigCross( int );
extern void initFigCircle( int );
extern void initFigPGM( int, char* );
extern void fixFig( int );
extern void printFig( int );

// 出力関連関数: output.c

extern void printEye( int );
extern void plotLeftEyeXZ( char*, int );
extern void plotRightEyeXZ( char*, int );
extern void plotBothEyeYZ( char*, int );
extern void plotBothEyeXY( char*, int );
extern void plotBothEyeXZ( char*, int );

extern void greyPlotLeftEyeXZ( char*, int );
extern void greyPlotRightEyeXZ( char*, int );
extern void greyPlotBothEyeXZ( char*, int );

extern void plotBothVPL1( char* );
extern void plotBothVPL2( char*, int );

extern void outToFile( char* );
extern void outToFileXYZ( char* );
extern void outToFileRslt( char* );
extern int  inFromFile( char* );

// このファイルで定義された関数

double filter( double );
double dotCheck( double, double, double, double, double );
void   proToEye( int, int, int );
void   applySigmoid( int );

double VPL1rf( int, double, double, double, int ); 
int    VPL1resp(); 

double VPL2rf( int, double, double, double ); 
int    VPL2resp(); 

/*****************************************************************************

  複眼への画像の投影

*****************************************************************************/

double filter( double angle ) {
  double limit, eyeAngle;
  double value;

  limit = 0.16;
  
  eyeAngle = beeParam.omDeg/2. * TO_RAD;              // 個眼の視野角
  /*
  if ( angle < eyeAngle ) { 
    value = 1.-1./eyeAngle*angle; 
  } else value = 0.;
  */

  // 個眼の視野における減衰特性をガウス関数で近似

  if ( angle < eyeAngle ) {
     value = exp( -beeParam.omRFcoef * angle * TO_DEG * angle * TO_DEG );
     //     printf( "value: %lf, %lf\n", angle*TO_DEG, value );
  } else value = 0;

  return value;
}

double dotCheck( double visVecTh, double visVecPh, 
                 double objTh, double objPh, double objR ) {
  double diffTh, diffPh, diffAngle;

  diffTh = fabs( visVecTh - objTh );
  diffPh = fabs( visVecPh - objPh );
  diffAngle = sqrt( diffTh*diffTh + diffPh*diffPh );

  //  printf( "diffAngle: %lf\n", diffAngle );

  return filter( diffAngle );

}


// 複眼に写る像を求める
//   0: right, 1: left

void proToEye(int RorL, int numOM, int figNum) {
  int    i, j, k;
  double ph, th, eyeAngle;
  double rfArea, dotArea;
  double lightResponse;
  double shiftX, shiftY, shiftZ;
  double over;
  double objX, objY, objZ, objR, objTh, objPh, s;

  double figXangle, figYangle, angleH, angleV;

  double alpha1, objTh1;

  dotArea = M_PI * figure[figNum].dotDiam * figure[figNum].dotDiam;     
                                                      // 画像1ドットの面積
  eyeAngle = beeParam.omDeg/2. * TO_RAD;              // 個眼の視野角

  for ( k = 0; k < numOM; k++ ) {

    // 個眼位置を原点にするためのシフト量

    // X方向の不連続性を解消するために右側は座標系をマイナスからプラスに
    // 変換して計算するように変更した

    figXangle = figure[figNum].angleX * TO_RAD;
    figYangle = figure[figNum].angleY * TO_RAD;

    if ( !RorL ) {
      shiftX = rightEye[k].x; 
      shiftY = rightEye[k].y; 
      shiftZ = rightEye[k].z;
    } else {
      shiftX = leftEye[k].x; 
      shiftY = leftEye[k].y; 
      shiftZ = leftEye[k].z;
    }

    lightResponse = 0.;
    for (j = 0; j < figure[figNum].dotY; j++) {
      for (i = 0; i < figure[figNum].dotX; i++) {

        if (figure[figNum].pixel[i][j].br == 0) continue;

	// 個眼位置を原点に設定

        objX = figure[figNum].pixel[i][j].x - shiftX;
        objY = figure[figNum].pixel[i][j].y - shiftY;
        objZ = figure[figNum].pixel[i][j].z - shiftZ;

        // 個眼から映像点までの距離、角度を求める
        objR  = sqrt( objX*objX + objY*objY + objZ*objZ );
        objTh = atan( objX/objY );

        if ( objY < 0. && objX  > 0. ) objTh += M_PI;
        if ( objY < 0. && objX <=  0. ) objTh -= M_PI;

	s = sqrt( objX*objX + objY*objY );
        objPh = atan( objZ/s );

        // 画像のドットがどの程度視野に入っているかを求める

        if ( !RorL ) {
          over = dotCheck( rightEye[k].alpha, rightEye[k].beta,
                           objTh, objPh, objR ); 
        } else {
          over = dotCheck( leftEye[k].alpha, leftEye[k].beta,
                           objTh, objPh, objR ); 
        }

         if ( over != 0. )  {
            if ( figure[figNum].pixel[i][j].br != 0.) {
 	      rfArea = M_PI * (objR * tan(eyeAngle) * objR * tan(eyeAngle));

              // 照度は距離の二乗に反比例する 2001.11.14
              // cosはX、Y方向について画像ピクセルと視線ベクトルとの方向
              // のずれを考慮するための成分

              angleH = objTh - figXangle; angleV = objPh - figYangle;
              if ( cos( M_PI/2. - angleH ) >= 0. ) {
// 放射光の場合
/*
    
            lightResponse += figure[figNum].pixel[i][j].br 
                  * dotArea * over/rfArea / (s*s)
	  	  * cos( M_PI/2. - angleH )
		  * cos( angleV )
                  * 1.e6;
*/

// 反射光の場合

                lightResponse += figure[figNum].pixel[i][j].br 
                  * dotArea * over/rfArea
	  	  * cos( M_PI/2. - angleH )
		  * cos( angleV )
                  * 1.e6;

       }

	      /*
	printf( "k, i, j, objPh, objTh, shadow: %d, %d, %d, %lf, %lf, %lf\n", 
          k, i, j, objPh*TO_DEG, objTh*TO_DEG, shadow );
	      */
            }
	    /*
	printf( "k, alpha, beta, ojbPh, objTh: %d, %lf, %lf, %lf, %lf\n",
	  k,
	  rightEye[k].alpha*TO_DEG, rightEye[k].beta*TO_DEG, 
          objTh*TO_DEG, objPh*TO_DEG );
	    */
	  }
       }
    }

    if ( !RorL ) {
      rightEye[k].br +=  lightResponse;
      //if ( rightEye[k].br != 0. )
      //  printf( "right(%d): %lf\n", k, rightEye[k].br );
    } else {
      leftEye[k].br +=  lightResponse;
      //if ( leftEye[k].br != 0. ) 
      //  printf( "left(%d): %lf\n", k, leftEye[k].br );
    }

  }

}

void applySigmoid( int numOM ) {
  int  i;

  for ( i = 0; i < numOM; i++ ) {
    if ( leftEye[i].br <= 50. && leftEye[i].br >= -50. ) {  
      leftEye[i].br =  2.*(1./(1.+exp( beeParam.sigCoef * leftEye[i].br )) 
                    - 0.5);
    } else if ( leftEye[i].br > 50. ) {
      leftEye[i].br = 1.;
    } else {
      leftEye[i].br = -1.;
    }

    if ( rightEye[i].br <= 50. && rightEye[i].br >= -50. ) {  
      rightEye[i].br =  2.*(1./(1.+exp( beeParam.sigCoef * rightEye[i].br )) 
                     - 0.5);
    } else if ( rightEye[i].br > 50. ) {
      rightEye[i].br = 1.;
    } else {
      rightEye[i].br = -1.;
    }
  }
}

void applySigmoid2( int numOM ) {
  int  i;

  for ( i = 0; i < numOM; i++ ) {
    leftEye[i].br =  2./(1.+exp( beeParam.sigCoef * leftEye[i].br )) - 1.;
    rightEye[i].br = 2./(1.+exp( beeParam.sigCoef * rightEye[i].br )) - 1.;
  }
}

/*****************************************************************************

 画像情報処理層(VPL1)細胞の応答を求める

 -----------------------------------------------------------------------------
 2002.01.31: 網膜層からの入力を受け、複数の個眼の応答の平均を求める

 [VPL1細胞の特性: RFtypeで設定]
   １： 一定の

 *****************************************************************************/

// この関数は使っていない 2003/4/11

double VPL1rf( int rfType, double rfCoef, double th, double ph, 
               int left_right ) 
{
  double angle2, resp;

  resp = 0.;
  angle2 = th*th + ph*ph;
  switch ( rfType ) {
    case 0: {
        resp = exp( rfCoef * angle2 * TO_DEG * TO_DEG );
        break;
    }
    case 1: {
	if ( ((th > 0) && (left_right == 0)) || 
             ((th < 0) && (left_right == 1)) ) {      
          resp = exp( rfCoef * angle2 * TO_DEG * TO_DEG );
        }
        break;
    }
    case 2: {
	if ( ((th < 0) && (left_right == 0)) || 
             ((th > 0) && (left_right == 1)) ) {      
          resp = exp( rfCoef * angle2 * TO_DEG * TO_DEG );
	}
        break;
    }
    case 3: {
	if ( ph > 0 ) {      
          resp = exp( rfCoef * angle2 * TO_DEG * TO_DEG );
        }
        break;
    }
    case 4: {
	if ( ph < 0 ) {      
          resp = exp( rfCoef * angle2 * TO_DEG * TO_DEG );
        }
        break;
    }
  }

  return resp;

}

int VPL1resp() {
  int     i, j, k, rfType;
  double  diffTh, diffPh, diffAngle;
  double  resp, rfCoef;

  printf( "start calc of Visual-information Processing Layer 1 response\n" );

  // 左側

  for ( i = 0; i < beeParam.numOfVPL1; i++ ) { 
    rfType = leftVPL1[i].RFtype;
    rfCoef = leftVPL1[i].RFcoef;

    resp = 0.;
    for ( j = 0; j < leftVPL1[i].conNumOfOM; j++ ) {
      k = leftVPL1[i].connectOM[j];
//      diffTh = leftEye[k].alpha - leftVPL1[i].alpha; 
//      diffPh = leftEye[k].beta - leftVPL1[i].beta;
//      resp += VPL1rf( rfType, rfCoef, diffTh, diffPh, 0 ) * leftEye[k].br; 
      resp += leftEye[k].br; 
    }
    leftVPL1[i].resp = resp/leftVPL1[i].conNumOfOM;
    //    leftVPL1[i].resp = resp;

    if ( leftVPL1[i].resp != 0. ) {
      printf( "leftVPL1[%d]: %lf\n", i, leftVPL1[i].resp );
    }

  }

  // 右側

  for ( i = 0; i < beeParam.numOfVPL1; i++ ) { 
    rfType = rightVPL1[i].RFtype;
    rfCoef = rightVPL1[i].RFcoef;

    resp = 0.;
    for ( j = 0; j < rightVPL1[i].conNumOfOM; j++ ) {
      k = rightVPL1[i].connectOM[j];
//      diffTh = rightEye[k].alpha - rightVPL1[i].alpha;
//      diffPh = rightEye[k].beta - rightVPL1[i].beta;
//      resp += VPL1rf( rfType, rfCoef, diffTh, diffPh, 1 ) * rightEye[k].br; 
      resp += rightEye[k].br; 
    }
    rightVPL1[i].resp = resp/rightVPL1[i].conNumOfOM;
    //    rightVPL1[i].resp = resp;

    if ( rightVPL1[i].resp != 0. ) {
      printf( "rightVPL1[%d]: %lf\n", i, rightVPL1[i].resp );
    }

  }

  return 0;

}

/*****************************************************************************

 画像情報処理層(VPL2)細胞の応答を求める

 -----------------------------------------------------------------------------

 2002.01.31: VPL1細胞からの入力を受けオプティカルフローを計算する
 type 0: 単純に合計
 type 1: 水平方向の動き
 type 2: 鉛直方向の動き

 *****************************************************************************/

int VPL2resp() {
  int     i, j, k, rfType, rfTypeVPL1;
  int     count, countP;
  double  diffTh, diffPh, diffAngle;
  double  resp, respP;

  double  resp1[VPL1_RF_NUM], resp1P[VPL1_RF_NUM];
  int     count1[VPL1_RF_NUM], count1P[VPL1_RF_NUM];

  // 左側

  for ( i = 0; i < beeParam.numOfVPL2; i++ ) { 
    rfType = leftVPL2[i].RFtype;
    for ( j = 0; j < VPL1_RF_NUM; j++ ) {
      resp1[j] = resp1P[j] = 0.;
      count1[j] = count1P[j] = 0;
    }

    resp = respP = 0.;
    count = countP = 0;
    for ( j = 0; j < leftVPL2[i].conNumOfVPL1; j++ ) {
      k = leftVPL2[i].connectVPL1[j];
      rfTypeVPL1 = leftVPL1[k].RFtype;
      diffTh = leftVPL1[k].alpha - leftVPL2[i].alpha;
      diffPh = leftVPL1[k].beta - leftVPL2[i].beta;

      if ( rfTypeVPL1 == 0 ) { 
        resp1[0] += leftVPL1[k].resp; count1[0]++;
      }

      if ( diffTh >= 0 ) { 
        resp1[1]  += fabs(leftVPL1[k].resp); count1[1]++;
        resp1P[1] += fabs(leftVPL1mem[VPL2_DELAY - 1][k]); count1P[1]++;
      }
      if ( diffTh < 0 ) { 
        resp1[2]  += fabs(leftVPL1[k].resp); count1[2]++;
        resp1P[2] += fabs(leftVPL1mem[VPL2_DELAY - 1][k]); count1P[2]++;
      }
      if ( diffPh >= 0 ) { 
        resp1[3]  += fabs(leftVPL1[k].resp); count1[3]++;
        resp1P[3] += fabs(leftVPL1mem[VPL2_DELAY - 1][k]); count1P[3]++;
      }
      if ( diffPh < 0 ) { 
        resp1[4]  += fabs(leftVPL1[k].resp); count1[4]++;
        resp1P[4] += fabs(leftVPL1mem[VPL2_DELAY - 1][k]); count1P[4]++;
      }

    }

    if ( rfType == 0 ) {
      if ( count1[0] != 0 ) 
        leftVPL2[i].resp = resp1[0];
    }
    if ( rfType == 1 ) {
      leftVPL2[i].resp =  resp1[1] * resp1P[2] - resp1[2] * resp1P[1];
    }
    if ( rfType == 2 ) {
      leftVPL2[i].resp =  resp1[3] * resp1P[4] - resp1[4] * resp1P[3];
    }

    if ( leftVPL2[i].resp != 0. && rfType != 0 ) {
            printf( "leftVPL2[%d](%d): %lf\n", i, rfType, leftVPL2[i].resp );
    }

  }

  // 右側

  for ( i = 0; i < beeParam.numOfVPL2; i++ ) { 
    rfType = rightVPL2[i].RFtype;
    for ( j = 0; j < VPL1_RF_NUM; j++ ) {
      resp1[j] = resp1P[j] = 0.;
      count1[j] = count1P[j] = 0;
    }

    resp = respP = 0.;
    count = countP = 0;
    for ( j = 0; j < rightVPL2[i].conNumOfVPL1; j++ ) {
      k = rightVPL2[i].connectVPL1[j];
      rfTypeVPL1 = rightVPL1[k].RFtype;
      diffTh = rightVPL1[k].alpha - rightVPL2[i].alpha;
      diffPh = rightVPL1[k].beta - rightVPL2[i].beta;

      if ( rfTypeVPL1 == 0 ) { 
        resp1[0] += rightVPL1[k].resp; count1[0]++;
      }

      // 注意！！ diffThについて左右で符号を反転させる

      if ( diffTh <= 0 ) { 
        resp1[1]  += fabs(rightVPL1[k].resp); count1[1]++;
        resp1P[1] += fabs(rightVPL1mem[VPL2_DELAY - 1][k]); count1P[1]++;
      }
      if ( diffTh > 0 ) { 
        resp1[2]  += fabs(rightVPL1[k].resp); count1[2]++;
        resp1P[2] += fabs(rightVPL1mem[VPL2_DELAY - 1][k]); count1P[2]++;
      }
      if ( diffPh >= 0 ) { 
        resp1[3]  += fabs(rightVPL1[k].resp); count1[3]++;
        resp1P[3] += fabs(rightVPL1mem[VPL2_DELAY - 1][k]); count1P[3]++;
      }
      if ( diffPh < 0 ) { 
        resp1[4]  += fabs(rightVPL1[k].resp); count1[4]++;
        resp1P[4] += fabs(rightVPL1mem[VPL2_DELAY - 1][k]); count1P[4]++;
      }

    }


    if ( rfType == 0 ) {
      if ( count1[0] != 0 ) 
        rightVPL2[i].resp = resp1[0];
    }
    if ( rfType == 1 ) {
      rightVPL2[i].resp = resp1[1] * resp1P[2] - resp1[2] * resp1P[1];
    }
    if ( rfType == 2 ) {
      rightVPL2[i].resp = resp1[3] * resp1P[4] - resp1[4] * resp1P[3];
    }

    if ( rightVPL2[i].resp != 0. && rfType != 0 ) {
            printf( "rightVPL2[%d](%d): %lf\n", i, rfType, rightVPL2[i].resp );
    }

  }

  return 0;

}

/*****************************************************************************

 これまでの応答を保存、読み込むための関数を追加した

 *****************************************************************************/

int loadVPLresp( int time ) {
  int    t, i, j ;
  double leftVPL1resp[NUM_VPL1], rightVPL1resp[NUM_VPL1];
  char   filename[256];
  FILE   *fp;
  size_t cnt;

  for ( i = 0, t = time-1; i < VPL1_MEM; i++, t-- ) {
    if ( t >= 0 ) { 
      sprintf( filename, "./Responses/%d", t );

      fp = fopen( filename, "r" );
      cnt = fread( leftVPL1resp, sizeof leftVPL1resp, 1, fp );
      cnt = fread( rightVPL1resp, sizeof rightVPL1resp, 1, fp );
      fclose( fp );
    }

    for ( j = 0; j < NUM_VPL1; j++ ) {
      if ( t >= 0 ) { 
        leftVPL1mem[i][j] = leftVPL1resp[j];      
        rightVPL1mem[i][j] = rightVPL1resp[j];
      } else {
        leftVPL1mem[i][j] = 0.;
        rightVPL1mem[i][j] = 0.;
      }      
    }
  }

  return 0;
}

int saveVPLresp( int time ) {
  int    t, i, j;
  char   filename[256];
  double leftVPL1resp[NUM_VPL1], rightVPL1resp[NUM_VPL1];
  FILE   *fp;
  size_t cnt;

  for ( j = 0; j < NUM_VPL1; j++ ) {
    leftVPL1resp[j] = leftVPL1[j].resp;      
    rightVPL1resp[j] = rightVPL1[j].resp;      
  }

  sprintf( filename, "./Responses/%d", time );
  fp = fopen( filename, "w" );
  cnt = fwrite( leftVPL1resp, sizeof leftVPL1resp, 1, fp );
  cnt = fwrite( rightVPL1resp, sizeof rightVPL1resp, 1, fp );
  fclose( fp );

  return 0;
}

// 複眼、神経細胞情報の保存、読み込み

int loadCellInfo() {
  FILE *fp;
  size_t cnt;

  fp = fopen( "./Results/cellInfo.bin", "r" );

  cnt = fread( leftEye, sizeof(compound_eye), NUM_CE, fp );
  cnt = fread( rightEye, sizeof(compound_eye), NUM_CE, fp );

  cnt = fread( leftVPL1, sizeof(VPL1cell), NUM_VPL1, fp );
  cnt = fread( rightVPL1, sizeof(VPL1cell), NUM_VPL1, fp );

  cnt = fread( leftVPL2, sizeof(VPL2cell), NUM_VPL2, fp );
  cnt = fread( rightVPL2, sizeof(VPL2cell), NUM_VPL2, fp );

  cnt = fread( &beeParam, sizeof(parameters), 1, fp );
  
  fclose( fp );

  return 0;
}

int saveCellInfo() {
  char filename[256];
  FILE *fp;
  size_t cnt;

  fp = fopen( "./Results/cellInfo.bin", "w" );

  cnt = fwrite( leftEye, sizeof(compound_eye), NUM_CE, fp );
  cnt = fwrite( rightEye, sizeof(compound_eye), NUM_CE, fp );

  cnt = fwrite( leftVPL1, sizeof(VPL1cell), NUM_VPL1, fp );
  cnt = fwrite( rightVPL1, sizeof(VPL1cell), NUM_VPL1, fp );

  cnt = fwrite( leftVPL2, sizeof(VPL2cell), NUM_VPL2, fp );
  cnt = fwrite( rightVPL2, sizeof(VPL2cell), NUM_VPL2, fp );

  cnt = fwrite( &beeParam, sizeof(parameters), 1, fp );
  
  fclose( fp );

  return 0;
}

/*****************************************************************************

   ここからがメインプログラム
 ---------------------------------------------------------------------------
   コマンドオプション: 
   argv[1]
     -v: version 表示
     -n: 番号付きのバッチ処理
   argv[2]
     シミュレーション番号
   argv[3]
     TIFFファイル出力の有無（-plot for plotting)
 ****************************************************************************/

int main(int argc, char *argv[]) {
    int   i, numOM, numFig, time;
    char  disDev[8];

    // print version number

    if ( !strcmp(argv[1], "-v") ) {
      printf( VERSION ); printf( "\n" );
      return 0;
    }

    // simulationの実行

    if ( !strcmp(argv[1], "-n") ) {
      rmFiles();
      readConfig();

      // 保存していたVPL応答をロードする

      time = atoi( argv[2] );
      loadVPLresp( time );
    } else return 0;

      // 個眼の配置

    if ( !strcmp( argv[1], "-n") && time != 0 ) {
      printf( "---------> load cell information\n" );
      loadCellInfo();
    } else {
//      initEye();   // これを使用するときはbeeVision.conf.base.1を使用
//      initEye2();  // これを使用するときはbeeVision.conf.base.2を使用
      initEye3();    // これを使用するときはbeeVision.conf.base.3を使用
      printf( "---------> END: initialize Eye\n" );
      //      initVPL1();
      //      printf( "---------> END: initialize VPL1\n" );
      //      initVPL2();
      //      printf( "---------> END: initialize VPL2\n" );
      saveCellInfo();
      printf( "---------> END: save cell infromation\n" );
    }

    outToFileXYZ( "./Results/" );
    printf( "---------> END: save ./Results/xyz*.asc\n" );

      // 目標パターンの設定

    printf( "---------> start initialization of Targets\n" );

    printf( "numOfFig: %d\n", beeParam.numOfFig );
    for ( numFig = 0; numFig < beeParam.numOfFig; numFig++ ) {
       switch ( figure[numFig].pattern ) {
   	 case -1: { initFigPGM( numFig, figure[numFig].fileName ); break; }
   	 case  0: { initFigPlus( numFig ); break; }
  	 case  1: { initFigCross( numFig ); break; }
  	 case  2: { initFigCircle( numFig ); break; }
       }
       fixFig( numFig );
	//        printFig( numFig );
    }

    printf( "---------> end initialization of Targets\n" );

    // 複眼への投影
          
    printf( "---------> start calculation projection image on Eye\n" );

    for ( numFig = 0; numFig < beeParam.numOfFig; numFig++ ) {
      if ( figure[numFig].show ) {
         proToEye( 0, beeParam.numOfOM, numFig );       // 右目への投影
	 proToEye( 1, beeParam.numOfOM, numFig );       // 左目への投影
      }
    }
    applySigmoid2( beeParam.numOfOM );

    printf( "---------> end calculation projection image on Eye\n" );

    // 画像処理層の計算

    //    printEye();

    //    printf( "---------> start calculation VPL1 response\n" );
    //    VPL1resp();
    //    printf( "---------> end calculation VPL1 response\n" );

    //    printf( "---------> start calculation VPL2 response\n" );
    //    VPL2resp();
    //    printf( "---------> end calculation VPL2 response\n" );

    // 計算結果の出力

    printf( "---------> start output results to ./Results\n" );
    outToFile( "./Results" );
    printf( "---------> end output results to ./Results\n" );

    // シミュレーション結果の作成

    if ( !strcmp(argv[3], "-plot") ) {
      strcpy( disDev, "tiff" );

      plotLeftEyeXZ( disDev, beeParam.numOfOM );
         printf( "---------> plot left eye XY\n" );
      plotRightEyeXZ( disDev, beeParam.numOfOM );
      plotBothEyeYZ( disDev, beeParam.numOfOM );
      plotBothEyeXY( disDev, beeParam.numOfOM );
      plotBothEyeXZ( disDev, beeParam.numOfOM );

      greyPlotBothEyeXZ( disDev, beeParam.numOfOM );
      greyPlotLeftEyeXZ( disDev, beeParam.numOfOM );
      greyPlotRightEyeXZ( disDev, beeParam.numOfOM );

      //      plotBothVPL1( disDev );

      //      plotBothVPL2( disDev, 0 );
      //      plotBothVPL2( disDev, 1 );
      //      plotBothVPL2( disDev, 2 );
      //      plotBothVPL2( disDev, 3 );
      //      plotBothVPL2( disDev, 4 );
    }
    saveVPLresp( time );

    return 0;
}
