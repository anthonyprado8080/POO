Proyecto de Gestión de Remedios
Descripción
Este proyecto permite gestionar remedios caseros basados en plantas, ofreciendo una interfaz para agregar, consultar, eliminar y buscar remedios según los síntomas que tratan. Los remedios se almacenan en un archivo de texto (remedios.txt) para su persistencia y se cargan al iniciar el programa. Los usuarios pueden consultar remedios para síntomas comunes como dolor de cabeza, mareos, náuseas, entre otros.

Características
Agregar un remedio: Permite ingresar información sobre el remedio, como el nombre, la planta utilizada, la preparación y el síntoma que trata.
Consultar síntomas: El programa proporciona una lista de síntomas comunes y muestra los remedios disponibles para cada uno.
Eliminar remedio: Permite eliminar un remedio registrado por su nombre.
Listar todos los remedios: Muestra una lista de todos los remedios registrados.
Buscar un remedio por nombre: Permite buscar un remedio y ver su información detallada.
Instrucciones de instalación
Clonar el repositorio:

bash
Copiar
git clone https://github.com/tuusuario/gestion-remedios.git
cd gestion-remedios
Compilar el proyecto:

Si estás usando g++ en un entorno Linux o macOS, puedes compilar el proyecto de la siguiente manera:

bash
Copiar
g++ -o gestion_remedios main.cpp
En Windows, puedes utilizar un entorno como MinGW o Visual Studio para compilar el archivo.

Instrucciones de ejecución
Ejecutar el programa:

Una vez compilado, ejecuta el programa con el siguiente comando:

bash
Copiar
./gestion_remedios
Si estás en Windows, el archivo ejecutable podría ser gestion_remedios.exe, por lo que lo ejecutarías con:

bash
Copiar
gestion_remedios.exe
Interacción con el usuario:

El programa presentará un menú con varias opciones. Podrás agregar remedios, consultar síntomas, eliminar remedios, listar todos los remedios o buscar un remedio por nombre.

Explicación de las diferencias entre la versión estructurada y la orientada a objetos
Versión estructurada:
En la versión estructurada, el código está organizado de manera secuencial. Las funciones se utilizan para realizar tareas específicas y los datos se pasan entre ellas. No hay una clara separación entre los datos y las funciones que los manipulan. En este modelo, el enfoque principal es sobre las funciones y su secuencia de ejecución, con datos representados generalmente en estructuras.

Por ejemplo, si tuviéramos una versión estructurada de este programa, tendríamos funciones separadas para agregar remedios, eliminar remedios y consultar síntomas. Las funciones tomarían los datos como parámetros y operarían sobre ellos sin una clara encapsulación de los datos.

Versión orientada a objetos:
En la versión orientada a objetos, el código está organizado en clases y objetos. Cada clase tiene atributos (datos) y métodos (funciones) que operan sobre esos datos. Esto permite encapsular la lógica y los datos, mejorando la modularidad, reutilización y mantenibilidad del código. Además, las clases pueden interactuar entre sí, como en el caso de las clases Remedio, RemedioService y RemedioController, donde cada una tiene responsabilidades claras.

En la versión orientada a objetos, se hace un uso extenso de conceptos como la encapsulación, donde los atributos están protegidos y solo accesibles a través de métodos públicos (getters y setters). Además, la herencia y polimorfismo podrían ser utilizados para ampliar o modificar comportamientos, si fuera necesario.

Diferencias clave:
Modularidad: En OOP (Orientación a Objetos), los componentes del sistema se encapsulan en clases, lo que facilita la organización del código y su mantenimiento. En la versión estructurada, los datos y las funciones están separados.
Reusabilidad: En OOP, las clases pueden ser reutilizadas y extendidas, lo que permite que el código sea más flexible. En la programación estructurada, se tiende a escribir funciones para tareas específicas, lo que puede resultar en duplicación de código.
Mantenibilidad: El enfoque orientado a objetos permite una mayor mantenibilidad debido a la claridad en la definición de responsabilidades de cada clase. En programación estructurada, a medida que el programa crece, puede volverse más difícil de gestionar.
#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
using namespace std;

// Clase que representa un remedio.
class Remedio {
private:
    string nombre;         // Nombre del remedio
    string planta;         // Planta utilizada en el remedio
    string descripcion;    // Descripción del remedio
    string preparacion;    // Cómo preparar el remedio
    string sintoma;        // Síntoma que trata el remedio

public:
    // Constructor que inicializa los atributos del remedio
    Remedio(const string& nombre, const string& planta, const string& descripcion, const string& preparacion, const string& sintoma)
        : nombre(nombre), planta(planta), descripcion(descripcion), preparacion(preparacion), sintoma(sintoma) {}

    // Métodos para obtener los atributos del remedio
    string getNombre() const { return nombre; }
    string getPlanta() const { return planta; }
    string getDescripcion() const { return descripcion; }
    string getPreparacion() const { return preparacion; }
    string getSintoma() const { return sintoma; }

    // Método para mostrar la información del remedio
    void mostrarInformacion() const {
        cout << "\nRemedio: " << nombre << endl;
        cout << "Planta: " << planta << endl;
        cout << "Descripción: " << descripcion << endl;
        cout << "Preparación: " << preparacion << endl;
        cout << "Síntoma: " << sintoma << endl;
    }

    // Método que devuelve una cadena con todos los atributos del remedio, separados por punto y coma
    string toString() const {
        return nombre + ";" + planta + ";" + descripcion + ";" + preparacion + ";" + sintoma;
    }
};

// Clase que maneja la lógica de los remedios y las operaciones con ellos.
class RemedioService {
private:
    vector<Remedio> remedios;   // Vector que almacena los remedios
    const string archivo = "remedios.txt";   // Nombre del archivo donde se guardan los remedios

public:
    // Método para agregar un remedio al vector y guardar la lista de remedios en un archivo
    void agregarRemedio(const Remedio& nuevoRemedio) {
        remedios.push_back(nuevoRemedio);
        guardarRemediosEnArchivo(); // Guardamos la lista de remedios en el archivo
    }

    // Método para mostrar remedios según el síntoma que trata
    void mostrarRemediosPorSintoma(const string& sintoma) const {
        bool encontrado = false;
        for (const auto& remedio : remedios) {
            if (remedio.getSintoma() == sintoma) {
                remedio.mostrarInformacion(); // Muestra el remedio si coincide el síntoma
                encontrado = true;
            }
        }
        if (!encontrado) {
            cout << "No hay remedios registrados para este síntoma.\n";
        }
    }

    // Método para eliminar un remedio según su nombre y actualizar el archivo
    bool eliminarRemedio(const string& nombre) {
        for (auto it = remedios.begin(); it != remedios.end(); ++it) {
            if (it->getNombre() == nombre) {
                remedios.erase(it); // Elimina el remedio
                guardarRemediosEnArchivo(); // Guarda la lista actualizada de remedios
                return true;
            }
        }
        return false; // Retorna false si no se encuentra el remedio
    }

    // Método para guardar todos los remedios en un archivo de texto
    void guardarRemediosEnArchivo() {
        ofstream archivoSalida(archivo);
        if (!archivoSalida) {
            cout << "Error al abrir el archivo para guardar los remedios.\n";
            return;
        }
        for (const auto& remedio : remedios) {
            archivoSalida << remedio.toString() << endl; // Escribe cada remedio en el archivo
        }
        archivoSalida.close(); // Cierra el archivo
    }

    // Método para cargar los remedios desde un archivo de texto
    void cargarRemediosDesdeArchivo() {
        ifstream archivoEntrada(archivo);
        if (!archivoEntrada) {
            cout << "No hay un archivo de remedios previo. Se iniciará sin datos.\n";
            return;
        }

        remedios.clear(); // Limpiamos el vector de remedios

        string nombre, planta, descripcion, preparacion, sintoma;
        // Lee el archivo y agrega los remedios al vector
        while (getline(archivoEntrada, nombre, ';') &&
               getline(archivoEntrada, planta, ';') &&
               getline(archivoEntrada, descripcion, ';') &&
               getline(archivoEntrada, preparacion, ';') &&
               getline(archivoEntrada, sintoma)) {
            remedios.emplace_back(nombre, planta, descripcion, preparacion, sintoma); // Agrega el remedio al vector
        }
        archivoEntrada.close(); // Cierra el archivo
    }

    // Método para listar todos los remedios registrados
    void listarRemedios() const {
        if (remedios.empty()) {
            cout << "No hay remedios registrados.\n";
            return;
        }
        for (const auto& remedio : remedios) {
            cout << "- " << remedio.getNombre() << endl; // Muestra el nombre de cada remedio
        }
    }

    // Método para buscar un remedio por nombre
    bool buscarRemedioPorNombre(const string& nombre) const {
        for (const auto& remedio : remedios) {
            if (remedio.getNombre() == nombre) {
                remedio.mostrarInformacion(); // Muestra la información si lo encuentra
                return true;
            }
        }
        cout << "Remedio no encontrado.\n"; // Mensaje si no se encuentra el remedio
        return false;
    }
};

// Clase que actúa como controlador, gestionando la interacción con el usuario
class RemedioController {
private:
    RemedioService service; // Instancia del servicio que maneja los remedios

public:
    // Método para agregar un nuevo remedio
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
        service.agregarRemedio(nuevoRemedio); // Agrega el remedio al servicio
        cout << "Remedio agregado con éxito.\n";
    }

    // Método para consultar remedios por síntoma, mostrando opciones comunes
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

        service.mostrarRemediosPorSintoma(sintoma); // Muestra los remedios para el síntoma seleccionado
    }

    // Método para eliminar un remedio por nombre
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

    // Método para listar todos los remedios
    void listarRemedios() {
        cout << "\n--- Lista de Remedios ---\n";
        service.listarRemedios();
    }

    // Método para buscar un remedio por su nombre
    void buscarRemedio() {
        string nombre;
        cout << "Ingrese el nombre del remedio a buscar: ";
        cin.ignore();
        getline(cin, nombre);
        service.buscarRemedioPorNombre(nombre);
    }

    // Método para cargar los remedios desde el archivo al iniciar el programa
    void iniciarPrograma() {
        service.cargarRemediosDesdeArchivo();
    }

    // Método para guardar los remedios en el archivo al finalizar el programa
    void finalizarPrograma() {
        service.guardarRemediosEnArchivo();
    }
};

int main() {
    RemedioController controller; // Creamos un controlador para manejar las operaciones
    controller.iniciarPrograma(); // Cargamos los remedios desde el archivo al inicio
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

        // Ejecuta la opción seleccionada por el usuario
        switch (opcion) {
            case 1: controller.agregarRemedio(); break;
            case 2: controller.consultarSintomas(); break;
            case 3: controller.eliminarRemedio(); break;
            case 4: controller.listarRemedios(); break;
            case 5: controller.buscarRemedio(); break;
            case 6:
                controller.finalizarPrograma(); // Guarda los remedios en el archivo al salir
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while (opcion != 6); // Continuamos hasta que el usuario elija salir
    return 0;
}
