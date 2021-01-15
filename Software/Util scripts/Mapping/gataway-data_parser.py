# Created by Medad Rufus Newman on 19/03/2020


import pandas as pd
import json

import json

with open('gateway-data.json',encoding="utf8") as f:
  data = json.load(f)

# Output: {'name': 'Bob', 'languages': ['English', 'Fench']}
#print(data)

# Pretty Printing JSON string back
#print(json.dumps(data, indent = 4, sort_keys=True))


df  = pd.read_json("gateway-data.json")
print (df)

msgs = pd.io.json.json_normalize(resp.json())