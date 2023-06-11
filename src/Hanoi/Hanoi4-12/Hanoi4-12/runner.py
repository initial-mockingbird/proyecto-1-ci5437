import subprocess
import time

test_files = ["../../../benchmarks/hanoi_4p12d/hanoi_4p12d.d=005",
              "../../../benchmarks/hanoi_4p12d/hanoi_4p12d.d=010",
              "../../../benchmarks/hanoi_4p12d/hanoi_4p12d.d=015",
              "../../../benchmarks/hanoi_4p12d/hanoi_4p12d.d=2000",
              "../../../benchmarks/hanoi_4p12d/hanoi_4p12d.d=2000000"] 
archivo = "./hanoi4-12.a_star"

for test_file in test_files:
  with open(test_file,"r") as f:
    i = 0
    for test_case in f.readlines():
      test_case = test_case.rstrip()
      difficulty = test_file.split("=")[1]
      if (i == 5):
        break
      out_file = f'{test_case} astar_4-12d{difficulty}.txt'
      print(out_file)
      with open(out_file,'w') as out:
        subprocess.run(["valgrind",archivo,f'{test_case}'],stdout=out)
      time.sleep(10)
      i += 1