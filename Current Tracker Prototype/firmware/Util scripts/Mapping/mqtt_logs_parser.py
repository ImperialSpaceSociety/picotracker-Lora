#---------------------------------------
#
# Created: 30/09/2020
# Author: Medad Newman
#
#---------------------------------------

import re
from pathlib import Path



line_selector = '([0-9]{4})-(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1]) (2[0-3]|[01][0-9]):([0-5][0-9]):([0-5][0-9]),([0-9]{3}) (.*)'


filename = "ICSPACE20-21.out"

raw_data = Path(filename).read_text()

lines = re.findall(line_selector, raw_data)


print(lines, sep="\n")
