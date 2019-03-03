
                        ;
                        ;  stub.asm -- standard stub
                        ;
                        ;  This stub can't be used with
                        ;  PUB library for DOS.
                        ;
                        ;  by Park, Kyu Hyun
                        ;
                        ;  1994.11.16
                        ;

                        .model small,pascal

code                    segment
                        assume cs:code, ds:data, ss:stk

      dos               macro       call_id
                        mov         ah,call_id
                        int         21h
                        endm

      start:            mov   ax,data
                        mov   ds,ax
                        mov   dx,offset msg
                        dos   09h

      exit:             dos     4ch
code                    ends

data                    segment
      msg               db 'This program is not DOS excutable.',0dh,0ah,'$'
data                    ends

stk                     segment stack
                        db 100 dup(?)
stk                     ends

                        end start

