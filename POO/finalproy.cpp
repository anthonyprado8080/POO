#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
using namespace std;

class Remedio {
private:
    string nombre;
    string planta;
    string descripcion;
    string preparacion;
    string sintoma;

public:
    Remedio(const string& nombre, const string& planta, const string& descripcion, const string& preparacion, const string& sintoma)
        : nombre(nombre), planta(planta), descripcion(descripcion), preparacion(preparacion), sintoma(sintoma) {}

    string getNombre() const { return nombre; }
    string getPlanta() const { return planta; }
    string getDescripcion() const { return descripcion; }
    string getPreparacion() const { return preparacion; }
    string getSintoma() const { return sintoma; }

    void mostrarInformacion() const {
        cout << "\nRemedio: " << nombre << endl;
        cout << "Planta: " << planta << endl;
        cout << "Descripción: " << descripcion << endl;
        cout << "Preparación: " << preparacion << endl;
        cout << "Síntoma: " << sintoma << endl;
    }

    string toString() const {
        return nombre + ";" + planta + ";" + descripcion + ";" + preparacion + ";" + sintoma;
    }
};

class RemedioService {
private:
    vector<Remedio> remedios;
    const string archivo = "remedios.txt";

public:
    void agregarRemedio(const Remedio& nuevoRemedio) {
        remedios.push_back(nuevoRemedio);
        guardarRemediosEnArchivo(); 
    }

    void mostrarRemediosPorSintoma(const string& sintoma) const {
        bool encontrado = false;
        for (const auto& remedio : remedios) {
            if (remedio.getSintoma() == sintoma) {
                remedio.mostrarInformacion();
                encontrado = true;
            }
        }
        if (!encontrado) {
            cout << "No hay remedios registrados para este síntoma.\n";
        }
    }

    bool eliminarRemedio(const string& nombre) {
        for (auto it = remedios.begin(); it != remedios.end(); ++it) {
            if (it->getNombre() == nombre) {
                remedios.erase(it);
                guardarRemediosEnArchivo(); 
                return true;
            }
        }
        return false;
    }

    void guardarRemediosEnArchivo() {
        ofstream archivoSalida(archivo);
        if (!archivoSalida) {
            cout << "Error al abrir el archivo para guardar los remedios.\n";
            return;
        }
        for (const auto& remedio : remedios) {
            archivoSalida << remedio.toString() << endl;
        }
        archivoSalida.close();
    }

    void cargarRemediosDesdeArchivo() {
        ifstream archivoEntrada(archivo);
        if (!archivoEntrada) {
            cout << "No hay un archivo de remedios previo. Se iniciará sin datos.\n";
            return;
        }

        remedios.clear(); 

        string nombre, planta, descripcion, preparacion, sintoma;
        while (getline(archivoEntrada, nombre, ';') &&
               getline(archivoEntrada, planta, ';') &&
               getline(archivoEntrada, descripcion, ';') &&
               getline(archivoEntrada, preparacion, ';') &&
               getline(archivoEntrada, sintoma)) {
            remedios.emplace_back(nombre, planta, descripcion, preparacion, sintoma);
        }
        archivoEntrada.close();
    }

    void listarRemedios() const {
        if (remedios.empty()) {
            cout << "No hay remedios registrados.\n";
            return;
        }
        for (const auto& remedio : remedios) {
            cout << "- " << remedio.getNombre() << endl;
        }
    }
    bool buscarRemedioPorNombre(const string& nombre) const {
        for (const auto& remedio : remedios) {
            if (remedio.getNombre() == nombre) {
                remedio.mostrarInformacion();
                return true;
            }
        }
        cout << "Remedio no encontrado.\n";
        return false;
    }
};

class RemedioController {
private:
    RemedioService service;

public:
    void agregarRemedio() {
        string nombre, planta, descripcion, preparacion, sintoma;
        cout << "Ingrese el nombre del remedio: ";
        cin.ignore();
        getline(cin, nombre);
        cout << "Ingrese la planta utilizada: ";
        getline(cin, planta);
        cout << "Ingrese la descripción del remedio: ";
        getline(cin, descripcion);
        cout << "Ingrese la preparación del remedio: ";
        getline(cin, preparacion);
        cout << "Ingrese el síntoma que trata: ";
        getline(cin, sintoma);

        Remedio nuevoRemedio(nombre, planta, descripcion, preparacion, sintoma);
        service.agregarRemedio(nuevoRemedio);
        cout << "Remedio agregado con éxito.\n";
    }

    void consultarSintomas() {
        int opcion;
        cout << "\n--- Síntomas comunes ---\n";
        cout << "1. Dolor de cabeza\n";
        cout << "2. Dolor de espalda\n";
        cout << "3. Quemaduras leves\n";
        cout << "4. Mareos\n";
        cout << "5. Náuseas\n";
        cout << "6. Dolores musculares\n";
        cout << "7. Problemas digestivos\n";
        cout << "8. Insomnio\n";
        cout << "9. Ansiedad\n";
        cout << "10. Estrés\n";
        cout << "Ingrese el número del síntoma que desea consultar: ";
        cin >> opcion;
        cin.ignore();

        string sintoma;
        switch (opcion) {
            case 1: sintoma = "Dolor de cabeza"; break;
            case 2: sintoma = "Dolor de espalda"; break;
            case 3: sintoma = "Quemaduras leves"; break;
            case 4: sintoma = "Mareos"; break;
            case 5: sintoma = "Náuseas"; break;
            case 6: sintoma = "Dolores musculares"; break;
            case 7: sintoma = "Problemas digestivos"; break;
            case 8: sintoma = "Insomnio"; break;
            case 9: sintoma = "Ansiedad"; break;
            case 10: sintoma = "Estrés"; break;
            default:
                cout << "Opción no válida. Intente nuevamente.\n";
                return;
        }

        service.mostrarRemediosPorSintoma(sintoma);
    }

    void eliminarRemedio() {
        string nombre;
        cout << "Ingrese el nombre del remedio a eliminar: ";
        cin.ignore();
        getline(cin, nombre);
        if (service.eliminarRemedio(nombre)) {
            cout << "Remedio eliminado con éxito.\n";
        } else {
            cout << "Remedio no encontrado.\n";
        }
    }

    void listarRemedios() {
        cout << "\n--- Lista de Remedios ---\n";
        service.listarRemedios();
    }

    void buscarRemedio() {
        string nombre;
        cout << "Ingrese el nombre del remedio a buscar: ";
        cin.ignore();
        getline(cin, nombre);
        service.buscarRemedioPorNombre(nombre);
    }

    void iniciarPrograma() {
        service.cargarRemediosDesdeArchivo();
    }

    void finalizarPrograma() {
        service.guardarRemediosEnArchivo();
    }
};

int main() {
    RemedioController controller;
    controller.iniciarPrograma();
    int opcion;
    do {
        cout << "\n--- Menú ---\n";
        cout << "1. Agregar remedio\n";
        cout << "2. Consultar síntomas y remedios\n";
        cout << "3. Eliminar remedio\n";
        cout << "4. Listar todos los remedios\n";
        cout << "5. Buscar remedio por nombre\n";
        cout << "6. Salir\n";
        cout << "Ingrese el número de la opción que desea seleccionar: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: controller.agregarRemedio(); break;
            case 2: controller.consultarSintomas(); break;
            case 3: controller.eliminarRemedio(); break;
            case 4: controller.listarRemedios(); break;
            case 5: controller.buscarRemedio(); break;
            case 6:
                controller.finalizarPrograma();
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while (opcion != 6);
    return 0;
}