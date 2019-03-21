#include <18F4620.h>
#include <stdio.h>
#include <stdlib.h>
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

#use fast_io(a)
#use fast_io(b)
#use fast_io(c)
#use fast_io(d)
#use fast_io(e)
long  operando1 = 0, operando2 = 0, resultado = 0;
void rebound(void);
void main (void){
   setup_oscillator(OSC_16MHZ);
   setup_adc_ports(NO_ANALOGS);
   set_tris_a(0x10);
   set_tris_b(0xff);
   set_tris_c(0x00);
   set_tris_d(0xff);
   set_tris_e(0xf);
   int operacion=0;
   while(1){
       
       operando1 = input_b();
       operando2 = input_d();
      
       
       if(input(PIN_E0) ==1)
          operacion=1;
       if(input(PIN_E1) ==1)
          operacion=2;
       if(input(PIN_E2) ==1)
          operacion=3;
       if(input(PIN_A5) ==1)
          operacion=4;
        
       if(input(PIN_E0)==1 && operacion==1){
           resultado = operando1 + operando2; 
           operacion=0;
      }
       if(input(PIN_E1)==1 && operacion==2){
           resultado = operando1 - operando2;
           operacion=0;
     }
       if(input(PIN_E2)==1 && operacion==3){
           resultado = operando1 * operando2;
           operacion=0;
   }
       if(input(PIN_A5)==1 && operacion==4){
           if(input_d()!=0){
               resultado= operando1 / operando2;
               operacion=0;
       }
       else{
           rebound();
       }
           
   }
     output_c(resultado);
     output_a(resultado>>8);
   }
}

void rebound(void){
   long Error = 0x0;
   for(int parpadeo = 1; parpadeo < 4; parpadeo++){
       Error = 0x1fff;
       output_c(Error);
       output_a(Error>>8);
       delay_ms(250);
       Error = 0x0;
       output_c(Error);
       output_a(Error>>8);
       delay_ms(250);
   }
}    

