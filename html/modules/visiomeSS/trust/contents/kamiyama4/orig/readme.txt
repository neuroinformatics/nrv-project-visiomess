NRV Project Model Distribution
==============================

Title:
 A Stochastic Model of Retinal Ganglion Cell
Author:
 KAMIYAMA Yoshimi
e-mail:
 kamiyama@ist.aichi-pu.ac.jp
Reference Paper:
 Kamiyama, Y. and Usui. S. (2002)
 A stochastic model of spike generation in retinal ganglion cells 
 Society for Neuroscience 
-------------------------------------------------------------

This package contains the following files:

 Readme.txt
   This file.	

 rgc-markov            (for Linux)
 rgc-markov.exe        (for Windows) 
   Binary model files for the stochastic model of retinal ganglion cell.
 rgc-deterministic     (for Linux)  
 rgc-deterministic.exe (for Windows)
   Binary model files for the deterministic model of retinal ganglion cell.
 vclamp-area.sl
   SATELLITE shell script file for voltage clamp with the model.
   The script writes the results in data files and displays the
   results in the GPM window. 
	The voltage-clamp step response of the membrane conductances,
   gNa, gCa, gK, gA will be displayed.
 cc-noise.sl
   SATELLITE shell script file for current clamp with the model.
   The script writes the results in 40 data files and displays the
   results in the GPM window.  
	Twenty superimposed spike responses and the raster plots to
   repeated DC and Gaussian current stimuli will be displayed.  
  	
 
HOW TO RUN
----------

0) This package is running with SATELLITE system developed at
   Biological & Physiological Engineering Laboratory, Toyohashi
   University of Technology. SATELLITE will be found in the 
   followings: 
       http://www.nrv.neuroinformatics.jp/
       ftp://ftp.nrv.neuroinformatics.jp/

1) Put all files in the same working directory.

2) In the working directory, run SATELLITE by "sl" command. 

3) Execute the script by inline command, 
   [SATELLITE]% inline("vclamp-area.sl")
   or
   [SATELLITE]% inline("cc-noise.sl")

   The simulated results will be displayed on the GPM window.

For further information, please contact:

Yoshimi Kamiyama (kamiyama@ist.aichi-pu.ac.jp)
Information Science and Technology
Aichi Prefectural University
Nagakute, Aichi, 480-1198
Japan
// Copyright 2003, KAMIYAMA Yoshimi
// $Revision: 1.1 $ Last updated $Date: 2008/05/19 05:31:08 $
// $Author: okumura $ 