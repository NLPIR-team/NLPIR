# -*- coding: utf-8 -*-
import json
import os

# Scrapy settings for scrapy1 project
#
# For simplicity, this file contains only settings considered important or
# commonly used. You can find more settings consulting the documentation:
#
#     https://doc.scrapy.org/en/latest/topics/settings.html
#     https://doc.scrapy.org/en/latest/topics/downloader-middleware.html
#     https://doc.scrapy.org/en/latest/topics/spider-middleware.html
BOT_NAME = 'GS'
LOG_LEVEL='INFO'
SPIDER_MODULES = ['GS.spiders']
NEWSPIDER_MODULE = 'GS.spiders'
with open("09GeneralSpider.conf", encoding="gbk") as f:
    conf = json.loads(f.read())
if "numbers" in conf:
    DEPTH_LIMIT = int(conf["numbers"])
else:
    DEPTH_LIMIT = 1
if "route" in conf:
    OUTDIR = conf["route"]
else:
    OUTDIR = ""
OUTDIR = os.path.join(OUTDIR ,"站点采集")
if not os.path.exists(OUTDIR):
    os.makedirs(OUTDIR)
# 读取conf配置文件 获取内容
# 需要采集的网址
CRAWL_LIST = conf["url_list"]
# 最大采集量
if "MaxCount" in conf:
    MAX_CRAWL = int(conf["MaxCount"])
else:
    MAX_CRAWL = 1000
# Crawl responsibly by identifying yourself (and your website) on the user-agent
#USER_AGENT = 'scrapy1 (+http://www.yourdomain.com)'

# Obey robots.txt rules
ROBOTSTXT_OBEY = False
#取消默认的useragent,使用新的useragent

# Configure maximum concurrent requests performed by Scrapy (default: 16)
#CONCURRENT_REQUESTS = 32

# Configure a delay for requests for the same website (default: 0)
# See https://doc.scrapy.org/en/latest/topics/settings.html#download-delay
# See also autothrottle settings and docs
#DOWNLOAD_DELAY = 3
# The download delay setting will honor only one of:
#CONCURRENT_REQUESTS_PER_DOMAIN = 16
#CONCURRENT_REQUESTS_PER_IP = 16

# Disable cookies (enabled by default)
#COOKIES_ENABLED = False

# Disable Telnet Console (enabled by default)
#TELNETCONSOLE_ENABLED = False

# Override the default request headers:
#DEFAULT_REQUEST_HEADERS = {
#   'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
#   'Accept-Language': 'en',
#}

# Enable or disable spider middlewares
# See https://doc.scrapy.org/en/latest/topics/spider-middleware.html
#SPIDER_MIDDLEWARES = {
#    'scrapy1.middlewares.Scrapy1SpiderMiddleware': 543,
#}

# Enable or disable downloader middlewares
# See https://doc.scrapy.org/en/latest/topics/downloader-middleware.html
#DOWNLOADER_MIDDLEWARES = {
#    'scrapy1.middlewares.Scrapy1DownloaderMiddleware': 543,
#}
DOWNLOADER_MIDDLEWARES = {
        # 'scrapy1.middlewares.ChromeDownloaderMiddleware': 543,
        'scrapy.contrib.downloadermiddleware.useragent.UserAgentMiddleware' : None,
        'GS.rotate_useragent.RotateUserAgentMiddleware' :400
}
DOWNLOAD_TIMEOUT = 15

# Enable or disable extensions
# See https://doc.scrapy.org/en/latest/topics/extensions.html
#EXTENSIONS = {
#    'scrapy.extensions.telnet.TelnetConsole': None,
#}

# Configure item pipelines
# See https://doc.scrapy.org/en/latest/topics/item-pipeline.html
ITEM_PIPELINES = {
    'GS.pipelines.Scrapy1Pipeline': 300,
}

# Enable and configure the AutoThrottle extension (disabled by default)
# See https://doc.scrapy.org/en/latest/topics/autothrottle.html
#AUTOTHROTTLE_ENABLED = True
# The initial download delay
#AUTOTHROTTLE_START_DELAY = 5
# The maximum download delay to be set in case of high latencies
#AUTOTHROTTLE_MAX_DELAY = 60
# The average number of requests Scrapy should be sending in parallel to
# each remote server
#AUTOTHROTTLE_TARGET_CONCURRENCY = 1.0
# Enable showing throttling stats for every response received:
#AUTOTHROTTLE_DEBUG = False

# Enable and configure HTTP caching (disabled by default)
# See https://doc.scrapy.org/en/latest/topics/downloader-middleware.html#httpcache-middleware-settings
#HTTPCACHE_ENABLED = True
#HTTPCACHE_EXPIRATION_SECS = 0
#HTTPCACHE_DIR = 'httpcache'
#HTTPCACHE_IGNORE_HTTP_CODES = []
#HTTPCACHE_STORAGE = 'scrapy.extensions.httpcache.FilesystemCacheStorage'
