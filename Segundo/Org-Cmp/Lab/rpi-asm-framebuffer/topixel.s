.text
.global topixel

/* Toma (x1, x2) como argumentos y devuelve en x3 esa posicion
de pixeles como una adress */ 
topixel:
    sub sp, sp, 16
    stur lr, [sp, 8]
    stur x9, [sp, 0]
    mov x9, 640
    mul x3, x22, x9      // y * 640
    add x3, x3, x11     // y * 640 + x
    lsl x3, x3, 2      // 4*(y * 640 + x )
    add x3, x3, x20    // 4*(y * 640 + x ) + direccion base
    ldur lr, [sp, 8]
    ldur x9, [sp, 0]
    add sp, sp, 16
    br lr
