#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>



void
cambiarAMayusculas(char *s){            //funcion que cambia las mayusculas por las minusculas, pasandolo por parametro
   int i;
  
   for (i=0;i<strlen(s);i++){
      if (isupper(s[i])) 
          s[i]=tolower(s[i]);
   }
 
}
int main(int argc, char *argv[]){

	int i,opcioni,opcionr,opcionn,posicion;
        opcioni=0;
        opcionr=0;
        opcionn=0;
        posicion=0;

       for (i=1;i<argc; i++){
	   if (strcmp(argv[i],"-n")==0){       //se marca opcionn=1 si encuentra -n
                    opcionn=1;
                    posicion=i;
           }
           else if (strcmp(argv[i],"-r")==0){
                    opcionr=1;                  //se marca opcionn=1 si encuentra -r
                    posicion=i;
	   }
           else if (strcmp(argv[i],"-i")==0){
                    opcioni=1;                   //se marca opcionn=1 si encuentra -i
                    posicion=i;
           
           }
           else
               break;                           //si no encuentra ninguna de las dos opciones no sigue comprobando
        }
	
    posicion++;
    
   
   if (opcioni){ 
         for (i=posicion;i<argc;i++)      
             cambiarAMayusculas(argv[i]);          //si la opcino es -i se llama a la funcion cambiarAMayusculas para cambiar la cadena completa

   }

   
   if (opcionr){
     for (i=argc-1;i>=posicion;i--)               //si la opcion es -r muestra los argumentos forma al reves
		printf("%s ",argv[i]);
   }   
   else{
        for (i=posicion;i<argc;i++)               //si no hay ninguna opcion te muestra la cadena de caracteres segun esta
         printf("%s ",argv[i]);
   }
   
   if (opcionn){
     for (i=argc-1;i>=posicion;i--)              //si la opcion es -n no muestra retorno de carro al final 
		printf("%s \n",argv[i]);
   }

   
   if (opcionn==0){                              //si no hay opcion -n, no se encuentra se hace un salto de linea
       printf("\n");
   
   }



  return 0;
}


