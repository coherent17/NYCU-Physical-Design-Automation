.subckt XOR8 A B OUT 
mp1 out b 1 vdd pmos_rvt l=0.18u w=0.15n nfin=3
mp2 1 abar vdd vdd pmos_rvt l=0.18u w=0.15n nfin=3
mp3 2 a vdd vdd pmos_rvt l=0.18u w=0.15n nfin=3
mp4 out bbar 2 vdd pmos_rvt l=0.18u w=0.15n nfin=3
mn1 out b 3 gnd nmos_rvt l=0.18u w=0.15n nfin=3
mn2 3 a gnd gnd nmos_rvt l=0.18u w=0.15n nfin=3
mn3 out bbar 4 gnd nmos_rvt l=0.18u w=0.15n nfin=3
mn4 4 abar gnd gnd nmos_rvt l=0.18u w=0.15n nfin=3
.ENDS