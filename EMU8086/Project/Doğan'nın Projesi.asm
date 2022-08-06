name "ELE338_PROJECT_21728198"


PUTC    MACRO   char
        PUSH    AX
        MOV     AL, char
        MOV     AH, 0Eh
        INT     10h     
        POP     AX
 ENDM

 org 100h
 
jmp code 
 
msg1 db "Welcome to the calculator ",'$'   
msg2 db 0dh,0ah,"Here is our options : ",'$'  
msg3 db 0dh,0ah,"",'$'   
msg4 db 0dh,0ah,"a. Resistances R1 and R2 from given gain of amplifier for non-inverting Op-Amp.",'$' 
msg5 db 0dh,0ah,"b. Resistances R1 and R2 from given gain of amplifier for inverting Op-Amp.   ",'$' 
msg6 db 0dh,0ah,"c. Gain of amplifier from resistances R1 and R2 for non-inverting Op-Amp.   ",'$' 
msg7 db 0dh,0ah,"d. Gain of amplifier from resistances R1 and R2 for inverting Op-Amp    ",'$' 
msg8 db 0dh,0ah,"",'$' 
msg9 db 0dh,0ah,"Select the choice you want to do :  ",'$' 
msg10 db 0dh,0ah,"You entered invalid value. All done is canceled. Try again : ",'$'
msg11 db 0dh,0ah,"You have the gain and you want to know ratio of R2/R1. : ",'$' 
msg12 db 0dh,0ah,"We have the gain value. The ratio of R2/R1 are supposed to be :",'$'
msg13 db 0dh,0ah,"The gain value you enteres is  : ",'$'
msg14 db 0dh,0ah,"Now enter the gain value. : ",'$' 
msg15 db 0dh,0ah,"Please enter the R1 value ( ohm ) : ",'$'
msg16 db 0dh,0ah,"Please enter the R2 value ( ohm ) : ",'$'
msg17 db 0dh,0ah,"Please enter the gain value : ",'$' 
msg18 db 0dh,0ah,"Your gain value is : ",'$' 
msg19 db " / ",'$'  
msg20 db 0dh,0ah,"Press any key to see the shape of amplifier...",'$' 
msg21 db 0dh,0ah,"",'$'
msg22 db "                               R2=",'$'
msg23 db "                         Rc",'$'
msg24 db "ohm",'$'
msg25 db "               R1=",'$' 
msg26 db "                               R2=",'$'
msg27 db "               R1=",'$'
 

msg28 db 0dh,0ah,"To execute process , we are assuming R1 to be 1k ohm.",'$'
msg29 db 0dh,0ah,"Now your R2 value are supposed to be : ",'$' 
msg30 db "k ohm",'$' 
msg31 db "1",'$' 
msg32 db 0dh,0ah,"Your gain value has to be negative. Please enter the MAGNITUDE OF GAIN!!",'$'
msg33 db 0dh,0ah,"Your gain value is : -",'$'


  

res1 dw ?
res2 dw ?  
gain dw ?

ten             DW      10

choice db 1 dup (?) 




code:   

call start
call determiner


  
RET               

;-------------------------------------------------------------------------------------  
proc start
    
 mov dx,offset msg1       
 mov ah,9
 int 21h 
 mov dx,offset msg2       
 mov ah,9
 int 21h 
 mov dx,offset msg3       
 mov ah,9
 int 21h
 mov dx,offset msg4       
 mov ah,9
 int 21h
 mov dx,offset msg5            ; PRÝNTÝNG STARDART MESSAGES ON THE SCREEN
 mov ah,9
 int 21h
 mov dx,offset msg6       
 mov ah,9
 int 21h
 mov dx,offset msg7       
 mov ah,9
 int 21h   
  mov dx,offset msg8       
 mov ah,9
 int 21h  
  mov dx,offset msg9       
 mov ah,9
 int 21h 
endp  start
ret

;------------------------------------------------------------------------------------- 
 proc determiner
 try:    
 mov ah,01h                    ; TAKÝNG ÝNPUT FROM USER TO EXECUTE
 int 21h
 mov cl,al                         
 
 cmp cl,'a'
 JZ call doA 
 cmp cl,'b'
 JZ  call doB                  ; CONTROLLING INPUT TO CALL RELATED PROC
 cmp cl,'c'
 JZ  call doC
 cmp cl,'d'
 JZ  call doD
 
 cmp cl,'A'
 JZ call doA 
 cmp cl,'B'
 JZ  call doB                  ; CONTROLLING INPUT TO CALL RELATED PROC
 cmp cl,'C'
 JZ  call doC
 cmp cl,'D'
 JZ  call doD
 
 mov dx,offset msg8           
 mov ah,9
 int 21h
 
 mov dx,offset msg10           ; CONDITION IF INPUT IS NOT VALID
 mov ah,9
 int 21h 
    
  mov dx,offset msg8           
 mov ah,9
 int 21h  
 
 mov dx,offset msg8           
 mov ah,9
 int 21h
 
 jmp code
 
  endp determiner     
  ret
;-------------------------------------------------------------------------------------

proc doA
    
 mov dx,offset msg11       
 mov ah,9
 int 21h 
 mov dx,offset msg17       
 mov ah,9
 int 21h 
 
 call scan_num                                  ; We are taking gain value.
 mov gain, cx  
 
 mov dx,offset msg18       
 mov ah,9
 int 21h
 
 mov ax,gain
 call print_num 
 
 mov dx,offset msg12       
 mov ah,9
 int 21h
 
 
 mov ax,gain
 dec ax 
 
 call print_num 
 
 mov dx,offset msg28       
 mov ah,9
 int 21h 
 
 mov dx,offset msg29       
 mov ah,9
 int 21h 
 
 mov ax,gain                                     ;We are assuming R1 to be 1k ohm and arrenge R2 for the gain.
 dec ax  
 call print_num
 
 
 mov dx,offset msg30       
 mov ah,9
 int 21h 
 
 mov dx,offset msg20       
 mov ah,9
 int 21h
 
 mov ah,01h                    
 int 21h
 mov cl,al
 
call draw12                                                  ; Here we are drawing the shape.
                                                             ; and arranging all the lines and spaces to write R1 and R2 on the shape
mov di,11

rpt1:
mov dx,offset msg21       
 mov ah,9
 int 21h
 dec di
 cmp di,0
JG rpt1  

mov dx,offset msg22       
 mov ah,9
 int 21h 
  
 mov ax,gain
 dec ax
 call print_num
 
 mov dx,offset msg30        
 mov ah,9
 int 21h
   
 
 mov di,20
 
 rpt2:
mov dx,offset msg21       
 mov ah,9
 int 21h
 dec di
 cmp di,0
JG rpt2      

mov dx,offset msg25       
 mov ah,9
 int 21h  
 
  mov dx,offset msg31       
 mov ah,9
 int 21h
 
 
mov dx,offset msg30       
 mov ah,9
 int 21h
 
 
 
 
 
 
 
    
endp  doA 
ret
 
;-------------------------------------------------------------------------------------

proc doB
    
 mov dx,offset msg11       
 mov ah,9
 int 21h
 mov dx,offset msg32       
 mov ah,9
 int 21h 
 mov dx,offset msg17       
 mov ah,9
 int 21h
 
 
  
 
 call scan_num                                   ; We are taking gain value.
 mov gain, cx  
 
 mov dx,offset msg33       
 mov ah,9
 int 21h
 
 mov ax,gain
 call print_num 
 
 mov dx,offset msg12       
 mov ah,9
 int 21h
 
 
 mov ax,gain                                       ;We are assuming R1 to be 1k ohm and arrenge R2 for the gain.
 call print_num 
 
 mov dx,offset msg28       
 mov ah,9
 int 21h 
 
 mov dx,offset msg29       
 mov ah,9
 int 21h 
 
 mov ax,gain   
 call print_num
 
 
 mov dx,offset msg30       
 mov ah,9
 int 21h 
 
 mov dx,offset msg20       
 mov ah,9
 int 21h
 
 mov ah,01h                    
 int 21h
 mov cl,al 
 
 call draw11                                               ; Here we are drawing the shape.
                                                           ; and arranging all the lines and spaces to write R1 and R2 on the shape
mov di,10

rpt3:
mov dx,offset msg21       
 mov ah,9
 int 21h
 dec di
 cmp di,0
JG rpt3
  
mov dx,offset msg26       
 mov ah,9
 int 21h  
 mov ax,gain
 call print_num
 
 mov dx,offset msg30               
 mov ah,9
 int 21h  
   
 mov di,13
 
 rpt4:
mov dx,offset msg21       
 mov ah,9
 int 21h
 dec di
 cmp di,0
JG rpt4      

mov dx,offset msg27       
 mov ah,9
 int 21h  
 
 mov dx,offset msg31       
 mov ah,9
 int 21h
 
   

mov dx,offset msg30       
 mov ah,9
 int 21h 
 
 mov di,6

rpt5:
mov dx,offset msg21       
 mov ah,9
 int 21h
 dec di
 cmp di,0
JG rpt5

mov dx,offset msg23       
 mov ah,9
 int 21h
 
 
  
 
    
 endp doB      
ret

;-------------------------------------------------------------------------------------

proc doC 
    
mov dx,offset msg15       
 mov ah,9
 int 21h
     
call scan_num
mov res1, cx                                        ; We are taking R1 value from user


mov dx,offset msg16       
 mov ah,9
 int 21h 
 
 call scan_num                                      ; We are taking R2 value from user
mov res2, cx 

mov dx,offset msg18       
 mov ah,9
 int 21h

mov ax,res1
add ax,res2
                                                    ; We are finding gain value and print it on the screen.
call print_num 
 
 mov dx,offset msg19       
 mov ah,9
 int 21h 
 mov ax,res1
 
 call print_num 
 
 mov dx,offset msg20       
 mov ah,9
 int 21h
 
 
 mov ah,01h                    
 int 21h
 mov cl,al
 
call draw12                                      ; Here we are drawing the shape.
                                                  ; and arranging all the lines and spaces to write R1 and R2 on the shape
mov di,11

rpt6:
mov dx,offset msg21       
 mov ah,9
 int 21h
 dec di
 cmp di,0
JG rpt6
  
mov dx,offset msg22       
 mov ah,9
 int 21h
   
 mov ax,res2
 call print_num
 
 mov dx,offset msg24       
 mov ah,9
 int 21h  
 mov ax,res2  
 
 mov di,20
 
 rpt7:
mov dx,offset msg21       
 mov ah,9
 int 21h
 dec di
 cmp di,0
JG rpt7      

mov dx,offset msg25       
 mov ah,9
 int 21h
 
 mov ax,res1
 
call print_num   

mov dx,offset msg24       
 mov ah,9
 int 21h
 

 
 
  
   



  


   
endp doC
ret

;-------------------------------------------------------------------------------------

proc doD  
    
    
mov dx,offset msg15       
 mov ah,9
 int 21h
     
call scan_num                                      ; We are taking R1 value from user
mov res1, cx 


mov dx,offset msg16       
 mov ah,9
 int 21h 
 
 call scan_num                                     ; We are taking R2 value from user
mov res2, cx 

mov dx,offset msg18       
 mov ah,9
 int 21h

mov ax,0
sub ax,res2                                     ; We are finding gain value and print it on the screen.
 
call print_num 
 
 mov dx,offset msg19       
 mov ah,9
 int 21h
  
 mov ax,res1
 
 call print_num 
 
 mov dx,offset msg20       
 mov ah,9
 int 21h
 
 
 mov ah,01h                    
 int 21h
 mov cl,al
 
call draw11                                   ; Here we are drawing the shape.
                                              ; and arranging all the lines and spaces to write R1 and R2 on the shape
mov di,10

rpt8:
mov dx,offset msg21       
 mov ah,9
 int 21h
 dec di
 cmp di,0
JG rpt8
  
mov dx,offset msg26       
 mov ah,9
 int 21h  
 mov ax,res2
 
 call print_num
 mov dx,offset msg24       
 mov ah,9
 int 21h  
 mov ax,res2  
 
 mov di,13
 
 rpt9:
mov dx,offset msg21       
 mov ah,9
 int 21h
 dec di
 cmp di,0
JG rpt9      

mov dx,offset msg27       
 mov ah,9
 int 21h
 
 mov ax,res1
 
call print_num   

mov dx,offset msg24       
 mov ah,9
 int 21h 
 
 mov di,6

rpt10:
mov dx,offset msg21       
 mov ah,9
 int 21h
 dec di
 cmp di,0
JG rpt10

mov dx,offset msg23       
 mov ah,9
 int 21h
  
 

    
endp doD
ret

;-------------------------------------------------------------------------------------   

Proc draw11 ; TO DRAW TRIANGLE
Mov AX,0012H ; To set 640*480 pixels
Int 10H
Int 10H
Mov CX,100 ; Starting points
Mov DX,200
Mov BX,si ; To keep height 

here1: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX
 Cmp cx,150                                            ; Here is our drawing code.
 JNE here1                                             ; Shape is a little bit difficult to draw.
                                                       ; Here is not much to say. just draw all the lines for shape
 here2: 
 Mov AH,0CH 
 Mov AL,0FH
 Int 10H
 Int 10H
 Inc CX
 dec dx
 Cmp cx,155
 JNE here2
 
 here3:
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX 
 inc dx
 Cmp cx,160
 JNE here3
 
 here4: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX 
 dec dx
 Cmp cx,165
 JNE here4 
 
 here5: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX 
 inc dx
 Cmp cx,170
 JNE here5
 
  here6: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX 
 dec dx
 Cmp cx,175
 JNE here6 
 
   here7:
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX 
 inc dx
 Cmp cx,180
 JNE here7
 
  here8: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX 
 dec dx
 Cmp cx,185
 JNE here8   
 
 here9: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX 
 inc dx
 Cmp cx,190
 JNE here9   
 
 here10: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX 
 Cmp cx,240
 JNE here10  
 
 mov cx,200
 
  here11: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H 
 dec dx
 Cmp dx,100
 JNE here11 
 
 here12: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx 
 Cmp cx,255
 JNE here12 
 
  here13: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX
 dec dx
 Cmp cx,260
 JNE here13
 
 here14: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX 
 inc dx
 Cmp cx,265
 JNE here14
 
 here15:
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX 
 dec dx
 Cmp cx,270
 JNE here15 
 
  here16:
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX 
 inc dx
 Cmp cx,275
 JNE here16
 
  here17: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX 
 dec dx
 Cmp cx,280
 JNE here17 
 
   here18: 
 Mov AH,0CH 
 Mov AL,0FH
 Int 10H
 Int 10H
 Inc CX 
 inc dx
 Cmp cx,285
 JNE here18
 
  here19: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX 
 dec dx
 Cmp cx,290
 JNE here19   
 
 here20: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX 
 inc dx
 Cmp cx,295
 JNE here20 
 
  here21: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 Inc CX 
 Cmp cx,350
 JNE here21 
 
 mov cx,220
 mov dx,200
 
 here22: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 dec dx 
 Cmp dx,180
 JNE here22  
 
  here23: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx 
 Cmp cx,240
 JNE here23 
 
 mov dx,140
 
 here24: 
 Mov AH,0CH
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx 
 Cmp dx,240
 JNE here24 
 
 mov cx,240
 mov dx,140
 
 here25: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx
 inc dx 
 Cmp cx,290
 JNE here25  
  
 mov cx,240
 mov dx,240
  
  here26:
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx
 dec dx 
 Cmp cx,290
 JNE here26  
 
  here27: 
 Mov AH,0CH
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx 
 Cmp cx,400
 JNE here27 
 
 mov dx,100
 mov cx,350 
 
  here28: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx 
 Cmp dx,190
 JNE here28   
 
  mov cx,220
  mov dx,200
  
  here29: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx 
 Cmp dx,220
 JNE here29 
        
 here30: 
 Mov AH,0CH 
 Mov AL,0FH
 Int 10H
 Int 10H
 inc dx
 inc cx 
 Cmp dx,225
 JNE here30
    
 here31: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx 
 dec cx
 Cmp dx,230
 JNE here31 
 
 here32: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx
 inc cx 
 Cmp dx,235
 JNE here32
    
 here33: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx 
 dec cx
 Cmp dx,240
 JNE here33
 
 here34: 
 Mov AH,0CH 
 Mov AL,0FH
 Int 10H
 Int 10H
 inc dx
 inc cx 
 Cmp dx,245
 JNE here34
    
 here35: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx 
 dec cx
 Cmp dx,250
 JNE here35
 
 here36: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx
 inc cx 
 Cmp dx,255
 JNE here36
    
 here37:
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx 
 dec cx
 Cmp dx,260
 JNE here37   
 
 
 here38: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx 
 Cmp dx,300
 JNE here38    
  
  mov cx,210 
  
  here39: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx 
 Cmp cx,230
 JNE here39  
  
  mov dx,180
  mov cx,250
  here40: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx 
 Cmp cx,260
 JNE here40
 
 mov dx,175
 mov cx,255
  here41: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx 
 Cmp dx,185
 JNE here41  
 
 mov dx,200
  mov cx,250
  here42: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx 
 Cmp cx,260
 JNE here42
  
 draw11  Endp 
 ret
  
;-------------------------------------------------------------------------------------   


Proc draw12 ; TO DRAW TRIANGLE
Mov AX,0012H ; To set 640*480 pixels
Int 10H
Int 10H
Mov CX,200 ; Starting points
Mov DX,100


her1:                                                   ; Here is our drawing code
 Mov AH,0CH                                             ; Shape is a little bit difficult to draw.
 Mov AL,0FH                                             ; Here is not much to say. just draw all the lines for shape
 Int 10H
 Int 10H
 inc dx
 Cmp dx,230
 Jne her1 
 
 her2: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx 
 inc cx
 Cmp dx,235
 Jne her2
   
  her3: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx
 dec cx 
 Cmp dx,240
 Jne her3  
 
  her4: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx 
 inc cx
 Cmp dx,245
 Jne her4
   
  her5: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx
 dec cx 
 Cmp dx,250
 Jne her5 
 
  her6: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx 
 inc cx
 Cmp dx,255
 Jne her6
   
  her7: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx
 dec cx 
 Cmp dx,260
 Jne her7 
 
  her8: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx 
 inc cx
 Cmp dx,265
 Jne her8
   
  her9: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx
 dec cx 
 Cmp dx,270
 Jne her9 
 
  her10: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx 
 Cmp dx,300
 Jne her10
 
 mov cx,190  
  her11: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx
  Cmp cx,210
 Jne her11  
 
  mov cx,150
  mov dx,160  
  her12: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx
  Cmp cx,250
 Jne her12  
 
 
 mov cx,200
  mov dx,200  
  her13: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx
  Cmp cx,250
 Jne her13  
 
  mov cx,250
  mov dx,130  
  her14: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx
 Cmp dx,230
 Jne her14  
 
 mov cx,250
  mov dx,130  
  her15: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx
 inc cx
 Cmp cx,300
 Jne her15 
 
 mov cx,250
  mov dx,230  
  her16: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx
 dec dx
 Cmp cx,300
 Jne her16 
 
  her17: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx
 Cmp cx,400
 Jne her17  
 
 mov cx,350
 mov dx,100
 her18: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx
 Cmp dx,180
 Jne her18
 
 mov cx,200
 mov dx,100 
 
  her19: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx
 Cmp cx,255
 Jne her19 
 
 her20: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx 
 dec dx
 Cmp cx,260
 Jne her20  
 
  her21: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx
 inc dx
 Cmp cx,265
 Jne her21   
 
  her22: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx 
 dec dx
 Cmp cx,270
 Jne her22  
 
  her23: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx
 inc dx
 Cmp cx,275
 Jne her23 
 
  her24: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx 
 dec dx
 Cmp cx,280
 Jne her24  
 
  her25: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx
 inc dx
 Cmp cx,285
 Jne her25  
 
  her26: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx 
 dec dx
 Cmp cx,290
 Jne her26  
 
  her27: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx
 inc dx
 Cmp cx,295
 Jne her27  
 
  her28: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx
 Cmp cx,350
 Jne her28  
 
 mov cx,255
 mov dx,160
 her29: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx
 Cmp cx,265
 Jne her29
  
 mov cx,260
 mov dx,155
  her30: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc dx
 Cmp dx,165
 Jne her30 
 
 mov cx,255
 mov dx,200
  her31: 
 Mov AH,0CH 
 Mov AL,0FH 
 Int 10H
 Int 10H
 inc cx
 Cmp cx,265
 Jne her31 
 
 
 

Endp draw12 
ret


;----------------------------------------------------------------------------------------------------------------
   
   
SCAN_NUM        PROC    NEAR                                       ; Here is our scan_num proc. 
        PUSH    DX
        PUSH    AX
        PUSH    SI
        
        MOV     CX, 0

        ; reset flag:
        MOV     CS:make_minus, 0

next_digit:

        ; get char from keyboard
        ; into AL:
        MOV     AH, 00h
        INT     16h
        ; and print it:
        MOV     AH, 0Eh
        INT     10h

        ; check for MINUS:
        CMP     AL, '-'
        JE      set_minus

        ; check for ENTER key:
        CMP     AL, 0Dh  ; carriage return?
        JNE     not_cr
        JMP     stop_input
not_cr:


        CMP     AL, 8                   ; 'BACKSPACE' pressed?
        JNE     backspace_checked
        MOV     DX, 0                   ; remove last digit by
        MOV     AX, CX                  ; division:
        DIV     CS:ten                  ; AX = DX:AX / 10 (DX-rem).
        MOV     CX, AX
        PUTC    ' '                     ; clear position.
        PUTC    8                       ; backspace again.
        JMP     next_digit
backspace_checked:


        ; allow only digits:
        CMP     AL, '0'
        JAE     ok_AE_0
        JMP     remove_not_digit
ok_AE_0:        
        CMP     AL, '9'
        JBE     ok_digit
remove_not_digit:       
        PUTC    8       ; backspace.
        PUTC    ' '     ; clear last entered not digit.
        PUTC    8       ; backspace again.        
        JMP     next_digit ; wait for next input.       
ok_digit:


        ; multiply CX by 10 (first time the result is zero)
        PUSH    AX
        MOV     AX, CX
        MUL     CS:ten                  ; DX:AX = AX*10
        MOV     CX, AX
        POP     AX

        ; check if the number is too big
        ; (result should be 16 bits)
        CMP     DX, 0
        JNE     too_big

        ; convert from ASCII code:
        SUB     AL, 30h

        ; add AL to CX:
        MOV     AH, 0
        MOV     DX, CX      ; backup, in case the result will be too big.
        ADD     CX, AX
        JC      too_big2    ; jump if the number is too big.

        JMP     next_digit

set_minus:
        MOV     CS:make_minus, 1
        JMP     next_digit

too_big2:
        MOV     CX, DX      ; restore the backuped value before add.
        MOV     DX, 0       ; DX was zero before backup!
too_big:
        MOV     AX, CX
        DIV     CS:ten  ; reverse last DX:AX = AX*10, make AX = DX:AX / 10
        MOV     CX, AX
        PUTC    8       ; backspace.
        PUTC    ' '     ; clear last entered digit.
        PUTC    8       ; backspace again.        
        JMP     next_digit ; wait for Enter/Backspace.
        
        
stop_input:
        ; check flag:
        CMP     CS:make_minus, 0
        JE      not_minus
        NEG     CX
not_minus:

        POP     SI
        POP     AX
        POP     DX
        RET
make_minus      DB      ?       ; used as a flag.
SCAN_NUM        ENDP 
ret 

;--------------------------------------------------------------------

PRINT_NUM       PROC    NEAR
        PUSH    DX
        PUSH    AX

        CMP     AX, 0
        JNZ     not_zero

        PUTC    '0'
        JMP     printed

not_zero:
        ; the check SIGN of AX,
        ; make absolute if it's negative:
        CMP     AX, 0
        JNS     positive
        NEG     AX

        PUTC    '-'

positive:
        CALL    PRINT_NUM_UNS
printed:
        POP     AX
        POP     DX
        RET
PRINT_NUM       ENDP 
ret

;----------------------------------------------------------------

PRINT_NUM_UNS   PROC    NEAR
        PUSH    AX
        PUSH    BX
        PUSH    CX
        PUSH    DX

        ; flag to prevent printing zeros before number:
        MOV     CX, 1

        ; (result of "/ 10000" is always less or equal to 9).
        MOV     BX, 10000       ; 2710h - divider.

        ; AX is zero?
        CMP     AX, 0
        JZ      print_zero

begin_print:

        ; check divider (if zero go to end_print):
        CMP     BX,0
        JZ      end_print

        ; avoid printing zeros before number:
        CMP     CX, 0
        JE      calc
        ; if AX<BX then result of DIV will be zero:
        CMP     AX, BX
        JB      skip
calc:
        MOV     CX, 0   ; set flag.

        MOV     DX, 0
        DIV     BX      ; AX = DX:AX / BX   (DX=remainder).

        ; print last digit
        ; AH is always ZERO, so it's ignored
        ADD     AL, 30h    ; convert to ASCII code.
        PUTC    AL


        MOV     AX, DX  ; get remainder from last div.

skip:
        ; calculate BX=BX/10
        PUSH    AX
        MOV     DX, 0
        MOV     AX, BX
        DIV     CS:ten  ; AX = DX:AX / 10   (DX=remainder).
        MOV     BX, AX
        POP     AX

        JMP     begin_print
        
print_zero:
        PUTC    '0'
        
end_print:

        POP     DX
        POP     CX
        POP     BX
        POP     AX
        RET
PRINT_NUM_UNS   ENDP 
ret                                                           