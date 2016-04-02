/*
 Nombre: Presentacion de Trabajo (caratula)
 Autores:  
        - Fabriccio Isla Chau
        - Percy Pariona Alanya
        - Jean Pier Sotelo Castáman
 Año de creacion: 2009
 
 Modificado por: 
        - Dan de la Cruz Guevara
        - Edgar Vasquez Vergara
 Año de Modificacion:2009
 
 Modificado por: 
	- Yoshitomi Maehara Aliaga
	- Johan Osorio Urrutia
 Año de Modificacion:2012
 */
#include<iostream>
using namespace std;

void mostrar(){
		cout<<"\n\n";
		for(int i=1;i<=11;i++){
			cout<<"\t\t\t";
			for(int j=1;j<=14;j++){
              if((j==2 && i>2) || (i==11 && j<=8 && j>1) || (j==14 && i<7) || (j==8 && i>2) || (i==3 && j>4 && j<12) || (j>4 && (i==1 || i==6)))
                 cout<<"x";
              else
                 cout<<" ";
            }
			if(i==4) cout<<"\t   UNIVERSIDAD";
			if(i==6) cout<<"\t   TECNOLOGICA";
			if(i==8) cout<<"\t   DEL PERU";
			cout<<endl;
		}
		cout <<"\n\n\n\t      FACULTAD DE INGENIERIA DE TRANSPORTE Y SOFTWARE\n\n\t";
		cout <<"       ESCUELA PROFESIONAL DE INGENIERIA DE SOFTWARE\n\n\t      ";
		cout <<"-----------------------------------------------\n\n\t\t\t   ";
		cout << "MATEMATICA DISCRETA II\n\n";
		cout <<"\t\t             GRAMATICAS LL(1) \n\n\t      ";
		cout <<"\t         SIMPLE Y SIN REGLAS VACIAS\n\n\t      ";
		cout <<"-----------------------------------------------\n\n\n\t\t  ";
		cout <<"PROFESOR     :  Carlos De Souza Ferreira\n\n\t\t  ";
		cout <<"INTEGRANTES  :\n\n\t\t\t";  
        cout <<"- Yoshitomi Maehara Aliaga\n\t\t\t";
        cout <<"- Johan Osorio Urrutia\n\n\t          ";
		cout <<"CICLO        :  IV\n\n\n\n\n";
}
