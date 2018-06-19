# -*- coding: utf-8 -*-
import scrapy
import os
import json
import ctypes
import re
import urllib
from selenium import webdriver
from readability.readability import Document
from pyquery import PyQuery as pq
from GS.items import Scrapy1Item 
from scrapy.utils.url import urljoin_rfc
from scrapy.utils.response import get_base_url
from datetime import datetime
import logging
from urllib.parse import urlparse
from scrapy.utils.project import get_project_settings


logging.getLogger("readability").setLevel(logging.WARNING)
class GeneralSpider(scrapy.Spider):
    name = 'GeneralSpider'
    # allowed_domains = ["dmoz.org"]
    start_urls = []
    def __init__(self):
        # 调用授权动态库,检查授权
        try:
            dll = ctypes.CDLL("License.dll")
            result = dll.IsValidLicense("LJSpider.user", "LJSpider")
        except Exception:
            result = 1 # TODO 改成0
        if result == 1:
            print("授权合法,开始采集！")
            settings = get_project_settings()
            print(settings.copy_to_dict())
            # 需要采集的网址
            href_list = settings.get("CRAWL_LIST")
            self.start_urls = href_list
            self.host_list = [urlparse(url).netloc for url in self.start_urls]
            # 最大采集量
            self.max_crawl = settings.get("MAX_CRAWL")
    
    def parse(self, response):
        if self.max_crawl < 1:
            return
        # response = scrapy.http.TextResponse(response)
        doc = Document(response.text)
        title = doc.short_title()
        content = pq(doc.summary()).text()
        if len(content) > 150:
            item = Scrapy1Item()
            item["content"] = content #.encode("utf-8")
            item["title"] = title #.encode("utf-8")
            item["url"] = response.url
            item["crawler_time"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            self.max_crawl -= 1
            yield item
        for url in response.xpath("//a/@href").extract():
            if "javascript" in url and "http" not in url:
                continue
            url=urllib.parse.urljoin(get_base_url(response), url)
            host = urlparse(url).netloc
            if host not in self.host_list:
                continue
            print("crawl {}".format(url))
            yield scrapy.Request(url, callback=self.parse)