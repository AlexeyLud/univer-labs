#include <iostream>
#include <Windows.h>
using namespace std;

int checkCondition(char* str) {
    int arg = 0;
    _asm
    {
        mov esi, str
        mov bl, '.'

        cmp[esi], '0'
        je numb
        cmp[esi], '1'
        je numb
        cmp[esi], '2'
        je numb
        cmp[esi], '3'
        je numb
        cmp[esi], '4'
        je numb
        cmp[esi], '5'
        je numb
        cmp[esi], '6'
        je numb
        cmp[esi], '7'
        je numb
        cmp[esi], '8'
        je numb
        cmp[esi], '9'
        je numb

        jmp endu

        start_loop :
            inc esi
            cmp[esi], '.'
            je last
            loop start_loop
            jmp endu

        numb :
            mov bl, [esi]
            jmp start_loop

        numb2 :
            cmp[esi], bl
            je endu
            jne ending

        ending :
            mov arg, 1
            jmp endu

        last :
            dec esi
            cmp[esi], '0'
            je numb2
            cmp[esi], '1'
            je numb2
            cmp[esi], '2'
            je numb2
            cmp[esi], '3'
            je numb2
            cmp[esi], '4'
            je numb2
            cmp[esi], '5'
            je numb2
            cmp[esi], '6'
            je numb2
            cmp[esi], '7'
            je numb2
            cmp[esi], '8'
            je numb2
            cmp[esi], '9'
            je numb2
            jmp endu
            endu :
    }
    return arg;
}

char* firstRule(char* str) {
    _asm
    {
        mov esi, str
        mov bl, 10

        for:
            cmp[esi], 122
            jg endif
            cmp[esi], 97
            jl endif

            xor ax, ax
            mov al, [esi]
            div bl

            cmp ah, 6
            jge substract
            jl summa

            substract :
                add ah, 42
                jmp endf

            summa :
                add ah, 52

            endf :
                mov[esi], ah

            endif :
                cmp[esi], '.'
                je endprog
                inc esi
            jmp for

            endprog :
    }
    return str;
}

char* secondRule(char* str) {
    _asm
    {
        mov eax, str
        push eax
        call dword ptr strlen
        add esp, 4

        add eax, eax
        push eax
        call dword ptr malloc
        add esp, 4

        mov esi, str
        mov ecx, eax

        for:
            mov bl, [esi]
            mov[eax], bl
            inc eax
            mov bl, [esi]
            mov[eax], bl
            inc eax
            inc esi
            cmp[esi], '.'
            je endprog
            jmp for

        endprog :
            mov[eax], '.'
            inc eax
            mov[eax], '\0'
            mov str, ecx
    }
    return str;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int maxLength = 100;
    char* str = new char[maxLength];
    cout << "Введите строку с . на концу: " << endl;
    cin.getline(str, maxLength);
    for (int i = 0; i < maxLength; i++) {
        if (str[i] == '.') {
            break;
        }
    }
    cout << "Проверяемое условие: ";
    cout << checkCondition(str) << endl;
    cout << "Выполнено" << endl << endl;
    if (checkCondition(str) == 0) {
    cout << "Первое правило:" << endl;
    cout << firstRule(str) << endl << endl;
    }
    else {
    cout << "Второе правило:" << endl;
    cout << secondRule(str) << endl << endl;
    }
    system("pause");
    return 0;
}



