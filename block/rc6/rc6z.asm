; Listing generated by Microsoft (R) Optimizing Compiler Version 16.00.40219.01 

	TITLE	C:\hub\rc6\rc6z.c
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	_xrc6_crypt
; Function compile flags: /Ogspy
; File c:\hub\rc6\rc6z.c
;	COMDAT _xrc6_crypt
_TEXT	SEGMENT
_S$ = -104						; size = 176
_L$ = 72						; size = 32
_D$ = 104						; size = 4
tv248 = 108						; size = 4
_C$ = 120						; size = 4
_key$ = 120						; size = 4
_data$ = 124						; size = 4
_xrc6_crypt PROC					; COMDAT

; 33   : {

	push	ebp
	lea	ebp, DWORD PTR [esp-112]
	sub	esp, 216				; 000000d8H
	push	ebx
	push	esi

; 34   :     w128_t  *x;
; 35   :     uint32_t A, B, C, D, T0, T1, i;
; 36   :     uint32_t S[RC6_KR], L[8];
; 37   :     uint32_t *k;
; 38   :     
; 39   :     x =(w128_t*)data;
; 40   :     k =(uint32_t*)S;
; 41   :     
; 42   :     // initialize L with 256-bit key
; 43   :     memcpy(&L, key, 32);

	mov	esi, DWORD PTR _key$[ebp]
	push	edi
	push	8
	pop	ecx
	lea	edi, DWORD PTR _L$[ebp]
	rep movsd

; 44   : 
; 45   :     // initialize S with constants
; 46   :     for (A=RC6_P, i=0; i<RC6_KR; i++) {

	mov	ecx, -1209970333			; b7e15163H
	xor	eax, eax
$LL9@xrc6_crypt:

; 47   :       S[i] = A;

	mov	DWORD PTR _S$[ebp+eax*4], ecx

; 48   :       A += RC6_Q;

	sub	ecx, 1640531527				; 61c88647H
	inc	eax
	cmp	eax, 44					; 0000002cH
	jb	SHORT $LL9@xrc6_crypt

; 49   :     }
; 50   :     
; 51   :     // mix with key
; 52   :     for (A=0,B=0,i=0; i<RC6_KR*3; i++) {

	xor	esi, esi
	xor	edi, edi
	xor	ebx, ebx
$LL6@xrc6_crypt:

; 53   :       A = S[i%RC6_KR] = ROTL32(S[i%RC6_KR] + A+B, 3);  

	xor	edx, edx
	push	44					; 0000002cH
	mov	eax, ebx
	pop	ecx
	div	ecx
	lea	ecx, DWORD PTR _S$[ebp+edx*4]
	mov	eax, DWORD PTR [ecx]
	add	eax, edi
	add	eax, esi
	rol	eax, 3
	mov	DWORD PTR [ecx], eax
	mov	esi, eax

; 54   :       B = L[i&7] = ROTL32(L[i&7] + A+B, A+B);

	mov	eax, ebx
	and	eax, 7
	lea	edx, DWORD PTR _L$[ebp+eax*4]
	lea	eax, DWORD PTR [edi+esi]
	add	eax, DWORD PTR [edx]
	lea	ecx, DWORD PTR [edi+esi]
	rol	eax, cl
	inc	ebx
	mov	DWORD PTR [edx], eax
	mov	edi, eax
	cmp	ebx, 132				; 00000084H
	jb	SHORT $LL6@xrc6_crypt

; 55   :     }
; 56   :     
; 57   :     // load plaintext
; 58   :     A=x->w[0]; B=x->w[1];

	mov	eax, DWORD PTR _data$[ebp]

; 59   :     C=x->w[2]; D=x->w[3];
; 60   :     
; 61   :     B += *k; k++; D += *k; k++;

	mov	edi, DWORD PTR [eax+4]
	mov	ebx, DWORD PTR [eax+12]
	add	edi, DWORD PTR _S$[ebp]
	add	ebx, DWORD PTR _S$[ebp+4]
	mov	edx, DWORD PTR [eax+8]
	mov	ecx, DWORD PTR [eax]
	mov	DWORD PTR _C$[ebp], edx
	mov	DWORD PTR _D$[ebp], ebx
	lea	esi, DWORD PTR _S$[ebp+8]
	mov	DWORD PTR tv248[ebp], 20		; 00000014H
$LL3@xrc6_crypt:

; 62   :     
; 63   :     for (i=0; i<RC6_ROUNDS; i++) {
; 64   :       T0 = ROTL32(B * (2 * B + 1), 5);

	lea	edx, DWORD PTR [edi+edi+1]
	imul	edx, edi

; 65   :       T1 = ROTL32(D * (2 * D + 1), 5);

	lea	eax, DWORD PTR [ebx+ebx+1]
	imul	eax, ebx
	rol	edx, 5
	rol	eax, 5

; 66   :       
; 67   :       A = ROTL32(A ^ T0, T1) + *k; k++;

	mov	ebx, edx
	xor	ebx, ecx
	mov	ecx, eax

; 68   :       C = ROTL32(C ^ T1, T0) + *k; k++;

	xor	eax, DWORD PTR _C$[ebp]
	rol	ebx, cl
	mov	ecx, edx
	add	ebx, DWORD PTR [esi]
	rol	eax, cl

; 69   :       // rotate 32-bits to the left
; 70   :       T0 = A;
; 71   :       A  = B; B  = C;

	mov	ecx, edi
	add	esi, 8
	add	eax, DWORD PTR [esi-4]
	dec	DWORD PTR tv248[ebp]
	mov	edi, eax

; 72   :       C  = D; D  = T0;

	mov	eax, DWORD PTR _D$[ebp]
	mov	DWORD PTR _C$[ebp], eax
	mov	DWORD PTR _D$[ebp], ebx
	jne	SHORT $LL3@xrc6_crypt

; 73   :     }
; 74   :     
; 75   :     A += *k; k++; C += *k; k++;
; 76   : 
; 77   :     // save ciphertext
; 78   :     x->w[0]=A; x->w[1]=B;

	mov	eax, DWORD PTR _data$[ebp]
	mov	edx, DWORD PTR [esi]
	add	edx, ecx
	mov	ecx, DWORD PTR [esi+4]
	add	ecx, DWORD PTR _C$[ebp]
	mov	DWORD PTR [eax+4], edi
	pop	edi
	pop	esi

; 79   :     x->w[2]=C; x->w[3]=D;

	mov	DWORD PTR [eax+12], ebx
	mov	DWORD PTR [eax], edx
	mov	DWORD PTR [eax+8], ecx
	pop	ebx

; 80   : }

	add	ebp, 112				; 00000070H
	leave
	ret	0
_xrc6_crypt ENDP
_TEXT	ENDS
END
