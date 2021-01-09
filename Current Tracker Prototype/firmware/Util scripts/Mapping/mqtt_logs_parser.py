# ---------------------------------------
#
# Created: 17/11/2020
# Author: Medad Newman
#
# This program plots the elapsed time between tranmissions, and colours the ones
# with empty packet in red and packets with data in blue. This allows me to tell
# that the tracker is resetting a lot.
# ---------------------------------------

import json
import re
from pathlib import Path

import matplotlib.pyplot as plt
import pandas as pd

line_selector = "\[(Sun|Mon|Tues|Wed|Thu|Fri|Sat), (\d{2}) (Jan|Feb|Mar|Apr|May|June|July|Aug|Sep|Oct|Nov|Dec) (\d{4}) ([0[0-9]|1[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])\] INFO b'(.*)'"

filename = "mqtt_log_data-1.txt"

raw_data = Path(filename).read_text()

lines = re.findall(line_selector, raw_data)

# print(*lines, sep="\n")

timestamps = []
colour_selection = []
for i in lines:
    day, date, month, year, hour, minute, second, data = i
    d = json.loads(data)
    try:
        if d["dev_id"] == "icspace22" and not "is_retry" in d:
            timestamps.append(d["metadata"]["time"][:-4])
            colour_selection.append("blue" if d["payload_raw"] else "red")
    except KeyError:
        pass

df = pd.DataFrame(timestamps, columns=["datetime"])
df["datetime"] = pd.to_datetime(df['datetime'])
diffs = df["datetime"].diff().dt.total_seconds()

# diffs = diffs[diffs[""] > 0]

plt.scatter(x=df, y=diffs, c=colour_selection)
plt.xlabel("datetime")
plt.ylabel("time gap from previous transmission(seconds)")
plt.title(
    "Elapsed time between previous and current transmission plotted against time. Red is an empty frame, blue is a data frame")
plt.show()
