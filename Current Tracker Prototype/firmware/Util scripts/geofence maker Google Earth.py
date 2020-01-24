# Created by Medad Rufus Newman on 27/12/2019


from bs4 import BeautifulSoup


def process_coords(raw):
    raw = raw.strip()
    raw  = raw.split(" ")
    coordinates_count = 0
    all_coords_str = ""
    for coord in raw:
        i,j,k = coord.split(",")
        coord = "{0:.5f},{1:.5f},".format(float(i),float(j))
        all_coords_str+=coord
        all_coords_str+="\n"
        coordinates_count+=1
    #raw  = [i+j for i,j,k in raw.split(",")]
    return all_coords_str, coordinates_count

with open("geofence.kml", encoding='utf8') as f:
    soup = BeautifulSoup(f, 'xml')

#print(soup.prettify())

results = soup.find_all('Placemark')

fences = []
region_counter = {}

# print c code for geofence.h
print("// GEOFENCE ARRAYS (longitude, latitude)")
for i in results:
    fence_name = i.find("name").get_text().replace("-", "")

    if fence_name not in region_counter.keys():
        region_counter[fence_name] = 1
    else:
        region_counter[fence_name]+=1

    all_coords_str, coordinates_count = process_coords(i.find("coordinates").get_text())
    print("static float " + fence_name + "_" + str(region_counter[fence_name]) + "F[{0}] = {{ ".format(coordinates_count * 2))

    print(all_coords_str)
    print("};")
    print("")
    fences.append([fence_name,region_counter[fence_name],coordinates_count])



# print c code for geofence.c
for i in fences:
    line = 	"else if(pointInPolygonF({2}, {0}_{1}F, latitude, longitude) == 1) {{GEOFENCE_no_tx = 0; " \
              "GEOFENCE_Region = {0};}}".format(i[0],i[1],i[2])
    print(line)