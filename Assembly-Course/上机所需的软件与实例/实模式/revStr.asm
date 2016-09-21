STACK SEGMENT STACK
        DW 100 DUP(0)
STACK ENDS

DATA  SEGMENT
        BUFFER DB 100, ?, 100 DUP(?)
        PRINT  DB 'Input a String: ', '$'
        CRLF   DB 0DH, 0AH, '$'
DATA  ENDS

CODE  SEGMENT
        ASSUME CS:CODE, DS:DATA, SS:STACK
MAIN  PROC FAR
      MOV AX, DATA
      MOV DS, AX
      MOV AH, 9
      LEA DX, PRINT
      INT 21H
      
      MOV AH, 0AH
      LEA DX, BUFFER
      INT 21H
      
      MOV AH, 9
      LEA DX, CRLF
      INT 21H
      
      MOV CL, BUFFER+1
      XOR CH, CH
      LEA SI, BUFFER+2
      ADD SI, CX
      ADD CL, 1
      
      MOV AH, 2
A:    MOV DL,[SI]
      INT 21H
      DEC SI
      LOOP A

      MOV AX, 4C00H
      INT 21H
MAIN  ENDP
CODE  ENDS
      END MAIN