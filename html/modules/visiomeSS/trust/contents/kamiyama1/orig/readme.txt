NRV Project Model Distribution
==============================

Title:
 Rod Photoreceptor Model 
Author: 
 Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
Reference Paper: 
 Kamiyama, Y., Ogura, T. and Usui, S. (1996),
 Ionic current model of the vertebrate rod photoreceptor,
 Vision Research, Vol.36, No.24, pp.4059-4068
-------------------------------------------------------------

This package contains the following files:

 README
   This file.	
 nrv-rod.mdl
   Model descriptions written in NCS language. 
 nrv-rod.sl
   SATELLITE shell script file for running the model.

HOW TO RUN
----------

0) This package is running with SATELLITE system developed at
   Biological & Physiological Engineering Laboratory, Toyohashi
   University of Technology. SATELLITE will be found in the 
   followings: 
       http://www.nrv.neuroinformatics.jp/
       ftp://ftp.nrv.neuroinformatics.jp/

1) Put "nrv-rod.mdl" and "nrv-rod.sl" in the same working directory.

2) In the working directory, run SATELLITE by "sl" command. 

3) Execute the script by "inline("nrv-rod.sl")".

   The simulation results as in Figure 5 of the reference paper will
   be displayed.

For further information, please contact:

Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
Faculty of Information System and Technology
Aichi Prefectural University
Nagakute, Aichi, 480-1198
Japan
$Revision: 1.1 $ Last updated $Date: 2008/05/14 02:54:16 $