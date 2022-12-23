__asm{
        .686
        .model flat, c

        get_length macro string1
            lea esi,[string1]
            xor ecx, ecx
        L :
            mov bl, byte ptr[esi]
            cmp bl, 0
            je end_macro
            inc ecx
            inc esi
            jmp L
        end_macro :
            mov len, ecx
        endm

        number_of_spaces macro string1, string2
            lea esi,[string1]
            mov ecx, len
            lea edi,[string2]
            mov al, byte ptr[edi]
        L4:
            mov bl, byte ptr[esi]
            cmp bl, al
            jne L3
            inc num
        L3 :
            inc esi
            loop L4
        Lend :
        endm

        find_space_index macro string1, string2
            mov ecx, len
            lea esi,[string1]
            mov eax, 0
            lea edi,[string2]
            mov al, byte ptr[edi]
        L1:
            mov bl, byte ptr[esi]
            cmp bl, al
            je end1
            inc esi
            inc eax
            jmp L1
        end1 :
        endm

        delete_space macro string1, pos
            mov edx, pos
            lea edi,[string1 + edx]
            inc edx
            lea esi,[string1 + edx]

            mov ecx, len
            sub ecx, pos
            inc ecx
        L2 :
            mov bl, byte ptr[esi]
            mov byte ptr[edi], bl
            inc esi
            inc edi
            loop L2
        endm

        .stack

        .data
            string1 byte 255 dup(0)
            string2 byte  1 dup(0)
            len dword 0
            num byte 0
            inputmsg1 byte "Enter a string: ", 0
            inputmsg2 byte "Enter a string: ", 0
            outmsg byte "Chnged string: %s", 10, 13, 0

        .code

            printf proto arg1 : ptr byte, printlist : vararg
            input proto s : ptr byte

        f proc
            invoke printf, addr inputmsg1
            invoke input, addr string1

            invoke printf, addr inputmsg2
            invoke input, addr string2

            get_length string1
            number_of_spaces string1, string2
        P :
            cmp num, 0
            je toend

            find_space_index string1, string2
            delete_space string1, eax

            dec num
            jmp P

        toend :
            invoke printf, addr outmsg, addr string1
            ret

        f endp
        end
}