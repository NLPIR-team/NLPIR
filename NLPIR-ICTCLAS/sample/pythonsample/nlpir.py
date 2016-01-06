# -*- coding: UTF-8 -*-
__author__ = 'Peter_Howe<haobibo@gmail.com>'

'''
Python Warpper for ICTCLAS2014
Loading functions from Dynamic Link Library  directly.
'''
from ctypes import *

#NLPIR2014 Lib File (NLPIR64, NLPIR32, libNLPIR64.so, libNLPIR32.so),
#Change this when you are not using a Win64 environment:
libFile = './nlpir/NLPIR64.dll'

dll =  CDLL(libFile)
def loadFun(exportName, restype, argtypes):
    global dll
    f = getattr(dll,exportName)
    f.restype = restype
    f.argtypes = argtypes
    return f

class ENCODING:
    GBK_CODE        =   0               #默认支持GBK编码
    UTF8_CODE       =   GBK_CODE+1      #UTF8编码
    BIG5_CODE       =   GBK_CODE+2      #BIG5编码
    GBK_FANTI_CODE  =   GBK_CODE+3      #GBK编码，里面包含繁体字

class POSMap:
    ICT_POS_MAP_SECOND  = 0 #计算所二级标注集
    ICT_POS_MAP_FIRST   = 1 #计算所一级标注集
    PKU_POS_MAP_SECOND  = 2 #北大二级标注集
    PKU_POS_MAP_FIRST   = 3	#北大一级标注集

POS = {
	"n": {  #1.	名词  (1个一类，7个二类，5个三类)
		"n":"名词",
		"nr":"人名",
		"nr1":"汉语姓氏",
		"nr2":"汉语名字",
		"nrj":"日语人名",
		"nrf":"音译人名",
		"ns":"地名",
		"nsf":"音译地名",
		"nt":"机构团体名",
		"nz":"其它专名",
		"nl":"名词性惯用语",
		"ng":"名词性语素"
	},
	"t": {  #2.	时间词(1个一类，1个二类)
		"t":"时间词",
		"tg":"时间词性语素"
	},
	"s": {  #3.	处所词(1个一类)
		"s":"处所词"
	},
	"f": {  #4.	方位词(1个一类)
		"f":"方位词"
	},
	"v": {  #5.	动词(1个一类，9个二类)
		"v":"动词",
		"vd":"副动词",
		"vn":"名动词",
		"vshi":"动词“是”",
		"vyou":"动词“有”",
		"vf":"趋向动词",
		"vx":"形式动词",
		"vi":"不及物动词（内动词）",
		"vl":"动词性惯用语",
		"vg":"动词性语素"
	},
	"a": {  #6.	形容词(1个一类，4个二类)
		"a":"形容词",
		"ad":"副形词",
		"an":"名形词",
		"ag":"形容词性语素",
		"al":"形容词性惯用语"
	},
	"b": {  #7.	区别词(1个一类，2个二类)
		"b":"区别词",
		"bl":"区别词性惯用语"
	},
	"z": {  #8.	状态词(1个一类)
		"z":"状态词"
	},
	"r": {  #9.	代词(1个一类，4个二类，6个三类)
		"r":"代词",
		"rr":"人称代词",
		"rz":"指示代词",
		"rzt":"时间指示代词",
		"rzs":"处所指示代词",
		"rzv":"谓词性指示代词",
		"ry":"疑问代词",
		"ryt":"时间疑问代词",
		"rys":"处所疑问代词",
		"ryv":"谓词性疑问代词",
		"rg":"代词性语素"
	},
	"m": {  #10.	数词(1个一类，1个二类)
		"m":"数词",
		"mq":"数量词"
	},
	"q": {  #11.	量词(1个一类，2个二类)
		"q":"量词",
		"qv":"动量词",
		"qt":"时量词"
	},
	"d": {  #12.	副词(1个一类)
		"d":"副词"
	},
	"p": {  #13.	介词(1个一类，2个二类)
		"p":"介词",
		"pba":"介词“把”",
		"pbei":"介词“被”"
	},
	"c": {  #14.	连词(1个一类，1个二类)
		"c":"连词",
		"cc":"并列连词"
	},
	"u": {  #15.	助词(1个一类，15个二类)
		"u":"助词",
		"uzhe":"着",
		"ule":"了 喽",
		"uguo":"过",
		"ude1":"的 底",
		"ude2":"地",
		"ude3":"得",
		"usuo":"所",
		"udeng":"等 等等 云云",
		"uyy":"一样 一般 似的 般",
		"udh":"的话",
		"uls":"来讲 来说 而言 说来",
		"uzhi":"之",
		"ulian":"连 " #（“连小学生都会”）
	},
	"e": {  #16.	叹词(1个一类)
		"e":"叹词"
	},
	"y": {  #17.	语气词(1个一类)
		"y":"语气词(delete yg)"
	},
	"o": {  #18.	拟声词(1个一类)
		"o":"拟声词"
	},
	"h": {  #19.	前缀(1个一类)
		"h":"前缀"
	},
	"k": {  #20.	后缀(1个一类)
		"k":"后缀"
	},
	"x": {  #21.	字符串(1个一类，2个二类)
		"x":"字符串",
		"xx":"非语素字",
		"xu":"网址URL"
	},
	"w":{   #22.	标点符号(1个一类，16个二类)
		"w":"标点符号",
		"wkz":"左括号", 	#（ 〔  ［  ｛  《 【  〖 〈   半角：( [ { <
		"wky":"右括号", 	#） 〕  ］ ｝ 》  】 〗 〉 半角： ) ] { >
		"wyz":"全角左引号", 	#“ ‘ 『
		"wyy":"全角右引号", 	#” ’ 』
		"wj":"全角句号",	#。
		"ww":"问号",	#全角：？ 半角：?
		"wt":"叹号",	#全角：！ 半角：!
		"wd":"逗号",	#全角：， 半角：,
		"wf":"分号",	#全角：； 半角： ;
		"wn":"顿号",	#全角：、
		"wm":"冒号",	#全角：： 半角： :
		"ws":"省略号",	#全角：……  …
		"wp":"破折号",	#全角：——   －－   ——－   半角：---  ----
		"wb":"百分号千分号",	#全角：％ ‰   半角：%
		"wh":"单位符号"	#全角：￥ ＄ ￡  °  ℃  半角：$
	}
}

class SegAtom(Structure):
    _fields_ = [("start", c_int32), ("length", c_int32),
        ("sPOS", c_char * 40),      ("iPOS", c_int32),
        ("word_ID", c_int32),       ("word_type", c_int32), ("weight", c_int32)
    ]

def translatePOS(sPOS):
    global POS
    if sPOS=='url': sPOS = 'xu'
    c = sPOS[0]
    return POS[c][sPOS]

Init = loadFun('NLPIR_Init',c_int, [c_char_p, c_int, c_char_p])
Exit = loadFun('NLPIR_Exit',c_bool, None)
ParagraphProcess = loadFun('NLPIR_ParagraphProcess',c_char_p, [c_char_p, c_int])
ParagraphProcessA = loadFun('NLPIR_ParagraphProcessA',POINTER(SegAtom), [c_char_p, c_void_p, c_bool])
#ParagraphProcessAW = loadFun('NLPIR_ParagraphProcessAW',None, [c_int, POINTER(SegAtom)])
FileProcess = loadFun('NLPIR_FileProcess',c_double, [c_char_p, c_char_p, c_int])
ImportUserDict = loadFun('NLPIR_ImportUserDict',c_uint, [c_char_p])
AddUserWord = loadFun('NLPIR_AddUserWord', c_int, [c_char_p])
SaveTheUsrDic = loadFun('NLPIR_SaveTheUsrDic', c_int, None)
DelUsrWord = loadFun('NLPIR_DelUsrWord',c_int, [c_char_p])
GetUniProb = loadFun('NLPIR_GetUniProb', c_double, [c_char_p])
IsWord = loadFun('NLPIR_IsWord',c_bool, [c_char_p])
GetKeyWords = loadFun('NLPIR_GetKeyWords',c_char_p, [c_char_p, c_int, c_bool])
GetFileKeyWords = loadFun('NLPIR_GetNewWords',c_char_p, [c_char_p, c_int, c_bool])
GetNewWords = loadFun('NLPIR_GetNewWords', c_char_p, [c_char_p, c_int, c_bool])
GetFileNewWords = loadFun('NLPIR_GetFileNewWords',c_char_p, [c_char_p, c_int, c_bool])
FingerPrint = loadFun('NLPIR_FingerPrint',c_ulong, [c_char_p])
SetPOSmap = loadFun('NLPIR_SetPOSmap',c_int, [c_int])
#New Word Identification
NWI_Start = loadFun('NLPIR_NWI_Start', c_bool, None)
NWI_AddFile = loadFun('NLPIR_NWI_AddFile',c_bool, [c_char_p])
NWI_AddMem = loadFun('NLPIR_NWI_AddMem',c_bool, [c_char_p])
NWI_Complete = loadFun('NLPIR_NWI_Complete', c_bool, None)
NWI_GetResult = loadFun('NLPIR_NWI_GetResult',c_char_p, [c_int])
NWI_Result2UserDict = loadFun('NLPIR_NWI_Result2UserDict',c_uint, None)

if not Init('',ENCODING.UTF8_CODE,''):
    print("Initialization failed!")
    exit(-111111)

'''
if not SetPOSmap(3): #POSMap.ICT_POS_MAP_SECOND
    print("Setting POS Map failed!")
    exit(-22222)
'''

def seg(paragraph):
    result = ParagraphProcess(paragraph, c_int(1))
    atoms = [i.strip().split('/') for i in result.split(' ') if len(i)>=1 and i[0]!=' ']
    atoms = [(a[0],a[1]) for a in atoms if len(a[0])>0]
    return atoms

def segment(paragraph):
    count = c_int32()
    result = ParagraphProcessA(paragraph, byref(count),c_bool(True))
    count = count.value
    atoms = cast(result, POINTER(SegAtom))
    return [atoms[i] for i in range(0,count)]

def Seg(paragraph):
    atoms = segment(paragraph)
    for a in atoms:
        if len(a.sPOS) < 1: continue
        i = paragraph[a.start: a.start + a.length]#.decode('utf-8')#.encode('ascii')
        yield (i, a.sPOS)

if __name__ == "__main__":
    p = "Big News: @解放日报 [最右]【呼市铁路局原副局长被判死缓 最头痛藏钱】2013年12月底，呼市铁路局原副局长马俊飞因受贿被判死缓。他说最头痛藏钱，从呼和浩特到北京，马俊飞又是购房又是租房，在挥之不去的恐惧中，人民币8800万、美元419万、欧元30万、港币27万，黄金43.3公斤，逐渐堆满了两所房子…… http://t.cn/8kgR6Yi"
    for t in Seg(p):
        s = '%s\t%s\t%s' % (t[0],t[1],translatePOS(t[1]))
        print(s)