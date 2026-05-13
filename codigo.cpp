#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

// Estructura para manejar los datos del reporte
struct Reporte {
    string estudiante = "Mateo Alexander Muyulema Moyolema"; // Tus datos personales
    string carrera = "Ingenieria en Software - UTA";
    string ciudad = "Ambato, Ecuador";
    string lenguaje = "C++";
    double promedio;
    double notaMayor;
    double notaMenor;
    int aprobados;
    int reprobados;
    int cargados;
};

void operacionesBasicas(double &n1, double &n2, bool &realizadas) {
    int op;
    cout << "\n--- 1. Operaciones Basicas ---" << endl;
    cout << "Primer numero: "; cin >> n1;
    cout << "Segundo numero: "; cin >> n2;

    cout << "\nResultados Obtenidos:" << endl;
    cout << "Suma: " << (n1 + n2) << endl;
    cout << "Resta: " << (n1 - n2) << endl;
    cout << "Multiplicacion: " << (n1 * n2) << endl;

    if (n2 != 0) {
        cout << "Division: " << (n1 / n2) << endl;
    } else {
        cout << "Division: Error (No se puede dividir para cero)" << endl;
    }
    realizadas = true;
}

int main() {
    int opcion;
    const int TOTAL_ESTUDIANTES = 30;
    string nombres[TOTAL_ESTUDIANTES];
    double notas[TOTAL_ESTUDIANTES];

    // Inicialización del reporte
    Reporte r;
    r.promedio = 0; r.notaMayor = -1; r.notaMenor = 11;
    r.aprobados = 0; r.reprobados = 0; r.cargados = 0;

    double num1 = 0, num2 = 0;
    bool opRealizadas = false;
    bool notasRegistradas = false;
    string fecha;

    do {
        cout << "\n=== APLICATIVO INTERACTIVO: LOGICODEUTA (C++) ===" << endl;
        cout << "1. Operaciones basicas" << endl;
        cout << "2. Procesar notas de 30 companeros (estudiantes.txt)" << endl;
        cout << "3. Guardar resultados finales (resultados.txt)" << endl;
        cout << "4. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            operacionesBasicas(num1, num2, opRealizadas);
        }
        else if (opcion == 2) {
            cout << "\n--- 2. Carga y Procesamiento de Notas ---" << endl;
            ifstream archivoEntrada("estudiantes.txt");

            if (!archivoEntrada) {
                cout << "Error: No se encontro 'estudiantes.txt' en la carpeta del proyecto." << endl;
            } else {
                double suma = 0;
                r.cargados = 0;
                r.notaMayor = -1; r.notaMenor = 11;
                r.aprobados = 0; r.reprobados = 0;

                while (archivoEntrada >> nombres[r.cargados] >> notas[r.cargados] && r.cargados < TOTAL_ESTUDIANTES) {
                    double notaActual = notas[r.cargados];
                    suma += notaActual;

                    if (notaActual > r.notaMayor) r.notaMayor = notaActual;
                    if (notaActual < r.notaMenor) r.notaMenor = notaActual;

                    if (notaActual >= 7.0) r.aprobados++;
                    else r.reprobados++;

                    r.cargados++;
                }
                archivoEntrada.close();

                if (r.cargados > 0) {
                    r.promedio = suma / r.cargados;
                    notasRegistradas = true;
                    cout << "Lectura exitosa. Se procesaron " << r.cargados << " estudiantes." << endl;
                    cout << fixed << setprecision(2);
                    cout << "Promedio General: " << r.promedio << endl;
                    cout << "Nota Mayor: " << r.notaMayor << " | Nota Menor: " << r.notaMenor << endl;
                }
            }
        }
        else if (opcion == 3) {
            cout << "\n--- 3. Guardar Reporte ---" << endl;
            cout << "Ingrese la fecha actual (dd/mm/aaaa): ";
            cin.ignore(); // Limpiar el buffer
            getline(cin, fecha);

            ofstream archivoSalida("resultados.txt");
            if (archivoSalida.is_open()) {
                archivoSalida << "========================================\n";
                archivoSalida << "      REPORTE DE EVALUACION FINAL       \n";
                archivoSalida << "========================================\n";
                archivoSalida << "Estudiante: " << r.estudiante << "\n";
                archivoSalida << "Carrera: " << r.carrera << "\n";
                archivoSalida << "Ubicacion: " << r.ciudad << "\n";
                archivoSalida << "Fecha: " << fecha << " | Lenguaje: " << r.lenguaje << "\n";
                archivoSalida << "----------------------------------------\n";

                if (opRealizadas) {
                    archivoSalida << "[Operaciones Basicas]\n";
                    archivoSalida << "Numeros: " << num1 << " y " << num2 << "\n";
                    archivoSalida << "Suma: " << (num1 + num2) << " | Resta: " << (num1 - num2) << "\n";
                    archivoSalida << "Multiplicacion: " << (num1 * num2) << "\n";
                    if (num2 != 0) archivoSalida << "Division: " << (num1 / num2) << "\n";
                    else archivoSalida << "Division: Error (Indeterminada)\n";
                    archivoSalida << "----------------------------------------\n";
                }

                if (notasRegistradas) {
                    archivoSalida << "[Listado del Curso y Estadisticas]\n";
                    for (int i = 0; i < r.cargados; i++) {
                        archivoSalida << left << setw(15) << nombres[i] << " : " << notas[i] << "\n";
                    }
                    archivoSalida << "\n[Estadisticas Finales]\n";
                    archivoSalida << fixed << setprecision(2);
                    archivoSalida << "Promedio General: " << r.promedio << "\n";
                    archivoSalida << "Nota Mayor: " << r.notaMayor << " | Nota Menor: " << r.notaMenor << "\n";
                    archivoSalida << "Aprobados: " << r.aprobados << " | Reprobados: " << r.reprobados << "\n";
                } else {
                    archivoSalida << "[Notas]: No se procesaron notas en esta sesion.\n";
                }

                archivoSalida << "========================================\n";
                archivoSalida.close();
                cout << "Reporte 'resultados.txt' generado correctamente en C++." << endl;
            } else {
                cout << "Error al crear el archivo de resultados." << endl;
            }
        }
    } while (opcion != 4);

    cout << "Finalizando programa" << endl;
    return 0;
}
