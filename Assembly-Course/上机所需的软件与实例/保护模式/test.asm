;PROG0411
.386
.model  flat, stdcall
;option  casemap:none
MessageBoxA	PROTO  :dword,  :dword,  :dword,  :dword
MessageBox	equ	<MessageBoxA>
Includelib	user32.lib
NULL	equ	0
MB_OK	equ	0
.stack  4096
.data
SzTitle	byte	'Hi!', 0
SzMsg	byte	'Hello World!' ,0

.code
start:
MOV	EAX ,0FFFFFFFFH


	invoke  	MessageBox, 
		NULL,	; HWND hWnd
		offset szMsg,	; LPCSTR lpText
		offset szTitle,	; LPCSTR lpCaption 
		MB_OK	; UINT uType 
	ret
end	start