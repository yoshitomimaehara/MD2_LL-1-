#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
#include<algorithm>
#include<string>
#include<conio2.h>
#include<vector>
#include<list>
#include<cstdio>
#include<windows.h>
#include<direct.h>
using namespace std;

#include "presentacion.h"
#define raya "------------------\n"


struct Gramatica{  //estructura gramatica
	char Izquierda;
	string Derecha;		
}L;

vector<Gramatica> prod; //vector de las producciones

char w1;//no terminal temporal
string w2;//terminal temporal
int nprod;//numero de producciones
string pila;//pila de derivaciones
string cinta;//cinta de salida
string CTermi;//conjunto de no terminales
string CnoTerm;//conjunto de terminales
string Alfabeto;//Alfabeto
string cadena;//cadena ingresada

char nom[100];//nombre de archivo
char tipo[]=".txt"; //extension .txt

//prototipos de funciones
void CrearArchivo();
void ActualizarArchivo();
void LimpiarGramatica();
void CrearGramatica();
void MostrarGramatica();
bool Verifica(char,string);
bool buscar(char,char);
string noterminales();
string terminales();
string alfabeto();
void modificaprod();
void modificanombre();
void FunAccion();
void verarchivos();
void CargarGramatica();
void menu();
void rastreo();
void NuevaCadena();

//funcion main()
int main(){
  mostrar();
  getch();
  system("cls");
  menu();
}


void LimpiarGramatica(){//limpia los elementos de la gramatica
	prod.clear();
    CTermi.clear();
    CnoTerm.clear();
    Alfabeto.clear();
}


void CrearArchivo(){//crea el archivo txt
    cout<<"ingrese el nombre del archivo:";cin>>nom;
    strcat(nom,tipo); //concatena el nombre con la extension
    ofstream fs(nom); //escribe
    for(int i=0;i<prod.size();i++){ //genera producciones
    	L=prod[i];
        fs<<L.Izquierda<<"->"<<L.Derecha<<"\n";
   	}
   	fs.close();
}


void CrearGramatica(){//crear una nueva gramatica
	int n,i=0;
	bool band=false;
	char op3;
	if(prod.size()==0){ // verifica si hay alguna gramatica cargada
  LimpiarGramatica();
  cout<<"Las Producciones son de la forma #->####\n";
	cout<<"Se debe comenzar con S\n";
	cout<<"Cuantas Produciones desea Ingresar:";cin>>n;
	while(n>i){ // verifica que existan producciones (>0)
        cout<<i+1<<"."; 
		L.Izquierda=getche(); // captura el caracter N.T
        if(i==0 && L.Izquierda=='S'){ // verifica que no haygan producciones cargadas y que el N.T sea S
          band=true;            
        }
        if(isupper(L.Izquierda) && band==true){ // comprueba que el N.T sea Mayuscula
          cout<<"->";
		  cin>>L.Derecha; // ingresa terminal
		  i++;
		  prod.push_back(L); //guarda las producciones
		}else{
         delline();
         gotoxy(1,i+4); // limpia la pantalla dependiendo de las producciones y las 4 lineas adicionales de instrucciones
        }
	}
    CrearArchivo();
 }else{
       cout<<"ya existe una gramatica cargada!\n";
       cout<<"Desea crear una nueva gramatica(s/n):";cin>>op3;
       switch(op3){
          case 's':
               system("cls");
               prod.clear();
               CrearGramatica();
               break;
          default:
             return;
             break;
       }
    }
}//fin crearGramatica


bool Verifica(char letra,string str){//verificar si ya existe el caracter 
  bool sw=false;
  for(int i=0;i<str.size();i++){
      if(letra==str[i]){
        sw=true;
        break;                 
      }
  }
  return sw;     
}


string noterminales(){//crea el conjunto de no terminales
    CnoTerm.clear();   
    for(int i=0;i<prod.size();i++){
    	L=prod[i];
        if(Verifica(L.Izquierda,CnoTerm)==false){
          CnoTerm.push_back(L.Izquierda);
        }
   	}	
   	return CnoTerm;
}


string terminales(){//crea el conjunto de terminales
    CTermi.clear();
    for(int i=0;i<prod.size();i++){
    	L=prod[i];
      for(int j=0;j<prod.size();j++){
        if(islower(L.Derecha[j])){
          if(Verifica(L.Derecha[j],CTermi)==false){
            CTermi.push_back(L.Derecha[j]);
          }                  
        }
      }
}
    list<char> ltermi(CTermi.begin(), CTermi.end()); // almacenamos todo en una Lista
    list<char>::iterator it;
    ltermi.sort(); // ordenamos todos las letras
    CTermi.clear();
    string c;
    for (it = ltermi.begin(); it != ltermi.end(); it++){ 
            c = *it;
            CTermi.append(c); //agrega cada simbolo
    } 	
    return CTermi;
}


string alfabeto(){//crear el alfabeto
  Alfabeto.clear();     
  noterminales();
  terminales();
  Alfabeto=CnoTerm+CTermi;
  return Alfabeto;
}


void MostrarGramatica(){
	if(prod.size()>0){  //verifica que existan producciones 
        for(int i=0;i<prod.size();i++){ //asigna producciones a la cadena de Terminales y No Terminales
    	L=prod[i];
        cout<<i+1<<"."<<L.Izquierda<<"->"<<L.Derecha<<"\n"; //muestra gramatica
   	    }
   	    cout<<"\n";
   	    alfabeto(); // obtiene el alfabeto
         cout<<"T={  ";
        for(int j=0;j<CTermi.size();j++){ //muestra Terminales
            cout<<CTermi[j]<<"  ";
        }
        cout<<"}\n";
        cout<<"N={  ";
        for(int k=0;k<CnoTerm.size();k++){ //muestra no Terminales
            cout<<CnoTerm[k]<<"  ";
        }
        cout<<"}\n";
        cout<<"A={  ";
        for(int l=0;l<Alfabeto.size();l++){ //Muestra el alfabeto
            cout<<Alfabeto[l]<<"  ";
        }
        cout<<"}\n\n";
        
        
    }else{
        cout<<"No existen producciones\n";
    }
}//fin MostrarGramatica


void verarchivos(){
    // tomado de MSDN de Visual Studio (recursos para desarrolladores)
    cin.ignore();
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    char DirectorioActual[MAX_PATH];
    if(NULL == _getcwd(DirectorioActual, MAX_PATH) ){ 
      perror("getcwd error"); 
      return; 
    } // obtenemos el directorio actual , sino error y salimos.
    strncat(DirectorioActual, "\\*", 3); // agregamos
    hFind = FindFirstFile(DirectorioActual, &FindFileData); // hacemos la busqueda de los archivos
    if(hFind == INVALID_HANDLE_VALUE){ // si algo va mal salimos 
        cout<<"Error: Directorio Invalido\n";
        return;
    }
    char * pch;
    cout << endl;

         while(FindNextFile(hFind, &FindFileData) != 0){
           pch = strstr(FindFileData.cFileName,".txt"); // filtramos solo los .txt
           if (pch != NULL){
             cout <<"  "<<FindFileData.cFileName<<"\n";
           }
          }
    cout << endl;
    FindClose(hFind);

    pch = NULL; // para que no tener un "wild pointer"

    return;
}



void CargarGramatica(){//carga el archivo que contiene la gramatica
    char op4;
    if(prod.size()==0){ //Verifica que existan producciones
    cout<<"escriba el nombre la gramatica a cargar\n";
    cout<<"no es necesario colocar la extension del archivo\n"; 
    cout<<"\n  Lista de gramaticas\n";
    cout<<"  --------------------";
    verarchivos(); // ve los archivos que hay
    LimpiarGramatica();
    ifstream fe; // se crea flujo de entrada de archivo
    string buffer; // cadena donde se guarda la produccion
    cout<<"  Archivo de Entrada : ";cin>> nom; //nombre de archivo
    strcat(nom,tipo);
    fe.open(nom); 
    if(!fe.good()){ 
      cerr<< "\n\t\t" <<"  Archivo no encontrado!" << "\n\n"; 
      getch(); 
      return; 
      } 
    else
     {
       while(!fe.eof()){
        L.Derecha.clear();
        L.Izquierda='\0';  // se establece el valor nulo
        fe>>buffer;//lee los datos del archivo
        L.Izquierda=buffer[0];  // asigna el primer simbolo de la cadena buffer
        L.Derecha.append(buffer,3,buffer.size());//lee la cadena a partir de la posicion 3
        prod.push_back(L);
       } 
       prod.erase(prod.end()); // borra las producciones anteriores
       cout<<"  Archivo Cargado!!!\n";
       getch();
     }
fe.close();
}else{
      cout<<"ya existe una gramatica cargada!\n";
       cout<<"Desea crear una nueva gramatica(s/n):";cin>>op4;
       switch(op4){
          case 's':
               system("cls");
               prod.clear(); //elimina producciones anteriores
               CargarGramatica();
               break;
          default:
             return;
             break;
             }
}
} //Fin Cargar Gramatica


void ActualizarArchivo(){//actualiza el contenido del archivo
    ofstream fs(nom);
    for(int i=0;i<prod.size();i++){ //asigna producciones a la cadena de Terminales y No Terminales
      L=prod[i];
      fs<<L.Izquierda<<"->"<<L.Derecha<<"\n"; //muestra y guarda los terminales y no terminales
    }
    fs.close();
}


void modificaprod(){
  int n;
  char op1;
  MostrarGramatica(); //muestra la gramatica
  if(prod.empty()){ //verifica que existan producciones
     cout <<"Tiene que agregar al menos una produccion"<<endl;
     system("pause"); 
     return;                
  }
  cout << "Cual Produccion desea modificar?: "; cin >> n; // se digita el numero de produccion a modificar
  cout << endl<< "Produccion Actual : " << prod[n-1].Izquierda << " -> " <<prod[n-1].Derecha << endl; //muestra produccion actual (-1 para que encaje con el vector)
  cout << "Produccion Nueva  : "; w1 = getch(); //Ingresa no terminal de la izquierda
  cout << w1 << " -> ";cin >> w2; //Muestra el no terminal anterior y pide ingresar terminales
  prod[n-1].Izquierda = w1; // guarda los valores del lado izquierdo en el vector
  prod[n-1].Derecha = w2; // guarda los valores del lado derecho en el vector
  ActualizarArchivo(); // actualiza archivo
} //Fin modificaprod

void modificanombre(){   
     int res;
     char nom2[100];
     fstream fs; // crea el flujo de archivo
     fs.open(nom,ios::in | ios::out);
     if (!fs) {
        cerr << "El archivo no se encuentra\n" << endl;
        getch();
     return;
     } 
     fs.close();
     
     cout<<"Nombre Anterior:"<<nom<<endl;
     cout<<"Nombre Nuevo:";cin>>nom2;
     strcat(nom2,tipo);
     res= rename( nom,nom2); // hace el cambio de nombre
     if ( res== 0 ) 
    puts ( "Cambio de Nombre Exitoso" );
    else
    perror( "Error al Cambiar de nombre" );
} // Fin modificanombre


bool buscar(char LT,char LNT){ // busca el simbolo en la gramatica
  bool sw=false;
  for(int i=0;i<prod.size();i++){  // busca en cada produccion
    if(LNT==prod[i].Izquierda && LT==prod[i].Derecha[0]){  // verifica el primer simbolo de la izquierda y el de la derecha
      sw=true;
      nprod=i;
      break;
    }else if(LNT==prod[i].Izquierda && isupper(prod[i].Derecha[0])){  // verifica si el primer elemento de la derecha es mayuscula
      sw=buscar(LT,prod[i].Derecha[0]);  // busca otra vez
      nprod=i;
    }
  }
  return sw;
}


void FunAccion(){
  if(prod.size()>0){ //Verifica que existan producciones
  alfabeto();
  CTermi.push_back('#'); // se agrega # al final del conjunto
  Alfabeto.push_back('#'); // se agrega # al final del conjunto
  cout<<"Simbolo"<<setw(35)<<"Simbolo de Entrada Actual\n";
  cout<<"\nPila    ";
  //Titulo
  for(int j=0;j<CTermi.size();j++) cout<<"  "<<CTermi[j]<<"\t";  
  cout<<endl<<endl;
  //cuerpo
   
    for(int i=0;i<Alfabeto.size();i++){
    cout<<"  "<<Alfabeto[i];
      for(int j=0;j<CTermi.size();j++){ //
        if(CTermi[j]!=Alfabeto[i] ){  // si el terminal es diferente del simbolo alfabeto
          if(buscar(CTermi[j],CnoTerm[i])==true){    // busca en la gramatica
            cout<<"\t"<<"("<<prod[nprod].Derecha<<","<<(nprod+1)<<")";  // si lo encuentra coloca el resultado
          }else{
            cout<<"\tError";
          }
        }else if(CTermi[j]=='#' && Alfabeto[i]=='#'){  // si son iguales a # 
          cout<<"\tAceptar";
        }else if(CTermi[j]==Alfabeto[i] && CTermi[j]!='#' && Alfabeto[i]!='#'){  // si son solo iguales y diferentes a #
          cout<<"\tE_C";                               
        }
      } 
    cout<<"\n\n";
  }
}
else{
   return;
}

}//Fin FunAccion


void rastreo(){
     char str;
     cinta.clear(); // limpia la cinta en caso haya datos
     cout<<"\n\n  Traza del analisis sintactico de "<<cadena<<endl<<endl;
     cout<<" Cadena de entrada       Pila      Cinta de salida\n";
     cout<<" -----------------       ----      ---------------\n";
     do{   
       cout<<setw(12)<<cadena<<setw(18)<<pila<<"\t\t  "<<cinta<<endl;
        if(cadena[0]!= pila[0]){ // si el primer simbolo de la cadena y de la pila son diferentes
           if(buscar(cadena[0],pila[0])) {
              pila.replace(0,1,prod[nprod].Derecha);//reemplazo el no terminal
              itoa((nprod+1),&str,10);//convierte numero a caracter
              cinta.push_back(str); // agrega el numero a la cinta
           }
           else{
            break;
           }
        }else{
            //eliminar cima
            pila.erase(pila.begin());
            cadena.erase(cadena.begin());
        }   
       }while(cadena[0]!='#' && pila[0]!='#'); // mientras cadena y pila no terminen en #
       
     cout<<setw(12)<<cadena<<setw(18)<<pila<<"\t\t  "<<cinta<<endl; 
     cout<<"\n\n"; 
     if (cadena[0]!='#' || pila[0]!='#'){ // si la cadena y pila no terminan en #
         cout<<"\n  Error: La cadena no puede ser generada por esta gramatica.\n\n";
     }
} 


void NuevaCadena(){ 
      if(prod.size()>0){ //verifica que existan producciones
        cin.ignore(); //sirve para que no considere el caracter ingresado
        cout<<"\n\n  Cadena: ";cin>>cadena; 
        cadena.push_back('#'); // guarda la cadena
        pila.assign("S#"); // agrega # al final de la cadena
        rastreo(); // hace el analisis
      }
} //Fin NuevaCadena
    
     
void menu(){//menu del programa
clrscr();
char i;
  cout<<"  "<<raya;
  cout<<"        Menu\n";
  cout<<"  "<<raya;
  cout<<"  1.Crear Gramatica\n";
  cout<<"  2.Mostrar Gramatica\n";
  cout<<"  3.Modifica Gramatica\n";
  cout<<"  4.Cargar Gramatica\n";
  cout<<"\n";
  cout<<"  5.Funcion Accion\n";
  cout<<"  6.Analizar Cadena\n";
  cout<<"\n";  
  cout<<"  7.Salir\n";
  
  cout<<"  "<<raya;
  cout<<"  ingrese la opcion que desea:";cin>>i;
  switch(i)
  {
    case '1':
      clrscr();
      CrearGramatica();
      menu();
      break;
    case '2':
      clrscr();
      MostrarGramatica();
      getch();
      menu();
      break;
    case '3':
      clrscr();
      char op1;
      cout<<"1.Modificar Producion\n";
      cout<<"2.Nombre del Archivo\n";
      cout<<"ingrese su opcion:";cin>>op1;
      switch(op1){
         case '1':
              modificaprod();
         break;
         case '2':
              modificanombre();
         break;
         default:
              menu();
         break;
      }

      menu(); 
      break;
    case '4':
      clrscr();
      CargarGramatica();
      menu();   
      break;
    case '5':
      clrscr();
      MostrarGramatica();
      FunAccion();
      getch();
      menu();   
      break;
    case '6':
      clrscr();
      system("cls");
      MostrarGramatica();
      FunAccion(); 
      NuevaCadena();
      getch();
      system("cls");
      menu(); 
      break;
    case '7':
      exit(1);
      break;
    default: 
      cout<<"  Opcion Incorrecta\n";
      getch();
      menu();
      break;     
  }
}
