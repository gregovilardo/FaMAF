	.equ SCREEN_WIDTH,   640
	.equ SCREEN_HEIGH,   480
	.equ BITS_PER_PIXEL, 32

	.equ GPIO_BASE,    0x3f200000
	.equ GPIO_GPFSEL0, 0x00
	.equ GPIO_GPLEV0,  0x34

	.globl main

main:
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

  

//STAR RECTRIANGLE
  sub sp, sp, 32
  stur x3, [sp,32]
  stur x4, [sp,16]
  stur x5, [sp, 8]
  stur x6, [sp, 0]
  mov x3, 16 // cantidad de iteraciones para el triangulo
  mov x4, SCREEN_HEIGH-160
  mov x5, 320-SCREEN_WIDTH/4 //160
  mov x6, SCREEN_WIDTH/2
rectriangle: 
  mov x11, x5// X Position
  mov x12, x4  // Y position
	mov x1, x6// X Size
	mov x2, 15// Y Size
  BL rectangle
  sub x4, x4, 15
  add x5, x5, 10
  sub x6, x6, 20
  sub x3, x3, 1
  cbnz x3, rectriangle
  ldur x3, [sp,32]
  ldur x4, [sp,16]
  ldur x5, [sp, 8]
  ldur x6, [sp, 0]
//END RECTRIANGLE
  mov x12, 480 //Paint outside
  mov x11, 640 // ""



//  mov x12, 0  // Y position 
//  mov x11, 0  // X position
//	mov x2, 50// Y Size
//	mov x1, 50// X Size
//  BL rectangle
//  mov x12, 480 //Paint outside
//  mov x11, 640 // ""

rectangle:

// solo necesito x1,x2,x11,x12 el resto debo guardar en stack (x3, x10, x26, x15)
  sub sp, sp, 32
  stur x15, [sp,24]
  stur x3, [sp,16]
  stur x10, [sp, 8]
  stur x26, [sp, 0]

	movz x10, 0xFF, lsl 16    //Color
	movk x10, 0x3900, lsl 00
  
  mov x3, 0

  mov x15, x1 // en x15 guardo x1
  mov x0, x20 // Debo volver a poner la direccion inicial del framebuffer en x0

// x12 sera la posicion en pixeles del Y axis
// x11 sera la posicion en pixeles del X axis

// x5 sera la posicion del framebuffer en la cual quiero empezar a pintar
// es decir (x11, x12) en bits

  mov x26, 2560 // 2560 (640x4) son todos los bits que caben en el ancho de una linea
  //  mov x12, 4 // Cantidad de bits por pixel, necesario para que x3 y x4 compartan las mismas medidas (y que no ocurran bugs por bits que no sean potencia de 4)

// En que linea quiero empezar
 // mov x12, x13  // Lugar en Y axis (El ejemplo es para la mitad.. 240-50) 
 // mov x11, x14 // Lugar en X axis (El ejemplo es para la mitad.. 320-50) 


  mul x3, x12, x26 // Convierto a bits la posicion de x11 con x11*2560 ... x3 = (0, x11)
  lsl x11, x11, 2 // Convierto x11 a bits (x11 * 4)
                // Cantidad de bits por pixel, necesario para que x11 y x12 compartan las mismas medidas (y que no ocurran bugs por bits que no sean potencia de 4)
  add x3, x3, x11 // x3 = (x11, x12)
  add x0, x20, x3 // x0 = posicion inicial del framebuffer + posicion donde quiero mi rectangulo
  
loop3:
	mov x1, x15 // X Size
loop2:
	stur w10,[x0]  // Colorear el pixel N
	add x0,x0, 4   // Siguiente pixel   Esto pint la pantalla bit por bit
	sub x1,x1,1    // Decrementar contador X    
	cbnz x1,loop2  // Si no terminó la fila, salto
	sub x2,x2,1    // Decrementar contador Y

  add x12, x12, 1 // Termine la linea => x3+1
  mul x3, x12, x26 // Multiplico nuevamente por la cantidad de bits que hay en 640pix y lo guardo x3
  add x3, x3, x11 // ahora le agrego la cantidad de pixeles para posicionarme horizontalmente
  add x0, x20, x3 // Con esto me posiciono debajo del primer pixel que pinte en la anterior iteracion

	cbnz x2,loop3  // Si no es la última fila, salto
  ldur x15, [sp,24]
  ldur x3, [sp,16]
  ldur x10, [sp, 8]
  ldur x26, [sp, 0]
  BR LR  
  // END RECTANGLE









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
