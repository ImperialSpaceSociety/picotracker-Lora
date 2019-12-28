# Created by Medad Rufus Newman on 27/12/2019


from bs4 import BeautifulSoup


def process_coords(raw):
    raw = raw.strip()
    raw  = raw.split(" ")
    all_coords = ""
    for coord in raw:
        i,j,k = coord.split(",")
        coord = "{0:.7f},{1:.7f},".format(float(i),float(j))
        all_coords+=coord
        all_coords+="\n"
    #raw  = [i+j for i,j,k in raw.split(",")]
    return all_coords

with open("geofence.kml", encoding='utf8') as f:
    soup = BeautifulSoup(f, 'xml')

#print(soup.prettify())

results = soup.find_all('Placemark')

fences = []

print("// GEOFENCE ARRAYS (longitude, latitude)")
for i in results:
    name = i.find("name").get_text().replace("-", "")
    print("static float "+name+"[] = {")

    print(process_coords(i.find("coordinates").get_text()))
    print("};")
    print("")
