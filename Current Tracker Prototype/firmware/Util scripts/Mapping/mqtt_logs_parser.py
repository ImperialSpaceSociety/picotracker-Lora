#---------------------------------------
#
# Created: 30/09/2020
# Author: Medad Newman
#
#---------------------------------------

import re
from pathlib import Path
import json
from datetime import datetime
import matplotlib.pyplot as plt
import pandas as pd

line_selector = "\[(Sun|Mon|Tues|Wed|Thurs|Fri|Sat), (\d{2}) (Jan|Feb|Mar|Apr|May|June|July|Aug|Sep|Oct|Nov|Dec) (\d{4}) ([0[0-9]|1[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])\] INFO b'(.*)'"


filename = "mqtt_log_data-1.txt"

raw_data = Path(filename).read_text()

lines = re.findall(line_selector, raw_data)


#print(*lines, sep="\n")

timestamps = []
for i in lines:
    day, date, month, year, hour, minute, second, data = i
    d = json.loads(data)
    try:
        if d["dev_id"] == "icspace22":
            ##print(d["metadata"]["time"].replace("Z",""))
            ##timestamps.append(datetime.strptime(d["metadata"]["time"][:-4], '%Y-%m-%dT%H:%M:%S.%f'))
            timestamps.append(d["metadata"]["time"][:-4])
    except KeyError:
        pass


df = pd.DataFrame(timestamps, columns = ["datetime"])
df = pd.to_datetime(df['datetime'])
diffs = df.diff().dt.total_seconds()

#diffs = diffs[diffs[""] > 0]

plt.scatter(x = df,y=diffs)
plt.show()