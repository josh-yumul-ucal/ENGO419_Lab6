import pandas as pd
# ERV vector is not asked for in lab doc
red  = pd.read_csv("results_redundancy.txt")
mdb  = pd.read_csv("results_MDB.txt")
glob = pd.read_csv("results_global_ERV.txt")
top3 = pd.read_csv("results_top3_ERV.txt")

table = red.merge(mdb, on="obs").merge(glob, on="obs").merge(top3, on="obs");

table.to_excel("Lab6_Table.xlsx", index=False);

print(table.to_string(index=False));