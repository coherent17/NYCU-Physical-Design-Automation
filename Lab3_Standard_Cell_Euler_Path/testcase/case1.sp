.SUBCKT OR4x2_ASAP7_75t_R A B C D VDD VSS Y
MM9 Y net12 VSS VSS nmos_rvt w=81.0n l=20n nfin=3
MM3 net12 D VSS VSS nmos_rvt w=81.0n l=20n nfin=3
MM2 net12 C VSS VSS nmos_rvt w=81.0n l=20n nfin=3
MM1 net12 B VSS VSS nmos_rvt w=81.0n l=20n nfin=3
MM0 net12 A VSS VSS nmos_rvt w=81.0n l=20n nfin=3
MM8 Y net12 VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM7 net12 A pd1 VDD pmos_rvt w=162.00n l=20n nfin=6
MM6 pd1 B pd2 VDD pmos_rvt w=162.00n l=20n nfin=6
MM5 pd2 C pd3 VDD pmos_rvt w=162.00n l=20n nfin=6
MM4 pd3 D VDD VDD pmos_rvt w=162.00n l=20n nfin=6
.ENDS