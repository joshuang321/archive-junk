SECTION .text
	GLOBAL	x87__sine
	GLOBAL	x87__cosine
	GLOBAL	x87__tangent
	GLOBAL	x87__cosecant
	GLOBAL	x87__secant
	GLOBAL	x87__cotangent
	GLOBAL	x87__arcsine
	GLOBAL	x87__arccosine
	GLOBAL	x87__arctangent
	GLOBAL	x87__arccotangent
	GLOBAL	x87__arcsecant
	GLOBAL	x87__arccosecant
	GLOBAL	x87__exponent
	GLOBAL	x87__10_exponent
	GLOBAL	x87__nat_exponent
	GLOBAL	x87__log
	GLOBAL	x87__10_log
	GLOBAL	x87__nat_log
	GLOBAL	x87__modf
	GLOBAL	x87__sqrt
	GLOBAL	x87__fabs
	GLOBAL	x87__floor
	GLOBAL	x87__ceil
	GLOBAL	x87__fmod
	GLOBAL	x87__sgn

x87__sine:
	FLD		QWORD[rbp -0x8]
	FSIN
	FSTP		QWORD[rbp -0x8]
	RET

x87__cosine:
	FLD		QWORD[rbp -0x8]
	FCOS
	FSTP		QWORD[rbp -0x8]
	RET

x87__tangent:
	FLD		QWORD[rbp -0x8]
	FPTAN
	FFREE		ST0
	FINCSTP
	FSTP		QWORD[rbp -0x8]
	RET

x87__cosecant:
	FLD1
	FLD		QWORD[rbp -0x8]
	FSIN
	FDIVP
	FSTP		QWORD[rbp -0x8]
	RET

x87__secant:
	FLD1
	FLD		QWORD[rbp -0x8]
	FCOS
	FDIVP
	FSTP		QWORD[rbp -0x8]
	RET
	
x87__cotangent:
	FLD		QWORD[rbp -0x8]
	FPTAN
	FDIVP		ST1, ST0	
	FSTP		QWORD[rbp -0x8]
	RET
	
x87__arcsine:
	FLD		QWORD[rbp -0x8]
	FLD1
	FLD		ST1
	FMUL		ST0, ST0
	FSUBP
	FSQRT
	FPATAN
	FSTP		QWORD[rbp -0x8]
	RET
	
x87__arccosine:
	FLD1
	FLD		QWORD[rbp -0x8]
	FMUL		ST0, ST0
	FSUBP
	FSQRT
	FLD		QWORD[rbp -0x8]
	FPATAN
	FSTP		QWORD[rbp -0x8]
	RET
	
x87__arctangent:
	FLD		QWORD[rbp -0x8]
	FLD1
	FPATAN
	FSTP		QWORD[rbp -0x8]
	RET
	
x87__arccotangent:
	FLD1
	FLD		QWORD[rbp -0x8]
	FPATAN
	FSTP		QWORD[rbp -0x8]
	RET
	
x87__arcsecant:
	FLD		QWORD[rbp -0x8]
	FTST
	FMULP		ST0
	FLD1
	FSUBP
	FSQRT
	CALL		x87__sgn
	FPATAN
	FSTP		QWORD[rbp -0x8]
	RET
	
x87__arccosecant:
	CALL		x87__sgn
	FLD		ST0
	FMUL		ST0, ST0
	FLD1
	FSUBP
	FSQRT
	FPATAN
	FSTP		QWORD[rbp -0x8]
	RET
	
x87__exponent:
	FLD		QWORD[rbp -0x8]
	FLD		QWORD[rbp -0x10]
	FYL2X
	CALL 		_x87__com_exponent
	FSTP		QWORD[rbp -0x10]
	RET

x87__10_exponent:
	FLD		QWORD[rbp -0x8]
	FLDL2T
	FMULP
	CALL		_x87__com_exponent
	FSTP		QWORD[rbp -0x8]
	RET

x87__nat_exponent:
	FLD		QWORD[rbp -0x8]
	FLDL2E
	FMULP
	CALL		_x87__com_exponent
	FSTP		QWORD[rbp -0x8]
	RET
	
_x87__com_exponent:
	FLD		ST0
	FNSTCW		WORD[rbp -0xA]
	MOV		ax, WORD[rbp -0xA]
	OR		WORD[rbp -0xA], 0x0C00
	FLDCW		WORD[rbp -0xA]
	FRNDINT
	MOV		WORD[rbp -0xA], ax
	FLDCW		WORD[rbp -0xA]
	FSUB		ST1, ST0
	FISTP		QWORD[rbp -0x8]
	MOV		rax, QWORD[rbp -0x8]
	ADD		rax, 0x3FF
	SHL		rax, 0x34
	MOV		QWORD[rbp -0x8], rax
	F2XM1
	FLD1
	FADDP
	FLD		QWORD[rbp -0x8]
	FMULP
	RET
	
x87__log:
	FLD1
	FLD		QWORD[rbp -0x8]
	FYL2X
	FLD1
	FLD		QWORD[rbp -0x10]
	FYL2X
	FDIVP
	FSTP		QWORD[rbp -0x10]
	RET

x87__10_log:
	FLDLG2
	FLD		QWORD[rbp -0x8]
	FYL2X
	FSTP		QWORD[rbp -0x8]
	RET
	
x87__nat_log:
	FLDLN2
	FLD		QWORD[rbp -0x8]
	FYL2X
	FSTP		QWORD[rbp -0x8]
	RET
	
x87__modf:
	FLD		QWORD[rbp -0x8]
	FLD		ST0
	FNSTCW		WORD[rbp -0xA]
	MOV		ax, WORD[rbp -0xA]
	OR		WORD[rbp -0xA], 0x0C00
	FLDCW		WORD[rbp -0xA]
	FRNDINT
	MOV		WORD[rbp -0xA], ax
	FLDCW		WORD[rbp -0xA]
	FSUBP
	FSTP		QWORD[rbp-0x8]
	RET
	
x87__sqrt:
	FLD		QWORD[rbp -0x8]
	FSQRT
	FSTP		QWORD[rbp -0x8]
	RET
	
x87__fabs:
	FLD		QWORD[rbp -0x8]
	FABS
	FSTP		QWORD[rbp -0x8]
	RET

x87__floor:
	FLD		QWORD[rbp -0x8]
	FNSTCW		WORD[rbp -0xA]
	MOV		ax, WORD[rbp -0xA]
	OR		WORD[rbp -0xA], 0x0400
	FLDCW		WORD[rbp -0xA]
	FRNDINT
	MOV		WORD[rbp -0xA], ax
	FLDCW		WORD[rbp -0xA]
	FSTP		QWORD[rbp -0x8]
	RET
	
x87__ceil:
	FLD		QWORD[rbp -0x8]
	FNSTCW		WORD[rbp -0xA]
	MOV		ax, WORD[rbp -0xA]
	OR		WORD[rbp -0xA], 0x0800
	FNCLEX
	FLDCW		WORD[rbp -0xA]
	FRNDINT
	MOV		WORD[rbp -0xA], ax
	FLDCW		WORD[rbp -0xA]
	FSTP		QWORD[rbp -0x8]
	RET
	
x87__fmod:
	FLD		QWORD[rbp -0x8]
	FLD		QWORD[rbp -0x10]
	FPREM
	FSTP		QWORD[rbp -0x10]
	FFREE		ST0
	FINCSTP
	RET

x87__sgn:
	FSTSW		ax
	SAHF
	FLD1
	FLDZ
	FLD1
	FCHS
	FINCSTP
	FINCSTP
	FCMOVB		ST0, ST6		;CF=1
	FCMOVE		ST0, ST7		;ZF=1
	FFREE		ST7
	FFREE		ST6
	FSTP		QWORD[rbp -0x8]
	RET
