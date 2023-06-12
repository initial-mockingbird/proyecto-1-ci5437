import subprocess
import time

test_files = ["../../../benchmarks/15-puzzle/15_puzzle_100_instances_korf.txt"] 
archivo = "./15puzzle.ida"

for test_file in test_files:
  with open(test_file,"r") as f:
    i = 0
    for test_case in f.readlines():
      test_case = test_case.rstrip()
      #difficulty = test_file.split("=")[1]
      if (i == 15):
        break
      out_file = f'{test_case} ida_15puzzle.txt'
      print(out_file)
      with open(out_file,'w') as out:
        subprocess.run([archivo,f'{test_case}'],stdout=out)
      time.sleep(10)
      i += 1