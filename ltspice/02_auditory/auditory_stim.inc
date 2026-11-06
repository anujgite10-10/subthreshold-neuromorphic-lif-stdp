* Auditory stimulus proxy for one cochlear channel at FC (behavioural test source, NOT part of the circuit under test)
* Delivered as the synaptic input current Iin of the paper's Fig. 3 (the paper generates Iin with Vin + 910k on the bench):
*   Iin(t) = pi * IM * env(t) * max(sin(2*pi*FC*t), 0)
*   -> half-wave rectified tone (first-order inner-hair-cell model); IM = mean current while env = 1
* Envelope building block: burst(x, t0, D, tr) = 1 inside [t0, t0+D] with raised-cosine on/off ramps of length tr

.func rc_on(x, t0, tr)  {0.5*(1 - cos(pi*(x - t0)/tr))}
.func burst(x, t0, D, tr) {if(x < t0, 0, if(x < t0+tr, rc_on(x, t0, tr), if(x < t0+D-tr, 1, if(x < t0+D, rc_on(t0+D-x, 0, tr), 0))))}
.func hwr(x, fc) {max(sin(2*pi*fc*x), 0)}
