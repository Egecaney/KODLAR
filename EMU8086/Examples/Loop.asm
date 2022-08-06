;LOOP

org 100h

;CX dongunun kac kere donecegini belirler.
;Bunun icin CX'e bir tekrar sayinin atanmasi gerekmektedir.
;Her loop CX'in degerini 1 azaltir.
;Dongu CX=0 olduguna kadar tekrar eder.

Mov AX,4455h
 

Mov CX,3
start:
     Dec AL
     Inc AH
     Loop start

ret
end
                     ;En sonunda
                       ;AL= 52h    (-3)
                       ;AH= 47h    (+3)
                       ;CX= 00h


