.text
.global dline

dline:
#include topixel.s

  sub sp, sp, 40
  stur x4, [sp, 32]
  stur x3, [sp, 24]
  stur x2, [sp, 16]
  stur x1, [sp, 8]
  stur lr, [sp, 0]
  // usamos x1, x2, x3, x4
  
  // posicion inicial (x1, x2) = (x1, y1)
  // posicion final (x11, x22) = (x2, y2)

  sub x3, x11, x1  // (x2 - x1)
  sub x4, x22, x2  // (y2 - y1)
  lsl x4, x4, 8    // (y2 - y1) * 256 
  udiv x4, x4, x3  // x4 = m = (y2-y1) * 256 / (x2-x1)
  mov x18, 10
 // udiv x4, x4, x18 
  
  lsl x2, x2, 8    // y = y1 * 256
  // x11 lo usa topixel por lo que lo guardamos en x6
  mov x6, x11

loop:
  cmp x1, x6   // x = x1 
  b.hi end     // x1 > x2
  lsr x22, x2, 8  
  mov x11, x1   //x11 = x
  bl topixel   // x3 = (x11, x22)
  stur w10, [x3]  // paint(x11, x22) = (x, y) = (x1, x2)
  add x1, x1, 1 // x1++
  add x2, x2, x4
  b loop
  
     
 end:  
  ldur x4, [sp, 32]
  ldur x3, [sp, 24]
  ldur x2, [sp, 16]
  ldur x1, [sp, 8]
  ldur lr, [sp, 0]
  add sp, sp, 40
	br lr
	

