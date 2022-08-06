.Model Small
.Stack 64
.Data
XandY DW 2 dup(?)
.Code

PROC Main
 Mov AX,Data
 Mov DS,AX 
 
 MOV AX, 12H            ; To set 640*480 pixels
 INT 10H
 INT 10H
 
 Start:
 Mov BX,0000h 
 Call Detect            ; Checks if the left mouse button has been pressed.
 DrawS:
 Call DrawSquare        ; If the left button is pressed, it draws a square there.
 Jmp Start
 
Endp Main

PROC Detect

 Lea BP,XandY 
  
 MOV AX, 01
 INT 33H
 
 GetXY:
 Mov AX,03
 Int 33H
 Shr CX,1
 MOV [XandY],CX       ; WRITE X COOR. TO MEMORY "X"
 MOV [XandY+2],DX     ; WRITE Y COOR. TO MEMORY "Y" 
 Cmp BX,1
 Je DrawS
 JMP GetXY  
Endp Detect

PROC DrawSquare          ; TO DRAW SQUARE     

 Add [XandY],04h
 Sub [XandY+2],04h       ; Starting Points
 Mov CX,[XandY]
 Mov DX,[XandY+2]
  
Mov BL,10d               ; To keep height
RightS:                  ; THE RIGHT EDGE OF THE SQUARE
    Mov AH,0CH
    Mov AL,0FH
    Int 10H
    
    Inc DX     
    Dec BL
    Cmp BL,00h           ; DX increase until it reaches its height.
    Jne RightS 
    
Mov BL,10d               ; To keep height
BottomS:                 ; THE BOTTOM OF THE SQUARE
    Mov AH,0CH
    Mov AL,0FH
    Int 10H
    
    Dec CX     
    Dec BL
    Cmp BL,00h           ; CX decrease until it reaches its height.
    Jne BottomS
    
Mov BL,10d               ; To keep height
LeftS:                   ; THE LEFT EDGE OF THE SQUARE
    Mov AH,0CH
    Mov AL,0FH
    Int 10H
    
    Dec DX     
    Dec BL
    Cmp BL,00h           ; DX decrease until it reaches its height.
    Jne LeftS
    
Mov BL,10d               ; To keep height
TopS:                    ; THE RIGHT SIDE OF THE SQUARE
    Mov AH,0CH
    Mov AL,0FH
    Int 10H
    
    Inc CX     
    Dec BL
    Cmp BL,00h           ; CX increase until it reaches its height.
    Jne TopS

Ret
ENDP DrawSquare
Ends