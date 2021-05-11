# cmds:
#
# ttn-lw-cli end-devices create --application-id "icss-lora-tracker"  --device-id "testing-budgie1"  --frequency-plan-id EU_863_870 --lorawan-version 1.0.2 --lorawan-phy-version 1.0.2-b --abp --with-session --mac-settings.resets-f-cnt -c ttn-lw-cli.yml
# ttn-lw-cli end-devices list-frequency-plans -c ttn-lw-cli.yml
# ttn-lw-cli end-devices create --application-id "icss-lora-tracker"  --device-id "testing-budgiedsa"  --frequency-plan-id AS_920_923_TTN_AU --lorawan-version 1.0.2 --lorawan-phy-version 1.0.2-b --abp --with-session --mac-settings.resets-f-cnt -c ttn-lw-cli.yml
# ttn-lw-cli end-devices list --application-id "icss-lora-tracker" --all  -c ttn-lw-cli.yml
#

frequency_plan_strings = ["EU_863_870"]
device_id = "testing-budgie1"


def generate_commands(frequency_plan_string):

    dev_id_for_plan = device_id + "-" + frequency_plan_string.replace("_","-").lower()
    cmd = 'ttn-lw-cli end-devices create --application-id "icss-lora-tracker" ' \
          ' --device-id "{0}" ' \
          ' --frequency-plan-id {1}' \
          ' --lorawan-version 1.0.2 --lorawan-phy-version 1.0.2-b --abp --with-session --mac-settings.resets-f-cnt ' \
          '-c ttn-lw-cli.yml'.format(dev_id_for_plan, frequency_plan_string)

    return cmd

def execute_subprocess(cmd):
    result = subprocess.run(cmd, stdout=PIPE, stderr=PIPE)
    print("stdout:", result.stdout)
    print("stderr:", result.stderr)

def generate_code():
    for frequency_plan_string in frequency_plan_strings:
        cmd = generate_commands(frequency_plan_string)
        print(cmd)
        execute_subprocess(cmd)


if __name__ == "__main__":

    generate_code()