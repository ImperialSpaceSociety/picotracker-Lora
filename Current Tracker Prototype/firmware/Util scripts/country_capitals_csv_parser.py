# Created by Medad Rufus Newman on 16/03/2020


import pandas

df = pandas.read_csv("selected_country_capitals.csv")
print(df)
print(df.count())
print(list(df.columns.values))


header ="""
/*dummy Coords ARRAYS (longitude, latitude) */
static float dummy_coords_array[{}] = {{ 
""".format(len(df)*2)
print(header)
for index, row in df.iterrows():
    print("{0:.4f},{1:.4f},  // {2}".format(row["CapitalLongitude"],row["CapitalLatitude"],row["CountryName"]))

print("};")