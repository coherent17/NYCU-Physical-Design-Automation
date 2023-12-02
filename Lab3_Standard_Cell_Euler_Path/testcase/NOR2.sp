.SUBCKT NOR2 A B VDD VSS Y
MM2 Y A VSS VSS nmos_rvt w=81.0n l=20n nfin=3
MM1 Y B VSS VSS nmos_rvt w=81.0n l=20n nfin=3
MM4 Y B net1 VDD pmos_rvt w=162.00n l=20n nfin=6
MM3 net1 A VDD VDD pmos_rvt w=162.00n l=20n nfin=6
.ENDS