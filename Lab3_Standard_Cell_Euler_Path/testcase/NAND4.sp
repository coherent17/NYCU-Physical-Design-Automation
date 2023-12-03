.SUBCKT NAND4 I1 I2 I3 I4 VDD VSS OUT
MM1 OUT I1 net1 VSS nmos_rvt w=81.0n l=20n nfin=3
MM2 net1 I2 net2 VSS nmos_rvt w=81.0n l=20n nfin=3
MM3 net2 I3 net3 VSS nmos_rvt w=81.0n l=20n nfin=3
MM4 net3 I4 VSS VSS nmos_rvt w=81.0n l=20n nfin=3
MM5 OUT I1 VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM6 OUT I2 VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM7 OUT I3 VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM8 OUT I4 VDD VDD pmos_rvt w=162.00n l=20n nfin=6
.ENDS