# encoding=utf-8
import json
import os
import re
import xlrd
import psutil
import subprocess
import pptx
import docx
import traceback
import logging
import ctypes
import argparse
import mailparser
import base64
import multiprocessing
from multiprocessing import Pool
from psutil import NoSuchProcess
from pdfminer.pdfparser import PSEOF
from pdfminer.high_level import extract_text
import sys

logging.getLogger("pdfminer").setLevel(logging.WARNING)


def clear_process():
    """
    清理程序运行后残留的word，ppt等后台进程，防止下次运行出现错误
    """
    try:
        pids = psutil.pids()
        for pid in pids:
            # 获取所有进程
            p = psutil.Process(pid)
            # 寻找word进程进行清理
            if "WORD" in p.name():
                logging.debug(f"kill pid:{pid},pname:{p.name}")
                psutil.Process(pid).terminate()
            # 寻找ppt进程进行清理
            if "POWERPNT" in p.name():
                logging.debug(f"kill pid:{pid},pname{p.name()}")
                psutil.Process(pid).terminate()
    except NoSuchProcess:
        pass


def extract_pdf(path_to_file):
    try:
        text = extract_text(path_to_file)
    except PSEOF:
        logging.error(f"reading {path_to_file} raise EOF error")
        logging.error(traceback.format_exc())
        return None, "txt"
    return text, "text"


def extract_ppt(path_to_file):
    text = ""
    # 打开文件
    ppt_file = pptx.Presentation(path_to_file)
    for shape in ppt_file.slides:
        data_s = shape.element.xml
        con_list = re.findall(r"<a:t>(.*)</a:t>", data_s)
        partial_content = ""
        for i in con_list:
            partial_content += i
        text += partial_content + "\t\n\n"
    return text, "txt"


def extract_word(path_to_file):
    file_name = os.path.basename(path_to_file)
    file_type = file_name.split(".")[-1]
    if file_type == "docx":
        dop = docx.Document(path_to_file)
        dop_text = '\n'.join([paragraph.text for paragraph in dop.paragraphs])
        return dop_text, "text"
    elif file_type == "doc":
        dop = subprocess.check_output([args.antiword_path, path_to_file]).decode("utf-8")
        return dop, "text"
    return None, "text"


def extract_excel(path_to_file):
    data = xlrd.open_workbook(path_to_file)
    text = ""
    table = data.sheets()[0]  # 表头
    n_rows = table.nrows  # 行数
    for ro_num in range(n_rows):
        row = table.row_values(ro_num)
        values = ""
        for d in row:
            values = values + json.dumps(d, ensure_ascii=False) + ","
            values = values.replace('"', "")
        # 拼接行数据变成字符串，按逗号分隔
        text += values + "\r\n"  # 将字符串写入新文件
    return text, "text"


def extract_email(path_to_file):
    decode_email = mailparser.parse_from_file(path_to_file)
    receive = ""
    for i in decode_email.received:
        if "for" in i:
            receive = i
            break
    return {
               "json": json.dumps(
                   {
                       "from": decode_email.from_,
                       "receive": receive,
                       "timestamp": int(decode_email.date.timestamp()),
                       "subject": decode_email.subject,
                       "text": decode_email.text_plain,
                       "to": decode_email.to,
                       "attachments": [_["filename"] for _ in decode_email.attachments]
                   }, ensure_ascii=False),
               "attachments": decode_email.attachments
           }, "email"


def set_log(log_level=logging.INFO):
    """
    日志函数,指定日志文件名称,值日等级,并存入数据库
    :param log_level: 日志级别
    """
    logging.basicConfig(
        level=log_level,
        format='%(asctime)s %(processName)s\t%(filename)s\t\t : %(levelname)s\t%(message)s',  # 定义输出log的格式
        datefmt='%Y-%m-%d %A %H:%M:%S'
    )


def file_gen(path):
    """
    given a path to generate the files in this path recursively
    :param path:
    :return: a generator
    """
    for root, dirs, files in os.walk(path):
        for file in files:
            p = os.path.join(root, file)
            yield p


def extract_file(path):
    """
    extract one file path
    :param path:
    :return: file path and state and result
    """
    if not os.path.isfile(path):
        return path, False, None

    # 文件名称
    filename = os.path.basename(path)
    # 文件后缀名称
    file_type = filename.split(".")[-1]
    if file_type == "pdf":
        return path, True, extract_pdf(path)
    elif file_type in ["doc", "docx"]:
        return path, True, extract_word(path)
    elif file_type == "pptx":
        return path, True, extract_ppt(path)
    elif file_type in ["xlsx", "xls"]:
        return path, True, extract_excel(path)
    elif file_type == "eml":
        return path, True, extract_email(path)
    else:

        logging.error(f"can't extract file {path}")
        return path, False, None


def get_save_path(root_path, origin_path, save_path):
    save_path = save_path + origin_path[len(root_path):]
    save_dir = os.path.split(save_path)[0]
    if not os.path.exists(save_dir):
        os.mkdir(save_dir)
    return save_path


def save_result(result):
    logging.info(f"finish {result[0]}, {result[1] and result[2][0] is not None}")
    if not result[1]:
        return
    if result[2][1] == "text":
        save_text(get_save_path(args.path, result[0], args.dest), result[2][0])
        return
    if result[2][1] == "email":
        save_email(get_save_path(args.path, result[0], args.dest), result[2][0])
        return


def save_text(save_path, content):
    with open(save_path + ".txt", "w", encoding="utf-8") as f:
        f.write(content)


def save_email(save_path, content):
    with open(save_path + ".json", "w", encoding="utf-8") as f:
        f.write(content["json"])
    attach_path = save_path + ".attach"
    if not os.path.exists(attach_path):
        os.mkdir(attach_path)
    for attachment in content["attachments"]:
        with open(os.path.join(attach_path, attachment["filename"]), "wb") as f:
            f.write(base64.b64decode(attachment["payload"]))


if __name__ == '__main__':
    multiprocessing.freeze_support()
    set_log(logging.INFO)

    parser = argparse.ArgumentParser(description="lingjoin document extractor")
    parser.add_argument('--file', type=str, default=None,
                        help="a path for single file to extract, disable if --path was given")
    parser.add_argument('--path', type=str, default=None,
                        help="a path to extract all files in this directory")
    parser.add_argument('--dest', type=str, default=None,
                        help="a path to save all result, will follow same struct of directory as --path, "
                             "default is path")
    parser.add_argument('--thread_num', type=int, default=16,
                        help="how many process used , default is 16")
    parser.add_argument('--lib_path', type=str, default="./")
    parser.add_argument('--antiword_path', type=str, default='antiword')

    execute_path = os.path.split(os.path.abspath(sys.argv[0]))[0]
    args = parser.parse_args()
    is_64bit = sys.maxsize > 2 ** 32
    if sys.platform.startswith('win'):
        lib = 'License.dll'
    elif sys.platform.startswith('linux') and is_64bit:
        lib = 'libLicense64.so'
    elif sys.platform.startswith('linux'):
        lib = 'libLicense.so'
        raise RuntimeError("Platform '{}' is not supported by NLPIR.".format(
            sys.platform))
    try:
        # 调用dll文件获取授权函数
        dll = ctypes.CDLL(os.path.join(execute_path, lib))
        # 调用dll中函数，返回1表示授权成功，否则授权失败
        if dll.IsValidLicense(
                os.path.join(execute_path, "TxtExtractor.user").encode("utf-8"),
                "TxtExtractor".encode("utf-8"),
                0,
                0
        ) != 1:
            sys.exit(1)
    except Exception:
        logging.error("call license fail, exit")
        logging.debug(traceback.format_exc())
        sys.exit(1)
    if args.file:
        args.file = os.path.abspath(args.file)
        file_iter = [args.file]
        args.path = os.path.split(args.file)[0]
        args.thread_num = 1
    elif args.path:
        args.path = os.path.abspath(args.path)
        file_iter = file_gen(args.path)
    else:
        logging.error("no input file, exit")
        parser.print_help()
        sys.exit(1)
    if not args.dest:
        args.dest = args.path
    if args.thread_num == 1:
        for _ in file_iter:
            result = extract_file(_)
            save_result(result)
    else:
        with Pool(args.thread_num) as pool:
            for result in pool.imap(extract_file, file_iter):
                save_result(result)
    clear_process()
