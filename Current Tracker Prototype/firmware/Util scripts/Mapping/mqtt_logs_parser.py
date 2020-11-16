#---------------------------------------
#
# Created: 30/09/2020
# Author: Medad Newman
#
#---------------------------------------

import re
from pathlib import Path



line_selector = "\[(Sun|Mon|Tues|Wed|Thurs|Fri|Sat), (\d{2}) (Jan|Feb|Mar|Apr|May|June|July|Aug|Sep|Oct|Nov|Dec) (\d{4}) ([0[0-9]|1[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])\] INFO b'(.*)'"


filename = "mqtt_log_data-1.txt"

raw_data = Path(filename).read_text()

lines = re.findall(line_selector, raw_data)


#print(*lines, sep="\n")


for i in lines:
    day, date, month, year, hour, minute, second, data = i
    print(data)

