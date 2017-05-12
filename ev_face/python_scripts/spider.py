# -*- coding: utf-8 -*-
import urllib
import urllib2
import os, sys
import threading
from BeautifulSoup import BeautifulSoup

male_star_url = 'http://www.manmankan.com/dy2013/mingxing/yanyuan/'
query_image_root = 'http://image.baidu.com/search/index'
query_dict = {
    'tn':'baiduimage',
    'ipn':'r',
    'ct':'201326592',
    'cl':'2',
    'lm':'-1',
    'st':'-1',
    'fm':'index',
    'fr':'',
    'hs':'0',
    'xthttps':'111111',
    'sf':'1',
    'fmq':'',
    'pv':'',
    'ic':'0',
    'nc':'1',
    'z':'',
    'se':'1',
    'showtab':'0',
    'fb':'0',
    'width':'',
    'height':'',
    'face':'0',
    'istype':'2',
    'ie':'utf-8',
    'word':'', # 关键字
    'oq':'', # 关键字
    'rsp':'-1'
}

# browser header
headers = [('Host','img0.imgtn.bdimg.com'),
('Connection', 'keep-alive'),
('Cache-Control', 'max-age=0'),
('Accept', 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8'),
('User-Agent', 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/36.0.1985.125 Safari/537.36'),
('Accept-Encoding','gzip,deflate,sdch'),
('Accept-Language', 'zh-CN,zh;q=0.8'),
('If-None-Match', '90101f995236651aa74454922de2ad74'),
('Referer','http://image.baidu.com/i?tn=baiduimage&ps=1&ct=201326592&lm=-1&cl=2&nc=1&word=%E4%BA%A4%E9%80%9A&ie=utf-8'),
('If-Modified-Since', 'Thu, 01 Jan 1970 00:00:00 GMT')]

# 获取图片地址
def get_img_urls(star_name, num_imgs=10):
    global query_image_root
    search_word = star_name + ' 明星 正面照'
    query_dict['word'] = search_word
    query_dict['oq'] = search_word
    data = urllib.urlencode(query_dict)
    # req = urllib2.Request(query_image_root, data)
    # get html content
    query_url = query_image_root + '?' + data
    print 'Query: ', query_url
    response = urllib2.urlopen(query_url)
    
    html = response.read()
    # get soup
    soup = BeautifulSoup(html, fromEncoding='utf8')
    pretty_soup = soup.prettify()
    # print pretty_soup
    lines = pretty_soup.split(',')
    img_urls = []
    for idx, line in enumerate(lines):
        if 'thumbURL' in line:
            line = line + ',' + lines[idx + 1]
            img_url = line.split('http:')[-1]
            img_url = img_url.split('.jpg')[0]
            img_url = 'http:' + img_url + '.jpg'
            img_url = img_url.replace('amp;', '')
            img_urls.append(img_url)
            # print img_url
    if len(img_urls) >= num_imgs:
        return img_urls[:num_imgs]
    else:
        return img_urls


# 保存图片
def save_img(img_url, img_path):
    global headers
    print 'retrieving ', img_path, ' from ', img_url
    opener = urllib2.build_opener()
    opener.addheaders = headers
    response = opener.open(img_url)
    # response = urllib2.urlopen(img_url)
    data = response.read()
    with open(img_path, 'wb') as f:
        f.write(data)

# 保存一个明星的照片
def save_n_imgs_for_a_star(star_name, n_imgs=10):
    img_urls = get_img_urls(star_name.encode('utf8'), n_imgs)
    # create path
    dataset_root = '../dataset/baidu_stars'
    star_name = star_name.replace(' ', '_')
    img_root = os.path.join(dataset_root, star_name)
    if not os.path.exists(img_root):
        os.system('mkdir %s' % img_root.encode('utf-8'))

    for idx, img_url in enumerate(img_urls):
        img_path = os.path.join(img_root, '%d.jpg' % (idx + 1))
        save_img(img_url, img_path)

if __name__ == '__main__':
    
    # get html content
    response = urllib2.urlopen(male_star_url)
    html = response.read()

    # beautiful soup
    soup = BeautifulSoup(html, fromEncoding='gb18030') # 网页是gb2312编码
    pretty_soup = soup.prettify()

    # print pretty_soup

    stars = soup.findAll('a', attrs={'class':'dis-500'})

    

    download_post_dict = {'fm':'', 'gp':''}

    for star in stars:
        star_name = star['title']
        save_n_imgs_for_a_star(star_name, 15)


        

    print 'Done.'