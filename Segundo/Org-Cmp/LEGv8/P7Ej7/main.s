.data
N: .dword 3
A: .dword 1,7,2,44,3,21,1,2,3 // A[N][N]
.text
ldr X0, =A // x0 =&A[0][0]
ldr X9, N // N=3
add X1, XZR, XZR // s=0
add X2, XZR, XZR // i=0
add X3, XZR, XZR // j=0
oLoop: cmp X2,X9 // if(i==N)
b.eq oEnd // goto oEnd;
add X3, XZR, XZR // j=0
iLoop: cmp X3,X9 // if(j==N)
b.eq iEnd // goto iEnd;
mul X12, X2, X9 // X12 = i * N
add X12, X12, X3 // X12 = (i * N) + j
lsl x12, x12, #3 // X12 = ((i * N ) + j) * 8
add X12, X12, X0 // X12 = &A[0][0] + ((i * N ) + j) * 8
ldur X11, [X12,#0] // X11=A[i][j]
add X1, X1, X11 // s+=A[i][j]
add X3, X3, #1 // j++;
b iLoop
iEnd: add X2, X2, #1 // i++;
b oLoop
oEnd:
