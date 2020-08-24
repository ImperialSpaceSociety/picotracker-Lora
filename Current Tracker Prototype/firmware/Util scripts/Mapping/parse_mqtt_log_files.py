#############################################
#
# Created: 22/08/2020
# Author: Medad Newman
#
# This file parses the logs of the mqtt log
##############################################

import csv
import json

from math import radians, cos, sin, asin, sqrt

from smallest_enclosing_circle import make_circle

time_stamp_info_part_size = len("2020-04-18 22:18:57,348 [INFO] b'")


class MqttLogParser:
    def __init__(self):
        pass

    @staticmethod
    def haversine(lon1, lat1, lon2, lat2):
        """
        Calculate the great circle distance between two points
        on the earth (specified in decimal degrees)
        """
        # convert decimal degrees to radians
        lon1, lat1, lon2, lat2 = map(radians, [lon1, lat1, lon2, lat2])

        # haversine formula
        dlon = lon2 - lon1
        dlat = lat2 - lat1
        a = sin(dlat / 2) ** 2 + cos(lat1) * cos(lat2) * sin(dlon / 2) ** 2
        c = 2 * asin(sqrt(a))
        r = 6371  # Radius of earth in kilometers. Use 3956 for miles
        return c * r

    def get_gateway_locations(self, json_line):
        gateway_locations = []  # list of [long,lat]
        for i in json_line["metadata"]["gateways"]:
            try:
                gateway_locations.append([i["latitude"],i["longitude"]])
            except KeyError:
                pass

        return gateway_locations

    def parse_line(self, line: str):
        line = line[time_stamp_info_part_size:]  # remove 2020-04-18 22:18:57,348 [INFO] b'
        line = line[:-2]  # remove \n'

        json_line = json.loads(line)

        # print(json.dumps(json_line, indent=4, sort_keys=True))

        return self.get_gateway_locations(json_line)

    def save_locations_to_csv(self, all_transmissions):
        # Now calculate and record down the centers of the minimum bounding circle of all gateways that pick up the
        # transmissions

        with open('coords_aug.csv', mode='w') as coords_file:
            writer = csv.writer(coords_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)

            writer.writerow(["lat", "long", "alt"])

            for i in all_transmissions:
                if not i:
                    continue

                lat, long, radius_degrees = make_circle(i)
                radius_meters = self.haversine(radius_degrees, 0, 0, 0)

                # Taken from
                # https://github.com/rossengeorgiev/habitat-mobile-tracker/blob/f4e4bfbd225962f9e875e5c45d350ac840762108/js/tracker.js#L895

                calculated_altitude = radius_meters ** 2 / 12.756
                writer.writerow([lat, long, calculated_altitude])

    def generate_csv_of_balloon_locations_from_mqtt_log(self):
        f = open("mqtt.log", "r")

        all_transmissions = []
        for line in f:
            gateway_locations = self.parse_line(line)
            if len(gateway_locations)>5:
                all_transmissions.append(gateway_locations)

        self.save_locations_to_csv(all_transmissions)


if __name__ == "__main__":
    MLP = MqttLogParser()
    MLP.generate_csv_of_balloon_locations_from_mqtt_log()
