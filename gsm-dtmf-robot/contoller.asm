$MOD51

    RELAY1     BIT   P0.1
    RELAY2     BIT   P0.2
    RELAY3     BIT   P0.3
    RELAY4     BIT   P0.4
    KEY        EQU   P1
    STD        BIT   P1.4
   
    ORG    00H

    MOV    SP,#08H
    MOV    KEY,#0FFH
        MOV P0,#00H
START:
   
    JNB    STD ,$
    CALL   KEY_READ
           CALL   ACTION
    CALL   DEBOUNCE
    JMP    START
KEY_READ:
    MOV    A,KEY
    ANL    A,#0FH
    MOV    R1,A
    RET
;----------------------
ACTION:
    MOV   A,R1
    CJNE  A,#02,J1
    SETB   RELAY1
    SETB   RELAY3
        CALL   DELAY
        CLR   RELAY1
        CLR   RELAY3
    JMP   J20

J1:    CJNE  A,#08,J2
    SETB   RELAY2
    SETB  RELAY4
        CALL  DELAY
        CLR   RELAY2
        CLR   RELAY4
    JMP   J20

J2:    CJNE  A,#04,J3
    SETB   RELAY2
        CALL  DELAY1
        CLR   RELAY2
           JMP   J20

J3:    CJNE  A,#06,J20
    SETB RELAY4
        CALL  DELAY1
        CLR  RELAY4
           JMP   J20

J20:    RET
;------------------------
DELAY:
     MOV R3,#7
J21:     MOV R4,#02H
J30:     MOV R5,#14H
J40:     MOV R6,#0FFH
     DJNZ R6,$
     DJNZ R5,J40
     DJNZ R4,J30
     DJNZ R3,J21
     RET
;................................
DELAY1:
     MOV R3,#2
J211:     MOV R4,#02H
J30A:     MOV R5,#15H
J40A:     MOV R6,#0FFH
     DJNZ R6,$
     DJNZ R5,J40A
     DJNZ R4,J30A
     DJNZ R3,J211
     RET
;................................
DEBOUNCE:
        MOV     R6,#80H
J81:    NOP
        MOV     R5,#0FFH
    DJNZ    R5,$
    DJNZ    R6,J81
    RET
;------------------------
END