/*
      Hodgkin-Huxley model: HH01.mdl
      2000, 12,  4   by. H.Ikeno
      Geometry     L: length (um), diam: diameter (um)
*/

type:              NETWORK;
module:            single;
cell:              HH[1];
connection:        HH[0] < ();
end;

type:              CELL;
module:            HH;
exinput:           Iext;
output:            V;
observable:        INa, IK, IL, m, h, n;
parameter:         L    = @@@NUMBER:10.@@@,   /* (um) */
                   diam = @@@NUMBER:10.@@@,   /* (um) */

                   Cm   = @@@NUMBER:1.0@@@,   /* (uF/cm2) */
                   GNa  = @@@NUMBER:120.0@@@,   /* (millisiemens/cm2) */
                   ENa  = @@@NUMBER:55.0@@@,   /* (millivolt) */	
                   GK   = @@@NUMBER:36.0@@@,   /* (millisiemens/cm2) */
                   EK   = @@@NUMBER:-72.0@@@,   /* (millivolt) */	
                   GL   = @@@NUMBER:0.3@@@,   /* (millisiemens/cm2) */
                   EL   = @@@NUMBER:-54.3@@@,   /* (millivolt) */	

                   V0   = @@@NUMBER:-65.@@@,   /* (millivolt) */
                   m0   = @@@NUMBER:0.02964@@@,
                   h0   = @@@NUMBER:0.6385@@@,
                   n0   = @@@NUMBER:0.3601@@@;
function:          S1 = ( (PI*diam*L)
                        + 2.*PI*(diam/2.)*(diam/2.) ) * 1e-8;
                                                   /* (um2)->(cm2) */

                   if (V != -35.) {
                      am = 0.1*(-35.-V)/(exp((-35.-V)/10.)-1.);
                   } else {
                      am = 0.1 * 10.;
                   }
                   bm = 4.*exp(-(V+60.)/18.);
                   dm = am*(1.-m) - bm*m;
                   m  = integral(m0, dm);

                   ah = 0.07*exp(-(V+60.)/20.);
                   bh = 1./(exp((-30.-V)/10.)+1.);
                   dh = ah*(1.-h) - bh*h;
                   h  = integral(h0, dh);
                   INa = GNa * pow(m, 3.) * h * (V-ENa);

                   if (V != -50.) {
                       an = 0.01*(-50.-V)/(exp((-50.-V)/10.)-1.);
                   } else {
                       an = 0.01 * 10.;
                   }
                   bn = 0.125*exp(-(V+60.)/80.);
                   dn = an*(1.-n) - bn*n;
                   n  = integral(n0, dn);
                   IK = GK * pow(n, 4.) * (V-EK);

                   IL = GL * (V-EL);

                   I = Iext/S1 - INa - IK - IL;
                   dV = I / Cm;
                   V = integral(V0, dV);
end;
