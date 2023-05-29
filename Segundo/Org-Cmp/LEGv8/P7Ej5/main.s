; .data
; f: .dword 1
; g: .dword 2
; h: .dword 3
; i: .dword 4
; j: .dword 5
;
.text
ADD X10, XZR, XZR
loop: LDUR X1, [X0,#0]
ADD X2, X2, X1
ADD X0, X0, #8
ADD X10, X10, #1
CMP X10, #100
B.LT loop

infloop: B infloop
