;-------------------------------------------------------------------
;	init: macro that gets the pixel delay times
;-------------------------------------------------------------------

%macro init 0

	push eax	; prevents stack errors later on
	xor eax,eax

%%begin:
	rdtsc
	mov ecx,eax
	push ecx	; save current # of cpu cycles elapsed on stack

	in al,378h	; input 1 byte from parallel port to al

	cmp 0h,al	; if there was no input from PP (error),
	je %%zero		; then start over

	cmp 88h,al	; 88h is the black/white threshold here
	jg %%black
	jng %%white

%%white:
		in al,378h
		cmp 0h,al
		je %%white	; if no value, do over
		cmp %1,1
		je %%white
			cmp 88h,al	; 88h is threshold of black/white
			jg %%begin
			jmp %%fin
		%%w:
			cmp 88h,al	; 88h is threshold of black/white
			jng %%white
	%%fin:

	rdtsc		; get current time (in ecx)
	mov ecx,eax
	pop ebx		; get previous time
	sub ecx,ebx	; get time between the 2 pixels
	add ecx,15h ; 15h is the threshold between pix/href/vref
	cmp pix,ecx
	jg %%pixel
	jle %%begin

%%black:
	in al,378h
		cmp 0h,al
		je %%whi	; if no value, do over
		cmp %1,1
		je %%whi
			cmp 88h,al	; 88h is threshold of black/white
			jg %%begin
			jmp %%f
		%%whi:
			cmp 88h,al	; 88h is threshold of black/white
			jng %%black
	%%f:
	rdtsc		; get current time (in ecx)
	mov ecx,eax
	pop ebx		; get previous time
	sub ecx,ebx	; get time between the 2 pixels
	add ecx,15h 	; is the threshold between pix/href/vref
	cmp pix,ecx
	jg %%pixel
	jle %%begin

%%zero:
	xor al,al	; zero out al
	call init	; start over

%%delay:
	in al,378h
		cmp 0h,al
		je %%wi	; if no value, do over
		cmp %1,1
		je %%wi
			cmp 88h,al	; 88h is threshold of black/white
			jg %%begin
			jmp %%f
		%%wi:
			cmp 88h,al	; 88h is threshold of black/white
			jng %%black
	%%fi:
	push eax
	rdtsc
	mov ecx,eax
	pop eax
	sub ecx,eax	; find time between the two times

	cmp ecx,pix	; find if any of the times aren't already taken
	jne %%begin	; if they all are, we're done
	cmp ecx,href	; else, start over to find the next one
	jne %%begin
	cmp ecx,vref
	jne %%begin

%%finish:
	pop eax		; prevents errors from beginning

%endmacro

;-------------------------------------------------------------------
;	pause: macro that pauses execution X number of CPU cycles
;-------------------------------------------------------------------

%macro pause 1

	push cx
	xor cx,cx	; zero out dh (dh is a counter)
	mov cx,%1

%%for:			; uses ~10 cycles
	nop
	loop %%for

	pop cx

%endmacro
;-------------------------------------------------------------------
;	calibrate: macro that waits until correct pixel is being
;		   drawn
;-------------------------------------------------------------------

;%macro calibrate 1

;%%begin:
;	in al,378h
;	cmp 0h,al
;	je %%begin	; if no value, do over
;	cmp %1,1
;	je %%white
;	%%black:
;		cmp 88h,al	; 88h is threshold of black/white
;		jg %%begin
;		jmp %%fin
;	%%white:
;		cmp 88h,al	; 88h is threshold of black/white
;		jng %%begin
;	%%fin:
;
;%endmacro

;-------------------------------------------------------------------
;	putpixel: macro that draws pixel of x,y,color
;-------------------------------------------------------------------

%macro putpixel 3
	push al

	mov al,320
	mul al,%2
	add al,%1
	mov es:di,al	;these 2 lines I'm not so sure about
	mov [es:di],%3

	pop al

%endmacro

[SECTION .data]

pix		db	2	; declare delay time variables
hrev	db	2
vref	db	2