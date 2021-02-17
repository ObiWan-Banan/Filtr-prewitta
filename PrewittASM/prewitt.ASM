;Filtr Prewitta z histogramem
;Rafa³ Œwiderski
;Rok akademicki 2020/2021
;wersja 1.0
;historia:
; wersja 0.1 : Szkielet zagnie¿d¿onych pêtli oraz œci¹ganie zmiennej ze stosu.
; wersja 0.2 : Wyliczanie adresu pikseli w inner_X_sum_loop + ify dla pikseli na rogach obrazka.
; wersja 0.25: Tworzenie wektora z elementów tablicy kernel.
; wersja 0.3 : Mno¿enie wektorów z wartoœciami piksela z wektorem elementów tablicy kernel oraz dodawanie ich do wektora wynikowego (xmm2).
; wersja 0.4 : Naprawienie wektora elementów tablic kernel i kernely.
; wersja 0.5 : Od teraz elementy w rejestrach xmm przechowywane s¹ jako float(poprzednio int), 
; optymalizacja pamiêciowa zmiennych (poprzednio np. tablica kernel by³a typu SDWORD, od teraz jest typu SBYTE.
; wersja 0.55: Obliczanie poprawnego wyniku dzia³ania algorytmu, który umieszczany jest w rejestrze xmm6 (wektor 3 elementowy z wartoœciami RGB).
; wersja 0.7 : Wyci¹ganie wartoœci nowego piksela z rejestru xmm oraz implementacji ifów sprawdzaj¹cych zakres nowych wartoœci RGB.
; wersja 0.9 : Procedura poprawnie dzia³a na jednym w¹tku, ale wysypuje siê przy próbie odpalenia na wiêcej ni¿ jednym.
; wersja 1.0 : Procedura poprawnie dzia³a na wielu w¹tkach.
.data
kernel SBYTE -1,0,1
       SBYTE -1,0,1
       SBYTE -1,0,1
kernely SBYTE 1,1,1
       SBYTE 0,0,0
       SBYTE -1,-1,-1
.code

;Procedura stosuje na podanej tablicy pikselów bitmapy filtr Prewitta.
;Nie sprawdza parametrów wejœciowych.
;@param char*: WskaŸnik na tablice pikseli, tablica ta nie mo¿e zawieraæ paddingu.
;@param char*: WskaŸnik na wynikow¹ tablice pikseli : char* , buffor do zapisu wyniku. W wyniku dzia³ania procedury wartoœci w tej tablicy ulegaj¹ zmianie.
; Wielkoœæ tablicy wynikowej musi byæ taka sama jak wielkoœæ tablicy pikseli.
;@param int  : Szerokoœæ bitmapy: int, szerokoœæ bitmapy w pikselach. UWAGA: Do procedury nale¿y podaæ szerokoœæ bitmapy pomniejszon¹ o 2 piksele.
;@param int  : Kolumna startowa: int, kolumna bitmapy od której procedura zacznie. W przypadku dzia³ania na 1 w¹tku podaæ 0,
;w przypadku dzia³ania na 2 podaæ po³owe wysokoœci bitmapy w pikselach itd.
;@param int  : Kolumna koñcowa: int, kolumna bitmapy na której algorytm skoñczy. W przypadku dzia³ania na 1 w¹tku podaæ wysokoœæ bitmapy w pikselach,
;w przypadku dzia³ania na 2 podaæ po³owe wysokoœci bitmapy w pikselach itd. Ostatni w¹tek (lub pierwszy jeœli procedura ma dzia³aæ tylko na jednym w¹tku) musi mieæ przekazany
;ten parametr pomniejszony o 2.
;@warning modyfikowane rejestry: RCX,RBX,RBP,RSI,R8,R9,R10,R11,R12,R13,R14,R15,XMM0,XMM1,XMM2,XMM3,XMM4,XMM5,XMM6
prewittFilter proc
; rcx - pointer to inputArray
; rdx - pointer to outputArray, przenoszony do r14 na pocz¹tku procedury
; rbp licznik wewnêtrznej pêtli
; r8 - bitmap width
; r9 - start height / i
; r10 - stop height / j
; xmm2 - wektor sumXb,sumXg,sumXr
; xmm4 - wektor sumYb, sumYg,sumYr
; xmm6 - wektor SUMb,SUMg,SUMr
    push rbp ; zapisywanie adresów rejestrów RBP,RBX, RDI,RSP, w celu zachowania spójnoœci pamiêci po wykonaniu procedury
    push rbx
    push rdi
    push rsp
    mov r15,[rsp+72] ; stop height do r15, 8* number_saved_reg(w tym przypadku 8*9)
    mov r14,rcx ;r14 - pointer to inputArray
    mov rbx,rdx ; rbx - pointer to outputArray  
    mov rdi,r9 ; start height do rdi

  ;zerowanie rejestrów-------------------------------------------------------
    xor rcx,rcx
    xor r11,r11 
    xor r12,r12
    xor r13,r13
   ;-------------------------------------------------------------------------
    mov ecx, edi ; Ustawianie licznika pêtlie (rejestru ecx). W edi znajduje siê zmienna start_height
    push r15
    outerLoop:
    pop r15
    cmp ecx,r15d ; Sprawdzanie warunka koñcz¹cego pêtle.
    push r15
    je done

    mov ebp,0
    innerLoop:
    cmp ecx,0 ; if(y==0) sumB,sumG,sumR = 0
    je skipX
    
    pop r15
    mov eax,r15d
    inc eax
    push r15
    cmp ecx,eax  ; if(y>=stop_height-1) sumB,sumG,sumR = 0 => skok do etykiety skipX
    jge skipX

    cmp ebp,0 ;if(x==0) sumB,sumG,sumR = 0 => skok do etykiety skipX
    je skipX

    mov eax, r8d
    dec eax
    cmp ebp,eax ; if(x>=width-1) sumB,sumG,sumR = 0 => skok do etykiety skipX
    jge skipX

  
    mov r9d,0
    outer_X_sum_loop:
    mov r10d,0

    inner_X_sum_loop:
    ; wyliczanie adresu piksela B [3 * (X + I + (Y + J) * width)]------------
    xor rax, rax
    xor r15,r15
    add eax,ecx
    add r15d,r10d
    dec r15d
    add eax,r15d
    mov r15d,r8d
    add r15d,2
    mul r15d
    add eax,ebp
    xor r15,r15
    mov r15d,r9d
    dec r15d
    add eax,r15d
    xor r15,r15
    mov r15b,3
    movzx r15d,r15b
    mul r15d
    mov r11b, [r14+rax] ;przeniesienie wartoœci piksela B do rejestru r11b , inputArray[3 * (X + I + (Y + J) * width)]
    ;-----------------------------------------------------------------------
    inc rax  ; inkrementacja rax, aby dostaæ adres piksela G 
    mov r12b,[r14+rax] ; przeniesienie wartoœci piksela B do rejestru r12b , inputArray[3 * (X + I + (Y + J) * width) + 1]
    ;-----------------------------------------------------------------------
    inc rax ; inkrementacja rax po raz drugi, aby dostaæ adres piksela R
    mov r13b,[r14+rax] ; przeniesienie wartoœci piksela R do rejestru r13b , inputArray[3 * (X + I + (Y + J) * width) + 2]
    ;-----------------------------------------------------------------------
    ; Umieszczanie wartoœci pikseli B, G i R w rejestrze xmm0---------------
    movzx r11d,r11b
    cvtsi2ss xmm0,r11d
    pshufd xmm0,xmm0,207 ; 207 - maska bitowa 11001111b
    movzx r12d,r12b
    cvtsi2ss xmm0,r12d
    pshufd xmm0,xmm0,227 ; 227 - maska bitowa 11100011b
    movzx r13d,r13b
    cvtsi2ss xmm0,r13d
    movaps xmm3,xmm0 ; tworzenie kopii wektora xmm0, aby wykorzystaæ j¹ do liczenia sum dla Y
    ;-----------------------------------------------------------------------
    ; Tworzenie wektora elementów z tablicy kernel--------------------------
    lea rsi,[kernel] ;pobranie adresu tablicy kernel do rsi
    xor r15,r15
    mov eax,r9d
    mov r15b,3
    movzx r15d,r15b
    mul r15d
    add eax,r10d
    xor r15,r15
    mov r15b,[rsi+rax]
    movsx r15d,r15b
    cvtsi2ss xmm1,r15d
    pshufd xmm1,xmm1,192 ; 192 - maska bitowa 11000000b
    ;-----------------------------------------------------------------------
    ; Mno¿enie inputArray[3 * (X + I + (Y + J) * width)] * kernel[I + 1][J + 1], czyli elementy wektora z rejestru xmm0 * elementy xmm1,
    ; a potem dodanie dodanie wyniku operacji do wektora z rejestru xmm2
    mulps xmm0,xmm1
    addps xmm2,xmm0
    ;-----------------------------------------------------------------------
    ; w rezultacie efekt mo¿na opisaæ za pomoc¹ kodu c++ nastêpuj¹co:
    ;sumXb += inputArray[3 * (X + I + (Y + J) * width)] * kernel[I + 1][J + 1];
	;sumXg += inputArray[3 * (X + I + (Y + J) * width) + 1] * kernel[I + 1][J + 1];
	;sumXr += inputArray[3 * (X + I + (Y + J) * width) + 2] * kernel[I + 1][J + 1];
    ;-----------------------------------------------------------------------
    ; Tworzenie wektora elementów z tablicy kernely-------------------------
    lea rsi,[kernely] ;pobranie adresu tablicy kernely do rsi
    xor r15,r15
    mov eax,r9d
    mov r15b,3
    movzx r15d,r15b
    mul r15d
    add eax,r10d
    xor r15,r15
    mov r15b,[rsi+rax]
    movsx r15d,r15b
    cvtsi2ss xmm1,r15d
    pshufd xmm1,xmm1,192 ; 192 - maska bitowa 11000000b
    ;-----------------------------------------------------------------------
    ; Mno¿enie inputArray[3 * (X + I + (Y + J) * width)] * kernely[I + 1][J + 1], czyli elementy wektora z rejestru xmm3 * elementy xmm1,
    ; a potem dodanie dodanie wyniku operacji do wektora z rejestru xmm4
    mulps xmm3,xmm1
    addps xmm4,xmm3
    ;-----------------------------------------------------------------------
    ; w rezultacie efekt mo¿na opisaæ za pomoc¹ kodu c++ nastêpuj¹co:
    ;sumYb += inputArray[3 * (X + I + (Y + J) * width)] * kernely[I + 1][J + 1];
	;sumYg += inputArray[3 * (X + I + (Y + J) * width) + 1] * kernely[I + 1][J + 1];
	;sumYr += inputArray[3 * (X + I + (Y + J) * width) + 2] * kernely[I + 1][J + 1];
    ;-----------------------------------------------------------------------

    cmp r10d,2
    jge inner_X_sum_done
    inc r10d
    jmp inner_X_sum_loop

    inner_X_sum_done:
    cmp r9d,2
    jge outer_X_sum_done
    inc r9d
    jmp outer_X_sum_loop
    
    outer_X_sum_done:
    ; Obliczanie wyniku koñcowego-------------------------------------------
    mulps xmm2,xmm2 ; podnoszenie elementów wektora do potêgi 2
    mulps xmm4,xmm4 ; podnoszenie elementów wektora do potêgi 2
    movaps xmm6,xmm2 ; przeniesienie jednego z wektorów do rejestru xmm6(rejestr wynikowy)
    addps xmm6,xmm4
    sqrtps xmm6,xmm6
    ;-----------------------------------------------------------------------
    ; W rezultacie w rejestrze xmm6 znajduje siê wektor elementów SUMb,SUMg i SUMr. Dzia³ania powy¿ej mo¿na opisaæ za pomoc¹ kodu c++:
    ;SUMb = sqrt((sumXb * sumXb) + (sumYb * sumYb));
	;SUMg = sqrt((sumXg * sumXg) + (sumYg * sumYg));
	;SUMr = sqrt((sumXr * sumXr) + (sumYr * sumYr));
    ;-----------------------------------------------------------------------
    ; Wyci¹ganie wartoœci nowych pikseli z rejestru xmm6. Wartoœæ R l¹duje w r11d, wartoœæ G w r12d, a B w r13d
    movaps xmm5,xmm6
    cvtss2si r11d,xmm5
    pshufd xmm5,xmm5,237 ; sum g od teraz na 1 pozycji
    cvtss2si r12d,xmm5
    pshufd xmm5,xmm5,254 ; sum b na 1 pozycji
    cvtss2si r13d,xmm5
    ;-----------------------------------------------------------------------
    ; Sprawdzanie czy nowa wartoœæ pikseli mieœci siê w granicy 0-255. Dodatkowo jak nowa wartoœæ jest <20 to ustawianie jej na 0.
    ; Ca³y poni¿szy kod mo¿na w c++ zapisaæ jako:
    ;if (SUMb > 255) SUMb = 255;
	;if (SUMg > 255) SUMg = 255;
	;if (SUMr > 255) SUMr = 255;
	;if (SUMb < 20) SUMb = 0;
	;if (SUMg < 20) SUMg = 0;
	;if (SUMr < 20) SUMr = 0;
    cmp r13d,255 ; if (SUMb > 255) SUMb=255
    jg set_SUMb255

    if_SUMgGreaterThan255:
    cmp r12d,255 ; if (SUMb > 255) SUMg=255
    jg set_SUMg255

    if_SUMrGreaterThan255:
    cmp r11d,255 ;if (SUMr > 255) SUMr = 255;
    jg set_SUMr255

    if_SUMbLesserThan20:
    cmp r13d,20 ;if (SUMb < 20) SUMb = 0;
    jl set_SUMb0

    if_SUMgLesserThan20:
    cmp r12d,20 ;if (SUMg < 20) SUMg = 0;
    jl set_SUMg0

    if_SUMrLesserThan20:
    cmp r11d,20 ;if (SUMr < 20) SUMr = 0;
    jl set_SUMr0

    jmp noSUM_set ; Je¿eli wartoœci by³y w granicach skok do noSUM_set

    ; Etykiety set_SUM ustawiaj¹ wartoœci RGB piksela na 0 lub 255
    set_SUMb255:
    mov r13d,255
    jmp if_SUMgGreaterThan255

    set_SUMg255:
    mov r12d,255
    jmp if_SUMrGreaterThan255

    set_SUMr255:
    mov r11d,255
    jmp if_SUMbLesserThan20

    set_SUMb0:
    mov r13d,0
    jmp if_SUMgLesserThan20

    set_SUMg0:
    mov r12d,0
    jmp if_SUMrLesserThan20

    set_SUMr0:
    mov r11d,0
    ;-----------------------------------------------------------------------
    noSUM_set:
    xorpd xmm2,xmm2
    xorpd xmm4,xmm4
    xorpd xmm6,xmm6
    jmp valuesNot0
    skipX:
    ; Ustawianie sk³adowych RGB piksela na 0.
    mov r11b,0
    mov r12b,0
    mov r13b,0
    ;----------------------------------------------------------------------
    valuesNot0:
    ; Wyliczanie adresu nowych wartoœci piksela, outputArray[3 * (X + Y * width)]
    xor rax,rax
    add eax,ecx
    mov r15d,r8d
    add r15d,2
    mul r15d
    add eax,ebp
    xor r15,r15
    mov r15b,3
    movzx r15d,r15b
    mul r15d
    xor r15,r15
    ;----------------------------------------------------------------------
    ; Umieszczanie nowych wartoœci RGB w tablicy wynikowej outputArray
    mov [rbx+rax],r13b
    inc rax
    mov [rbx+rax],r12b
    inc rax
    mov [rbx+rax],r11b
    ;----------------------------------------------------------------------
    ; Zerowanie rejestrów
    xor r13,r13
    xor r12,r12
    xor r11,r11
    ;----------------------------------------------------------------------
    ; W rezultacie powy¿szy kod mo¿na pokazaæ za pomoc¹ c++:
    ; outputArray[3 * (X + Y * width)] = SUMb;
	; outputArray[3 * (X + Y * width) + 1] = SUMg;
	; outputArray[3 * (X + Y * width) + 2] = SUMr;
    ;----------------------------------------------------------------------
    cmp ebp,r8d
    je innerLoopDone
    inc ebp
    jmp innerLoop

   innerLoopDone:
    inc ecx
    jmp outerLoop

    done:
    pop r15
    pop rsp ; Œci¹ganie wartoœci rejestrów ze stosu
    pop rdi
    pop rbx
    pop rbp
    mov eax,0 ; procedura zwraca 0
	ret
prewittFilter endp
end