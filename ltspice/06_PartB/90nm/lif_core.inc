* Part B 90 nm copy of ltspice/01_LIF_baseline/lif_core.inc: only the model names changed (-> NMOS90 / PMOS90)
* LIF neuron core - Yang et al., ISLPED 2021, Fig. 3 (transistor-for-transistor)
* Shared by every testbench in this folder. All values come from .param in the testbench.
* Nets: vm (membrane), vo (Schmitt output), x / y (Schmitt internal), vrst (M2 gate), spike
* Bulk choice (not drawn in the paper): NMOS -> 0, PMOS -> vdd (one shared n-well)

* membrane capacitor, leak and reset
Cm   vm   0     {CM}
M1   vm   vlk   0     0     NMOS90 W={WN} L={LN}
M2   vm   vrst  0     0     NMOS90 W={WN} L={LN}

* Schmitt trigger (dotted box): 2 PMOS + 2 NMOS stack, gates = vm
MP1  x    vm    vdd   vdd   PMOS90 W={WP} L={LP}
MP2  vo   vm    x     vdd   PMOS90 W={WP} L={LP}
MN2  vo   vm    y     0     NMOS90 W={WN} L={LN}
MN1  y    vm    0     0     NMOS90 W={WN} L={LN}
* hysteresis feedback: PMOS x->gnd, NMOS vdd->y, both gated by vo
MPF  0    vo    x     vdd   PMOS90 W={WP} L={LP}
MNF  vdd  vo    y     0     NMOS90 W={WN} L={LN}

* pulse-width inverter, supplied by Vwidth, drives the reset transistor M2
MPW  vrst vo    vwidth vdd  PMOS90 W={WP} L={LP}
MNW  vrst vo    0     0     NMOS90 W={WN} L={LN}

* output inverter: spike = NOT(vo)
MPO  spike vo   vdd   vdd   PMOS90 W={WP} L={LP}
MNO  spike vo   0     0     NMOS90 W={WN} L={LN}
