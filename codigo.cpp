#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    int opcion;
    string nombreEstudiante = "Mateo Muyulema";
    string fecha = "";
    string lenguaje = "C++";
    
    double num1 = 0, num2 = 0;
    bool opRealizadas = false;
    
    const int TOTAL_ESTUDIANTES = 39;
    string nombres[TOTAL_ESTUDIANTES];
    double notas[TOTAL_ESTUDIANTES];
    
    double promedio = 0, notaMayor = -1, notaMenor = 11;
    int aprobados = 0, reprobados = 0;
    int cargados = 0;
    bool notasRegistradas = false;

    do {
        cout << "\n=== APLICATIVO INTERACTIVO DE LOGICA Y ALGORITMOS ===" << endl;
        cout << "1. Operaciones basicas" << endl;
        cout << "2. Procesar nomina oficial de 39 estudiantes (estudiantes.txt)" << endl;
        cout << "3. Guardar resultados finales (resultados.txt)" << endl;
        cout << "4. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "\n--- 1. Operaciones Basicas ---" << endl;
            cout << "Ingrese el primer numero: "; cin >> num1;
            cout << "Ingrese el segundo numero: "; cin >> num2;
            
            cout << "\nResultados Obtenidos:" << endl;
            cout << "Suma: " << (num1 + num2) << endl;
            cout << "Resta: " << (num1 - num2) << endl;
            cout << "Multiplicacion: " << (num1 * num2) << endl;
            if (num2 != 0) {
                cout << "Division: " << (num1 / num2) << endl;
            } else {
                cout << "Division: Error (Division para cero no permitida)" << endl;
            }
            opRealizadas = true;
        } 
        else if (opcion == 2) {
            cout << "\n--- 2. Carga y Procesamiento de Nómina ---" << endl;
            ifstream archivoEntrada("estudiantes.txt");
            
            if (!archivoEntrada.is_open()) {
                cout << "Error: No se encontro el archivo 'estudiantes.txt' en la raiz." << endl;
            } else {
                double suma = 0;
                notaMayor = -1; notaMenor = 11;
                aprobados = 0; reprobados = 0;
                cargados = 0;

                string nom, apellido;
                double notafinal;
                
                while (cargados < TOTAL_ESTUDIANTES && archivoEntrada >> nom >> apellido >> notafinal) {
                    nombres[cargados] = nom + " " + apellido;
                    notas[cargados] = notafinal;
                    suma += notafinal;

                    if (notafinal > notaMayor) notaMayor = notafinal;
                    if (notafinal < notaMenor) notaMenor = notafinal;

                    if (notafinal >= 7.0) aprobados++;
                    else reprobados++;

                    cargados++;
                }
                archivoEntrada.close();

                if (cargados > 0) {
                    promedio = suma / cargados;
                    notasRegistradas = true;
                    cout << "¡Lectura exitosa! Se procesaron " << cargados << " estudiantes de la nomina oficial.\n" << endl;
                    cout << "Métricas del Curso:" << endl;
                    cout << "Promedio general: " << fixed << setprecision(2) << promedio << endl;
                    cout << "Nota mayor: " << notaMayor << " | Nota menor: " << notaMenor << endl;
                    cout << "Aprobados (>=7): " << aprobados << " | Reprobados (<7): " << reprobados << endl;
                } else {
                    cout << "Advertencia: El archivo se encuentra vacio o con estructura corrupta." << endl;
                }
            }
        } 
        else if (opcion == 3) {
            cout << "\n--- 3. Guardar Reporte ---" << endl;
            cout << "Ingrese la fecha actual (ej. 13/05/2026): ";
            cin.ignore();
            getline(cin, fecha);

            ofstream archivoSalida("resultados.txt");
            if (archivoSalida.is_open()) {
                archivoSalida << "========================================\n";
                archivoSalida << "        REPORTE DE EVALUACION           \n";
                archivoSalida << "========================================\n";
                archivoSalida << "Estudiante: " << nombreEstudiante << "\n";
                archivoSalida << "Fecha: " << fecha << " | Lenguaje: " << lenguaje << "\n";
                archivoSalida << "----------------------------------------\n";
                
                if (opRealizadas) {
                    archivoSalida << "[Operaciones Basicas]\n";
                    archivoSalida << "Numeros: " << num1 << " y " << num2 << "\n";
                    archivoSalida << "Suma: " << (num1 + num2) << " | Resta: " << (num1 - num2) << "\n";
                    archivoSalida << "Multiplicacion: " << (num1 * num2) << "\n";
                    if (num2 != 0) archivoSalida << "Division: " << (num1 / num2) << "\n";
                    else archivoSalida << "Division: Error (Division para cero)\n";
                    archivoSalida << "----------------------------------------\n";
                }

                if (notasRegistradas) {
                    archivoSalida << "[Nómina Oficial del Curso y Estadisticas]\n";
                    for(int i = 0; i < cargados; i++) {
                        archivoSalida << left << setw(22) << nombres[i] << " : " << fixed << setprecision(1) << notas[i] << "\n";
                    }
                    archivoSalida << "\nPromedio General: " << fixed << setprecision(2) << promedio << "\n";
                    archivoSalida << "Nota Mayor: " << notaMayor << " | Nota Menor: " << notaMenor << "\n";
                    archivoSalida << "Aprobados: " << aprobados << " | Reprobados: " << reprobados << "\n";
                } else {
                    archivoSalida << "[Notas]: Nomina no procesada en esta sesion.\n";
                }
                archivoSalida << "========================================\n";
                archivoSalida.close();
                cout << "¡Archivo 'resultados.txt' guardado exitosamente en disco!" << endl;
            } else {
                cout << "Error critico al intentar crear el reporte local." << endl;
            }
        }
    } while (opcion != 4);

    cout << "¡Hasta luego!" << endl;
    return 0;
}
