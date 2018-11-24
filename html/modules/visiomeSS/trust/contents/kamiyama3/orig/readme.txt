NRV Project Model Distribution
==============================

Title:
 Ionic Current Model of Bipolar Cell Soma
Author: 
 Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
 Akito Ishihara (ishihara@bpel.ics.tut.ac.jp)
Reference Paper: 
 Usui, S., Ishihara, A., Kamiyama, Y. and Ishii, H. (1996),
 Ionic current model of bipolar cells in lower vertebrate 
 retina, Vision Research, Vol.36, No.24, pp.4096-4076	 
-------------------------------------------------------------

This package contains the following files:

 README
   This file.	
 nrv-BCsoma.mdl
   Model descriptions written in NCS language. 
 nrv-BCsoma.sl
   SATELLITE shell script file for running the model.

HOW TO RUN
----------

0) This package is running with SATELLITE system developed at
   Biological & Physiological Engineering Laboratory, Toyohashi
   University of Technology. SATELLITE will be found in the 
   followings: 
       http://www.nrv.neuroinformatics.jp/
       ftp://ftp.nrv.neuroinformatics.jp/

1) Put "nrv-BCsoma.mdl" and "nrv-BCsoma.sl" in the same working directory.

2) In the working directory, run SATELLITE by "sl" command. 

3) Execute the script by "inline("nrv-BCsoma.sl")".

   The simulation results as in Figure 2 of the reference paper will
   be displayed.

For further information, please contact:

Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
Faculty of Information System and Technology
Aichi Prefectural University
Nagakute, Aichi, 480-1198
Japan
$Revision: 1.1 $ Last updated $Date: 2008/05/14 06:42:42 $