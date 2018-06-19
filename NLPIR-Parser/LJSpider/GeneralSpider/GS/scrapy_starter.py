# -*- coding: utf-8 -*-  
from scrapy.crawler import CrawlerProcess  
from scrapy.utils.project import get_project_settings  
  
# 这里是必须引入的
import scrapy.spiderloader  
import scrapy.statscollectors  
import scrapy.logformatter  
import scrapy.dupefilters  
import scrapy.squeues  
import scrapy.log
import scrapy.extensions.spiderstate  
import scrapy.extensions.corestats  
import scrapy.extensions.telnet  
import scrapy.extensions.logstats  
import scrapy.extensions.memusage  
import scrapy.extensions.memdebug  
import scrapy.extensions.feedexport  
import scrapy.extensions.closespider  
import scrapy.extensions.debug  
import scrapy.extensions.httpcache  
import scrapy.extensions.statsmailer  
import scrapy.extensions.throttle  
  
import scrapy.core.scheduler  
import scrapy.core.engine  
import scrapy.core.scraper  
import scrapy.core.spidermw  
import scrapy.core.downloader  
  
import scrapy.downloadermiddlewares.stats  
import scrapy.downloadermiddlewares.httpcache  
import scrapy.downloadermiddlewares.cookies  
import scrapy.downloadermiddlewares.useragent  
import scrapy.downloadermiddlewares.httpproxy  
import scrapy.downloadermiddlewares.ajaxcrawl  
import scrapy.downloadermiddlewares.chunked  
import scrapy.downloadermiddlewares.decompression  
import scrapy.downloadermiddlewares.defaultheaders  
import scrapy.downloadermiddlewares.downloadtimeout  
import scrapy.downloadermiddlewares.httpauth  
import scrapy.downloadermiddlewares.httpcompression  
import scrapy.downloadermiddlewares.redirect  
import scrapy.downloadermiddlewares.retry  
import scrapy.downloadermiddlewares.robotstxt  
  
import scrapy.spidermiddlewares.depth  
import scrapy.spidermiddlewares.httperror  
import scrapy.spidermiddlewares.offsite  
import scrapy.spidermiddlewares.referer  
import scrapy.spidermiddlewares.urllength  
  
import scrapy.pipelines  
import scrapy.item
  
import scrapy.core.downloader.handlers.http  
import scrapy.core.downloader.contextfactory  
import logging


import scrapy.contrib
import scrapy.contrib.downloadermiddleware
import scrapy.contrib.downloadermiddleware.useragent
import selenium.common.exceptions
import pyquery
import readability
import readability.readability
import selenium
import json
import codecs
import xml.dom.minidom
import time
import random
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
from scrapy import signals
from scrapy.http import HtmlResponse
from selenium import webdriver
import GS.settings
import GS.items
import GS.pipelines
import GS.rotate_useragent
import GS.middlewares
import GS.spiders
from GS.spiders import GeneralSpider

from importlib import import_module
from pkgutil import iter_modules
# print("+_+_+_+_++_+_+_+_+_+_")
# mods = []
# path = "GS.spiders"
# mod = import_module("GS.spiders")
# mods.append(mod)
# if hasattr(mod, '__path__'):
#     for _, subpath, ispkg in iter_modules(mod.__path__):
#         print(subpath)
#         fullpath = path + '.' + subpath
#         if ispkg:
#             print("pkg")
#             print(fullpath)
#             # mods += walk_modules(fullpath)
#         else:
#             submod = import_module(fullpath)
#             mods.append(submod)
# print(mods)

# print("~_+~_+~_+~_~+_+~_+_~+_~~+_+~_")
# logging.basicConfig(level=logging.INFO)
settings = get_project_settings()
# print("settings:")
# print(settings.copy_to_dict())
print(settings.getlist('SPIDER_MODULES'))
process = CrawlerProcess(settings)
# 'Books' is the name of one of the spiders of the project.  
process.crawl('GeneralSpider')  
process.start()  # the script will block here until the crawling is finished  