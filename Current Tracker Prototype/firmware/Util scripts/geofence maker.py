# Created by Medad Rufus Newman on 27/12/2019


from bs4 import BeautifulSoup


def process_coords(raw):
    raw = raw.replace(" ", "")
    raw  = raw.split("\n")
    raw = raw[1:-1]
    all_coords = ""
    for i in raw:
        i,j,k = i.split(",")
        coord = i+", "+j+", "
        all_coords+=coord
        all_coords+="\n"
    #raw  = [i+j for i,j,k in raw.split(",")]
    return all_coords

with open("geofence.kml", encoding='utf8') as f:
    soup = BeautifulSoup(f, 'xml')

#print(soup.prettify())

results = soup.find_all('Placemark')


print("// GEOFENCE ARRAYS (longitude, latitude)")
for i in results:
    print("static float "+i.find("name").get_text().replace("-", "")+"[] = {")

    print(process_coords(i.find("coordinates").get_text()))
    print("};")
