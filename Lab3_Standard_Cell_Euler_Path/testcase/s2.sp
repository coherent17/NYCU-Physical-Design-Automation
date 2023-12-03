.SUBCKT s2 A B C D E VDD VSS OUT
MM1 OUT A XN VSS nmos_rvt w=81.0n l=20n nfin=3
MM2 XN B VSS VSS nmos_rvt w=81.0n l=20n nfin=3
MM3 XN C VSS VSS nmos_rvt w=81.0n l=20n nfin=3
MM4 OUT D YN VSS nmos_rvt w=81.0n l=20n nfin=3
MM5 YN E VSS VSS nmos_rvt w=81.0n l=20n nfin=3
MM6 OUT A YP VDD pmos_rvt w=162.00n l=20n nfin=6
MM7 XP B YP VDD pmos_rvt w=162.00n l=20n nfin=6
MM8 OUT C XP VDD pmos_rvt w=162.00n l=20n nfin=6
MM9 YP D VDD VDD pmos_rvt w=162.00n l=20n nfin=6
MM10 YP E VDD VDD pmos_rvt w=162.00n l=20n nfin=6
.ENDS