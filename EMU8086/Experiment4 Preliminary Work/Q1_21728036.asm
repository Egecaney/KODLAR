.Model Small
.Stack 64
.Data
String1 DB "Press S/s for square, T/t for triangle: ","$"
String2 DB 0Ah,0Dh,"Press enter the height of shape: ","$" 
Select DB 1 dup(?)
Height DB 1 dup(?)
NotValid DB "It is not valid input","$" 
Cross1 DB 0ah,0dh,"X","$"
Cross2 DB "X","$"
SpaceX DB " ","$"
NextLine DB 0Ah,0Dh,"$"

.Code
Proc Main 
MOV AX,Data
MOV DS,AX

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
Mov AH,01h
Int 21h                  ; To get the height
Mov [BP],AL              ; To keep height
SUB [BP],48d             ; Numbers in ASCII start at 48 
                         ; I subtract 48 from the height to find exact number

Mov AH,9h
Mov DX,OFFSET NextLine   ; To pass next line
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
Endp Main
 
Proc DrawSquare
  MOV CL,[BP]            ; To keep height 
  MOV CH,CL              
  SUB CH,2d              ; To keep the height of the middle area 
 
 TOP:                    ; TOP OF THE SQUARE
  Mov AH,9h
  Mov DX,OFFSET Cross2
  Int 21h                ; To print top of the square
  Dec CL
  Cmp CL,00d
 JNE TOP
  
 ALLSIDE:                ; MIDDLE PART OF SQUARE
  MOV CL,[BP]
  DEC CH
  FirstX: 
  Mov AH,9h
  Mov DX,OFFSET Cross1   ; To print first X
  Int 21h
  Dec CL
  Space:
  Mov AH,9h
  Mov DX,OFFSET SpaceX   ; To print spaces
  Int 21h
  Dec CL
  Cmp CL,01h
  JNE Space
  FinalX:
  Mov AH,9h
  Mov DX,OFFSET Cross2   ; To print final X
  Int 21h
  Cmp CH,00d
 JNE ALLSIDE
 
  Mov AH,9h
  Mov DX,OFFSET NextLine
  Int 21h
   
  MOV CL,[BP]
 BOTTOM:                 ; BOTTOM OF THE SQUARE
  Mov AH,9h
  Mov DX,OFFSET Cross2   ; To print bottom of the square
  Int 21h
  Dec CL
  Cmp CL,00d
 JNE BOTTOM  
Ret
Endp DrawSquare

Proc DrawTriangle          
 TriTop: 
  Mov CX,[BP]            ; To keep height 
  Sub CX,01h             ; To print space
  Mov CH,00h             ; I gave 0 to CH to fix the number.
  Spa1:
  Mov AH,9h
  Mov DX,OFFSET SpaceX   ; To print space up to the HEÝGHT-1
  Int 21h
  Loop Spa1 
  
  Mov AH,9h
  Mov DX,OFFSET Cross2   ; To print X
  Int 21h
  Mov AH,9h
  Mov DX,OFFSET NextLine
  Int 21h
  
  Mov DI,01h
  Mov BX,01h
  Mov CX,[BP]            ; I edited registers for other parts
  Sub CX,02h
  MOV CH,00h
  
 TriSide:
  Mov SI,CX              
  
  Spa2:
  Mov AH,9h               ; First Spaces
  Mov DX,OFFSET SpaceX    ; To print space up to the HEÝGHT-2 
  Int 21h
  Dec SI
  Cmp SI,00h
  Jne Spa2
  
  Mov AH,9h
  Mov DX,OFFSET Cross2    ; To printf X
  Int 21h
  
  OtherSpa2:               
  Mov AH,9h               ; Second Spaces
  Mov DX,OFFSET SpaceX     
  Int 21h       
  Dec DI
  Cmp DI,00h
  Jne OtherSpa2
  
  Mov AH,9h
  Mov DX,OFFSET Cross2    ; To print other X on the same line
  Int 21h

  Add BX,02h              ; To adjust other spaces ýn the lower line
  Mov DI,BX

  Mov AH,9h
  Mov DX,OFFSET NextLine
  Int 21h
 Loop TriSide

  Mov BX,[BP]
  Sub BX,01h
  Mov BH,00h              ; I edited registers for other parts
  mov CX,[BP]
  Mov CH,00h
  Add CX,BX
  
  TriBottom:
  Mov AH,9h
  Mov DX,OFFSET Cross2    ; To print bottom of the triangle 
  Int 21h
  Loop TriBottom
Ret
Endp DrawTriangle
Finish:
Ends