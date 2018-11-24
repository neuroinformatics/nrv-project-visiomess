#define VERSION "Bee Vision Version 3.20           -- (c) Hidetoshi Ikeno --"

/*****************************************************************************

Bee Vision  - Simulation Program of Compound Eye Vision -

 ********************************************* (c) Hidetoshi Ikeno **********/

// rad -> deg�ؤ��Ѵ���deg -> rad�ؤ��Ѵ�

#define TO_DEG      180./M_PI
#define TO_RAD      M_PI/180.

// ʣ��ط��Υѥ�᡼��

#define NUM_CE       7500           // �Ĵ�(��¦)�κ����

// ʣ��ǡ����������

typedef struct {
  double r, th, ph;                  // �Ĵ�κ�ɸ
  double x, y, z;                    // �Ĵ��X, Y, Z��ɸ
  double alpha, beta;                // �Ĵ�λ��������٥��ȥ�
  double br;                         // �Ĵ�μ��Ƹ�����
  double UVr, Br, Gr;                // ���˦����
} compound_eye;

// ����������(VPL1)�ط��Υѥ�᡼��

#define NUM_VPL1       4000          // ��˦(��¦)�κ����
#define VPL1_CON_OM     100          // ��˦(��¦)�κ����

#define VPL1_MEM          5          // ��˦��������¸���

#define VPL1_RF_NUM       5          // ��������׿�
#define VPL1_RF_COEF      1.

// ��˦�ǡ����������

typedef struct {
  double r, th, ph;                  // ��˦�κ�ɸ
  double x, y, z;                    // ��˦��X, Y, Z��ɸ
  double alpha, beta;                // ��˦�λ��������٥��ȥ�
  double resp;                       // ��˦����
  int    conNumOfOM;                 // �Ĥʤ��äƤ���Ĵ��
  int    connectOM[VPL1_CON_OM];     // �Ĥʤ��äƤ���Ĵ��ֹ�
  int    respMode;                   // ��������  
                                     // 0:non EMD, 1:EMD
  int    RFtype;                     // ���������
                                     // 0:circle, 1:th+, 2:th-, 3:ph+,4: ph-
  double RFcoef;                     // �������
  double rfAngle;                    // ���������
  int    MEMlength;                  // ���α�����ɤ�����Ȥ��� 
} VPL1cell;

// ����������(VPL2)�ط��Υѥ�᡼��

#define NUM_VPL2       6000          // ��˦(��¦)�κ����
#define VPL2_CON_1      100          // ��˦(��¦)�κ����

#define VPL2_MEM          1          // ��˦��������¸���

#define VPL2_RF_NUM       3          // ��������׿�
#define VPL2_RF_COEF      1.

#define VPL2_DELAY        1          // VPL1�������˷׻�����Ȥ����٤�

// ��˦�ǡ����������

typedef struct {
  double r, th, ph;                  // ��˦�κ�ɸ
  double x, y, z;                    // ��˦��X, Y, Z��ɸ
  double alpha, beta;                // ��˦�λ��������٥��ȥ�
  double resp;                       // ��˦����
  int    conNumOfVPL1;               // �Ĥʤ��äƤ���Ĵ��
  int    connectVPL1[VPL2_CON_1];    // �Ĥʤ��äƤ���VPL1��˦�ֹ�
  int    respMode;                   // ��������  
                                     // 0:non EMD, 1:EMD
  int    RFtype;                     // ���������
                                     // 0:circle, 1:th+, 2:th-, 3:ph+,4: ph-
  double rfAngle;                    // ���������
  int    MEMlength;                  // ���α�����ɤ�����Ȥ��� 
} VPL2cell;

/******************************************************************************
  ��ɸ�޷�
******************************************************************************/

#define   N_FIGURE    5           // �󼨤���޷��ο�
#define   DOT_MAX     1000        // �޷����������ɥåȤκ����
#define   FNAME_LEN   1024        // �ե�����̾�κ���Ĺ

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
 �����ѿ�������
******************************************************************************/

// �ߥĥХ���ͭ�Υѥ�᡼��

typedef struct {

  double headR;             // �ߥĥХ�Ƭ��Ⱦ�� (mm)

  // ʣ��ط��Υѥ�᡼��
  double maxVC;             // �����濴������κ�Ĺ��Υ (mm)
  double minVC;             // �����濴������κ�û��Υ (mm)
  double venPh;             // �濴����겼¦�γ���(��)
  double dorPh;             // �濴������¦�γ���(��)
  double stepPh;            // ��ľ�����θĴ����ֳ��٥��ƥå�(��)
  double venLimit;          // ��ʿ�����θĴ������ˤ����ϰϳ���(��)��ʢ¦
  double dorLimit;          // ��ʿ�����θĴ������ˤ����ϰϳ���(��)����¦
  double frontTh;           // ��ʿ������������(��)
  double rearTh;            // ��ʿ�����θ����(��)

  double xPostMax, xAntMax; // ʣ���X������Ĺ�� (mm)��initEye3�ǻ���
  double rotAng, rotXoff, rotYoff; // XYʿ�̤Ǥβ�ž�Ѥ�᡼����initEye3�ǻ���

  double thW2, centerTh;
  double stepTh;            // ��ʿ�����θĴ����ֳ��٥��ƥå�(��)

  double omDeg;             // �Ĵ�λ������(��)
 
  double omVenMax, omDorMax;         // ʢ¦����¦�Ĵ�κ�������(��) 
  double omFrMax, omReMax;           // ���̡����̤κ�������(��) 

  double omRFcoef;          // �Ĵ�μ������
  double sigCoef;           // �Ĵ������sigmoid�ؿ��ǵ��ʲ�������η���

  int    numOfOM;           // �Ĵ�θĿ�

  // VPL1��Ϣ

  double VPL1rf_min;        // VPL1��˦�κǾ����������(��)
  double VPL1rf_max;        // VPL1��˦�κ�����������(��)
  int    numOfVPL1;         // VPL1��˦�θĿ�

  // VPL2��Ϣ

  double VPL2rf_min;        // VPL2��˦�κǾ����������(��)
  double VPL2rf_max;        // VPL2��˦�κ�����������(��)
  int    numOfVPL2;         // VPL2��˦�θĿ�

  // ����¾

  double flightAngle;       // ���Ƴ���

  int    numOfFig;         // �󼨤������ɸ���������

} parameters;
