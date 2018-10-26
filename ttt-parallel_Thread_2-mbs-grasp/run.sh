/opt/openmpi-2.1.1/bin/mpirun -n 2 --machinefile 2maquinas -map-by ppr:1:node dmer danoint.mps.g.g 100 100000 96| tee output2_100-ttt.txt
/opt/openmpi-2.1.1/bin/mpirun -n 2 --machinefile 2maquinas -map-by ppr:1:node dmer bienst1.mps.g.g 100 100000 90| tee output3_100-ttt.txt
/opt/openmpi-2.1.1/bin/mpirun -n 2 --machinefile 2maquinas -map-by ppr:1:node dmer danoint.mps.g.g 50 100000 96| tee output2_50-ttt.txt
/opt/openmpi-2.1.1/bin/mpirun -n 2 --machinefile 2maquinas -map-by ppr:1:node dmer bienst1.mps.g.g 50 100000 90| tee output3_50-ttt.txt
/opt/openmpi-2.1.1/bin/mpirun -n 2 --machinefile 2maquinas -map-by ppr:1:node dmer 1-t0.300-to0.05-y2003-m11-p90-signed.g.g 100 100000 336| tee output1_100-ttt.txt
/opt/openmpi-2.1.1/bin/mpirun -n 2 --machinefile 2maquinas -map-by ppr:1:node dmer 1-t0.300-to0.05-y2003-m11-p90-signed.g.g 50 100000 336| tee output1_50-ttt.txt

#/opt/openmpi-2.1.1/bin/mpirun -n 2 dmer 1-t0.300-to0.05-y2003-m11-p90-signed.g.g 4 20 | tee output.txt
#/opt/openmpi-2.1.1/bin/mpirun -n 3 dmer 1-t0.300-to0.05-y2003-m11-p90-signed.g.g 9 600 | tee output.txt