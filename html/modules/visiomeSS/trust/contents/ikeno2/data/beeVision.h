#define VERSION "Bee Vision Version 3.20           -- (c) Hidetoshi Ikeno --"

/*****************************************************************************

Bee Vision  - Simulation Program of Compound Eye Vision -

 ********************************************* (c) Hidetoshi Ikeno **********/

// rad -> degへの変換、deg -> radへの変換

#define TO_DEG      180./M_PI
#define TO_RAD      M_PI/180.

// 複眼関係のパラメータ

#define NUM_CE       7500           // 個眼(片側)の最大数

// 複眼データ型の定義

typedef struct {
  double r, th, ph;                  // 個眼の座標
  double x, y, z;                    // 個眼のX, Y, Z座標
  double alpha, beta;                // 個眼の視線方向ベクトル
  double br;                         // 個眼の受容光強度
  double UVr, Br, Gr;                // 視細胞応答
} compound_eye;

// 画像処理層(VPL1)関係のパラメータ

#define NUM_VPL1       4000          // 細胞(片側)の最大数
#define VPL1_CON_OM     100          // 細胞(片側)の最大数

#define VPL1_MEM          5          // 細胞応答の保存枚数

#define VPL1_RF_NUM       5          // 受容野タイプ数
#define VPL1_RF_COEF      1.

// 細胞データ型の定義

typedef struct {
  double r, th, ph;                  // 細胞の座標
  double x, y, z;                    // 細胞のX, Y, Z座標
  double alpha, beta;                // 細胞の視線方向ベクトル
  double resp;                       // 細胞応答
  int    conNumOfOM;                 // つながっている個眼数
  int    connectOM[VPL1_CON_OM];     // つながっている個眼番号
  int    respMode;                   // 応答形態  
                                     // 0:non EMD, 1:EMD
  int    RFtype;                     // 受容野タイプ
                                     // 0:circle, 1:th+, 2:th-, 3:ph+,4: ph-
  double RFcoef;                     // 受容野係数
  double rfAngle;                    // 受容野角度
  int    MEMlength;                  // 過去の応答をどれだけ使うか 
} VPL1cell;

// 画像処理層(VPL2)関係のパラメータ

#define NUM_VPL2       6000          // 細胞(片側)の最大数
#define VPL2_CON_1      100          // 細胞(片側)の最大数

#define VPL2_MEM          1          // 細胞応答の保存枚数

#define VPL2_RF_NUM       3          // 受容野タイプ数
#define VPL2_RF_COEF      1.

#define VPL2_DELAY        1          // VPL1応答を基に計算するときの遅れ

// 細胞データ型の定義

typedef struct {
  double r, th, ph;                  // 細胞の座標
  double x, y, z;                    // 細胞のX, Y, Z座標
  double alpha, beta;                // 細胞の視線方向ベクトル
  double resp;                       // 細胞応答
  int    conNumOfVPL1;               // つながっている個眼数
  int    connectVPL1[VPL2_CON_1];    // つながっているVPL1細胞番号
  int    respMode;                   // 応答形態  
                                     // 0:non EMD, 1:EMD
  int    RFtype;                     // 受容野タイプ
                                     // 0:circle, 1:th+, 2:th-, 3:ph+,4: ph-
  double rfAngle;                    // 受容野角度
  int    MEMlength;                  // 過去の応答をどれだけ使うか 
} VPL2cell;

/******************************************************************************
  目標図形
******************************************************************************/

#define   N_FIGURE    5           // 提示する図形の数
#define   DOT_MAX     1000        // 図形を形成するドットの最大数
#define   FNAME_LEN   1024        // ファイル名の最大長

typedef struct {
  double centerX, centerY, centerZ;
  double angleX, angleY;
  int    dotX, dotY;
  double dotDiam;
  int    pattern;
  int    show;
  int    color;
  char   fileName[FNAME_LEN];

  struct {
    double  r, th, ph;
    double  x, y, z;
    double  br;
  } pixel[DOT_MAX][DOT_MAX];
} target;

/******************************************************************************
 共通変数の設定
******************************************************************************/

// ミツバチ固有のパラメータ

typedef struct {

  double headR;             // ミツバチ頭部半径 (mm)

  // 複眼関係のパラメータ
  double maxVC;             // 仮想中心点からの最長距離 (mm)
  double minVC;             // 仮想中心点からの最短距離 (mm)
  double venPh;             // 中心線より下側の角度(°)
  double dorPh;             // 中心線より上側の角度(°)
  double stepPh;            // 鉛直方向の個眼配置角度ステップ(°)
  double venLimit;          // 水平方向の個眼数一定にする範囲角度(°)、腹側
  double dorLimit;          // 水平方向の個眼数一定にする範囲角度(°)、背側
  double frontTh;           // 水平方向の前角度(°)
  double rearTh;            // 水平方向の後角度(°)

  double xPostMax, xAntMax; // 複眼のX方向の長さ (mm)、initEye3で使用
  double rotAng, rotXoff, rotYoff; // XY平面での回転ぱらめーた、initEye3で使用

  double thW2, centerTh;
  double stepTh;            // 水平方向の個眼配置角度ステップ(°)

  double omDeg;             // 個眼の視野角度(°)
 
  double omVenMax, omDorMax;         // 腹側、背側個眼の最大視野角(°) 
  double omFrMax, omReMax;           // 前面、後面の最大視野角(°) 

  double omRFcoef;          // 個眼の受容野係数
  double sigCoef;           // 個眼応答をsigmoid関数で規格化する時の係数

  int    numOfOM;           // 個眼の個数

  // VPL1関連

  double VPL1rf_min;        // VPL1細胞の最小受容野角度(°)
  double VPL1rf_max;        // VPL1細胞の最大受容野角度(°)
  int    numOfVPL1;         // VPL1細胞の個数

  // VPL2関連

  double VPL2rf_min;        // VPL2細胞の最小受容野角度(°)
  double VPL2rf_max;        // VPL2細胞の最大受容野角度(°)
  int    numOfVPL2;         // VPL2細胞の個数

  // その他

  double flightAngle;       // 飛翔角度

  int    numOfFig;         // 提示される目標画像の枚数

} parameters;
