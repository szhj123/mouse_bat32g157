void ISPJMP(void);



void ISPJMP(void)
{
#pragma asm
	CLR IE.7
	MOV B, #0A5H 
	MOV A, #5AH
	LJMP		0xfF00
#pragma endasm	
}
