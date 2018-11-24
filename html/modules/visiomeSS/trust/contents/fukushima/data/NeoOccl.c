
       /////////////////////////////////////////////////
       /////  Neocognitron        by K. Fukushima  /////
       /////        4 staged neteork               /////
       /////     Alphabet  with masking patterns   /////
       /////////////////////////////////////////////////

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

////  Prototype
int main(void);
double ***getp(			// memory for 1-D pointer array **u[L]
	int		L
	);
double *get1D(			// get memory for 1-D array m[N]
	int		N
	);
int *get1Di(			// get memory for 1-D int array m[N]
	int		N
	);
double **get2D(			// get memory for 2-D array u[N1][N2]
	int		N1,
	int		N2
	);
int **get2Di(			// get memory for 2-D int array m[N1][N2]
	int		N1,
	int		N2
	);
double ***geta3D(		// get addable memory for 3-D array u[K][N1][N2]
	int		K,			// initial array size
	int		N1,
	int		N2,
	int		Kmax		// maximum possible array size: u[Kmax][N1][N2]
	);
void add3D(				// add memory to 3-D array u[K][N1][N2]
	double	***u,		// (in) u = (double ***)malloc(sizeof(double **) * Kmax)
	int		Knew,		// new array size
	int		N1,
	int		N2,
	int		Kmax		// maximum possiboe array size
	);
double ****geta4D1(		// get addable memory for 1-D pointer array ***a[]
	int		Kmax		// maximum possible pointer array size: ***a[Kmax]
	);
void add4D2(			// add memory to 2-D pointer array **a[K][Kc]
	double	****a,		// (in) a = (double ****)malloc(sizeof(double *) * Kmax)
	int		Knew,		// new pointer array size: **a[Knew][Kc]
	int		Kc,
	int		Kmax		// maximum possible array size: **a[Kmax][Kc]
	);
void Sres(				// response of S-layer
	double	***us,		// (out) response of S-cells: us[Ks][Ns][Ns]
	double	*usmax,		// (out) max response of S-cell-planes: usmax[Ks]
	double	***uc,		// (in) response of C-cells: uc[Kc][Nc][Nc]
	double	*ucmax,		// (in) max response of C-cell-planes: ucmax[Kc]
	double	****as,		// (in) exc. connections to S-cells: as[Ks][Kc][Na][Na]
	double	**cs,		// (in) exc. connections to V-cells: cs[Na][Na]
	double	*bs,		// (in) inh. connections to S-cells: bs[Ks]
	double	**vs2,		// (work) response**2 of V-cells: vs2[Ns][Ns]
	int		Nc,			// size of the C-layer: (nc*2+1)
	int		Kc,			// number of cell-planes in C-layer
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		Ks,			// numberof cell-planes in S-layer
	int		Na,			// size of the connections (as & cs): (na*2+1)
	double	theta		// threshold of an S-cell
	);
void Cres1(				// response of C-layer (get max instead of sum)
	double	***uc,		// (out) response of C-cells: uc[K][Nc][Nc]
	double	*ucmax,		// (out) max response of C-cell-planes: ucmax[K]
	double	***us,		// (in) response of S-cells: us[K][Ns][Ns]
	double	*usmax,		// (in) max response of S-cell-planes: usmax[K]
	double	**ac,		// (in) exc. connections to C-cells: ac[Nd][Nd]
	int		*ncmax,		// (work) upper bound of the conection: ncmax[Ns]
	int		*ncmin,		// (work) lower bound of the conection: ncmin[Ns]
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		ms,			// step of S-cells
	int		Nc,			// size of the C-layer: (nc*2+1)
	int		mc,			// step of C-cells
	int		K,			// number of cell-planes in S- and C-layers (K=Ks=Kc)
	int		Nd			// size of the connections (ac): (nd*2+1)
	);
void CresL(				// response of C-layer without lateral inhibition
	double	***uc,		// (out) response of C-cells: uc[Kc][1][1]
	double	*ucmax,		// (out) max response of C-cell-planes: ucmax[Kc]
	double	*usmax,		// (in) max response of S-cell-planes: usmax[Ks]
	int		*cat,		// (in) category of the S-plane: cat[Ks]
	int		Ks,			// number of cell-planes in S-layers (Ks)
	int		Kc			// number of cell-planes in C-layers (Kc)
	);
void onoff(				// response of on- & off-center cell layers
	double	***uc,		// (out) response of on- & off-center cells: uc[2][Nc][Nc]
	double	*ucmax,		// (out) max response of on- & off- cells: ucmax[2]
	double	**us,		// (in) response of receptor cells: us[Ns][Ns]
	double	**ag,		// (in) connections for on-center: ag[Ng][Ng]
	int		Ns,			// size of the receptor layer: (ns*2+1)
	int		Nc,			// size of the on- & off-center cell layer: (nc*2+1)
	int		Ng			// size of the connections (ag): (ng*2+1)
	);
void make_cg(			// make connections for on-center
	double	**cg,		// (out) Connections: cg[Ng][Ng]
	double	Ag,			// radius of the off-periphery (connect. area)
	double	Ag0,		// radius of the on-center component
	double	gamcg		// spatial decay at x=Ag
	);
void make_c(			// make connections (spatial weight)
	double	**c,		// (out) Connections: c[Na][Na]
	double	A,			// radius of the connectable area
	double	gamma,		// spatial decay at x=A
	double  co			// value of c[][] at the center
	);
void norm_c(			// make normalized connections (spatial weight)
	double	**c,		// (out) Connections: c[Na][Na]
	double	A,			// radius of the connectable area
	double	gamma,		// spatial decay at x=A
	double  cno			// strength of the connections
	);
void angle(				// draw an angle of ang degree
	double	**u,		// (out) generated pattern: u[N][N]
	int		N,			// size of the layer: (n*2+1)
	int		K,			// number of different orientations
	int		k,			// sequence number of the orientation of the edge
	double	ang,		// angle (in degree) of the bend
	double	offset		// offset of the senter of the pattern
	);
void edge(
	double	**u,		// (i/o) generated pattern: u[N][N]
	int		N,			// size of the layer: (n*2+1)
	double	xs,
	double	ys,			// edge from (xs,ys) to (xe,ye)
	double	xe,
	double	ye
	);
int Sorg(				// self-organization of S-layer
	double	****as,		// (out) exc. connections to S-cells: as[Ks][Kc][Na][Na]
	double	*bs,		// (out) inh. connections to S-cells: bs[Ks], new Ks
	double	***uc,		// (in) response of C-cells: uc[Kc][Nc][Nc]
	double	*ucmax,		// (in) max response of C-cell-planes: ucmax[Kc]
	double	**cs,		// (in) spatial weight: cs[Na][Na]
	double	**asini,	// (in) exc. initial connections to S-cells: as[Na][Na]
	double	**cl,		// (in) connect. for lat.inh. from us to usini: cl[Nl][Nl]
	double	***us,		// (work) response of S-cells: us[Ks][Ns][Ns], old Ks
	double	*usmax,		// (work) max response of S-cell-planes: usmax[Ks], old Ks
	double	**vs2,		// (work) response**2 of V-cells: vs2[Ns][Ns]
	double	**usini,	// (work) response of seed-selecting plane: usini[Ns][Ns]
	double	**work,		// (work) for wmax[][] & us[Ks][][]: work[Ns][Ns]
	int		**kwmax,	// (work) kwmax[Ns][Ns]
	int		*iseed,		// (work) iseed[Ks], old Ks
	int		*jseed,		// (work) jseed[Ks], old Ks
	int		Nc,			// size of the C-layer: (nc*2+1)
	int		Kc,			// number of cell-planes in C-layer
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		Ks,			// number of cell-planes in S-layer, old value
	int		Na,			// size of the connections (as & cs): (na*2+1)
	int		Nasini,		// size of the connect. asini: (nasini*2+1)
	double	D,			// radius of competition area
	double	Al,			// radius of lat.inh. from us to usini
	double	qs,			// parameter determining the speed of learning
	double	theta,		// threshold of an S-cell
	int		Ksmax,		// maximum possible Ks
	double	thrini		// threshold for cutting usini
	);
void delta(				// strengthen connections
	double	****as,		// (out) exc. connections to S-cells: as[Ks][Kc][Na][Na]
	double	*bs,		// (out) inh. connections to S-cells: bs[Ks]
	double	***uc,		// (in) response of C-cells: uc[Kc][Nc][Nc]
	double	*ucmax,		// (in) max response of C-cell-planes: ucmax[Kc]
	double	**cs,		// (in) spatial weight: cs[Na][Na]
	int		Na,			// size of the connections (as & cs): (na*2+1)
	int		Nc,			// size of the C-layer: (nc*2+1)
	int		Kc,			// numberof cell-planes in C-layer
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		kseed,		// cell-plane of the seed cell
	int		iseed,		// x-coordinate of the seed cell
	int		jseed,		// y-coordinate of the seed cell
	double	qs			// parameter determining the speed of learning
	);
void seed(				// select seed cells
	int		*iseed,		// (out) x-coordinate of the k-th cell-plane: iseed[Ks]
	int		*jseed,		// (out) y-coordinate of the k-th cell-plane: jseed[Ks]
	double	***us,		// (in) response of S-cells: us[Ks][Ns][Ns]
	double	**wmax,		// (work) working area: wmax[Ns][Ns]
	int		**kwmax,	// (work) working area: kwmax[Ns][Ns]
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		Ks,			// number of cell-planes in S-layer
	double	D			// radius of competition area
	);
void Sresini(			// response of seed-selecting plane
	double	**usini,	// (out) response of seed-selecting plane: usini[Ns][Ns]
	double	***uc,		// (in) response of C-cells: uc[Kc][Nc][Nc]
	double	*ucmax,		// (in) max response of C-cell-planes: ucmax[Kc]
	double	**asini,	// (in) exc. initial connections to S-cells: as[Na][Na]
	int		Nc,			// size of the C-layer: (nc*2+1)
	int		Kc,			// number of cell-planes in C-layer
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		Na,			// size of the connections (asini, as & cs): (na*2+1)
	double	thrini		// threshold for cutting usini
	);
void seedini(			// select seed cells
	int		*iseed0,	// (out) x-coordinate of the k-th cell-plane: iseed0[1]
	int		*jseed0,	// (out) y-coordinate of the k-th cell-plane: jseed0[1]
	double	**usini,	// (in) response of S-cells: usini[Ns][Ns]
	int		Ns			// size of the S-layer: (ns*2+1)
	);
void lat(				// lateral inhibition from uin to uout
	double	**ut,		// (i/o) cell-plane to be inhibited: ut[N][N]
	double	**uf,		// (in) inhibiting cell-plane: uf[N][N]
	double	**cl,		// (in) connections for lateral inhibition: cl[Nl][Nl]
	int		N,			// size of the layer: (n*2+1)
	double	Al			// radius of lat.inh.
	);
void copyplane(			// copy the response of a cell-plane
	double	**ut,		// (out) copied to this cell-plane: ut[N][N]
	double	*utmax,		// (out) max value of ut[1]
	double	**uf,		// (in) copied from this cell-plane: uf[N][N]
	int		N			// size of the layer: (n*2+1)
	);
int SorgL(				// self-organization of S-layer
	double	****as,		// (out) exc. connections to S-cells: as[Ks][Kc][Na][Na]
	double	*bs,		// (out) inh. connections to S-cells: bs[Ks], new Ks
	int		*cat,		// (out) category of the S-plane: cat[Ks]
	int		Cat,		// (in) category of the training pattern
	double	***uc,		// (in) response of C-cells: uc[Kc][Nc][Nc]
	double	*ucmax,		// (in) max response of C-cell-planes: ucmax[Kc]
	double	**cs,		// (in) spatial weight: cs[Na][Na]
	double	**asini,	// (in) exc. initial connections to S-cells: as[Na][Na]
	double	***us,		// (work) response of S-cells: us[Ks][Ns][Ns], old Ks
	double	*usmax,		// (work) max response of S-cell-planes: usmax[Ks], old Ks
	double	**vs2,		// (work) response**2 of V-cells: vs2[Ns][Ns]
	double	**usini,	// (work) response of seed-selecting plane: usini[Ns][Ns]
	double	**work,		// (work) for wmax[][] & us[Ks][][]: work[Ns][Ns]
	int		Nc,			// size of the C-layer: (nc*2+1)
	int		Kc,			// number of cell-planes in C-layer
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		Ks,			// number of cell-planes in S-layer, old value
	int		Na,			// size of the connections (as & cs): (na*2+1)
	int		Nasini,		// size of the connect. asini: (nasini*2+1)
	double	qs,			// parameter determining the speed of learning
	double	theta,		// threshold of an S-cell
	int		Ksmax,		// maximum possible Ks
	double	thrini		// threshold for cutting usini
	);
void seedL(				// select seed cells
	int		*iseed0,	// (out) x-coordinate of the k-th cell-plane: iseed0[1]
	int		*jseed0,	// (out) y-coordinate of the k-th cell-plane: jseed0[1]
	int		*kseed0,	// (out) cell-plane of the seed cell: kseed0[1]
	int		*cat,		// (in) category of the S-plane: cat[Ks]
	int		Cat,		// (in) category of the training pattern
	double	***us,		// (in) response of S-cells: us[Ks][Ns][Ns]
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		Ks			// number of cell-planes in S-layer
	);
void rwcon(				// read/write connections
	FILE	*fpC,		// (in) file pointer
	char	*fnameC,	// (in) file name
	double	*****as,	// (i/o) exc. connect. to S-cells: as[L][Ks][Kc][Na][Na]
	double	**bs,		// (i/o) inh. connect. to S-cells: bs[L][Ks]
	int		**cat0,		// (i/o) category of the cell-plane UsL: cat0[1][KsL]=cat[KsL]
	int		*Na,		// (in) size of connect. as
	int		*Kc,		// (i/o) no. of C-cell-planes: Kc[L+1]
	int		*Ks,		// (i/o) no. of S-cell-planes: Ks[L]
	int		*Mas,		// (out) no. of active as[L][Ks][Kc]: Mas[L]
	int		L,			// number of stages
	int		learn		// switch:  if (learn==1) write, else read
	);
void printu(
	FILE	*fp,		// (in) file pointer
	double	***u,		// (in) layer to be printed: u[K][N][N]
	double	*umax,		// (in) max response of cell-planes: umax[K]
	int		N,			// size of a cell-plane: (n*2+1)
	int		K,			// number of cell-planes
	char	title[],	// title to be printed
	int		l			// stage number to be printed in the title
	);
void outH1(				// hexadecinmal output of the response of a layer
	FILE	*fp,		// (in) file pointer
	double	***u,		// (in) layer to be printed: u[K][N][N]
	double	*umax,		// (in) max response of cell-planes: umax[K]
	int		N,			// size of a cell-plane: (n*2+1)
	int		K,			// number of cell-planes
	char	title[],	// title to be printed
	int		l			// stage number to be printed in the title. if (l<0) no print
	);
void printuadd(			// print sum of k1-th to k2-th cell-planes
	FILE	*fp,		// (in) file pointer
	double	***u,		// (in) layer to be printed: u[K][N][N]
	double	*umax,		// (in) max response of cell-planes: umax[K]
	int		N,			// size of a cell-plane: (n*2+1)
	char	title[],	// title to be printed
	int		l,			// stage number to be printed in the title. if (l<0) no print
	int		k1,			// added cell-planes from k1
	int		k2			// added cell-planes to k2
	);
void pat(					// generate a pattern from a buffer
	double	**u,			// (out) generated pattern: u[N][N]
	double	*umax,			// (out) max value of the pattern umax[1]
	unsigned char	**patP,	// pattern beffer patP[Npat][N*Lchar+1]
	int		Npat,			// Total number of pat. in buffer pat[Npat][N][N]
	int		N,				// size of the layer: (n*2+1)
	int		t				// pattern number
	);
unsigned char **patread(	// create buffer pat[Npat][Nchar] and read patterns
	char	*fnameP,		// (in) file name
	int		*NpatAddress,	// (out) &Npat = Total number of pat.: Npat=NpatAddress[0]
	int		N				// size of the layer: (n*2+1)
	);
void Ssup(				// suppressed response of S-layer
	double	***us,		// (i/o) response of S-cells: us[Ks][Ns][Ns]
	double	*usmax,		// (out) max response of S-cell-planes: usmax[Ks]
	double	***umask,	// (in) masking pattern: unask[1][Ns][Ns]
	double	**csup,		// (in) connections for blurring masking pat: csup[Na][Na]
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		Ks,			// numberof cell-planes in S-layer
	int		Na			// size of the connections csup: (na*2+1)
	);
void patmask(			// subtract patterns
	double	**u,		// (out) generated pattern: u[N][N]
	double	*umax,		// (out) max value of the pattern umax[1]
	double	**upat,		// (in) masked pattern: upat[N][N]
	double	**umask,	// (in) masking pattern: umask[N][N]
	double	amask,		// amplitude (or gain) for umask[n][n]
	int		N			// size of the layer: (n*2+1)
	);

// *************************************************************************


int main(void) {

  ////  Parameters

	int		L = 4;				// number of stages

		// layer:	   U0 UG S1 C1 S2 C2 S3 C3 S4 C4
	int		N0      =  65;								// size of input layer U0: n0*2+1
	int		Nc[]	= {   65,   35,   21,   11,    1};	// size of Uc(or U0) cell-plane: (nc*2+1),  Nc[L+1]
	int		Ns[]	= {      65,   35,   21,    7   };	// size of Us cell-planes: (ns*2+1),  Ns[L]
	int		ms[]	= {       1,    1,    1,    1   };	// Cres: step of S-cells,  ms[L]
	int		mc[]	= {          2,    2,    2,    1};	// Cres: step of C-cells,  mc[L]

	double	Ag		=     3.9;							// radius of connect. ag (off-surround): Ng=((int)Ag)*2+1
	double	Ago		=     1.5;							// radius of on-center of ag
	double	As[]	= {     3.9,  3.9,  3.9,  3.9   };	// radius of connect. as: Na=((int)As)*2+1, As[L]
	double	Ac[]	= {        3.9,  3.9,  3.9,  3.9};	// radius of connect. ac: Nd=((int)Ac)*2+1, Ac[L]
	double	D[]		= {     0.0,  2.1,  2.1,  8.5   };	// radius of competition area,  D[L]
	double	Asini[]	= {     3.9,  3.9,  3.9,  3.9   };	// radius of connect. asini: Nasini=((int)Asini)*2+1, Asini[L]
	double	Al[]	= {     0.0,  4.1,  4.1,  8.5   };	// radius of lat.inh. cl: Nl=((int)Al)*2+1, Al[L]

	double	gamcg	=  0.1;								// make_cg: spatial decay of cg at x=Ag
	double	gamS[]	= {     0.7,  0.7,  0.7,  0.7   };	// make_c: spatial decay, gammaS,  gamS[L]
	double	coS[]	= {     1.0,  1.0,  1.0,  1.0   };	// make_c: value at the center,  coS[L]
	double	gamSini[]={     0.7,  0.7,  0.7,  0.7   };	// make_c: spatial decay,  gamSini[L]
	double	coSini[]= {   0.0001,0.0001,0.0001,0.0001   };	// make_c: value at the center,  coSini[L]
	double	gamC[]	= {        0.7,  0.7,  0.7,  0.7};	// make_c: spatial decay, gammaC,  gamC[L]
	double	coC[]	= {        4.0,  4.0,  4.0,  1.0};	// make_c: value at the center,  coC[L]
	double	gaml[]	= {     0.0,  0.7,  0.7,  1.0   };	// norm_c: spatial decay, lat.inh. cl,  gaml[L]
	double	cnol[]	= {     0.0,  1.0,  1.0,  1.0   };	// norm_c: strength of lat.inh. cl,  cnol[L]
	double	thetal[]= {    0.00, 0.80, 0.80, 0.70   };	// Sres: threshold of S-cells (learning),  theta[L]
	double	thetar[]= {    0.63, 0.57, 0.49, 0.30   };	// Sres: threshold of S-cells (recognition),  theta[L]
	double	qs[]	= {     5.0,  0.5,  0.5,  0.5   };	// speed of learning,  qs[L]
	double	thrini[]= {     0.0,  0.4,  0.4,  0.4   };	// Sresini: threshold for cutting usini,  thrini[L]

	double	amask = 0.3;		// intensity of masking pattern
	double	Asup = 1.9;			// radius of supressing connection csup: Nsup=((int)Asup)*2+1
	double	gamsup = 0.7;		// make_c: spatial decay, gammaC
	double	cosup = 1.0;		// make_c: value at the center of csup[][]

	int		Ks[]	= {      16,   69,   72,   26   };	// no. of S-cell-planes, init.val., changeable,  Ks[L]
	int		Ksmax[]	= {      16,  200,  300,  300   };	// max. possible no. of S-cell-planes, changeable in test,  Ksmax[L+1]
	int		Kc[]	= {    2,   16,    0,    0,   26};	// no. of C-cell-planes, init.val., changeable,  Kc[L+1]
	int		repeat[]= {       1,    4,    4,    4   };	// no. of repetition / pat. in the learning,  repeat[L]

	int		learn = 1;			// learn=1: learning and test recognition,  =0: test recognition without learning
//	int		learn = 0;			// learn=1: learning and test recognition,  =0: test recognition without learning
//	int		ifpN = 0;			// =0: no output to ps nor eps files
	int		ifpN = 1;			// =1: separate eps files
	//	int		ifpN = 2;			// =2: all data in one ps file
	int		iprl[]	= { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	// file output control in the learning
//	int		iprl[]	= { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};	// file output control in the learning
	int		iprt[]	= { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	// file output control in the test (==2: printuadd)
//	int		iprt[]	= { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};	// file output control in the test (==2: printuadd)
//	int		iprt[]	= { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};	// file output control in the test (==2: printuadd)

//	int		tpm[][2] =	{{3,3}, {6,6}, {6,7}, {7,8}, {7,9}, {-1,-1}};	// D, UJ -> U, UJ -> J, HE -> H, HE -> E
	int		tpm[][2] =	{{0,0}, {1,1}, {2,2}, {3,3}, {4,4}, {5,5},	// A, B, C, D, E, F
						 {6,6}, {6,7},								// UJ -> U, UJ -> J
						 {7,8}, {7,9},								// HE -> H, HE -> E
						 {-1,-1}};									// end
								// combination of maskee (upat) & masker (umask).  (-1)=(end)


	char	fnamea[] = "res.dat";			// (w) output file (fpa: response, ASCII)
	char	fnameNhead[] = "Header.dat";	// (r) header of fnameN (fpNh)
	char	fnameN[] = "out   .eps";		// (w) hexadecimal output (fpN: response)
	char	fnameNall[] = "outall.ps";		// (w) output (fpN), all responses together
	char	fnameC[] = "connect.dat";		// (r/w) connections (fpC)
	char	fnamePL[] = "PatLearn.dat";		// (r) Learning pattern set (patL)
	char	fnamePT[] = "PatTest.dat";		// (r) Test pattern set (patT) = target pat. to be occluded
	char	fnamePM[] = "PatMask.dat";		// (r) Masking pattern set

   // memories for parameters
	int		Ng = ((int) Ag) * 2 + 1;	// size of connect. for on-center ag[Ng][Ng]
	int		*Na;		// size of connect. as & cs:  Na=((int)As)*2+1,  Na[L]
	int		*Nd;		// size of connect. ac:  Nd=((int)Ac)*2+1,  Nd[L]
	int		*Nasini;	// size of connect. asini: Nasini=((int)Asini)*2+1, Nasini[L]
	int		*Nl;		// size of lat.inh. cl:  Nl=((int)Al)*2+1,  Nl[L]
	int		*Mas;		// no. of active as[L][Ks][Kc]: Mas[L]
	int		Nsup = ((int) Asup) * 2 + 1;	// size of supressing connect. csup[Nsup][Nsup]

   // memories for fixed connections
	double	**cg;		// connect. of on-center: cg[Ng][Ng]
	double	***cs;		// exc. connect. to V-cells: cs[L][Na][Na]
	double	***ac;		// exc. connect. to C-cells: ac[L][Nd][Nd]
	double	***asini;	// exc. initial connect. to S-cells: asini[L][Nasini][Nasini]
	double	***cl;		// lat.inh. from us to usini: cl[L][Nl][Nl]
	double	**csup;		// Ssup: supressing connections from masking pat: csup[Nsup][Nsup]

   // working memories commonly used for all stages -- fixed size
	int		*ncmax;		// (work) upper bound of the conection: ncmax[NsMAX]
	int		*ncmin;		// (work) lower bound of the conection: ncmin[NsMAX]
	double	**vs2;		// (work) response**2 of V-cells: vs2[NsMAX][NsMAX]
	double	**usini;	// (work) response of seed-selecting plane: usini[NsMAX][NsMAX]
	double	**work;		// (work) for wmax[][] & us[Ks][][]: work[NsMAX][NsMAX]
	int		**kwmax;	// (work) kwmax[NsMAX][NsMAX]
	int		*iseed;		// (work) iseed[KsMAX], old Ks
	int		*jseed;		// (work) jseed[KsMAX], old Ks

   // memories for responses -- fixed
	double	***u0;		// response of input layer: u0[N0][N0]
	double	u0max[1];	// max response of input layer
	int		**mat;		// confusion matrix: mat[KcL][KcL+1]
	double	***upat;	// masked patern: upat[N0][N0]
	double	upatmax[1];	// max value of masked patern
	double	***umask;	// masking patern: umask[1][N0][N0]
	double	umaskmax[1];// max value of masking pattern

   // memories for responses -- expandable
	double	****us;		// response of S-cells: us[L][Ks][Ns][Ns]
	double	**usmax;	// max response of S-cell-planes: usmax[L][Ks]
	double	****uc;		// response of C-cells: uc[L][Kc][Nc][Nc]
	double	**ucmax;	// max response of C-cell-planes: ucmax[L][Kc]
	int		*cat;		// category of the cell-plane in UsL: cat[KsL]

   // memories for connections -- expandable
	double	*****as;	// exc. connect. to S-cells: as[L][Ks][Kc][Na][Na]
	double	**bs;		// inh. connect. to S-cells: bs[L][Ks]

   // memories for pattern buffers -- expandable ( alocated in patread() )
	unsigned char	**patL;		// Learning Pattern set (patL)
	unsigned char	**patT;		// Test Pattern set (patT)
	unsigned char	**patM;		// Masking Pattern set (patM)
	int		NpatL;				// Total number of pat. in patL[NpatL][Nchar]
	int		NpatT;				// Total number of pat. in patT[NpatT][Nchar]
	int		NpatM;				// Total number of pat. in patM[NpatM][Nchar]


   // working
	int		NsMAX;				// NsMAX=max(Ns[l]) for l=0,1,..,L-1
	int		KsMAX;				// KsMAX=max(Ksmax[l]) for l=0,1,..,L-1
	FILE	*fpa = NULL;		// (w) file pointer (response, ASCII)
	FILE	*fpN = NULL;		// (w) file pointer (response, hexadecimal)
	FILE	*fpNh = NULL;		// (r) file pointer (header of fpN file)
	FILE	*fpC = NULL;		// (r/w) file pointer (connections)
	char	linebuf[101];		// line buffer for copying data to fpN
	int		l, ll, t, k, Cat, tt, ttt, ipage, Pages, ipr;


	/// get array and set parameters
	Na = get1Di(L);				// size of connect. as & cs: Na[L]
	for (l = 0; l < L; l++)  Na[l] = ((int) As[l]) * 2 + 1;

	Nd = get1Di(L);				// size of connect. ac: Nd[L]
	for (l = 0; l < L; l++)  Nd[l] = ((int) Ac[l]) * 2 + 1;

	Nasini = get1Di(L);			// size of lat.inh. asini: Nasini[L]
	for (l = 0; l < L; l++)  Nasini[l] = ((int) Asini[l]) * 2 + 1;

	Nl = get1Di(L);				// size of lat.inh. cl: Nl[L]
	for (l = 0; l < L; l++)  Nl[l] = ((int) Al[l]) * 2 + 1;

	Mas = get1Di(L);			// no. of active as[L][Ks][Kc]: Mas[L]


  ////  get memory for arrays

  ///  fixed connections -- get memory & calculate
	cg = get2D(Ng, Ng);
	make_cg(cg, Ag, Ago, gamcg);

	cs = getp(L);
	for (l = 0; l < L; l++) {
		cs[l] = get2D(Na[l], Na[l]);
		make_c(cs[l], As[l], gamS[l], coS[l]);
	}

	ac = getp(L);
	for (l = 0; l < L; l++) {
		ac[l] = get2D(Nd[l], Nd[l]);
		make_c(ac[l], Ac[l], gamC[l], coC[l]);
	}

	as = (double *****)getp(L);		// actual memories will be allocated later
	bs = (double **)getp(L);		// actual memories will be allocated later

	if (learn == 1) {
		asini = getp(L);
		for (l = 0; l < L; l++) {
			asini[l] = get2D(Nasini[l], Nasini[l]);
			make_c(asini[l], Asini[l], gamSini[l], coSini[l]);
		}

		cl = getp(L);
		for (l = 0; l < L; l++) {
			cl[l] = get2D(Nl[l], Nl[l]);
			norm_c(cl[l], Al[l], gaml[l], cnol[l]);
		}
	}

	csup = get2D(Nsup, Nsup);
	make_c(csup, Asup, gamsup, cosup);

   // memories for responses -- fixed
	u0 = geta3D(1, N0, N0, 1);
	mat = get2Di(Kc[L], Kc[L] + 1);
	upat = geta3D(1, N0, N0, 1);
	umask = geta3D(1, N0, N0, 1);

   // memories for responses -- memory for arrays will be allocated later
	us = (double ****)getp(L);
	usmax = (double **)getp(L);
	uc = (double ****)getp(L+1);	// memory(l>0) will be allocated after learning of us
	uc[0] = geta3D(Kc[0], Nc[0], Nc[0], Kc[0]);
	ucmax = (double **)getp(L+1);	// memory(l>0) will be allocated after learning of us
	ucmax[0] = get1D(Kc[0]);

   // working memories commonly used for all stages -- fixed size
	NsMAX = 0;
	for (l = 0; l < L; l++) {
		if (Ns[l] > NsMAX)  NsMAX = Ns[l];
	}
	ncmax = get1Di(NsMAX);
	ncmin = get1Di(NsMAX);
	vs2 = get2D(NsMAX, NsMAX);

  /// get memories for learning (including test after learning)
	if (learn == 1) {

   // working memories for learning used commonly in all stages -- fixed size
		KsMAX = 0;
		for (l = 0; l < L; l++) {
			if (Ksmax[l] > KsMAX)  KsMAX = Ksmax[l];
		}
		usini = get2D(NsMAX, NsMAX);
		work = get2D(NsMAX, NsMAX);
		kwmax = get2Di(NsMAX, NsMAX);
		iseed = get1Di(KsMAX);
		jseed = get1Di(KsMAX);

   // memories for variable connections -- fixed to the maximum possible values
		for (l = 0; l < L; l++) {
			bs[l] = get1D(Ksmax[l]);
		}

   // memories for responses -- fixed to the maximum possible values
		for (l = 0; l < L; l++) {
			usmax[l] = get1D(Ksmax[l]);
		}
		cat = get1Di(Ksmax[L-1]);

   // memories for responses -- expandable
		for (l = 0; l < L; l++) {
			us[l] = geta3D(Ks[l], Ns[l], Ns[l], Ksmax[l]);	// may be expanded after Sorg
		}

   // memories for variable connections -- expandable
		for (l = 0; l < L; l++) {
			as[l] = geta4D1(Ksmax[l]);	// memory will be allocated in Sorg
		}
	}


   // open file "fnamea"
	ipr = 0;
	for (l = 0; l < L * 2 + 2; l++) {
		if (iprl[l] > 0)  ipr = 1;
		if (iprt[l] > 0)  ipr = 1;
	}
	if (ipr == 1) {
		if ((fpa = fopen(fnamea, "w")) == NULL) {
			printf("file open error fpa\n");
			exit(1);
		}
	}

  ////  start learning
	if (learn == 1) {
	   // read file "fnamePL" (NpatL is read here)
		patL = patread(fnamePL, &NpatL, N0);

	   // Train the first layer (Us1, i.e., ll=0) to detect edges
		add4D2(as[0], Ks[0], Kc[0], Ks[0]);	// create pointer array as[0][Ks[0]][Kc[0]]
		for (k = 0; k < Ks[0]; k++) {
			angle(u0[0], N0, Ks[0], k, 180.0, 0.0);		// generate a straight edge
			onoff(uc[0], ucmax[0], u0[0], cg, N0, Nc[0], Ng);
			delta(as[0], bs[0], uc[0], ucmax[0], cs[0], Na[0], Nc[0], Kc[0], Ns[0],
						k, Ns[0]/2, Ns[0]/2, qs[0]);
		}
		uc[1] = geta3D(Kc[1], Nc[1], Nc[1], Kc[1]);	// get memory for uc
		ucmax[1] = get1D(Kc[1]);					// get memory for ucmax

		for (ll = 1; ll < L; ll++) {	   // Learning of Us(ll+1)
			Ks[ll] = 0;
			for (t = 0; t < repeat[ll] * NpatL; t++) {
				pat(u0[0], u0max, patL, NpatL, N0, t);
				if (ll == 1  &&  iprl[0] == 1) {
					fprintf(fpa, "\nLEARNING FOR LAYER %d,   time=%d\n", ll + 1, t);
					printu(fpa, u0, u0max, N0, 1, "U", 0);
				}
				onoff(uc[0], ucmax[0], u0[0], cg, N0, Nc[0], Ng);
				if (ll == 1  &&  iprl[1] == 1) {
					printu(fpa, uc[0], ucmax[0], Nc[0], 2, "UG", -1);
				}
				for (l = 0; l < ll; l++) {
					Sres(us[l], usmax[l], uc[l], ucmax[l], as[l], cs[l], bs[l], vs2, 
							Nc[l], Kc[l], Ns[l], Ks[l], Na[l], thetar[l]);
					if (l == ll-1  &&  iprl[l*2+2] == 1) {
						fprintf(fpa, "\nLEARNING FOR LAYER %d,   time=%d\n", ll + 1, t);
						printu(fpa, us[l], usmax[l], Ns[l], Ks[l], "Us", l+1);
					}
					Cres1(uc[l+1], ucmax[l+1], us[l], usmax[l], ac[l], ncmax, ncmin, 
							Ns[l], ms[l], Nc[l+1], mc[l], Kc[l+1], Nd[l]);
					if (l == ll-1  &&  iprl[l*2+3] == 1) {
						fprintf(fpa, "\nLEARNING FOR LAYER %d,   time=%d\n", ll + 1, t);
						printu(fpa, uc[l+1], ucmax[l+1], Nc[l+1], Kc[l+1], "Uc", l+1);
					}
				}

				if (ll != L - 1) {
					Ks[ll] = Sorg(as[ll], bs[ll], uc[ll], ucmax[ll], 
							cs[ll], asini[ll], cl[ll], us[ll], usmax[ll], 
							vs2, usini, work, kwmax, iseed, jseed, 
							Nc[ll], Kc[ll], Ns[ll], Ks[ll], Na[ll], Nasini[ll],
							D[ll], Al[ll], qs[ll], thetal[ll], Ksmax[ll], thrini[ll]);
					Kc[ll+1] = Ks[ll];
				}
				else {
					Cat = t % Kc[L];
					Ks[ll] = SorgL(as[ll], bs[ll], cat, Cat, uc[ll], ucmax[ll], 
							cs[ll], asini[ll], us[ll], usmax[ll], vs2, usini, work, 
							Nc[ll], Kc[ll], Ns[ll], Ks[ll], Na[ll], Nasini[ll],
							qs[ll], thetal[ll], Ksmax[ll], thrini[ll]);
				}
				add3D(us[ll], Ks[ll], Ns[ll], Ns[ll], Ksmax[ll]);		// add memory to us
				printf("   Learned:    layer=%d,    t=%d,    Ks=%d\n", ll+1, t, Ks[ll]);
				if (ipr == 1)  fprintf(fpa, "   Learned:    layer=%d,    t=%d,    Ks=%d\n", ll+1, t, Ks[ll]);
			}
			uc[ll+1] = geta3D(Kc[ll+1], Nc[ll+1], Nc[ll+1], Kc[ll+1]);	// get memory for uc
			ucmax[ll+1] = get1D(Kc[ll+1]);								// get memory for ucmax
			printf(" Finished learning of layer %d,    Ks=%d\n\n", ll+1, Ks[ll]);
			if (ipr == 1) {
				fprintf(fpa, " Finished learning of layer %d,    Ks=%d\n\n", ll+1, Ks[ll]);
				fprintf(fpa, "################################################################################\n\n");
			}
		}
		printf("\nLearning Completed\n");
	}


  ////  read/write connections  ===>  get Mas arrays [Na][Na] when read
   // Also get memories for as, bs and cat, when read (recognition)
	rwcon(fpC, fnameC, as, bs, &cat, Na, Kc, Ks, Mas, L, learn); 	// if (learn==1) write, else read

  /// get memories for responses, in case of recognition without learning
	if (learn != 1) {
		for (l = 0; l < L; l++) {
			us[l] = geta3D(Ks[l], Ns[l], Ns[l], Ks[l]);
			usmax[l] = get1D(Ks[l]);
			uc[l+1] = geta3D(Kc[l+1], Nc[l+1], Nc[l+1], Kc[l+1]);
			ucmax[l+1] = get1D(Kc[l+1]);
		}
	}

  ////  test recognition
	if (ipr == 1) {
		fprintf(fpa, "Scale of the network:\n");
		for (l = 0; l < L; l++) {
			fprintf(fpa, "    Stage %d:        Ks = %d,      Mas = %d\n", l+1, Ks[l], Mas[l]);
		}
		fprintf(fpa, "\n");
	}


   ///  Test responses to masked patterns

   // read file "fnamePT" and "fnamePM" (NpatT and NpatM are read here)
	patT = patread(fnamePT, &NpatT, N0);	// test patterns (target patterns to be masked)
	patM = patread(fnamePM, &NpatM, N0);	// masking patterns

	for (t = 0; tpm[t][0] >= 0; t++) {				// test

		printf("Test response       t=%d\n", t);
		if (ipr == 1)  fprintf(fpa, "\nTest response       t=%d\n", t);

		pat(upat[0], upatmax, patT, NpatT, N0, tpm[t][0]);
		pat(umask[0], umaskmax, patM, NpatM, N0, tpm[t][1]);
		for (tt = 0; tt <= 3; tt++) {
		   // open file "fnameN" (hexadecimal output)
			if (ifpN == 1) {
				fnameN[3] = '0' + t / 10;		// fnameN[] = "out   .eps"
				fnameN[4] = '0' + t % 10;		// fnameN[] = "out   .eps"
				fnameN[5] = '0' + tt;			// fnameN[] = "out   .eps"
				if ((fpN = fopen(fnameN, "w")) == NULL) {
					printf("file open error fpN\n");
					exit(1);
				}
			   // open file "fnameNhead"
				if ((fpNh = fopen(fnameNhead, "r")) == NULL) {
					printf("file open error fpNh\n");
					exit(1);
				}
				while (fgets(linebuf, 101, fpNh) != NULL) {		// copy fpNh to fpN
					if (fputs(linebuf, fpN) != 0)  printf("file write error fpN\n");
				}
				fclose(fpNh);
			} else if (ifpN == 2) {
				if (t == 0  &&  tt == 0) {
					if ((fpN = fopen(fnameNall, "w")) == NULL) {
						printf("file open error fpN\n");
						exit(1);
					}
				   // open file "fnameNhead"
					if ((fpNh = fopen(fnameNhead, "r")) == NULL) {
						printf("file open error fpNh\n");
						exit(1);
					}
					fgets(linebuf, 101, fpNh);					// read the 1st line and discard it
					if (fputs("%!PS-Adobe-3.0\n", fpN) != 0)  printf("file write error fpN\n");
					fgets(linebuf, 101, fpNh);					// read 1 line and copy it (%%BoundingBox:)
					if (fputs(linebuf, fpN) != 0)  printf("file write error fpN\n");

					for (ttt = 0; tpm[ttt][0] >= 0; ttt++) {}		// conut max number of test patterns
					Pages = ttt * 4;								// number of pages in the output file
					fprintf(fpN, "%%%%Pages: %d\n", Pages);			// "%%Pages: ?"

					while (fgets(linebuf, 101, fpNh) != NULL) {		// copy fpNh to fpN (from the 3rd line)
						if (fputs(linebuf, fpN) != 0)  printf("file write error fpN\n");
					}
					fclose(fpNh);
					ipage = 0;
				}
				ipage++;
				fprintf(fpN, "\n%%%%Page: %d %d\n", ipage, ipage);		// "%%Page: ? ?"
			}

		   // generate an input pattern U0
			if (tt == 0) {			// intact pattern, no response in UM
				copyplane(u0[0], u0max, upat[0], N0);
				umaskmax[0] = 0.0;
			} else if (tt == 1) {	// pat minus masker (invisible masker), no response in UM
				patmask(u0[0], u0max, upat[0], umask[0], 0.0, N0);
				umaskmax[0] = 0.0;
			} else if (tt == 2) {	// pat with masker (visible masker), with response in UM
				patmask(u0[0], u0max, upat[0], umask[0], amask, N0);
				umaskmax[0] = 1.0 / amask;
			} else if (tt == 3) {	// pat with masker, no response in UM
				patmask(u0[0], u0max, upat[0], umask[0], amask, N0);
				umaskmax[0] = 0.0;
			}
			if (iprt[0] == 1)  printu(fpa, u0, u0max, N0, 1, "U0", -1);

			if (fpN != NULL)  outH1(fpN, u0, u0max, N0, 1, "U", 0);
			if (fpN != NULL)  outH1(fpN, umask, umaskmax, N0, 1, "UM", -1);

			onoff(uc[0], ucmax[0], u0[0], cg, N0, Nc[0], Ng);
			if (iprt[1] == 1)  printu(fpa, uc[0], ucmax[0], Nc[0], 2, "UG", -1);
			if (fpN != NULL)  outH1(fpN, uc[0], ucmax[0], Nc[0], 2, "UG", -1);

			for (l = 0; l < L; l++) {
				Sres(us[l], usmax[l], uc[l], ucmax[l], as[l], cs[l], bs[l], vs2, 
						Nc[l], Kc[l], Ns[l], Ks[l], Na[l], thetar[l]);
				if (tt == 2  &&  l == 0) {
					Ssup(us[l], usmax[l], umask, csup, Ns[l], Ks[l], Nsup);
				}
				if (iprt[l*2+2] == 1) {
					printu(fpa, us[l], usmax[l], Ns[l], Ks[l], "Us", l+1);
				} else if (iprt[l*2+2] == 2) {
					printuadd(fpa, us[l], usmax[l], Ns[l], "Us", l+1, 0, Ks[l]-1);
				}

				if (l != L - 1) {
					Cres1(uc[l+1], ucmax[l+1], us[l], usmax[l], ac[l], ncmax, ncmin,
						Ns[l], ms[l], Nc[l+1], mc[l], Kc[l+1], Nd[l]);
				} else {
					CresL(uc[l+1], ucmax[l+1], usmax[l], cat, Ks[l], Kc[l+1]);
				}
				if (iprt[l*2+3] == 1) {
					printu(fpa, uc[l+1], ucmax[l+1], Nc[l+1], Kc[l+1], "Uc", l+1);
				} else if (iprt[l*2+3] == 2) {
					printuadd(fpa, uc[l+1], ucmax[l+1], Nc[l+1], "Uc", l+1, 0, Kc[l+1]-1);
				}
				if (fpN != NULL)  outH1(fpN, uc[l+1], ucmax[l+1], Nc[l+1], Kc[l+1], "UC", l+1);
			}
			if (fpN != NULL) {
				if (tt == 3) {							// without layer UM
					fprintf(fpN, "\n/drawcross 1 def");	// "/drawcross 1 def"
				} else {
					fprintf(fpN, "\n/drawcross 0 def");	// "/drawcross 0 def"
				}
				fprintf(fpN, "\ndisplay\n");			// "display"
				if (ifpN == 1) {
					fclose(fpN);
					fpN = NULL;
				} else if (ifpN == 2) {
					fprintf(fpN, "\nshowpage\n");		// "showpage"
					if (tpm[t+1][0] < 0  &&  tt == 3) {
						fclose(fpN);
						fpN = NULL;
					}
				}
			}
		}
	}

	if (fpa != NULL)  fclose(fpa);

	return 0;
}			//  end of main


// *********************************************************************

////  Function Definition

double ***getp(			// memory for 1-D pointer array **u[L]
	int		L
	)
{
	double	***u;

	u = (double ***)malloc(sizeof(double **) * L);
	if (u == NULL) {
		printf("Memory allocation error!\n");
		exit(1);
	}
	return  u;
}



double *get1D(			// get memory for 1-D array m[N]
	int		N
	)
{
	double		*u;

	u = (double *)malloc(sizeof(double) * N);
	if (u == NULL)  printf("Memory allocation error!\n");
	return  u;
}



int *get1Di(			// get memory for 1-D int array m[N]
	int		N
	)
{
	int		*m;

	m = (int *)malloc(sizeof(int) * N);
	if (m == NULL)  printf("Memory allocation error!\n");
	return  m;
}



double **get2D(			// get memory for 2-D array u[N1][N2]
	int		N1,
	int		N2
	)
{
	int		i;
	double	**u;

	u = (double **)malloc(sizeof(double *) * N1);
	if (u == NULL)  printf("Memory allocation error!\n");

	u[0] = (double *)malloc(sizeof(double) * N1 * N2);
	if (u[0] == NULL)  printf("Memory allocation error!\n");

	for (i = 1; i < N1; i++) {
		u[i] = u[i-1] + N2;
	}

	return  u;
}



int **get2Di(			// get memory for 2-D int array m[N1][N2]
	int		N1,
	int		N2
	)
{
	int		i;
	int		**m;

	m = (int **)malloc(sizeof(int *) * N1);
	if (m == NULL)  printf("Memory allocation error!\n");

	m[0] = (int *)malloc(sizeof(int) * N1 * N2);
	if (m[0] == NULL)  printf("Memory allocation error!\n");

	for (i = 1; i < N1; i++) {
		m[i] = m[i-1] + N2;
	}

	return  m;
}



double ***geta3D(		// get addable memory for 3-D array u[K][N1][N2]
	int		K,			// initial array size
	int		N1,
	int		N2,
	int		Kmax		// maximum possible array size: u[Kmax][N1][N2]
	)
{
	int		i, j;
	double	***u;

	if (K > Kmax) {
		printf("Cannot get array larger than Kmax:  K = %d", K);
		exit(1);
	}

	u = (double ***)malloc(sizeof(double **) * Kmax);
	if (u == NULL) {
		printf("Memory allocation error!\n");
		exit(1);
	}

	u[0] = (double **)malloc(sizeof(double *) * K * N1);
	if (u[0] == NULL) {
		printf("Memory allocation error!\n");
		exit(1);
	}
	for (i = 1; i < K; i++) {
		u[i] = u[i-1] + N1;
	}
	for (i = K; i < Kmax; i++) {
		u[i] = NULL;
	}

	u[0][0] = (double *)malloc(sizeof(double) * K * N1 * N2);
	if (u[0][0] == NULL) {
		printf("Memory allocation error!\n");
		exit(1);
	}
	for (i = 1; i < K; i++) {
		u[i][0] = u[i-1][0] + N1 * N2;
	}
	for (i = 0; i < K; i++) {
		for (j = 1; j < N1; j++) {
			u[i][j] = u[i][j-1] + N2;
		}
	}

	return  u;
}



void add3D(				// add memory to 3-D array u[K][N1][N2]
	double	***u,		// (in) u = (double ***)malloc(sizeof(double **) * Kmax)
	int		Knew,		// new array size
	int		N1,
	int		N2,
	int		Kmax		// maximum possiboe array size
	)
{
	int		i, j;
	int		Kold;		// previous array size
	int		Kadd;		// size of the added memory

	for (Kold = 0; Kold < Kmax; Kold++) {
		if (u[Kold] == NULL)  break;
	}
	Kadd = Knew - Kold;
	if (Kadd <= 0)  return;

	if (Knew > Kmax) {
		printf("Cannot get array larger than Kmax:  Knew = %d", Knew);
		exit(1);
	}

	u[Kold] = (double **)malloc(sizeof(double *) * Kadd * N1);
	if (u[Kold] == NULL) {
		printf("Memory allocation error!\n");
		exit(1);
	}
	for (i = Kold + 1; i < Knew; i++) {
		u[i] = u[i-1] + N1;
	}

	u[Kold][0] = (double *)malloc(sizeof(double) * Kadd * N1 * N2);
	if (u[Kold][0] == NULL) {
		printf("Memory allocation error!\n");
		exit(1);
	}
	for (i = Kold + 1; i < Knew; i++) {
		u[i][0] = u[i-1][0] + N1 * N2;
	}
	for (i = Kold; i < Knew; i++) {
		for (j = 1; j < N1; j++) {
			u[i][j] = u[i][j-1] + N2;
		}
	}
}



double ****geta4D1(		// get addable memory for 1-D pointer array ***a[]
	int		Kmax		// maximum possible pointer array size: ***a[Kmax]
	)
{
	int		i;
	double	****a;

	a = (double ****)malloc(sizeof(double *) * Kmax);
	if (a == NULL) {
		printf("Memory allocation error!\n");
		exit(1);
	}
	for (i = 0; i < Kmax; i++) {
		a[i] = NULL;
	}
	return  a;
}



void add4D2(			// add memory to 2-D pointer array **a[K][Kc]
	double	****a,		// (in) a = (double ****)malloc(sizeof(double *) * Kmax)
	int		Knew,		// new pointer array size: **a[Knew][Kc]
	int		Kc,
	int		Kmax		// maximum possible array size: **a[Kmax][Kc]
	)
{
	int		i, j;
	int		Kold;			// previous array size
	int		Kadd;			// added memory size

	for (Kold = 0; Kold < Kmax; Kold++) {
		if (a[Kold] == NULL)  break;
	}
	Kadd = Knew - Kold;
	if (Kadd <= 0)  return;

	if (Knew > Kmax) {
		printf("Cannot get array larger than Kmax:  Knew = %d", Knew);
		exit(1);
	}

	a[Kold] = (double ***)malloc(sizeof(double *) * Kc * Kadd);
	if (a[Kold] == NULL) {
		printf("Memory allocation error!\n");
		exit(1);
	}
	for (i = Kold + 1; i < Knew; i++) {
		a[i] = a[i-1] + Kc;
	}

	for (i = Kold; i < Knew; i++) {
		for (j = 0; j < Kc; j++) {
			a[i][j] = NULL;
		}
	}
}



void Sres(				// response of S-layer
	double	***us,		// (out) response of S-cells: us[Ks][Ns][Ns]
	double	*usmax,		// (out) max response of S-cell-planes: usmax[Ks]
	double	***uc,		// (in) response of C-cells: uc[Kc][Nc][Nc]
	double	*ucmax,		// (in) max response of C-cell-planes: ucmax[Kc]
	double	****as,		// (in) exc. connections to S-cells: as[Ks][Kc][Na][Na]
	double	**cs,		// (in) exc. connections to V-cells: cs[Na][Na]
	double	*bs,		// (in) inh. connections to S-cells: bs[Ks]
	double	**vs2,		// (work) response**2 of V-cells: vs2[Ns][Ns]
	int		Nc,			// size of the C-layer: (nc*2+1)
	int		Kc,			// number of cell-planes in C-layer
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		Ks,			// numberof cell-planes in S-layer
	int		Na,			// size of the connections (as & cs): (na*2+1)
	double	theta		// threshold of an S-cell
	)
{
	int		is, js, ks, ic, jc, kc, ismin, ismax, jsmin, jsmax;
	double	uu, uu2, aas, vv, thv, uus;
	double	theta1 = theta / (1 - theta);
	int		na = Na / 2;			// Na=(na*2+1)
	int		ns = Ns / 2;			// Ns=(ns*2+1)
	int		nc = Nc / 2;			// Nc=(nc*2+1)

	for (ks = 0; ks < Ks; ks++) {		// claer us & usmax
		usmax[ks] = 0.0;
		for (is = 0; is < Ns; is++) {
			for (js = 0; js < Ns; js++) {
				us[ks][is][js] = 0.0;
			}
		}
	}
	for (is = 0; is < Ns; is++) {		// claer vs2
		for (js = 0; js < Ns; js++) {
			vs2[is][js] = 0.0;
		}
	}
	for (kc = 0; kc < Kc; kc++) {	// send signals from uc to us & vs2
		if (ucmax[kc] > 0.0) {
			for (ic = -nc; ic <= nc; ic++) {
				ismin = ic - na;
				if (ismin < -ns)  ismin = -ns;
				ismax = ic + na;
				if (ismax > ns)  ismax = ns;
				for (jc = -nc; jc <= nc; jc++) {
					if ((uu = uc[kc][ic + nc][jc + nc]) > 0.0) {
						uu2 = uu * uu;
						jsmin = jc - na;
						if (jsmin < -ns)  jsmin = -ns;
						jsmax = jc + na;
						if (jsmax > ns)  jsmax = ns;
						for (is = ismin; is <= ismax; is++) {
							for (js = jsmin; js <= jsmax; js++) {
								vs2[is + ns][js + ns] += cs[ic - is + na][jc - js + na] * uu2;
							}
						}
						for (ks = 0; ks < Ks; ks++) {
							if (as[ks][kc] != NULL) {		// sarting adress in the memory as
								for (is = ismin; is <= ismax; is++) {
									for (js = jsmin; js <= jsmax; js++) {
										if ((aas = as[ks][kc][ic - is + na][jc - js + na]) > 0.0) {
											us[ks][is + ns][js + ns] += aas * uu;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	for (is = 0; is < Ns; is++) {
		for (js = 0; js < Ns; js++) {
			if ((vv = vs2[is][js])> 0.0) {
				thv = theta * sqrt(vv);
				for (ks = 0; ks < Ks; ks++) {
					if ((uu = us[ks][is][js]) > 0.0) {
						uu = (1.0 + uu)/(1.0 + thv * bs[ks]);
						if (uu > 1.0) {
							uus = theta1 * (uu - 1.0);
							us[ks][is][js] = uus;
							if (uus > usmax[ks])  usmax[ks] = uus;
						}
						else {
							us[ks][is][js] = 0.0;
						}
					}
				}
			}
		}
	}
}



void Cres1(				// response of C-layer (get max instead of sum)
	double	***uc,		// (out) response of C-cells: uc[K][Nc][Nc]
	double	*ucmax,		// (out) max response of C-cell-planes: ucmax[K]
	double	***us,		// (in) response of S-cells: us[K][Ns][Ns]
	double	*usmax,		// (in) max response of S-cell-planes: usmax[K]
	double	**ac,		// (in) exc. connections to C-cells: ac[Nd][Nd]
	int		*ncmax,		// (work) upper bound of the conection: ncmax[Ns]
	int		*ncmin,		// (work) lower bound of the conection: ncmin[Ns]
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		ms,			// step of S-cells
	int		Nc,			// size of the C-layer: (nc*2+1)
	int		mc,			// step of C-cells
	int		K,			// number of cell-planes in S- and C-layers (K=Ks=Kc)
	int		Nd			// size of the connections (ac): (nd*2+1)
	)
						// ratio of thinning-out = mc : ms
{
	int		k, ic, jc, is, js;
	double	uu, acu, uuc;
	int		nd = Nd / 2;				// Nd=(nd*2+1)
	int		nc = Nc / 2;				// Nc=(nc*2+1)
	int		ns = Ns / 2;				// Ns=(ns*2+1)
	int		ns2 = Ns - 1;				// =ns*2
	int		nc2 = Nc - 1;				// =nc*2
	int		nd0 = - ns * ms + nc * mc + nd;

	for (is = 0; is < Ns; is++) {
		ncmax[is] = (is * ms + nd0) / mc;
		if (ncmax[is] > nc2)  ncmax[is] = nc2;
		ncmin[ns2 - is] = nc2 - ncmax[is];
	}

	for (k = 0; k < K; k++) {
		ucmax[k] = 0.0;
		for (ic = 0; ic < Nc; ic++) {		// claer uc
			for (jc = 0; jc < Nc; jc++) {
				uc[k][ic][jc] = 0.0;
			}
		}
		if (usmax[k] > 0.0) {		// send signals from us to uc
			for (is = 0; is < Ns; is++) {
				for (js = 0; js < Ns; js++) {
					if ((uu = us[k][is][js]) > 0.0) {
						for (ic = ncmin[is]; ic <= ncmax[is]; ic++) {
							for (jc = ncmin[js]; jc <= ncmax[js]; jc++) {
								acu = ac[is * ms - ic * mc + nd0][js * ms - jc * mc + nd0]
										* uu;
								if (uc[k][ic][jc] < acu) {
									uc[k][ic][jc] = acu;
								}
							}
						}
					}
				}
			}
			for (ic = 0; ic < Nc; ic++) {			// calculate the response of uc
				for (jc = 0; jc < Nc; jc++) {
					if ((uu = uc[k][ic][jc]) > 0.0) {
						uuc = uu / (1.0 + uu);
						uc[k][ic][jc] = uuc;
						if (uuc > ucmax[k])  ucmax[k] = uuc;
					}
				}
			}
		}
	}
}



void CresL(				// response of C-layer without lateral inhibition
	double	***uc,		// (out) response of C-cells: uc[Kc][1][1]
	double	*ucmax,		// (out) max response of C-cell-planes: ucmax[Kc]
	double	*usmax,		// (in) max response of S-cell-planes: usmax[Ks]
	int		*cat,		// (in) category of the S-plane: cat[Ks]
	int		Ks,			// number of cell-planes in S-layers (Ks)
	int		Kc			// number of cell-planes in C-layers (Kc)
	)
						// ratio of thinning-out = mc : ms
{
	int		ks, kc, Cat;
	double	Usmax;

	for (kc = 0; kc < Kc; kc++) {
		ucmax[kc] = 0.0;
		uc[kc][0][0] = 0.0;
	}
	Usmax = 0.0;
	Cat = -1;
	for (ks = 0; ks < Ks; ks++) {
		if (usmax[ks] > Usmax) {
			Usmax = usmax[ks];
			Cat = cat[ks];
		}
	}
	if (Cat >= 0) {
		uc[Cat][0][0] = Usmax;
		ucmax[Cat] = Usmax;
	}
}



void onoff(				// response of on- & off-center cell layers
	double	***uc,		// (out) response of on- & off-center cells: uc[2][Nc][Nc]
	double	*ucmax,		// (out) max response of on- & off- cells: ucmax[2]
	double	**us,		// (in) response of receptor cells: us[Ns][Ns]
	double	**cg,		// (in) connections for on-center: cg[Ng][Ng]
	int		Ns,			// size of the receptor layer: (ns*2+1)
	int		Nc,			// size of the on- & off-center cell layer: (nc*2+1)
	int		Ng			// size of the connections (ag): (ng*2+1)
	)
{
	int		ic, jc, is, js, icmin, icmax, jcmin, jcmax;
	double	uu;
	int		ng = Ng / 2;				// Ng=(ng*2+1)
	int		nc = Nc / 2;				// Nc=(nc*2+1)
	int		ns = Ns / 2;				// Ns=(ns*2+1)

	for (ic = 0; ic < Nc; ic++) {
		for (jc = 0; jc < Nc; jc++) {
			uc[0][ic][jc] = 0.0;
		}
	}
	for (is = -ns; is <= ns; is++) {
		icmin = is - ng;
		if (icmin < -nc)  icmin = -nc;
		icmax = is + ng;
		if (icmax > nc)  icmax = nc;
		for (js = -ns; js <= ns; js++) {
			if ((uu = us[is + ns][js + ns]) > 0.0) {
				jcmin = js - ng;
				if (jcmin < -nc)  jcmin = -nc;
				jcmax = js + ng;
				if (jcmax > nc)  jcmax = nc;
				for (ic = icmin; ic <= icmax; ic++) {
					for (jc = jcmin; jc <= jcmax; jc++) {
						uc[0][ic + nc][jc + nc] += cg[is - ic + ng][js - jc + ng] * uu;
					}
				}
			}
		}
	}
	ucmax[0] = 0.0;
	ucmax[1] = 0.0;
	for (ic = 0; ic < Nc; ic++) {
		for (jc = 0; jc < Nc; jc++) {
			if ((uu = uc[0][ic][jc]) > 0.0001) {
				uc[1][ic][jc] = 0.0;
				if (uu > ucmax[0])  ucmax[0] = uu;
			}
			else if (uu < -0.0001) {
				uc[0][ic][jc] = 0.0;
				uc[1][ic][jc] = -uu;
				if (-uu > ucmax[1])  ucmax[1] = -uu;
			}
			else {
				uc[0][ic][jc] = 0.0;
				uc[1][ic][jc] = 0.0;
			}
		}
	}
}



void make_cg(			// make connections for on-center
	double	**cg,		// (out) Connections: cg[Ng][Ng]
	double	Ag,			// radius of the off-periphery (connect. area)
	double	Ago,		// radius of the on-center component
	double	gamcg		// spatial decay at x=Ag
	)
								//  Ng=ng*2+1,  ng=(int) Ag
{
	int		i, j, i2, r2;
	double	Spos, Sneg, SSpos, SSneg, cc;
	int		ng = (int) Ag;
	int		Ng = ng * 2 + 1;
	double	Ag2 = Ag * Ag;
	double	Ago2 = Ago * Ago;
	double	C = 1 / Ag2;
	double	Co = 1 / Ago2;

	Spos = 0.0;
	Sneg = 0.0;
	for (i = -ng; i <= ng; i++) {
		i2 = i * i;
		for (j = -ng; j <= ng; j++) {
			r2 = i2 + j * j;
			if (r2 <= Ag2) {
				cc = Co * pow(gamcg, r2 / Ago2) - C * pow(gamcg, r2 / Ag2);
				cg[i + ng][j + ng] = cc;
				if (cc > 0.0)  Spos += cc;
				else           Sneg -= cc;
			}
			else {
				cg[i + ng][j + ng] = 0.0;
			}
		}
	}
	SSpos = 1 / Spos;
	SSneg = 1 / Sneg;
	for (i = 0; i < Ng; i++) {
		for (j = 0; j < Ng; j++) {
			if (cg[i][j] > 0.0) {
				cg[i][j] *= SSpos;
			}
			else {
				cg[i][j] *= SSneg;
			}
		}
	}
}



void make_c(			// make connections (spatial weight)
	double	**c,		// (out) Connections: c[Na][Na]
	double	A,			// radius of the connectable area
	double	gamma,		// spatial decay at x=A
	double  co			// value of c[][] at the center
	)
								//  Na=na*2+1,  na=(int) A
{
	int		i, j, i2, r2;
	int		na = (int) A;
	double	A2 = A * A;

	for (i = -na; i <= na; i++) {
		i2 = i * i;
		for (j = -na; j <= na; j++) {
			r2 = i2 + j * j;
			if (r2 <= A2) {
				c[i + na][j + na] = co * pow(gamma, r2 / A2);
			}
			else {
				c[i + na][j + na] = 0.0;
			}
		}
	}
}



void norm_c(			// make normalized connections (spatial weight)
	double	**c,		// (out) Connections: c[Na][Na]
	double	A,			// radius of the connectable area
	double	gamma,		// spatial decay at x=A
	double  cno			// strength of the connections
	)
{
	int		i, j;
	double	sum, cns;
	int		na = (int) A;
	int		Na = na * 2 + 1;

	make_c(c, A, gamma, 1.0);
	sum = 0.0;
	for (i = 0; i < Na; i++) {
		for (j = 0; j < Na; j++) {
			sum += c[i][j];
		}
	}
	cns = cno / sum;
	for (i = 0; i < Na; i++) {
		for (j = 0; j < Na; j++) {
			c[i][j] *= cns;
		}
	}
}



void angle(				// draw an angle of ang degree
	double	**u,		// (out) generated pattern: u[N][N]
	int		N,			// size of the layer: (n*2+1)
	int		K,			// number of different orientations
	int		k,			// sequence number of the orientation of the edge
	double	ang,		// angle (in degree) of the bend
	double	offset		// offset of the senter of the pattern
	)
{
	int		i, j;
	double	rad, Rcosa, Rsina, Rcosb, Rsinb, x1, y1, x2, y2;
	double	pi = 3.141592653589793;
	double	radc = k * (2.0 * pi / K);
	double	radang2 = ang * pi / 360.0;		// ang/2 in radian
	double	rada = radc + radang2;
	double	radb = radc - radang2;
	double	radstep = pi * 0.0625;
	double	R = ((double) N) * 0.43;
	double	x0 = offset * cos(radc);	// x-coordinate of the corner
	double	y0 = offset * sin(radc);	// y-coordinate of the corner

	Rcosa = R * cos(rada);
	Rsina = R * sin(rada);
	Rcosb = R * cos(radb);
	Rsinb = R * sin(radb);

	for (i = 0; i < N; i++) {			// clear u[][]
		for (j = 0; j < N; j++) {
			u[i][j] = 0.0;
		}
	}

	edge(u, N, Rcosa + x0, Rsina + y0, x0, y0);
	edge(u, N, x0, y0, Rcosb + x0, Rsinb + y0);
	x1 = Rcosb + x0;
	y1 = Rsinb + y0;
	for (rad = radb; rad < rada; rad += radstep) {
		x2 = R * cos(rad) + x0;
		y2 = R * sin(rad) + y0;
		edge(u, N, x1, y1, x2, y2);
		x1 = x2;
		y1 = y2;
	}
	edge(u, N, x1, y1, Rcosa + x0, Rsina + y0);

	for (i = 0; i < N; i++) {			// eliminate rounding error
		for (j = 0; j < N; j++) {
			if (u[i][j] < 0.0001)  u[i][j] = 0.0;
			if (u[i][j] > 0.9999)  u[i][j] = 1.0;
		}
	}
}



void edge(
	double	**u,		// (i/o) generated pattern: u[N][N]
	int		N,			// size of the layer: (n*2+1)
	double	xs,
	double	ys,			// edge from (xs,ys) to (xe,ye)
	double	xe,
	double	ye
	)
{
	int		i, j, ia, ii;
	double	center, xpol, x1, y1, x2, y2, p, x, y, xa, ya, w;
	
	center = ((double) N) / 2.0;
	if (fabs(xe - xs) < 0.0001)  return;
	if (xs < xe) {
		xpol = 1.0;
		x1 = center + xs;
		y1 = center - ys;		// i increases from up to down
		x2 = center + xe;
		y2 = center - ye;
	}
	else {
		xpol = -1.0;
		x1 = center + xe;
		y1 = center - ye;
		x2 = center + xs;
		y2 = center - ys;
	}
	p = (y2 - y1) / (x2 - x1);
	if (x1 < 0.0) {
		y1 = y1 - p * x1;
		x1 = 0.0;
	}
	if (x2 > N) {
		y2 = y2 - p * (x2 - N);
		x2 = N;
	}
	if (fabs(p) < 0.0001)  p = 0.0;
	x = x1;
	y = y1;
	while (x < x2) {
		j = (int) x;
		i = (int) floor(y);
		if ((i == y) && (p < 0.0))  i = i - 1;
		xa = j + 1;
		if (xa > x2)  xa = x2;
		ya = y + p * (xa - x);
		ia = (int) floor(ya);
		if (ia > i) {
			ya = i + 1;
			xa = x + (ya - y) / p;
		}
		else if (ia < i) {							// p<0.0
			ya = i;
			xa = x + (ya - y) / p;
		}
		w = xpol * (xa - x);
		if (i >= 0) {
			if (i < N) {
				u[i][j] += w * ((y + ya) / 2.0 - i);
				for (ii = 0; ii < i; ii++) {
					u[ii][j] += w;
				}
			}
			else {
				for (ii = 0; ii < N; ii++) {
					u[ii][j] += w;
				}
			}
		}
		x = xa;
		y = ya;
	}
}



int Sorg(				// self-organization of S-layer
	double	****as,		// (out) exc. connections to S-cells: as[Ks][Kc][Na][Na]
	double	*bs,		// (out) inh. connections to S-cells: bs[Ks], new Ks
	double	***uc,		// (in) response of C-cells: uc[Kc][Nc][Nc]
	double	*ucmax,		// (in) max response of C-cell-planes: ucmax[Kc]
	double	**cs,		// (in) spatial weight: cs[Na][Na]
	double	**asini,	// (in) exc. initial connections to S-cells: as[Na][Na]
	double	**cl,		// (in) connect. for lat.inh. from us to usini: cl[Nl][Nl]
	double	***us,		// (work) response of S-cells: us[Ks][Ns][Ns], old Ks
	double	*usmax,		// (work) max response of S-cell-planes: usmax[Ks], old Ks
	double	**vs2,		// (work) response**2 of V-cells: vs2[Ns][Ns]
	double	**usini,	// (work) response of seed-selecting plane: usini[Ns][Ns]
	double	**work,		// (work) for wmax[][] & us[Ks][][]: work[Ns][Ns]
	int		**kwmax,	// (work) kwmax[Ns][Ns]
	int		*iseed,		// (work) iseed[Ks], old Ks
	int		*jseed,		// (work) jseed[Ks], old Ks
	int		Nc,			// size of the C-layer: (nc*2+1)
	int		Kc,			// number of cell-planes in C-layer
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		Ks,			// number of cell-planes in S-layer, old value
	int		Na,			// size of the connections (as & cs): (na*2+1)
	int		Nasini,		// size of the connect. asini: (nasini*2+1)
	double	D,			// radius of competition area
	double	Al,			// radius of lat.inh. from us to usini
	double	qs,			// parameter determining the speed of learning
	double	theta,		// threshold of an S-cell
	int		Ksmax,		// maximum possible Ks
	double	thrini		// threshold for cutting usini
	)
{
	int		ks, iseed0, jseed0;
	double	usmax0;		// max value of work[][]=us[Ks][][], corresponding to usmax[Ks]
	int		ns = Ns / 2;

	if (Ks > 0) {
		Sres(us, usmax, uc, ucmax, as, cs, bs, vs2, Nc, Kc, Ns, Ks, Na, theta);
										// Sres, using old connections
		seed(iseed, jseed, us, work, kwmax, Ns, Ks, D);		// work=wmax
		for (ks = 0; ks < Ks; ks++) {
			if (iseed[ks] >= 0) {
				delta(as, bs, uc, ucmax, cs, Na, Nc, Kc, Ns,
						ks, iseed[ks], jseed[ks], qs);
								// reinforce connect. for old cell-planes
								// memory for as[] may be increased by delta()
			}
		}
		Sres(us, usmax, uc, ucmax, as, cs, bs, vs2, Nc, Kc, Ns, Ks, Na, theta);
										// Sres, using renewed connections
	}
	Sresini(usini, uc, ucmax, asini, Nc, Kc, Ns, Nasini, thrini);
	for (ks = 0; ks < Ks; ks++) {
		lat(usini, us[ks], cl, Ns, Al);			// lat.inh. from us to usini
	}
	for (ks = Ks; ks < Ksmax; ks++) {
		seedini(&iseed0, &jseed0, usini, Ns);	// location of seed = max.-output cell
		if (iseed0 == -1)  break;
		add4D2(as, ks + 1, Kc, Ksmax);		// add Kc elements to pointer array **as
		delta(as, bs, uc, ucmax, cs, Na, Nc, Kc, Ns,
				ks, iseed0, jseed0, qs);
								// reinforce connect. for new cell-planes
								// memory for as[] may be increased by delta()
								// memory for bs[] must have been prepared beforehand
		Sres(&work, &usmax0, uc, ucmax, &as[ks], cs, &bs[ks], vs2, 
				Nc, Kc, Ns, 1, Na, theta);
											// Sres, for the new cell-plane
		lat(usini, work, cl, Ns, Al);		// lat.inh. from new us to usini
	}
	return  ks;
}



void delta(				// strengthen connections
	double	****as,		// (out) exc. connections to S-cells: as[Ks][Kc][Na][Na]
	double	*bs,		// (out) inh. connections to S-cells: bs[Ks]
	double	***uc,		// (in) response of C-cells: uc[Kc][Nc][Nc]
	double	*ucmax,		// (in) max response of C-cell-planes: ucmax[Kc]
	double	**cs,		// (in) spatial weight: cs[Na][Na]
	int		Na,			// size of the connections (as & cs): (na*2+1)
	int		Nc,			// size of the C-layer: (nc*2+1)
	int		Kc,			// numberof cell-planes in C-layer
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		kseed,		// cell-plane of the seed cell
	int		iseed,		// x-coordinate of the seed cell
	int		jseed,		// y-coordinate of the seed cell
	double	qs			// parameter determining the speed of learning
	)
{
	int		i, j, ic, jc, kc, icmin, icmax, jcmin, jcmax;
	double	**ma;
	int		m_inc;
	double	uu, b2, cc, aa;
	int		na = Na / 2;			// Na=(na*2+1)
	int		nc = Nc / 2;			// Nc=(nc*2+1)
	int		ns = Ns / 2;			// Ns=(ns*2+1)
	int		iseedo = iseed - ns;
	int		jseedo = jseed - ns;

	m_inc = 0;
	for (kc = 0; kc < Kc; kc++) {
		if (ucmax[kc] > 0.0) {
			if (as[kseed][kc] == NULL) {
				m_inc++;
			}
		}
	}
	ma = get2D(Na * m_inc, Na);			// get m_inc arrays [Na][Na]
	icmin = iseedo - na;
	if (icmin < -nc)  icmin = -nc;
	icmax = iseedo + na;
	if (icmax > nc)  icmax = nc;
	jcmin = jseedo - na;
	if (jcmin < -nc)  jcmin = -nc;
	jcmax = jseedo + na;
	if (jcmax > nc)  jcmax = nc;
	for (kc = 0; kc < Kc; kc++) {
		if (ucmax[kc] > 0.0) {
			if (as[kseed][kc] == NULL) {
				as[kseed][kc] = ma;
				ma += Na;
				for (i = 0; i < Na; i++) {
					for (j = 0; j < Na; j++) {
						as[kseed][kc][i][j] = 0.0;
					}
				}
			}
			for (ic = icmin; ic <= icmax; ic++) {
				for (jc = jcmin; jc <= jcmax; jc++) {
					i = ic - iseedo + na;
					j = jc - jseedo + na;
					if ((uu = uc[kc][ic + nc][jc + nc]) > 0.0) {
						if ((cc = cs[i][j]) > 0.0) {
							as[kseed][kc][i][j] += qs * cc * uu;
						}
					}
				}
			}
		}
	}

	b2 = 0.0;
	for (kc = 0; kc < Kc; kc++) {
		if (as[kseed][kc] != NULL) {
			for (i = 0; i < Na; i++) {
				for (j = 0; j < Na; j++) {
					if ((aa = as[kseed][kc][i][j]) > 0.0) {
						if ((cc = cs[i][j]) > 0.0) {
							b2 += aa * aa / cc;
						}
					}
				}
			}
		}
	}
	bs[kseed] = sqrt(b2);
}



void seed(				// select seed cells
	int		*iseed,		// (out) x-coordinate of the k-th cell-plane: iseed[Ks]
	int		*jseed,		// (out) y-coordinate of the k-th cell-plane: jseed[Ks]
	double	***us,		// (in) response of S-cells: us[Ks][Ns][Ns]
	double	**wmax,		// (work) working area: wmax[Ns][Ns]
	int		**kwmax,	// (work) working area: kwmax[Ns][Ns]
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		Ks,			// number of cell-planes in S-layer
	double	D			// radius of competition area
	)
{
	int		k, i, j, ii, jj, iii, jjj, i2, r2, imin, jmin, imax, jmax, ks;
	double	wm;
	double	d2 = D * D;				// D**2 in the scale of this layer
	int		id = (int) D;

	for (k = 0; k < Ks; k++) {		// reset iseed & jseed
		iseed[k] = -1;
		jseed[k] = -1;
	}
	for (i = 0; i < Ns; i++) {		// competition among k at each location
		for (j = 0; j < Ns; j++) {
			wmax[i][j] = 0.0;
			kwmax[i][j] = -1;
			for (k = 0; k < Ks; k++) {
				if (us[k][i][j] > wmax[i][j]) {
					wmax[i][j] = us[k][i][j];
					kwmax[i][j] = k;
				}
			}
		}
	}
	for (i = 0; i < Ns; i++) {		// find a winner in each hypercolumn
		imin = i - id;
		if (imin < 0)  imin = 0;
		imax = i + id;
		if (imax >= Ns)  imax = Ns - 1;
		for (j = 0; j < Ns; j++) {
			if ((wm = wmax[i][j]) > 0.0) {
				jmin = j - id;
				if (jmin < 0)  jmin = 0;
				jmax = j + id;
				if (jmax >= Ns)  jmax = Ns - 1;
				for (ii = imin; ii <= imax; ii++) {
					iii = ii - i;
					i2 = iii * iii;
					for (jj = jmin; jj <= jmax; jj++) {
						jjj = jj - j;
						r2 = i2 + jjj * jjj;
						if (r2 <= d2 && r2 != 0.0) {
							if (wmax[ii][jj] > wm) {		// defeated
								kwmax[i][j] = -1;
								goto skip;
							}
							else if (wmax[ii][jj] == wm) {	// tie
								wmax[ii][jj] = wm * 0.9999;
							}
						}
					}
				}
			}
			skip:	;
		}
	}
	for (i = 0; i < Ns; i++) {		// find a winner for each cell-plane
		for (j = 0; j < Ns; j++) {
			if ((ks = kwmax[i][j]) >= 0) {
				if ((iseed[ks] < 0) ||	// first appearance of a winner in ks
						(wmax[i][j] > wmax[iseed[ks]][jseed[ks]])) {
					iseed[ks] = i;		// replace the seed
					jseed[ks] = j;
				}
			}
		}
	}
}



void Sresini(			// response of seed-selecting plane
	double	**usini,	// (out) response of seed-selecting plane: usini[Ns][Ns]
	double	***uc,		// (in) response of C-cells: uc[Kc][Nc][Nc]
	double	*ucmax,		// (in) max response of C-cell-planes: ucmax[Kc]
	double	**asini,	// (in) exc. initial connections to S-cells: as[Na][Na]
	int		Nc,			// size of the C-layer: (nc*2+1)
	int		Kc,			// number of cell-planes in C-layer
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		Na,			// size of the connections (asini, as & cs): (na*2+1)
	double	thrini		// threshold for cutting usini
	)
{
	int		is, js, ic, jc, kc, ismin, ismax, jsmin, jsmax;
	double	uu;
	double	usimax, usicut;
	int		na = Na / 2;			// Na=(na*2+1)
	int		ns = Ns / 2;			// Ns=(ns*2+1)
	int		nc = Nc / 2;			// Nc=(nc*2+1)

	for (is = 0; is < Ns; is++) {
		for (js = 0; js < Ns; js++) {
			usini[is][js] = 0.0;
		}
	}
	for (kc = 0; kc < Kc; kc++) {
		if (ucmax[kc] > 0.0) {
			for (ic = -nc; ic <= nc; ic++) {
				ismin = ic - na;
				if (ismin < -ns)  ismin = -ns;
				ismax = ic + na;
				if (ismax > ns)  ismax = ns;
				for (jc = -nc; jc <= nc; jc++) {
					if ((uu = uc[kc][ic + nc][jc + nc]) > 0.0) {
						jsmin = jc - na;
						if (jsmin < -ns)  jsmin = -ns;
						jsmax = jc + na;
						if (jsmax > ns)  jsmax = ns;
						for (is = ismin; is <= ismax; is++) {
							for (js = jsmin; js <= jsmax; js++) {
								usini[is + ns][js + ns] += asini[ic - is + na][jc - js + na] * uu;
							}
						}
					}
				}
			}
		}
	}
	usimax = 0.0;
	for (is = 0; is < Ns; is++) {
		for (js = 0; js < Ns; js++) {
			if (usini[is][js] > usimax)  usimax = usini[is][js];
		}
	}
	usicut = usimax * thrini;
	for (is = 0; is < Ns; is++) {
		for (js = 0; js < Ns; js++) {
			usini[is][js] -= usicut;
			if (usini[is][js] < 0.0)  usini[is][js] = 0.0;
		}
	}
}



void seedini(			// select seed cells
	int		*iseed0,	// (out) x-coordinate of the k-th cell-plane: iseed0[1]
	int		*jseed0,	// (out) y-coordinate of the k-th cell-plane: jseed0[1]
	double	**usini,	// (in) response of S-cells: usini[Ns][Ns]
	int		Ns			// size of the S-layer: (ns*2+1)
	)
{
	int		i, j;
	double	umax;

	umax = 0.0;
	iseed0[0] = -1;
	jseed0[0] = -1;
	for (i = 0; i < Ns; i++) {		// find maximum output
		for (j = 0; j < Ns; j++) {
			if (usini[i][j] > umax) {
				umax = usini[i][j];
				iseed0[0] = i;
				jseed0[0] = j;
			}
		}
	}
}



void lat(				// lateral inhibition from uin to uout
	double	**ut,		// (i/o) cell-plane to be inhibited: ut[N][N]
	double	**uf,		// (in) inhibiting cell-plane: uf[N][N]
	double	**cl,		// (in) connections for lateral inhibition: cl[Nl][Nl]
	int		N,			// size of the layer: (n*2+1)
	double	Al			// radius of lat.inh.
	)
						//  Nl=nl*2+1,  nl=Al
{
	int		i, j, ii, jj, iii, jjj;
	double	uu;
	int		nl = (int) Al;
	int		Nl = nl * 2 + 1;

	for (i = 0; i < N; i++) {			// send inhibitory signals
		for (j = 0; j < N; j++) {
			if ((uu = uf[i][j]) > 0.0) {
				for (ii = 0; ii < Nl; ii++) {
					iii = i + ii - nl;
					if (iii >= 0 && iii < N) {
						for (jj = 0; jj < Nl; jj++) {
							jjj = j + jj - nl;
							if (jjj >= 0 && jjj < N) {
								ut[iii][jjj] -= cl[ii][jj] * uu;
							}
						}
					}
				}
			}
		}
	}
	for (i=0; i < N; i++) {				// thresholding
		for (j = 0; j < N; j++) {
			if (ut[i][j] < 0.0) {
				ut[i][j] = 0.0;
			}
		}
	}
}



void copyplane(			// copy the response of a cell-plane
	double	**ut,		// (out) copied to this cell-plane: ut[N][N]
	double	*utmax,		// (out) max value of ut[1]
	double	**uf,		// (in) copied from this cell-plane: uf[N][N]
	int		N			// size of the layer: (n*2+1)
	)
{
	int		i, j;

	utmax[0] = 0.0;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			ut[i][j] = uf[i][j];
			if (ut[i][j] > utmax[0])  utmax[0] = ut[i][j];
		}
	}
}



int SorgL(				// self-organization of S-layer
	double	****as,		// (out) exc. connections to S-cells: as[Ks][Kc][Na][Na]
	double	*bs,		// (out) inh. connections to S-cells: bs[Ks], new Ks
	int		*cat,		// (out) category of the S-plane: cat[Ks]
	int		Cat,		// (in) category of the training pattern
	double	***uc,		// (in) response of C-cells: uc[Kc][Nc][Nc]
	double	*ucmax,		// (in) max response of C-cell-planes: ucmax[Kc]
	double	**cs,		// (in) spatial weight: cs[Na][Na]
	double	**asini,	// (in) exc. initial connections to S-cells: as[Na][Na]
	double	***us,		// (work) response of S-cells: us[Ks][Ns][Ns], old Ks
	double	*usmax,		// (work) max response of S-cell-planes: usmax[Ks], old Ks
	double	**vs2,		// (work) response**2 of V-cells: vs2[Ns][Ns]
	double	**usini,	// (work) response of seed-selecting plane: usini[Ns][Ns]
	double	**work,		// (work) for wmax[][] & us[Ks][][]: work[Ns][Ns]
	int		Nc,			// size of the C-layer: (nc*2+1)
	int		Kc,			// number of cell-planes in C-layer
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		Ks,			// number of cell-planes in S-layer, old value
	int		Na,			// size of the connections (as & cs): (na*2+1)
	int		Nasini,		// size of the connect. asini: (nasini*2+1)
	double	qs,			// parameter determining the speed of learning
	double	theta,		// threshold of an S-cell
	int		Ksmax,		// maximum possible Ks
	double	thrini		// threshold for cutting usini
	)
{
	int		ks, iseed0, jseed0, kseed0;
	int		ns = Ns / 2;

	kseed0 = -1;
	if (Ks > 0) {
		ks = Ks;
		Sres(us, usmax, uc, ucmax, as, cs, bs, vs2, Nc, Kc, Ns, Ks, Na, theta);
										// Sres, using old connections
		seedL(&iseed0, &jseed0, &kseed0, cat, Cat, us, Ns, Ks);		// work=wmax
		if (kseed0 >= 0) {
			delta(as, bs, uc, ucmax, cs, Na, Nc, Kc, Ns,
					kseed0, iseed0, jseed0, qs);
							// reinforce connect. for old cell-planes
							// memory for as[] may be increased by delta()
		}
	}
	if (kseed0 < 0) {
		ks = Ks + 1;
		Sresini(usini, uc, ucmax, asini, Nc, Kc, Ns, Nasini, thrini);
		seedini(&iseed0, &jseed0, usini, Ns);	// location of seed = max.-output cell
		if (iseed0 == -1)  return Ks;
		cat[Ks] = Cat;
		add4D2(as, Ks + 1, Kc, Ksmax);		// add Kc elements to pointer array **as
		delta(as, bs, uc, ucmax, cs, Na, Nc, Kc, Ns, Ks, iseed0, jseed0, qs);
								// reinforce connect. for new cell-planes
								// memory for as[] may be increased by delta()
								// memory for bs[] must have been prepared beforehand
	}
	return  ks;
}



void seedL(				// select seed cells
	int		*iseed0,	// (out) x-coordinate of the k-th cell-plane: iseed0[1]
	int		*jseed0,	// (out) y-coordinate of the k-th cell-plane: jseed0[1]
	int		*kseed0,	// (out) cell-plane of the seed cell: kseed0[1]
	int		*cat,		// (in) category of the S-plane: cat[Ks]
	int		Cat,		// (in) category of the training pattern
	double	***us,		// (in) response of S-cells: us[Ks][Ns][Ns]
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		Ks			// number of cell-planes in S-layer
	)
{
	int		k, i, j;
	double	wm;

	iseed0[0] = -1;
	jseed0[0] = -1;
	kseed0[0] = -1;
	wm = 0.0;
	for (k = 0; k < Ks; k++) {
		if (cat[k] == Cat) {			// competition
			for (i = 0; i < Ns; i++) {
				for (j = 0; j < Ns; j++) {
					if (us[k][i][j] > wm) {
						iseed0[0] = i;
						jseed0[0] = j;
						kseed0[0] = k;
						wm = us[k][i][j];
					}
				}
			}
		}
	}
}



void rwcon(				// read/write connections.  Also get memores as and bs, in the read mode
	FILE	*fpC,		// (in) file pointer
	char	*fnameC,	// (in) file name
	double	*****as,	// (i/o) exc. connect. to S-cells: as[L][Ks][Kc][Na][Na]
	double	**bs,		// (i/o) inh. connect. to S-cells: bs[L][Ks]
	int		**cat0,		// (i/o) category of the cell-plane UsL: cat0[1][KsL]=cat[Ks]
	int		*Na,		// (in) size of connect. as
	int		*Kc,		// (i/o) no. of C-cell-planes: Kc[L+1]
	int		*Ks,		// (i/o) no. of S-cell-planes: Ks[L]
	int		*Mas,		// (i/o) no. of active as[L][Ks][Kc]: Mas[L]
	int		L,			// number of stages
	int		learn		// switch:  if (learn==1) write, else read
	)
{
	double	**ma;
	int		l, isize, Na2, ks, kc, m;

	if (learn == 1) {							// write
		fpC = fopen(fnameC, "wb");
	    if (fpC == NULL) {
			printf("file open error fpC\n");
			exit(1);
    	}

		isize = fwrite(Kc, sizeof(int), L+1, fpC);
		if (isize != L+1)  goto error;

		isize = fwrite(Ks, sizeof(int), L, fpC);
		if (isize != L)  goto error;

		for (l = 0; l < L; l++) {
			Mas[l] = 0;
			for (ks = 0; ks < Ks[l]; ks++) {
				for (kc = 0; kc < Kc[l]; kc++) {
					if (as[l][ks][kc] != NULL) {
						Mas[l]++;
					}
				}
			}
		}
		isize = fwrite(Mas, sizeof(int), L, fpC);
		if (isize != L)  goto error;

		for (l = 0; l < L; l++) {
			Na2 = Na[l] * Na[l];
			for (ks = 0; ks < Ks[l]; ks++) {
				for (kc = 0; kc < Kc[l]; kc++) {
					if ((ma = as[l][ks][kc]) != NULL) {
						isize = fwrite(&ks, sizeof(int), 1, fpC);
						if (isize != 1)  goto error;
						isize = fwrite(&kc, sizeof(int), 1, fpC);
						if (isize != 1)  goto error;
						isize = fwrite(ma[0], sizeof(double), Na2, fpC);
						if (isize != Na2)  goto error;
					}
				}
			}

			isize = fwrite(bs[l], sizeof(double), Ks[l], fpC);
			if (isize != Ks[l])  goto error;
		}

		isize = fwrite(cat0[0], sizeof(int), Ks[L-1], fpC);
		if (isize != Ks[L-1])  goto error;
	}
	else {					// read
		fpC = fopen(fnameC, "rb");
	    if (fpC == NULL) {
			printf("file open error fpC\n");
			exit(1);
    	}

		isize = fread(Kc, sizeof(int), L+1, fpC);
		if (isize != L+1)  goto error;

		isize = fread(Ks, sizeof(int), L, fpC);
		if (isize != L)  goto error;

		isize = fread(Mas, sizeof(int), L, fpC);
		if (isize != L)  goto error;

		for (l = 0; l < L; l++) {
			as[l] = geta4D1(Ks[l]);
			add4D2(as[l], Ks[l], Kc[l], Ks[l]);	// get Kc[l]*Ks[l] elements to pointer array
			Na2 = Na[l] * Na[l];
			for (ks = 0; ks < Ks[l]; ks++) {
				for (kc = 0; kc < Kc[l]; kc++) {
					as[l][ks][kc] = NULL;
				}
			}
			ma = get2D(Na[l] * Mas[l], Na[l]);			// get Mas arrays [Na][Na]
			for (m = 0; m < Mas[l]; m++) {
				isize = fread(&ks, sizeof(int), 1, fpC);
				if (isize != 1)  goto error;
				isize = fread(&kc, sizeof(int), 1, fpC);
				if (isize != 1)  goto error;
				as[l][ks][kc] = ma;
				isize = fread(ma[0], sizeof(double), Na2, fpC);
				if (isize != Na2)  goto error;
				ma += Na[l];
			}

			bs[l] = get1D(Ks[l]);
			isize = fread(bs[l], sizeof(double), Ks[l], fpC);
			if (isize != Ks[l])  goto error;
		}

		cat0[0] = get1Di(Ks[L-1]);
		isize = fread(cat0[0], sizeof(int), Ks[L-1], fpC);
		if (isize != Ks[L-1])  goto error;
	}

	printf("Scale of the network:\n");
	for (l = 0; l < L; l++) {
		printf("    Stage %d:        Ks = %d,      Mas = %d\n", l+1, Ks[l], Mas[l]);
	}
	printf("\n");
	fclose(fpC);
	return;

error:	printf("i/o error in fpC:       isize=%d\n", isize);
		fclose(fpC);
		return;
}



void printu(
	FILE	*fp,		// (in) file pointer
	double	***u,		// (in) layer to be printed: u[K][N][N]
	double	*umax,		// (in) max response of cell-planes: umax[K]
	int		N,			// size of a cell-plane: (n*2+1)
	int		K,			// number of cell-planes
	char	title[],	// title to be printed
	int		l			// stage number to be printed in the title. if (l<0) no print
	)
{
	int		k, i, j, iuu, line;
	double	amax, anorm, uu;
	char	ch[2] = " ";
	int		n = N / 2;		// N=(n*2+1)

	amax = 0.0;
	for (k = 0; k < K; k++) {
		if (umax[k] > amax)  amax = umax[k];
	}
	if (l >= 0) {
		fprintf(fp, "\n%s%d      max = %.9f        %d cell-planes\n", title, l, amax, K);
	}
	else {
		fprintf(fp, "\n%s      max = %.9f        %d cell-planes\n", title, amax, K);
	}
	anorm = (amax > 0.0) ?  10.0 / amax : 0.0;

	if (N == 1) {
		if (amax > 0.0) {
			fprintf(fp, "\n   ");
			for (k = 0; k < K; k++)  fprintf(fp, "%3d", k);
			fprintf(fp, "\n   ");
			for (k = 0; k < K; k++) {
				uu = u[k][0][0] * anorm;
				if (uu == 0.0)  ch[0] = ' ';
				else if (u[k][0][0] == amax)  ch[0] = 'X';
				else if (uu < 0.0)  ch[0] = '-';
				else if (uu < 0.01)  ch[0] = '_';
				else  ch[0] = '0' + ((int) uu);
				fprintf(fp, "  %1s", ch);
			}
			fprintf(fp, "\n");
		}
		return;
	}

	for (k = 0; k < K; k++) {
		if (umax[k] > 0.0) {
			if (K != 1) {
				if (l >= 0) {
					fprintf(fp, "\n %s%d(k=%d)  (max of this cell-plane) = %.9f\n", title, l, k, umax[k]);
				}
				else {
					fprintf(fp, "\n %s(k=%d)  (max of this cell-plane) = %.9f\n", title, k, umax[k]);
				}
			}

			fprintf(fp, "   ");
			for (j = -n; j <= n; j++)  fprintf(fp, "%1d", abs(j) % 10);
			fprintf(fp, "\n");

			fprintf(fp, "   ");
			for (j = 0; j < N; j++)  fprintf(fp, "*");
			fprintf(fp, "\n");

			for (i = 0; i < N; i++) {
				line = abs(i - n);
				fprintf(fp, "%2d*", line);
				for (j = 0; j < N; j++) {
					uu = u[k][i][j] * anorm;
					iuu = (int) uu;
					if (u[k][i][j] == amax)  iuu = 10;		// in case of rounding error

					if (uu == 0.0) {
						if ( (abs(j-n) % 10 == 0) || (line % 10 == 0) )  ch[0] = ',';
						else  ch[0] = '.';
					}
					else if (uu < 0.0) {
						ch[0] = '-';
					}
					else if (uu < 0.01) {
						ch[0] = '_';
					}
					else if (iuu >= 10) {
						ch[0] = 'X';
					}
					else {
						ch[0] = '0' + iuu;
					}
					fprintf(fp, "%1s", ch);
				}
				fprintf(fp, "*%1d\n", line % 10);
			}

			fprintf(fp, "   ");
			for (j = 0; j < N; j++)  fprintf(fp, "*");
			fprintf(fp, "\n");

			fprintf(fp, "   ");
			for (j = -n; j <= n; j++)  fprintf(fp, "%1d", abs(j) % 10);
			fprintf(fp, "\n");
		}
	}
}



void outH1(				// hexadecinmal output of the response of a layer
	FILE	*fp,		// (in) file pointer
	double	***u,		// (in) layer to be printed: u[K][N][N]
	double	*umax,		// (in) max response of cell-planes: umax[K]
	int		N,			// size of a cell-plane: (n*2+1)
	int		K,			// number of cell-planes
	char	title[],	// title to be printed
	int		l			// stage number to be printed in the title. if (l<0) no print
	)
{
	int		k, i, j, iuu, line;
	double	amax, anorm, uu;
	char	ch[2] = " ";
	int		n = N / 2;		// N=(n*2+1)

	if (l >= 0) {
		fprintf(fp, "/%s%1dplnumber %d def\n", title, l, K);
														// "/??plnumber K def"
		fprintf(fp, "/%s%1dpattern %d array def\n", title, l, K);
														// "/??pattern K array def"
		fprintf(fp, "/%s%1dpattern [\n", title, l);		// "/??pattern ["
	} else {
		fprintf(fp, "/%splnumber %d def\n", title, K);
														// "/?plnumber K def"
		fprintf(fp, "/%spattern %d array def\n", title, K);
														// "/?pattern K array def"
		fprintf(fp, "/%spattern [\n", title);			// "/?pattern ["
	}

	amax = 0.0;
	for (k = 0; k < K; k++) {
		if (umax[k] > amax)  amax = umax[k];
	}
	anorm = (amax > 0.0) ?  16.0 / amax : 0.0;

	for (k = 0; k < K; k++) {
		if (umax[k] > 0.0) {
			fprintf(fp, "<\n");
			for (i = 0; i < N; i++) {
				line = abs(i - n);
				for (j = 0; j < N; j++) {
					uu = u[k][i][j] * anorm;
					iuu = 15 - ((int) uu);
					if (iuu > 15) {
						iuu = 15;
					} else if (iuu < 0) {
						iuu = 0;
					}
					fprintf(fp, "%1X", iuu);
				}
				fprintf(fp, "F\n");
			}
			fprintf(fp, ">\n");
		} else {
			fprintf(fp, "<FF>\n");
		}
	}
	fprintf(fp, "] def\n");
}



void printuadd(			// print sum of k1-th to k2-th cell-planes
	FILE	*fp,		// (in) file pointer
	double	***u,		// (in) layer to be printed: u[K][N][N]
	double	*umax,		// (in) max response of cell-planes: umax[K]
	int		N,			// size of a cell-plane: (n*2+1)
	char	title[],	// title to be printed
	int		l,			// stage number to be printed in the title. if (l<0) no print
	int		k1,			// added cell-planes from k1
	int		k2			// added cell-planes to k2
	)
{
	int		k, i, j, iuu, line;
	double	amax, anorm, uu, uuu;
	char	ch[2] = " ";
	int		n = N / 2;		// N=(n*2+1)

	amax = 0.0;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			uu = 0.0;
			for (k = k1; k <= k2; k++) {
				uu += u[k][i][j];
			}
			if (amax < uu)  amax = uu;
		}
	}

	if (l >= 0) {
		fprintf(fp, "\n%s%d        Sum of the %d-th to the %d-th cell-planes      max = %.9f\n",
													title, l, k1, k2, amax);
	}
	else {
		fprintf(fp, "\n%s        Sum of the %d-th to the %d-th cell-planes      max = %.9f\n",
													title, k1, k2, amax);
	}

	if (amax > 0.0) {
		anorm = 10.0 / amax;
		fprintf(fp, "   ");
		for (j = -n; j <= n; j++)  fprintf(fp, "%1d", abs(j) % 10);
		fprintf(fp, "\n");

		fprintf(fp, "   ");
		for (j = 0; j < N; j++)  fprintf(fp, "*");
		fprintf(fp, "\n");

		for (i = 0; i < N; i++) {
			line = abs(i - n);
			fprintf(fp, "%2d*", line);
			for (j = 0; j < N; j++) {
				uuu = 0.0;
				for (k = k1; k <= k2; k++) {
					uuu += u[k][i][j];
				}
				uu = uuu * anorm;
				iuu = (int) uu;

				if (uuu == amax) {
					iuu = 10;		// in case of rounding error
				}
				if (uu == 0.0) {
					if ( (abs(j-n) % 10 == 0) || (line % 10 == 0) )  ch[0] = ',';
					else  ch[0] = '.';
				}
				else if (uu < 0.0) {
					ch[0] = '-';
				}
				else if (uu < 0.01) {
					ch[0] = '_';
				}
				else if (iuu >= 10) {
					ch[0] = 'X';
				}
				else {
					ch[0] = '0' + iuu;
				}
				fprintf(fp, "%1s", ch);
			}
			fprintf(fp, "*%1d\n", line % 10);
		}

		fprintf(fp, "   ");
		for (j = 0; j < N; j++)  fprintf(fp, "*");
		fprintf(fp, "\n");

		fprintf(fp, "   ");
		for (j = -n; j <= n; j++)  fprintf(fp, "%1d", abs(j) % 10);
		fprintf(fp, "\n");
	}
}



void pat(					// generate a pattern from a buffer
	double	**u,			// (out) generated pattern: u[N][N]
	double	*umax,			// (out) max value of the pattern umax[1]
	unsigned char	**patP,	// pattern beffer patP[Npat][N*Lchar+1]
	int		Npat,			// Total number of pat. in buffer pat[Npat][N][N]
	int		N,				// size of the layer: (n*2+1)
	int		t				// pattern number
	)
{
	int		i, j, k, l, ip, Lbyte, Lchar;

	Lbyte= N / 8;
	if ((N % 8) != 0)  Lbyte++;		// number of Bytes/line
	Lchar = Lbyte * 2;				// number of characters/line (1 Byte = 2 characters)

	t = t % Npat;
	umax[0] = 1.0;
	for (i = 0; i < N; i++) {
		k = i * Lchar;
		l = 0;
		for (j = 0; j < N; j++) {
			if (l == 0) {
				ip = patP[t][k] - '0';
				if (ip > 9)  ip = patP[t][k] - 'A' + 10;
			}
			if (ip >= 8) {
				u[i][j] = 0.0;
				ip -= 8;
			} else {
				u[i][j] = 1.0;
			}
			ip *= 2;
			l++;
			if (l >= 4) {
				l = 0;
				k++;
			}
		}
	}
}



unsigned char **patread(	// create buffer pat[Npat][Nchar] and read patterns
	char	*fnameP,		// (in) file name
	int		*NpatAddress,	// (out) &Npat = Total number of pat.: Npat=NpatAddress[0]
	int		N				// size of the layer: (n*2+1)
	)
{
	unsigned char	**pat;				// pat[Npat][Nchar]
	char	dummy[65];
	FILE	*fpP;						// file pointer
	int		i, l, ipat, Npat, Lbyte, Lchar, Nchar;

	Lbyte= N / 8;
	if ((N % 8) != 0)  Lbyte++;		// number of Bytes/line
	Lchar = Lbyte * 2;				// number of characters/line (1 Byte = 2 characters)
	Nchar = N * Lchar + 1;

	fpP = fopen(fnameP, "r");
    if (fpP == NULL) {
		printf("file open error fpP\n");
		exit(1);
	}
	if (fscanf(fpP, "%d", NpatAddress) == EOF) {;	// read the number of patterns
		printf("seek error at the beginning of the file fpP\n");
		fclose(fpP);
		exit(1);
	}
	Npat = NpatAddress[0];

	pat = (unsigned char **)malloc(sizeof(unsigned char *) * Npat);
	if (pat == NULL)  printf("Memory allocation error!\n");
	pat[0] = (unsigned char *)malloc(sizeof(unsigned char) * Npat * Nchar);
	if (pat[0] == NULL)  printf("Memory allocation error!\n");
	for (i = 1; i < Npat; i++) {
		pat[i] = pat[i-1] + Nchar;
	}

	for (ipat = 0; ipat < Npat; ipat++) {
		if (fscanf(fpP, "%s", dummy) == EOF) {;
			printf("seek error at the beginning of a pat in fpP\n");
			fclose(fpP);
			exit(1);
		}
		for (l = 0; l < 19; l++) {
			if (fscanf(fpP, "%s", &pat[ipat][l*64]) == EOF) {
				printf("seek error at    ipat=%d,  l=%d\n", ipat, l);
				fclose(fpP);
				exit(1);
			}
		}
	}
	fclose(fpP);
	return pat;
}



void Ssup(				// suppressed response of S-layer
	double	***us,		// (i/o) response of S-cells: us[Ks][Ns][Ns]
	double	*usmax,		// (out) max response of S-cell-planes: usmax[Ks]
	double	***umask,	// (in) masking pattern: unask[1][Ns][Ns]
	double	**csup,		// (in) connections for blurring masking pat: csup[Na][Na]
	int		Ns,			// size of the S-layer: (ns*2+1)
	int		Ks,			// numberof cell-planes in S-layer
	int		Na			// size of the connections csup: (na*2+1)
	)
{
	int		is, js, ks, ia, ja, isa, jsa;
	double	uu;
	int		na = Na / 2;			// Na=(na*2+1)

	for (is = 0; is < Ns; is++) {
		for (js = 0; js < Ns; js++) {
			if ((uu = umask[0][is][js]) > 0.0) {
				for (ia = 0; ia < Na; ia++) {
					isa = is + ia - na;
					if (isa > 0 && isa < Ns) {
						for (ja = 0; ja < Na; ja++) {
							jsa = js + ja - na;
							if (jsa > 0 && jsa < Ns) {
								for (ks = 0; ks < Ks; ks++) {
									us[ks][isa][jsa] -= csup[ia][ja] * uu;
								}
							}
						}
					}
				}
			}
		}
	}
	for (ks = 0; ks < Ks; ks++) {
		usmax[ks] = 0.0;
		for (is = 0; is < Ns; is++) {
			for (js = 0; js < Ns; js++) {
				if ((uu = us[ks][is][js]) > 0.0) {
					if (uu > usmax[ks])  usmax[ks] = uu;
				} else {
					us[ks][is][js] = 0.0;
				}
			}
		}
	}
}



void patmask(			// combine masked and masking patterns
	double	**u,		// (out) generated pattern: u[N][N]
	double	*umax,		// (out) max value of the pattern umax[1]
	double	**upat,		// (in) masked pattern: upat[N][N]
	double	**umask,	// (in) masking pattern: umask[N][N]
	double	amask,		// amplitude (or gain) for umask[n][n]
	int		N			// size of the layer: (n*2+1)
	)
{
	int		i, j;
	double	amask1;

	umax[0] = 0.0;
	if (amask <= 1.0) {
		for (i = 0; i < 65; i++) {
			for (j = 0; j < 65; j++) {
				if (umask[i][j] > 0.0) {
					u[i][j] = umask[i][j] * amask;
				} else {
					u[i][j] = upat[i][j];
				}
				if (u[i][j] > umax[0])  umax[0] = u[i][j];
			}
		}
	} else {
		amask1 = 1.0 / amask;
		for (i = 0; i < 65; i++) {
			for (j = 0; j < 65; j++) {
				if (umask[i][j] > 0.0) {
					u[i][j] = umask[i][j];
				} else {
					u[i][j] = upat[i][j] * amask1;
				}
				if (u[i][j] > umax[0])  umax[0] = u[i][j];
			}
		}
	}
}



