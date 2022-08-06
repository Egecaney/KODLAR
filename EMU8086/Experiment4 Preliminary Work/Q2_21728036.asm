.Model Small
.Stack 64
.Data
String1 DB "Press S/s for square, T/t for triangle: ","$"
String2 DB 0Ah,0Dh,"Press enter the height of shape: ","$" 
Select DB 1 dup(?)
Height DB 1 dup(?)
NotValid DB "It is not valid input","$" 
NextLine DB 0Ah,0Dh,"$"
.Code

PROC Main
Mov AX,Data
Mov DS,AX 

Start:    
Lea BX,Select            ; To keep the SELECTION in memory
Lea BP,Height            ; To keep the HEIGHT in memory

Mov AH,9h
Mov DX,OFFSET String1    ; To printf String1
Int 21h 
Mov AH,01h
Int 21h                  ; To get the selection
Mov [BX],AL              ; To keep selection

Mov AH,9h
Mov DX,OFFSET String2    ; To printf String2
Int 21h 
Mov AH,01h               ; To get the height
Int 21h                  

Mov [BP],AL              ; To keep height
Sub [BP],48d             ; Numbers in ASCII start at 48 
Mov AL,10d               ; I subtract 48 from the height to find exact number
Mul [BP]                 ; I multiplied the number by ten because to enlarge the image on the screen
Mov [BP],AL              ; I put the number back into memory. 

Mov AH,9h
Mov DX,OFFSET NextLine   
Int 21h

Cmp [BX],53h             ; IF Select Data is S/s
Je Square                ; Jump to Square
Cmp [BX],73h 
Je Square

Cmp [BX],54h             ; IF Select Data is T/t
Je Triangle              ; Jump to Triangle
Cmp [BX],74h  
Je Triangle
Jne Invalid              ; If the select is not S/s or T/t, the code jumps to Invalid.

Square:
CALL DrawSquare          ; To draw square
Jmp Finish

Triangle:
CALL DrawTriangle        ; To draw triangle
Jmp Finish 

Invalid: 
Mov AH,9h
Mov DX,OFFSET NotValid   ; When the select is not S/s or T/t 
Int 21h                  ; To print screen "It is not valid input".
Mov AH,9h
Mov DX,OFFSET NextLine
Int 21h
Jmp Start                ; It jumps to Start to select a valid input.
ENDP Main

Proc DrawTriangle        ; TO DRAW TRIANGLE     
Mov AX,0012H             ; To set 640*480 pixels
Int 10H
Int 10H

Mov AX,[BP]
Mov AH,00h
Mov BL,02h
Div BL 
Mov CX,320               ; Starting points
Mov DX,240
Sub DX,AX

Mov BX,[BP]              ; To keep height
RightT:                  ; THE RÝGHT EDGE OF THE TRIANGLE 
    Mov AH,0CH           ; Places a single pixel
    Mov AL,0FH           ; Pixel color is white
    Int 10H
    
    Inc DX
    Inc CX
    Dec BL               ; CX and DX increase until it reaches its height.
    Cmp BL,00h           
    Jne RightT
    
Mov BX,[BP]              ; To keep height
Mov AL,2                 ; I multiplied the height by two for the bottom.
Mul BL
Mov BL,AL   
BottomT:                 ; THE BOTTOM OF THE TRIANGLE
    Mov AH,0CH  
    Mov AL,0FH
    Int 10H
    
    Dec CX               
    Dec BL
    Cmp BL,00h           ; CX decrease until it reaches its bottom height.
    Jne BottomT 
    
Mov BX,[BP]              ; To keep height
LeftT:                   ; THE LEFT EDGE OF THE TRIANGLE
    Mov AH,0CH
    Mov AL,0FH
    Int 10H
    
    Inc CX
    Dec DX
    Dec BL               ; DX decrease, CX increase until it reaches its height.
    Cmp BL,00h    
    Jne LeftT
    
Ret
Endp DrawTriangle

PROC DrawSquare          ; TO DRAW SQUARE     
Mov AX,0012H             ; To set 640*480 pixels
Int 10H
Int 10H

Mov AX,[BP]
Mov AH,00h
Mov BL,02h
Div BL  
Mov CX,320
Add CX,AX               ; Starting points
Mov DX,240
Sub DX,AX
  
Mov BX,[BP]              ; To keep height
RightS:                  ; THE RIGHT EDGE OF THE SQUARE
    Mov AH,0CH
    Mov AL,0FH
    Int 10H
    
    Inc DX     
    Dec BL
    Cmp BL,00h           ; DX increase until it reaches its height.
    Jne RightS 
    
Mov BX,[BP]              ; To keep height
BottomS:                 ; THE BOTTOM OF THE SQUARE
    Mov AH,0CH
    Mov AL,0FH
    Int 10H
    
    Dec CX     
    Dec BL
    Cmp BL,00h           ; CX decrease until it reaches its height.
    Jne BottomS
    
Mov BX,[BP]              ; To keep height
LeftS:                   ; THE LEFT EDGE OF THE SQUARE
    Mov AH,0CH
    Mov AL,0FH
    Int 10H
    
    Dec DX     
    Dec BL
    Cmp BL,00h           ; DX decrease until it reaches its height.
    Jne LeftS
    
Mov BX,[BP]              ; To keep height
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
Finish:
Ends             
    
                


    
        

