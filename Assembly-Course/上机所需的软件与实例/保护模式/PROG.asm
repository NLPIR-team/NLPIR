;PROG0505
.386
.model flat,stdcall
;option casemap:none
includelib 	msvcrt.lib
printf       	PROTO C :dword,:vararg
.data
dArray       	byte  	15, 27, 39, 40, 68, 71, 82, 100, 200, 230
Items        	equ  	($-dArray)   		; 数组中元素的个数
Element      	byte  	14          		; 在数组中查找的数字
Index       	dword	?           		; 在数组中的序号
Count   	dword 	?             	; 查找的次数
szFmt		byte 	'Index=%d Count=%d Element=%d', 0ah, 0 ; 格式字符串
szErrMsg	byte	'Not found, Count=%d Element=%d', 0ah, 0 
.code
start:
       mov	Index, -1             	; 赋初值, 假设找不到
       mov  	Count, 0           	; 赋初值, 查找次数为0
       mov 	esi, 0             	; ECX表示查找范围的下界
       mov 	edi, Items-1      	; EDX表示查找范围的上界
       mov  	al, Element        	; EAX是要在数组中查找的数字
Compare:            
       cmp  	esi, edi           	; 下界是否超过上界
       ja   	notfound            	; 如果下界超过上界, 未找到
       mov  	ebx, esi    	; 取下界和上界的中点
       add   	ebx, edi    		; 
       shr	ebx, 1         			; EBX=(ESI+EDI)/2
       inc     	Count               		; 查找次数加1
       cmp	al, dArray[EBX]    		; 与中点上的元素比较
       jz  	Found          		; 相等, 查找结束
       ja    	MoveLow       		; 较大, 移动下界
       mov	edi, ebx       			; 较小, 移动上界
       dec	edi             		; ESI元素已比较过, 不再比较
       jmp	Compare        		; 范围缩小后, 继续查找
MoveLow:    
       mov	esi, ebx          		; 较大, 移动下界
       inc	esi       			; ESI元素已比较过, 不再比较
       jmp	Compare       		; 范围缩小后, 继续查找
Found:            
       mov	Index, ebx    			; 找到, EBX是下标
       xor	eax,  eax
       mov	al, dArray[esi]
       invoke 	printf, offset szFmt, Index, Count, eax
       ret
NotFound:            
       xor	eax,  eax
	   mov	al, Element	
	   invoke	printf, offset szErrMsg, Count, eax 
       ret
end    start