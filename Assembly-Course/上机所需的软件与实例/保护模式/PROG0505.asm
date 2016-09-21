;PROG0513
.386
.model flat,stdcall
option casemap:none
includelib	msvcrt.lib
printf    	PROTO C	:dword,:vararg
.data
dArray  	dword 		20, 15, 70, 30, 32, 89, 12
ITEMS     	equ  	($-dArray)/4           	; 数组中元素的个数
szFmt     	byte 	'dArray[%d]=%d', 0ah, 0	; 输出结果格式字符串
.code
start:
      	mov 	ecx, ITEMS-1
i10:            
           	xor  	esi, esi
i20:            
      	mov  	eax, dArray[esi*4]
          	mov  	ebx, dArray[esi*4+4]
      	cmp  	eax, ebx
          	jl   	i30
             	mov  	dArray[esi*4], ebx
          	mov 	dArray[esi*4+4], eax
i30:            
          	inc  	esi
      	cmp 	esi, ecx
        	jb	i20
       	loop 	i10
    		xor 	edi, edi
i40:            
       	invoke	printf, offset szFmt, edi, dArray[edi*4]
        	inc   	edi
        	cmp  	edi, ITEMS
         	jb   	i40
          	ret
end       	start
