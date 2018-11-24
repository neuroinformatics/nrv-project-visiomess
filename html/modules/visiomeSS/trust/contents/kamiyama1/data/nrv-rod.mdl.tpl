/* $VisiomeSS-Revision: 1.3 $ $VisiomeSS-Date: 2001/02/02 00:36:19 $
File: 
  nrv-rod.mdl
Title:
  Rod Photoreceptor Model 
Author: 
  Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
Reference Paper: 
  Kamiyama, Y., Ogura, T. and Usui, S. (1996),
  Ionic current model of the vertebrate rod photoreceptor,
  Vision Research, Vol.36, No.24, pp.4059-4068
*/
type: NETWORK;
module: SingleROD;
cell: Rod[1];
connection: Rod[0]<();
end;

type:           CELL;
module:         Rod;
exinput:        Jhv;
output:         V;
observable:     Ca, Cb, Rh, Rhi, T, PDE, cg,
                mCa, Ca_s, Cab_ls, Cab_hs,
                Ca_f, Cab_lf, Cab_hf,
                mKv, mKh, mKc, C1,
                C2, OP1, OP2, OP3,
                Iphoto, Ip2, Jphoto,
                ICa, ICl, IKv, IKc, Ih, Il;
parameter:

/*
  ---Outer Segment Parameters
  Rh: active rhodopsin (uM)
  Rhi: inactive rhodopsin (uM)
  T: active transducin (uM)
  Tt: total transducin (uM)  
  alpha1: rate constant of Rh* inactivation (/s)
  alpha2: rate constant of the reaction Rhi->Rh* (/s)
  alpha3: rate constant of the decay of inactive rhodopsin (/s)
  epsilon: rate constant of T* activation(/s uM)
  beta1: rate constant of T* inactivation (/s)
  tau1: rate constant of PDE activation (/s uM)
  tau2: rate constant of PDE inactivation (/s)
  PDE: activated phosphodiesterase (uM)
  PDEt: phosphodiesterase (uM)
  sigma: proportionality constant (/s uM)
  gammaCa: rate constant of Ca extrusion in the absence of Ca buffers
           mediated by the Na-Ca exchanger (/s)
  Ca: intracellular free Ca concentraion (uM)
  Cb: intracellular Ca concentration bound to the low-affinity buffer (uM)
  Co: intracellular Ca concentration at the steady state (uM)
  xb: proportionality constant between Ca influx and photocurrent (uM/s pA)
  k1: on rate constant for the binding of Ca to the buffer (/s uM)
  k2: off rate constant for the binding of Ca to the buffer (/s)
  et: low-affinity Ca buffer concentration (uM)
  Vd: cyclic GMP hydrolysis in dark (/s)
  kc: intracellular Ca concentration halving the cyclase activity
  Amax: maximal activity of guanylate cyclase (uM/s)
  Jmax: maximal cyclic GMP gate current in excised patches (pA)
  phg: proportionality constant

  ---Inner Segment Parameters
  V: membrane potential (mV)
  ICa: calcium current
  ICl: Ca-dependent Cl current
  IKv: delayed rectifying K current
  IKc: Ca-dependent K current
  Ih: hyperpolarization activated current
  Il: leakage current
  Ca_s: Ca concentration in submembrane area
  Ca_f: Ca concentration in free intracellular area
  Cab_ls: submembrane Ca concentration bound to low affinity buffer
  Cab_hs: submembrane Ca concentration bound to high affinity buffer
  Cab_lf: free intracellular Ca concentration bound to low affinity buffer
  Cab_hf: free intracellular Ca concentration bound to high affinity buffer
  Iex: Na-Ca exchanger current
  Iex2: Ca-ATPase pump current
  Lb1: on rate constant for the binding of Ca to low affinity buffer
  Lb2: off rate constant for the binding of Ca to low affinity buffer
  Hb1: on rate constant for the binding of Ca to high affinity buffer
  Hb2: on rate constant for the binding of Ca to high affinity buffer
  LB_to: maximum concentraion of low affinity buffer
  HB_to: maximum concentraion of high affinity buffer
  V1: volume of submembrane area
  V2: volume of deep intracellular area
  del: diffusion distance 
  Jex: maximum Na-Ca exchanger current
  Jex2: maximum Ca-ATPase pump current

            Iphoto     Er           
     ------,/\\\\/\\\\/\\\'-----|!--- 
     |      ICa        ECa |
     ------,/\\\\/\\\\/\\\'-----|!--- 
     |      IKv        Ek  |
     ------,/\\\\/\\\\/\\\'-----!|--- 
     |      IKc        Ek  |
     ------,/\\\\/\\\\/\\\'-----!|--- 
     |      Ih         Eh  |
     ------,/\\\\/\\\\/\\\'-----!|--- 
     |      ICl(Ca)    ECl | 
     ------,/\\\\/\\\\/\\\'-----|!--- 
     |      Il         El  |
     ------,/\\\\/\\\\/\\\'-----|!--- 
     |                     |
     --------(INa-K)--------
     |        IC           | 
     ----------||-----------

  
*/

  /* Outer Segment */
  Rh_0 = @@@NUMBER:0.@@@, Rhi_0 = @@@NUMBER:0.@@@, T_0 = @@@NUMBER:0.@@@, PDE_0 = @@@NUMBER:0.@@@,
  Ca_0 = @@@NUMBER:0.32092159986495972@@@,
  Cb_0 = @@@NUMBER:37.135780334472656@@@,
  cg_0 = @@@NUMBER:1.5316969156265259@@@,
  alpha1var = @@@NUMBER:61.173716@@@, alpha1max = @@@NUMBER:100.@@@, K_alpha = @@@NUMBER:0.1@@@,
  mm = @@@NUMBER:2.0@@@, alpha2 = @@@NUMBER:0.0005@@@, alpha3 = @@@NUMBER:0.05@@@, ep = @@@NUMBER:0.5@@@,
  Tt = @@@NUMBER:1000.@@@, beta1 = @@@NUMBER:10.6@@@, tau1 = @@@NUMBER:0.1@@@, tau2 = @@@NUMBER:10.@@@, 
  PDEt = @@@NUMBER:100.@@@, sigma = @@@NUMBER:1.@@@, gamma = @@@NUMBER:50.@@@, Co = @@@NUMBER:0.1@@@, 
  xb = @@@NUMBER:0.625@@@, k1 = @@@NUMBER:0.2@@@, k2 = @@@NUMBER:0.8@@@, et = @@@NUMBER:500.@@@, Vd = @@@NUMBER:0.4@@@, 
  kc = @@@NUMBER:0.1@@@, Amax = @@@NUMBER:65.6@@@, Jmax = @@@NUMBER:112.@@@, phg = @@@NUMBER:2.0@@@, 

  /* Inner Segment */
  Cm=@@@NUMBER:0.02@@@, 
  V0 = @@@NUMBER:-34.070648193359375@@@,

  /* ICa */
  mCa0 = @@@NUMBER:0.49830064177513123@@@,
  Ca_o = @@@NUMBER:1600.@@@, gCa = @@@NUMBER:0.7@@@,

  /* Ca */
  Ca_s0 = @@@NUMBER:0.166648268699646@@@,
  Ca_f0 = @@@NUMBER:0.166648268699646@@@,
  Cab_ls0 = @@@NUMBER:124.98964691162109@@@,
  Cab_hs0 = @@@NUMBER:46.870632171630859@@@,
  Cab_lf0 = @@@NUMBER:124.98964691162109@@@,
  Cab_hf0 = @@@NUMBER:46.870632171630859@@@,
  F = @@@NUMBER:9.649e4@@@, del = @@@NUMBER:3.e-5@@@, Km = @@@NUMBER:6.0e-8@@@, Kex = @@@NUMBER:2.3@@@, Kex2 = @@@NUMBER:0.5@@@,
  LB_to = @@@NUMBER:500.@@@, HB_to = @@@NUMBER:300.@@@, Lb1 = @@@NUMBER:0.4@@@, Lb2 = @@@NUMBER:0.2@@@, Hb1 = @@@NUMBER:100.@@@, 
  Hb2 = @@@NUMBER:90.@@@, Ca_e = @@@NUMBER:0.01@@@, Jex = @@@NUMBER:20.@@@, Jex2 = @@@NUMBER:20.@@@, V_f = @@@NUMBER:-43.@@@, 
  nc1 = @@@NUMBER:2.@@@,  nc2 = @@@NUMBER:10.@@@, V1 = @@@NUMBER:3.812e-13@@@, V2 = @@@NUMBER:5.236e-13@@@, 
  S1 = @@@NUMBER:3.142e-6@@@, 

  /* ICl */
  ECl=@@@NUMBER:-50.@@@, gcl=@@@NUMBER:6.5@@@, Cl_a=@@@NUMBER:0.37@@@, Cl_b=@@@NUMBER:0.09@@@,

  /* IKv */
  gKv = @@@NUMBER:2.0@@@, Ek =@@@NUMBER:-80.@@@, 
  mKh0 = @@@NUMBER:0.99892538785934448@@@,
  mKv0 = @@@NUMBER:0.45229718089103699@@@,

  /* IKc */
  mKc0 = @@@NUMBER:0.66410070657730103@@@,
  gKc=@@@NUMBER:0.5@@@, mKck=@@@NUMBER:0.3@@@, Kn=@@@NUMBER:1.0@@@,

  /* Ih */
  C1_s = @@@NUMBER:0.70495605468750000000@@@,
  C2_s = @@@NUMBER:0.25758647918701172000@@@,
  OP1_s = @@@NUMBER:0.03529517352581024200@@@,
  OP2_s = @@@NUMBER:0.00214943895116448400@@@,
  OP3_s = @@@NUMBER:0.00004908695700578392@@@,
  Eh=@@@NUMBER:-32.8@@@,
  gh=@@@NUMBER:3.@@@, a1=@@@NUMBER:3.0@@@, a2=@@@NUMBER:14.@@@, El=@@@NUMBER:-55.@@@, gl=@@@NUMBER:0.5@@@, Ink=@@@NUMBER:9.6@@@;

function:

  /* Photosensitive current */
  Ca_d   = xb*(-Iphoto) - gamma*(Ca - Co) - k1*(et - Cb)*Ca +k2*Cb;
  Ca     = integral( Ca_0, Ca_d); 
  Cb_d   = k1*(et - Cb)*Ca - k2*Cb;
  Cb     = integral( Cb_0, Cb_d); 
  alpha1 = alpha1var + (1/(1.+pow((Ca/K_alpha),mm))-0.5)*alpha1max;
  Rh_d   = Jhv - alpha1*Rh + alpha2*Rhi;
  Rh     = integral( Rh_0 , Rh_d);
  Rhi_d  = alpha1*Rh - (alpha2 + alpha3)*Rhi;
  Rhi    = integral( Rhi_0 , Rhi_d);
  T_d    = ep*Rh*( Tt - T) - beta1*T + tau2*PDE;
  T      = integral( T_0 , T_d);
  PDE_d  = tau1*T*(PDEt - PDE) - tau2*PDE;
  PDE    = integral( PDE_0 , PDE_d);
  cg_d   = Amax/(1.+pow((Ca/kc),4.)) - cg*(Vd + sigma*PDE);
  cg     = integral( cg_0, cg_d);
  tmp2   = cg*cg*cg;
  Jphoto = Jmax*(tmp2/(tmp2 + 1000.));
  Iphoto = Jphoto*(V - 10.);
  Ip2    = Iphoto*phg;

  /* Calcium current */
  amCa   = 300.*( 80.- V)/(exp((80.- V)/25.)-1.);
  bmCa   = 1000./(1. + exp((V + 38.)/7.));
  d_mCa  = amCa * ( 1. - mCa ) - bmCa * mCa;
  mCa_4  = pow( mCa,4.);
  ECa    = 12.9 *  log( Ca_o / Ca_s );
  ECa1   = V - ECa;
  ICa    = gCa*mCa_4*exp((40.-V)/18.)/( 1.+ exp((40.-V)/18.))*(V- ECa);
  mCa    = integral( mCa0 ,d_mCa );

 /* Intrecellular calcium */
  dCa_s  = -ICa/(2.*F*V1)*1.E-6 - Km*S1/(V1*del)*(Ca_s - Ca_f)
                + Lb2*Cab_ls - Lb1*Ca_s*(LB_to - Cab_ls)
                + Hb2*Cab_hs - Hb1*Ca_s*(HB_to - Cab_hs)
                -(Iex+Iex2)/(2.*F*V1)*1.E-6;
  Ca_s = integral( Ca_s0 , dCa_s);
  dCab_ls = Lb1*Ca_s*(LB_to - Cab_ls) - Lb2*Cab_ls;
  Cab_ls  = integral( Cab_ls0, dCab_ls);
  dCab_hs = Hb1*Ca_s*(HB_to - Cab_hs) - Hb2*Cab_hs;
  Cab_hs  = integral( Cab_hs0, dCab_hs);
  dCa_f   = Km*S1/(V2*del)*( Ca_s - Ca_f)
                + Lb2*Cab_lf - Lb1*Ca_f*(LB_to - Cab_lf)
                + Hb2*Cab_hf - Hb1*Ca_f*(HB_to - Cab_hf);
  Ca_f    = integral( Ca_f0, dCa_f);
  dCab_lf = Lb1*Ca_f*(LB_to - Cab_lf) - Lb2*Cab_lf;
  Cab_lf  = integral( Cab_lf0, dCab_lf);
  dCab_hf = Hb1*Ca_f*(HB_to - Cab_hf) - Hb2*Cab_hf;
  Cab_hf  = integral( Cab_hf0, dCab_hf);
  Iex = Jex*exp(-(V+14.)/70.)*(Ca_s - Ca_e)/(Ca_s - Ca_e + Kex);
  Iex2 = Jex2*(Ca_s - Ca_e)/(Ca_s - Ca_e + Kex2);

  /* Ca-dependent chloride current */
  mCl_c   = 1. / ( 1. + exp((Cl_a - Ca_s)/Cl_b));
  ICl     = gcl * mCl_c*(V - ECl);

  /* Voltage dependent K curent */
  amKv    = 5. * ( 100. - V ) / (exp((100.-V)/42.) - 1. );
  bmKv    = 9. * exp( -(V-20.) / 40. );
  d_mKv   = amKv * ( 1. - mKv ) - bmKv * mKv;
  mKv     = integral( mKv0, d_mKv );
  amKh    = 0.15 * exp( -V/ 22. );
  bmKh    = 0.4125 / (exp((10. -V)/7.) + 1. );
  d_mKh   = amKh * ( 1. - mKh ) - bmKh * mKh;
  mKh     = integral( mKh0, d_mKh );
  IKv     = gKv * pow(mKv,3.) * mKh*(V - Ek);

  /* Ca-dependent K current */
  mKc_c1  = pow(Ca_s, Kn)/( pow( Ca_s, Kn) +pow( mKck, Kn));
  amKc    = 15. * (80.1 - V ) / ( exp( ( 80.1 - V ) / 40. ) -1. );
  bmKc    = 20. * exp( -V/ 35. );
  d_mKc   = amKc * ( 1. - mKc ) - bmKc * mKc;
  mKc     = integral( mKc0, d_mKc );
  IKc     = gKc * mKc_c1*mKc*mKc*(V - Ek);

  /* Hyperpolarization activated current */
  a       = 8./(exp(( V + 78.)/ 14. )+1.);
  b       = 18./(exp(-( V + 8.)/ 19.)+1.);
  dC1     = b*C2 - 4.*a*C1;
  C1      = integral (C1_s, dC1);
  dC2     = C1*4.*a + OP1*2.*b - C2*b - C2*3.*a;
  C2      = integral (C2_s, dC2);
  dOP1    = C2*3.*a + OP2*3.*b - OP1*2.*(b+a);
  OP1     = integral (OP1_s, dOP1);
  dOP2    = OP1*2.*a + OP3*4.*b - OP2*(3.*b + a);
  OP2     = integral (OP2_s, dOP2);
  dOP3    = a*OP2 - 4.*b*OP3;
  OP3     = integral (OP3_s, dOP3);
  mgh     = OP1+OP2+OP3;
  Ih      = mgh * gh * ( V - Eh);

  /* Leakage current */
  Il      = gl * (V - El);

  /* Voltage */
  I_all   = - (ICa + ICl + Il + IKv + IKc + Ih + Ip2 + Ink);
  dV      = I_all/Cm;
  V       = integral( V0, dV);

end;
