.subckt dff_mtspc d q clk
mp2 t1 d   vdd vdd pmos_rvt l=0.18u w=0.15u nfin=3
mp1 a  clk t1  vdd pmos_rvt l=0.18u w=0.15u nfin=3
mn1 a  d   gnd gnd nmos_rvt l=0.18u w=0.15u nfin=3
mp3 t2 clk vdd vdd pmos_rvt l=0.18u w=0.15u nfin=3
mp7 b  a   t2  vdd pmos_rvt l=0.18u w=0.15u nfin=3
mn3 b  a   t3  gnd nmos_rvt l=0.18u w=0.15u nfin=3
mn2 t3 clk gnd gnd nmos_rvt l=0.18u w=0.15u nfin=3
mp5 q_ b   vdd vdd pmos_rvt l=0.18u w=0.15u nfin=3
mn5 q_ clk t4  gnd nmos_rvt l=0.18u w=0.15u nfin=3
mn4 t4 b   gnd gnd nmos_rvt l=0.18u w=0.15u nfin=3
mp6 q  q_  vdd vdd pmos_rvt l=0.18u w=0.15u nfin=3
mn6 q  q_  gnd gnd nmos_rvt l=0.18u w=0.15u nfin=3
.ENDS