;
; AssemblerApplication1.asm
;
; Created: 02.04.2020 13:06:16
; Author : Oleh
;


.include "m2560def.inc"

.def     WR1 = r16    ; the working registers
.def     WR2 = r17
.def     WR3 = r18
.def _countL = r23
.def _countK = r24
.def _temp = r25
.def _temp2 = r19
.def _flag = r20
.def _flag2 = r21
.def _flag3 = r22

.def     T1 = r13  
.def     T2 = r14
.def     T3 = r15

.macro mOut
    .if @0 > (0x3f)
      sts   @0,   @1
    .else
      out   @0,   @1
    .endif
  .endmacro

  .macro mIn
    .if @1 > (0x3f)
      lds   @0,   @1
    .else
      in    @0,   @1
    .endif
  .endmacro


.cseg
.org  $0000
    rjmp    Start

.org $005E         ; The address of the Timer5A compare match interrupt
    jmp     Timer5comp
    nop

.org INT_VECTORS_SIZE

Start:
    clr     T1 
    clr     T2
    clr     T3

	ldi		_flag2, 0b10000000
	ldi		_temp, 0x00

    ldi     WR1, (1<<WGM52)|(1<<CS50)  ; Timer in CTC mode
    sts     TCCR5B, WR1

    ldi     WR1, HIGH(1171) 
    ldi     WR2, LOW(1171)   
    sts     OCR5AH, WR1    
    sts     OCR5AL, WR2       

    ldi     WR1, 1 << OCIE5A  ; Enable Output Compare A match interrupt
    sts     TIMSK5, WR1

    ; I/O settings
    ldi     WR1, 0x00
	ldi		WR2, 0xFF               
    mOut     DDRL, WR2
    mOut     PORTL, WR1
	mOut     DDRK, WR2
    mOut     PORTK, WR1
	mOut     DDRC, WR2
    mOut     PORTC, WR1

	ldi		WR1, 0x00
	ldi		WR2, 0xFF
	mOut		DDRA, WR1
	mOut		PORTA, WR2

    ; Enable interrupts
    sei

firstbuttonFree:
	ldi     WR1, 0 << OCIE5A  
    sts     TIMSK5, WR1
	sbic PINA, 5
	rjmp firstbuttonFree
	rjmp firstButtonBusy

secondbuttonFree:
	ldi     WR1, 0 << OCIE5A  
    sts     TIMSK5, WR1
	sbic PINA, 7
	rjmp secondbuttonFree
	rjmp secondButtonBusy

firstButtonBusy:
	ldi     WR1, 1 << OCIE5A  
    sts     TIMSK5, WR1
	ldi		_temp, 0xFF
	ldi		_countL, 0b10000000
    ser    WR2
    mOut    PORTC, WR2
	rjmp mitka

secondButtonBusy:
	ldi     WR1, 1 << OCIE5A  
    sts     TIMSK5, WR1
	ldi _temp2, 0xFF
	ldi		_flag2, 0b10000000
	ser    WR2
    mOut    PORTC, WR2
	rjmp mitka2

main:
    cli                    ; Reset the ms counter
    clr    T1
    clr    T2
    clr    T3
    sei

	ldi		WR2, 0x00
	mOut    PORTC, WR2
	mIn _flag, PINA
	sbrc _flag, 5
	sbrs _temp, 0
	rjmp firstbuttonFree
mitka:
	mOut PORTL, _countL
	lsr _countL

	mIn _flag3, PINA
	sbrc _flag3, 7
	sbrs _temp2, 0
	rjmp secondButtonFree
mitka2:
	sbrc _flag2, 7
	ldi _countK, 0b10000000
	sbrc _flag2, 6
	ldi _countK, 0b00000001
	sbrc _flag2, 5
	ldi _countK, 0b01000000
	sbrc _flag2, 4
	ldi _countK, 0b00000010
	sbrc _flag2, 3
	ldi _countK, 0b00100000
	sbrc _flag2, 2
	ldi _countK, 0b00000100
	sbrc _flag2, 1
	ldi _countK, 0b00010000
	sbrc _flag2, 0
	ldi _countK, 0b00001000
	
	mOut PORTK, _countK
	ldi	_countK, 0x00
	lsr _flag2

    ldi    WR1, BYTE1(1000)
    ldi    WR2, BYTE2(1000)
    ldi    WR3, BYTE3(1000) 

Wait:
    cli
    cp     T1, WR1
    cpc    T2, WR2
    cpc    T3, WR3
    sei

    brlo   Wait

    rjmp   main

Timer5comp:
    ; Save the current state on the stack
    push    WR1
    in      WR1, SREG
    push    WR1

    inc     T1          ; Increment the ms counter
     brne    Timer5compEnd
    inc     T2
     brne    Timer5compEnd
    inc     T3

Timer5compEnd:
    ; Reset the state
    pop     WR1
    out     SREG, WR1
    pop     WR1

    reti