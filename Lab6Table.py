import pandas as pd
# ERV vector is not asked for in lab doc
red  = pd.read_csv("results_redundancy.txt")
mdb  = pd.read_csv("results_MDB.txt")
glob = pd.read_csv("results_global_ERV.txt")
top3 = pd.read_csv("results_top3_ERV.txt")

table = red.merge(mdb, on="obs").merge(glob, on="obs").merge(top3, on="obs");

table.rename(columns={"param1": "Most Affected Parameter [mm]",
                      "value1_mm": "Largest ERV Coordinate Change [mm]",
                      "param2": "Second Most Affected Parameter [mm]",
                      "value2_mm": "Second Largest ERV Coordinate Change [mm]",
                      "param3": "Third Most Affected Parameter",
                      "value3_mm": "Third Largest ERV Coordinate Change [mm]"}, inplace=True)

# Use excel sheet to create table for submission
table.to_excel("Lab6_Table.xlsx", index=False);
# Submit .csv so that the TA can check the data more precisely
table.to_csv("Lab6_Table.csv", index=False); 

print(table.to_string(index=False));