;PROG0409，文件名为hello.asm
.386
.model flat, stdcall
option casemap:none
; 说明程序中用到的库、函数原型和常量
includelib      msvcrt.lib
printf          PROTO C :ptr sbyte, :VARARG
; 数据区
.data
szMsg           byte    "Hello World! ", 0ah, 0
; 代码区
.code
start:
                invoke  printf, offset szMsg
                ret
end             start