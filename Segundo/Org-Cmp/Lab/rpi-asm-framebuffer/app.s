	.equ SCREEN_WIDTH,   640
	.equ SCREEN_HEIGH,   480
	.equ BITS_PER_PIXEL, 32

	.equ GPIO_BASE,    0x3f200000
	.equ GPIO_GPFSEL0, 0x00
	.equ GPIO_GPLEV0,  0x34

	.globl main

main:
#include rectangle.s
#include topixel.s
#include dline.s

	// x0 contiene la direccion base del framebuffer
	mov x20, x0 // Guarda la dirección base del framebuffer en x20
	//---------------- CODE HERE ------------------------------------

// Ok estas dos direcciones controlan el color
	movz x10, 0x22, lsl 16
	movk x10, 0x2222, lsl 00

	mov x2, SCREEN_HEIGH         // Y Size
loop1:
	mov x1, SCREEN_WIDTH         // X Size
loop0:
	stur w10,[x0]  // Colorear el pixel N
	add x0,x0,4    // Siguiente pixel   Esto pint la pantalla bit por bit
	sub x1,x1,1    // Decrementar contador X    
	cbnz x1,loop0  // Si no terminó la fila, salto
	sub x2,x2,1    // Decrementar contador Y
	cbnz x2,loop1  // Si no es la última fila, salto


	movz x10, 0xff, lsl 16
	movk x10, 0xffff, lsl 00
  
  // Checkeando topixel 
  mov x11, 200
  mov x22, 200
  bl topixel
  stur w10, [x3]
  
  //Checkeando rectangle con topixel
  //(x11, x22) coordenadas donde empieza el cuadrado
  //x1 X size
  //x2 Y size
  mov x1, 100
  mov x2, 100
  mov x11, 10
  mov x22, 10
  bl rectangle


  //Checkeando diagonal line
  // en dline (x1, x2) es el punto de inicio
  // (x11, x22) el punto final
  mov x1, 200
  mov x2, 200
  mov x11, 221 
  mov x22, 440

  bl dline


	// Ejemplo de uso de gpios
	mov x9, GPIO_BASE

	// Atención: se utilizan registros w porque la documentación de broadcom
	// indica que los registros que estamos leyendo y escribiendo son de 32 bits

	// Setea gpios 0 - 9 como lectura
	str wzr, [x9, GPIO_GPFSEL0]

	// Lee el estado de los GPIO 0 - 31
	ldr w10, [x9, GPIO_GPLEV0]

  

	// And bit a bit mantiene el resultado del bit 2 en w10 (notar 0b... es binario)
	// al inmediato se lo refiere como "máscara" en este caso:
	// - Al hacer AND revela el estado del bit 2
	// - Al hacer OR "setea" el bit 2 en 1
	// - Al hacer AND con el complemento "limpia" el bit 2 (setea el bit 2 en 0)
	and w11, w10, 0b00000010

	// si w11 es 0 entonces el GPIO 1 estaba liberado
	// de lo contrario será distinto de 0, (en este caso particular 2)
	// significando que el GPIO 1 fue presionado

	//---------------------------------------------------------------
	// Infinite Loop

InfLoop:
	b InfLoop
