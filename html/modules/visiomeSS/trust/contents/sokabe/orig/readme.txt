TITLE: A Structure-Function Study on a de novo Synthetic Hydrophobic Ion Channel
AUTHORS: Zhi Qi, Masahiro Sokabe, Kiyoshi Donowaki , and Hitoshi Ishida

Original Report:Z. Qi, M. Sokabe, K. Donowaki , and H. Ishida 1999 A Structure-Function Study on a de novo Synthetic Hydrophobic Ion Channel. Biophys. J. 76 (1999): 631-641

Email:msokabe@med.nagoya-u.ac.jp

[[MODEL]]-----------------------------------------------------

Software: Ajuste 95.
Description: The "Ajuste 95" is a software that can calculate ion currents from energy profiles 
and energy profiles from ion currents in multibarrier, multisite, multioccupancy channel model 
(See reference 1 for detail). 


[How to run]

Based on the inferred structure of the channel, we inferred the channel has two binding sites. 
Furthermore, electrophysiological data strongly suggest this is a one-ion channel. Therefore, a 
three energy barriers two binding sites (3B2S) model of Eyring rate theory with one ion 
occupancy (one-ion channel) is applied to calculate energy profiles of ions. To reduce the 
uncertainty of the model, sets of experimental data under different ionic conditions were used to 
get the model parameters. These data include I-V data at both symmetrical (5, 10, 50, 100, 200 
and 500 mM [ K+]) and biionic (10, 50, 100, 500 mM [ K+/Na+] as well as 50, 500 mM [K+/Li+]) 
conditions according to Alvarez, et. al. (1992). The values for electrical distances of energy 
barriers and energy wells were not pre-set, but were adjusted gradually as long as the 
symmetrical energy profile was ensured. Optimization of the parameters underwent several steps. 
First, energetic parameters (energy values at peaks, G1, G2, G3, and wells, U1, U2) for each ion 
were varied with fixed symmetrical distance parameters. Next, the distance parameters and 
energetic parameters were optimized simultaneously. Then, the distance parameters (D1, D2, D3, 
D4, D5, L1, L2) were fixed at new values, and the energetic parameters were reoptimized. These 
steps were repeated several times until the SUMSQ, the weighted sum of squared differences of 
experimental and theoretical data, was minimized. The final results are shown in the following 
table and figure. The electric distance of the binding site, D = D1 + D2, is 0.054 for monovalent 
cations.


[References]

1) O. Alvarez, A. Villarroel, and G. Eisenman. 1992. Calculation of ion currents from energy 
profiles and energy profiles from ion currents in multibarrier, multisite, multioccupancy channel 
model. Method. Enzymol. 207:816-854. 
2)  Z. Qi, M. Sokabe, K. Donowaki , and H. Ishida 1999 A Structure-Function Study on a de 
novo Synthetic Hydrophobic Ion Channel. Biophys. J. 76 (1999): 631-641


Ion Channel:
We measured single channel properties of an artificial ion channel. The permeability ratio 
between K+ and Na+ keeps constant under various biionic solutions, suggesting that the channel 
has a one-ion channel property. To correlate the structure and function of the channel, we built 
energy profiles for ions permeation through the channel according to 3B2S model of Eyring's 
theory. The fitting parameters are shown in the table.


TABLE  Best-fit energy profile parameters of the 3B2S model for Na+, Li+ and K+　
　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　   　　　　　　　　　　                 
 　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　                  　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　                  
 Parameter	    K+  (RT)       Na+  (RT)        Li+  (RT)
　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　                  　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　                  　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　   　　      　　　　　                 
    G1               4.57 ± 0.01     5.68 ± 0.08        30.90 ± 0.01
    G1               6.18 ± 0.01     6.95 ± 0.13        30.77 ± 0.26
    G3               4.57 ± 0.01     5.68 ± 0.08        30.90 ± 0.01
    U1              -8.19 ± 0.01     -7.59 ± 0.05        -9.63 ± 0.01
    U2              -8.19 ± 0.01     -7.59 ± 0.05        -9.63 ± 0.01
　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　                  　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　                  
Fitting routine is described in the text. Final values of distance parameters obtained from the 
routine are: D1=D3=0.047, D2=D4=0.007 and D5=0.5. The minimized value of weighted 
sum of squared differences of experimental and theoretical data, SUMSQ, is 2.93.


<mdl_fig1.jpg>

Figure caption
Best-fit energy barrier profiles for K+, Na+ and Li+ permeation through the AC164 channel. (A) 
Schematic diagram of the 3B2S model parameters. The peak energies, G1, G2, and G3, well 
energies, U1 and U2, are referred to the energy level of the cis and trans solutions in unit of RT 
with their positions defined as D1-D5. (B) Best-fit energy profiles for K+, Na+, and Li+ at 0 mV. 
Lines are drawn according to the energy parameters listed in the Table and the distance 
parameters: D1=D3=0.047, D2=D4=0.007 and D5=0.5. (C) CPK model of a side view of the 
AC164 channel. Double arrows indicate the most possible locations of the binding sites that 
correspond the energy wells.


[[DATA]]-----------------------------------------------------


Single Ion Channel:
We measured single channel currents of an artificial ion channel (AC164) reconsituted in lipid bilayers. The permeability ratio between K+ and Na+ keeps constant under various biionic solutions, suggesting that the channel has a one-ion channel property. To correlate the structure and function of the channel, we built energy profiles for ions permeation through the channel according to 3B2S model of Eyring's rate theory. 

<ex_fig1.jpg>

Figure caption
(Left) Single channel current traces under symmetric 500 mM KCl at different voltages. 
(Right) Single-channel current-voltage relationships of the AC164 channel under various biionic conditions. 

[References]
" A Structure-Function Study on a de novo Synthetic Hydrophobic Ion Channel" Zhi Qi, Masahiro Sokabe, Kiyoshi Donowaki , and Hitoshi Ishida  Biophys. J. 76 (1999): 631-641

About data (two sets)

1.	Current-voltage relation of the channel under various biionic conditions
Filename="ex_sample_data1.xls"

Column A: voltage in mV under symmetric solution of 500 mM K+;
Column B: corresponding current of column A;
Column C: voltage in mV under biionic condiiton of 500 mM K+/Na+;
Column D: corresponding current of column C;
Column E: voltage in mV under biionic condiiton of 100 mM K+/Na+;
Column F: corresponding current of column E;
Column G: voltage in mV under biionic condiiton of 50 mM K+/Na+;
Column H: corresponding current of column G;
Column I: voltage in mV under biionic condiiton of 10 mM K+/Na+;
Column J: corresponding current of column I;
Column K: voltage in mV under biionic condiiton of 500 mM K+/Li+;
Column L: corresponding current of column K;
Column M: voltage in mV under biionic condiiton of 50 mM K+/Li+;
Column N: corresponding current of column M.

2.	Current traces of the channel at different voltage values under symmetrical solution of 500 mM K+
Filename="ex_sample_data2.xls"

Column A: time in msec;
Column B: current trace at voltage of -104 mV;
Column C: current trace at voltage of -94 mV;
Column D: current trace at voltage of -84 mV;
Column E: current trace at voltage of -77 mV;
Column F: current trace at voltage of -68 mV;
Column G: current trace at voltage of -56 mV;
Column H: current trace at voltage of -43 mV;
Column I: current trace at voltage of +48 mV;
Column J: current trace at voltage of +54 mV;
Column K: current trace at voltage of +61 mV;
Column L: current trace at voltage of +68 mV.


