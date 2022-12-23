#include <iostream>
using namespace std;

void f() {
    _asm 
	{
        model small
        stack 128
        dataseg
        simvol db 0
        zamena db 0
        size_ db 0
        vvedite_massiv db 'VVedite massiv (max-253 byte): ', 0dh, 0ah, '$'
        massiv db 255, 255 dup(90h)
        perevod_stroki db 0dh, 0ah, '$'
        simvol_dly_poiska db 'Vvedite simvol dly poiska : $'
        simvol_dly_zameni db 'Vvedite simvol dly zameni : $'

        codeseg
        .386
        org 100h
        start :
        mov ax, @data
            mov ds, ax
            mov es, ax

            mov ah, 09h
            mov dx, offset vvedite_massiv
            int 21h
            mov ah, 0ah
            mov dx, offset massiv
            int 21h
            mov ah, 09
            mov dx, offset perevod_stroki
            int 21h

            mov ah, 09h
            mov dx, offset simvol_dly_poiska
            int 21h
            mov ah, 01h
            int 21h
            mov[simvol], al
            mov ah, 09
            mov dx, offset perevod_stroki
            int 21h

            mov ah, 09h
            mov dx, offset simvol_dly_zameni
            int 21h
            mov ah, 01h
            int 21h
            mov[zamena], al
            mov ah, 09
            mov dx, offset perevod_stroki
            int 21h
            ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        mov si, offset massiv
            inc si
            mov al, [si]
            mov[size_], al

            xor cx, cx
            mov cl, [size_]

            mass_1:
        inc si
            mov al, [si]
            cmp al, [simvol]
            jne mass_2

            mov al, [zamena]
            mov[si], al

            mass_2 :
        loop mass_1

            cld
            mov di, offset massiv
            xor bx, bx
            mov bl, [size_]
            add di, bx
            add di, 2
            mov si, offset perevod_stroki
            mov cx, 3
            rep movsb

            mov ah, 09h
            mov dx, offset massiv + 2
            int 21h

            ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

        exit:
        mov ax, 4c00h
            int 21h
            end start
    }
}

int main()
{
	f();
	system("pause");
	return 0;
}


