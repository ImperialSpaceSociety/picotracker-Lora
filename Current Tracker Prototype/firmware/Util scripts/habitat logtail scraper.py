# Created by Medad Rufus Newman on 21/01/2020
import requests
from lxml import html

while True:
    pageContent=requests.get('http://habitat.habhub.org/logtail/')
    tree = html.fromstring(pageContent.content)

    a=tree.xpath('/html/body/div[2]/pre/text()')

    print(a)