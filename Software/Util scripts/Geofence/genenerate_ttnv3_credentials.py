# cmds:
#
# ttn-lw-cli end-devices create --application-id "icss-lora-tracker"  --device-id "testing-budgie1"  --frequency-plan-id EU_863_870 --lorawan-version 1.0.2 --lorawan-phy-version 1.0.2-b --abp --with-session --mac-settings.resets-f-cnt -c ttn-lw-cli.yml
# ttn-lw-cli end-devices list-frequency-plans -c ttn-lw-cli.yml
# ttn-lw-cli end-devices create --application-id "icss-lora-tracker"  --device-id "testing-budgiedsa"  --frequency-plan-id AS_920_923_TTN_AU --lorawan-version 1.0.2 --lorawan-phy-version 1.0.2-b --abp --with-session --mac-settings.resets-f-cnt -c ttn-lw-cli.yml
# ttn-lw-cli end-devices list --application-id "icss-lora-tracker" --all  -c ttn-lw-cli.yml
#

# NOTE: Must manually change the Device ID field on the things stack website. Very important!!


import time
from datetime import datetime
import secrets


frequency_plan_strings = ["EU_863_870_TTN",
                          "US_902_928_FSB_2",
                          "AU_915_928_FSB_2",
                          "AS_923",
                          "KR_920_923_TTN",
                          "IN_865_867",
                          "RU_864_870_TTN",
                          "CN_470_510_FSB_11"
                          ]

#device_id = "test-09-06-2021"



device_id = datetime.today().strftime('%Y-%m-%d') + "-" +secrets.token_hex(2)



def generate_commands(frequency_plan_string):
    dev_id_for_plan = device_id + "-" + frequency_plan_string.replace("_", "-").lower()
    cmd = 'ttn-lw-cli end-devices create --application-id "icss-lora-tracker" ' \
          ' --device-id "{0}" ' \
          ' --frequency-plan-id {1}' \
          ' --lorawan-version 1.0.3 ' \
          '--lorawan-phy-version 1.0.3-a ' \
          '--abp ' \
          '--with-session' \
          ' --mac-settings.resets-f-cnt ' \
          '-c ttn-lw-cli.yml'.format(dev_id_for_plan, frequency_plan_string)

    return cmd


def execute_subprocess(cmd):
    # !/usr/bin/env python3

    import subprocess

    # Define command as string and then split() into list format
    # cmd = 'ping -c 5 google.com'

    # Use shell to execute the command, store the stdout and stderr in sp variable
    sp = subprocess.Popen(cmd,
                          shell=True,
                          stdout=subprocess.PIPE,
                          stderr=subprocess.PIPE)

    # Store the return code in rc variable
    rc = sp.wait()

    # Separate the output and error by communicating with sp variable.
    # This is similar to Tuple where we store two values to two different variables
    out, err = sp.communicate()

    print('Return Code:', rc, '\n')
    print('output is: \n', out)
    print('error is: \n', err)


def generate_code():
    for frequency_plan_string in frequency_plan_strings:
        cmd = generate_commands(frequency_plan_string)
        print(cmd)
        # execute_subprocess(cmd)s


if __name__ == "__main__":
    generate_code()
