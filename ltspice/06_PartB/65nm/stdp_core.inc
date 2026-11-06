* Part B 65 nm copy of ltspice/04_STDP/stdp_core.inc: only the model names changed (-> NMOS65 / PMOS65)
* STDP core - Yang et al., ISLPED 2021, Fig. 5 (FROZEN 26 Oct 2026, checkpoint 5a approved)
* Wiring decisions (docs/Phase5_STDP_results.md):
*   A1: spike -> inverter input; inverter output drives the M1/M3 gate and the opposite OTA's gate pin
*   A2 = A2a: the unlabelled NMOS between M1 and M2 (MD1 / MD2) is diode-connected (gate = drain = C1 node)
* Identical to stdp_core_A2a.inc; every testbench from S2 on includes this file.
* Ports used from the testbench: pre post vdd vtaupre vtaupost vrefpre vrefpost vc vw
* Nets: preb/postb = inverted spikes, c1/c2 = timing capacitors, d1/d2 = M2/M4 drains
* Bulk choice (not drawn in the paper): NMOS -> 0, PMOS -> vdd
.include ota.sub

* upper half (pre-spike trace, sampled by the post-spike -> LTP)
MIP1 preb  pre     vdd  vdd  PMOS65 W={WP} L={LP}
MIN1 preb  pre     0    0    NMOS65 W={WN} L={LN}
M1   c1    preb    vdd  vdd  PMOS65 W={WP} L={LP}
MD1  c1    c1      d1   0    NMOS65 W={WN} L={LN}
M2   d1    vtaupre 0    0    NMOS65 W={WN} L={LN}
C1   c1    0       {C1}
*   OTA pins: inn     inp  bias  gate   vc  w   vdd
XU1  vrefpre  c1   post  postb  vc  vw  vdd  OTA

* lower half (post-spike trace, sampled by the pre-spike -> LTD)
MIP2 postb post     vdd  vdd  PMOS65 W={WP} L={LP}
MIN2 postb post     0    0    NMOS65 W={WN} L={LN}
M3   c2    postb    vdd  vdd  PMOS65 W={WP} L={LP}
MD2  c2    c2       d2   0    NMOS65 W={WN} L={LN}
M4   d2    vtaupost 0    0    NMOS65 W={WN} L={LN}
C2   c2    0        {C2}
XU2  c2   vrefpost  pre   preb   vc  vw  vdd  OTA

* weight capacitor
Cw   vw    0       {CW}
