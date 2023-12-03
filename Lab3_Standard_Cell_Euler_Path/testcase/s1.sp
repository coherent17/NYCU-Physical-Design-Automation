.SUBCKT s1 A B C D VDD VSS Y
MM1 net1 A VSS VSS nmos_rvt w=81.0n l=20n nfin=3
MM2 net1 B VSS VSS nmos_rvt w=81.0n l=20n nfin=3
MM3 net1 C VSS VSS nmos_rvt w=81.0n l=20n nfin=3
MM4 Y D net1 VSS nmos_rvt w=81.0n l=20n nfin=3
MM5 net2 A VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM6 net3 B net2 VDD pmos_rvt w=162.00n l=20n nfin=6
MM7 Y C net3 VDD pmos_rvt w=162.00n l=20n nfin=6
MM8 Y D VDD VDD pmos_rvt w=162.00n l=20n nfin=6
.ENDS