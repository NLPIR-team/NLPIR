;PROG0412
;实现（a+b）/d运算,结果不在屏幕上显示
.386
.model  flat,stdcall
option  casemap:none
includelib       msvcrt.lib
printf  PROTO C:ptr sbyte,:VARARG
.data
szMsg 	byte   	"(a+b)/d=%d",0ah,0
a       	dw    	100
b       	dw    	26
d       	dw    	5
sum    	dw   	?
res     	dd    	?
.code
start:
        ;invoke	printf,offset szMsg
        mov   	ax,a
        add   	ax,b
        mov   	sum,ax
        mov   	bx,d
        sub   	dx,dx
        div   	bx
        mov  	word ptr res,ax
        ;mov  	word ptr res+2,0
        invoke	printf,offset szMsg,res
        ret
end     start