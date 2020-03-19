# Created by Medad Rufus Newman on 18/03/2020
import pandas as pd
df = pd.read_csv("flight_payload_time.csv")

print(df)
print(df.count())
print(list(df.columns.values))

receivers_dict = {}

for index, row in df.iterrows():
    if row["sentence_id"] not in receivers_dict:
        receivers_dict[row["sentence_id"]] = row["_receivers"].split(",")
    else:
        receivers_dict[row["sentence_id"]] += row["_receivers"].split(",")


for i in list(receivers_dict):
    print("sentence id:",i,"Number of receivers",len(receivers_dict[i]),"Names of receivers:",receivers_dict[i])