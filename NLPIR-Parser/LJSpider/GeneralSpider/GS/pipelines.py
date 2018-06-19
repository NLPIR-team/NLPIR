# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://doc.scrapy.org/en/latest/topics/item-pipeline.html

import json
import codecs
import xml.dom.minidom
import time
import os
import re
from scrapy.utils.project import get_project_settings  

class Scrapy1Pipeline(object):

    def __init__(self):
        # self.file = codecs.open('scraped_data_utf8.json', 'w', encoding='utf-8')
        self.out = get_project_settings().get("OUTDIR")
        if self.out is None:
            self.out = ""
        print("output dir : {}".format(self.out))
        pass

    def process_item(self, item, spider):
        doc = xml.dom.minidom.Document() 
        web = doc.createElement("web")
        title = doc.createElement('title') 
        title.appendChild(doc.createTextNode(item["title"]))
        content = doc.createElement("content")
        content.appendChild(doc.createTextNode(item["content"]))
        url = doc.createElement("url")
        url.appendChild(doc.createTextNode(item["url"]))
        crawler_time = doc.createElement("crawler_time")
        crawler_time.appendChild(doc.createTextNode(item["crawler_time"]))

        web.appendChild(title)
        web.appendChild(content)
        web.appendChild(url)
        web.appendChild(crawler_time)
        doc.appendChild(web)
        
        #去掉非法字符,截断字符长度
        file_name = item["title"][:50]
        file_name = re.sub(r'[\/:*?"<>|]', '-', file_name + ".xml")
        file_name = os.path.join(self.out, file_name)
        with open(file_name, 'w', encoding="utf-8") as f:
            doc.writexml(f, indent='\t', addindent='\t', newl='\n', encoding="utf-8")
        
        return item

    def spider_closed(self, spider):
        pass
        