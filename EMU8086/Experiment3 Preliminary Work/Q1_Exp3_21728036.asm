ORG 100H
.DATA
POINTS DB 57,46,58,48,93,63,67,74,70,40,89,99,72,98,43,90,73,95,65,87,71,76,95,60,54,60,100,58,77,86,69,85,57,59,98,75,50,67,95,96,85,62,52,80,54,100,74,54,44,54,73,51,48,100,75,48,99,99,81,88,53,100,82,80,40,95,90,77,44,46,72,41,82,45,50,57,90,43,82,58,55,46,77,98,56,92,82,93,62,60,'$' 
GRADE_MSG DB "Grade Students","$"
A1_MSG DB 0DH,0AH,0DH,0AH,"A1            :","$" 
A2_MSG DB 0DH,0AH,"A2            :","$" 
A3_MSG DB 0DH,0AH,"A3            :","$" 
B1_MSG DB 0DH,0AH,"B1            :","$" 
B2_MSG DB 0DH,0AH,"B2            :","$" 
B3_MSG DB 0DH,0AH,"B3            :","$" 
C1_MSG DB 0DH,0AH,"C1            :","$" 
C2_MSG DB 0DH,0AH,"C2            :","$" 
C3_MSG DB 0DH,0AH,"C3            :","$" 
D_MSG  DB 0DH,0AH," D            :","$" 
F3_MSG DB 0DH,0AH,"F3            :","$"
PASS_MSG DB  0DH,0AH,0DH,0AH, "PASS          :","$" 
FALL_MSG  DB 0DH,0AH,"FALL          :","$" 
TOTAL_MSG DB 0DH,0AH,"TOTAL         :","$"
A1 DW 0 
A2 DW 0
A3 DW 0
B1 DW 0
B2 DW 0
B3 DW 0
C1 DW 0
C2 DW 0
C3 DW 0
D DW 0
F3 DW 0 
PASS DW 0
FALL DW 0 
TOTAL DW 0 
RES DW 10 DUP('$') 
.CODE
MAIN PROC
    CALL NOTES
MAIN ENDP        

NOTES PROC
    MOV SI, OFFSET POINTS          ; I put the values in SI Register 
    MOV CX, 0
    
TRY:
MOV BL,[SI]
INC SI                             ; To pass other number
INC TOTAL                          ; Total Number
INC PASS                           ; Pass Number
CMP BL,'$'                         ; To Fýnýsh the compare and finding gradeletter
JE FINISH 
CALL COMPARE 
NOTES ENDP

COMPARE PROC
COMP_A1:
    CMP BL,94                      ; To find A1
    JG  CO_A1 
COMP_A2:    
    CMP BL,89                      ; To find A2
    JG  CO_A2
COMP_A3:    
    CMP BL,84                      ; To find A3
    JG  CO_A3    
COMP_B1:
    CMP BL,79                      ; To find B1
    JG  CO_B1 
COMP_B2:    
    CMP BL,74                      ; To find B2
    JG  CO_B2  
COMP_B3:    
    CMP BL,69                      ; To find B3
    JG  CO_B3 
COMP_C1:    
    CMP BL,64                      ; To find C1
    JG  CO_C1 
COMP_C2:
    CMP BL,59                      ; To find C2
    JG  CO_C2 
COMP_C3:    
    CMP BL,54                      ; To find C3
    JG  CO_C3  
COMP_D:     
    CMP BL,49                      ; To find D
    JG  CO_D
COMP_F3:     
    CMP BL,50                      ; To find F3
    JL  CO_F3 
                                
CO_A1:                             ; When Gradeletter is A1, Increment A1
    INC A1
    JMP TRY 
CO_A2:                             ; When Gradeletter is A2, Increment A2
    INC A2                         
    JMP TRY 
CO_A3:                             ; When Gradeletter is A3, Increment A3
    INC A3                        
    JMP TRY 
CO_B1:                             ; When Gradeletter is B1, Increment B1
    INC B1                         
    JMP TRY
CO_B2:                             ; When Gradeletter is B2, Increment B2
    INC B2                         
    JMP TRY                        
CO_B3:                             ; When Gradeletter is B3, Increment B3
    INC B3
    JMP TRY
CO_C1:                             ; When Gradeletter is C1, Increment C1
    INC C1
    JMP TRY 
CO_C2:                             ; When Gradeletter is C2, Increment C2
    INC C2
    JMP TRY 
CO_C3:                             ; When Gradeletter is C3, Increment C3
    INC C3
    JMP TRY 
CO_D:                              ; When Gradeletter is D,  Increment D
    INC D
    JMP TRY
CO_F3:                             ; When Gradeletter is F3, Increment F3
    INC F3
    JMP TRY                                             
COMPARE ENDP 

HEXDEC PROC NEAR
    MOV CX,0                       ; This is converter 
    MOV BX,10                      ; HEXADECIMAL ----> DECIMAL

LP1: MOV DX,0
     DIV BX
     ADD DL,30H
     PUSH DX
     INC CX
     CMP AX,9
     JNLE LP1

     ADD AL,30H
     MOV [SI],AL

LP2: POP AX
     INC SI
     MOV [SI],AL
     LOOP LP2
    RET
HEXDEC ENDP

FINISH:                             ; TO PRINT SCREEN 
    MOV CX,F3
    MOV FALL,CX                        
    SUB PASS,CX
    
    LEA DX, GRADE_MSG
    MOV AH, 09H
    INT 21H 
                
    LEA DX, A1_MSG
    MOV AH, 09H
    INT 21H
     
    MOV AX,A1
    LEA SI,RES
    CALL HEXDEC                    ; To show how many people pass with A1
    LEA DX,RES
    MOV AH,9
    INT 21H 

    LEA DX, A2_MSG
    MOV AH, 09H
    INT 21H 

    MOV AX,A2
    LEA SI,RES
    CALL HEXDEC                     ; To show how many people pass with A2
    LEA DX,RES
    MOV AH,9
    INT 21H  
    
    LEA DX, A3_MSG
    MOV AH, 09H
    INT 21H 

    MOV AX,A3
    LEA SI,RES
    CALL HEXDEC                     ; To show how many people pass with A3
    LEA DX,RES
    MOV AH,9
    INT 21H     
    
    LEA DX, B1_MSG
    MOV AH, 09H
    INT 21H 

    MOV AX,B1
    LEA SI,RES
    CALL HEXDEC                     ; To show how many people pass with B1
    LEA DX,RES
    MOV AH,9
    INT 21H
     
    LEA DX, B2_MSG
    MOV AH, 09H
    INT 21H 

    MOV AX,B2
    LEA SI,RES
    CALL HEXDEC                     ; To show how many people pass with B2
    LEA DX,RES
    MOV AH,9
    INT 21H
     
    LEA DX, B3_MSG
    MOV AH, 09H
    INT 21H 

    MOV AX,B3
    LEA SI,RES
    CALL HEXDEC                     ; To show how many people pass with B3
    LEA DX,RES
    MOV AH,9
    INT 21H
     
    LEA DX, C1_MSG
    MOV AH, 09H
    INT 21H 

    MOV AX,C1
    LEA SI,RES                      ; To show how many people pass with C1
    CALL HEXDEC
    LEA DX,RES
    MOV AH,9
    INT 21H 
    
    LEA DX, C2_MSG
    MOV AH, 09H
    INT 21H 

    MOV AX,C2
    LEA SI,RES
    CALL HEXDEC                    ; To show how many people pass with C2
    LEA DX,RES
    MOV AH,9
    INT 21H 
    
    LEA DX, C3_MSG
    MOV AH, 09H
    INT 21H 

    MOV AX,C3
    LEA SI,RES
    CALL HEXDEC                     ; To show how many people pass with C3
    LEA DX,RES
    MOV AH,9
    INT 21H
     
    LEA DX, D_MSG
    MOV AH, 09H
    INT 21H 

    MOV AX,D
    LEA SI,RES
    CALL HEXDEC                     ; To show how many people pass with D
    LEA DX,RES
    MOV AH,9
    INT 21H 
    
    LEA DX, F3_MSG
    MOV AH, 09H
    INT 21H 

    MOV AX,F3
    LEA SI,RES
    CALL HEXDEC                     ; To show how many people pass with F3
    LEA DX,RES
    MOV AH,9
    INT 21H 
    
    LEA DX, PASS_MSG
    MOV AH, 09H
    INT 21H 

    MOV AX,PASS
    LEA SI,RES
    CALL HEXDEC                     ; To show how many people PASS 
    LEA DX,RES
    MOV AH,9
    INT 21H 

    LEA DX, FALL_MSG
    MOV AH, 09H
    INT 21H 

    MOV AX,FALL
    LEA SI,RES
    CALL HEXDEC                     ; To show how many people FALL 
    LEA DX,RES
    MOV AH,9
    INT 21H 

    LEA DX, TOTAL_MSG
    MOV AH, 09H
    INT 21H
     
    MOV AX,TOTAL
    LEA SI,RES
    CALL HEXDEC                     ; To show how many people are there
    LEA DX,RES
    MOV AH,9
    INT 21h
             
HLT
END MAIN



