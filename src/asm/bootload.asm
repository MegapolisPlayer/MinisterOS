[org 0x7c00] 
mov [BOOTDSK], dl       

KRNLLOC equ 0x1000 ;Kernel Pos
KRNLSEC equ 50 ;Sectors        
                  
;Init Real Mode Stack                  
xor ax, ax                          
mov es, ax
mov ds, ax
mov bp, 0x8000
mov sp, bp

;Read Kernel Data
mov bx, KRNLLOC ;kernel location
mov ah, 0x02 ;has to be
mov al, KRNLSEC ;no of sectors
mov ch, 0x00 ;cylinder no
mov dh, 0x00 ;head no
mov cl, 0x02 ;sector no
mov dl, [BOOTDSK]
int 0x13
         
;Text Mode     
mov ah, 0
mov al, 0x3
int 0x10

;Global Descriptor Table - END of real mode code

GDTCSEG equ codedesc - GDTSTART
GDTDSEG equ datadesc - GDTSTART

cli
lgdt [GDTDESC]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp GDTCSEG:MODE32
jmp $
                                    
BOOTDSK: db 0

GDTSTART:
    nulldesc:
        dd 0x0
        dd 0x0
    codedesc:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10011010
        db 0b11001111
        db 0x0
    datadesc:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10010010
        db 0b11001111
        db 0x0
GDTEND:
GDTDESC:
    dw GDTEND - GDTSTART - 1
    dd GDTSTART

[bits 32]
MODE32:
    ;set registers
    mov ax, GDTDSEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax	
	mov ebp, 0x90000
	mov esp, ebp

        cli

    jmp KRNLLOC ;jump to krnl

times 510-($-$$) db 0              
dw 0xaa55