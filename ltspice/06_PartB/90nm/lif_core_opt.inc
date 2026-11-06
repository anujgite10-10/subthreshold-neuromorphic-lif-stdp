* Part B 90 nm copy of ltspice/03_PartC_optimization/lif_core_opt.inc: only the model names changed (-> NMOS90 / PMOS90)
* LIF neuron core for Part C (optimisation) - SAME topology as ../01_LIF_baseline/lif_core.inc (Yang et al. Fig. 3)
* Only difference: extra size parameters so individual device groups can be optimised.
*   LSN, LSP : channel length of the 6 Schmitt-trigger devices (MP1 MP2 MN2 MN1 MPF MNF)
*   WM2      : width of the reset transistor M2
* With LSN=LN, LSP=LP, WM2=WN this file is identical to the baseline core.

Cm   vm   0     {CM}
M1   vm   vlk   0     0     NMOS90 W={WN} L={LN}
M2   vm   vrst  0     0     NMOS90 W={WM2} L={LN}

MP1  x    vm    vdd   vdd   PMOS90 W={WP} L={LSP}
MP2  vo   vm    x     vdd   PMOS90 W={WP} L={LSP}
MN2  vo   vm    y     0     NMOS90 W={WN} L={LSN}
MN1  y    vm    0     0     NMOS90 W={WN} L={LSN}
MPF  0    vo    x     vdd   PMOS90 W={WP} L={LSP}
MNF  vdd  vo    y     0     NMOS90 W={WN} L={LSN}

MPW  vrst vo    vwidth vdd  PMOS90 W={WP} L={LP}
MNW  vrst vo    0     0     NMOS90 W={WN} L={LN}

MPO  spike vo   vdd   vdd   PMOS90 W={WP} L={LP}
MNO  spike vo   0     0     NMOS90 W={WN} L={LN}
