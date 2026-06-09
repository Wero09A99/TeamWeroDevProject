
/*
 * Reporte de Programa - Control de Contaminacion PET
 * Con colores ANSI, sin separadores ===/--, funcionalidades extra
 */

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Codigos de color ANSI
const string RESET   = "\033[0m";
const string NEGRITA = "\033[1m";
const string ROJO    = "\033[31m";
const string VERDE   = "\033[32m";
const string AMARILLO= "\033[33m";
const string AZUL    = "\033[34m";
const string MAGENTA = "\033[35m";
const string CIAN    = "\033[36m";
const string BLANCO  = "\033[97m";
const string BG_AZUL = "\033[44m";
const string BG_VERDE= "\033[42m";
const string BG_ROJO = "\033[41m";

int main() {

    // Configurar decimales
    cout << fixed << setprecision(2);

    // Pantalla de bienvenida
    cout << "\n" << BG_AZUL << BLANCO << NEGRITA;
    cout << "   SISTEMA DE CONTROL DE CONTAMINACION PET   ";
    cout << RESET << "\n";
    cout << CIAN << "  Registro de establecimientos y calculo de residuos\n" << RESET;
    cout << AMARILLO << "  Version 2.0 - Con colores y funcionalidades extra\n" << RESET;
    cout << "\n";

    // Variables globales
    int    totalEstablecimientos  = 0;
    int    totalReportes          = 0;
    double grandTotalPetUtilizado = 0.0;
    double grandTotalPetDesperdiciado = 0.0;
    int    totalComida   = 0;
    int    totalTienda   = 0;
    int    totalMercado  = 0;

    // Nombre del encargado
    string nombreEncargado;
    cout << NEGRITA << BLANCO << "Ingrese el nombre del encargado del registro: " << RESET;
    cin.ignore();
    getline(cin, nombreEncargado);
    if (nombreEncargado.empty()) nombreEncargado = "Sin nombre";
    cout << VERDE << "  Bienvenido/a, " << nombreEncargado << "!\n" << RESET;

    char registrarOtro = 's';

    while (registrarOtro == 's' || registrarOtro == 'S') {

        totalEstablecimientos++;

        cout << "\n" << BG_AZUL << BLANCO << NEGRITA;
        cout << "  ESTABLECIMIENTO #" << totalEstablecimientos << "  ";
        cout << RESET << "\n";

        // Nombre del establecimiento
        string nombreEstablecimiento;
        cout << AZUL << NEGRITA << "Nombre del establecimiento: " << RESET;
        cin.ignore();
        getline(cin, nombreEstablecimiento);
        if (nombreEstablecimiento.empty()) nombreEstablecimiento = "Sin nombre";

        // Tipo de establecimiento (switch)
        int  tipoEstablecimiento = 0;
        bool tipoValido = false;

        while (!tipoValido) {
            cout << "\n" << NEGRITA << CIAN << "Tipo de establecimiento:\n" << RESET;
            cout << AMARILLO << "  [1]" << RESET << " Establecimiento de comida\n";
            cout << AMARILLO << "  [2]" << RESET << " Tienda convencional\n";
            cout << AMARILLO << "  [3]" << RESET << " Mercado\n";
            cout << NEGRITA << "Opcion: " << RESET;
            cin >> tipoEstablecimiento;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << ROJO << "  [!] Entrada invalida. Ingrese 1, 2 o 3.\n" << RESET;
            } else if (tipoEstablecimiento < 1 || tipoEstablecimiento > 3) {
                cout << ROJO << "  [!] Opcion fuera de rango. Solo 1, 2 o 3.\n" << RESET;
            } else {
                tipoValido = true;
            }
        }

        string nombreTipo;
        switch (tipoEstablecimiento) {
            case 1: nombreTipo = "Establecimiento de comida"; totalComida++;  break;
            case 2: nombreTipo = "Tienda convencional";       totalTienda++;  break;
            case 3: nombreTipo = "Mercado";                   totalMercado++; break;
        }
        cout << VERDE << "  Tipo registrado: " << NEGRITA << nombreTipo << RESET << "\n";

        // Dias de operacion a la semana
        int  diasSemana = 0;
        bool diasValidos = false;

        while (!diasValidos) {
            cout << "\n" << CIAN << "Dias a la semana que opera el establecimiento " << RESET;
            cout << AMARILLO << "(1-7): " << RESET;
            cin >> diasSemana;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << ROJO << "  [!] Ingrese un numero entero.\n" << RESET;
            } else if (diasSemana < 1 || diasSemana > 7) {
                cout << ROJO << "  [!] El valor debe estar entre 1 y 7.\n" << RESET;
            } else {
                diasValidos = true;
            }
        }

        // Turno del establecimiento (funcionalidad extra)
        int  turno = 0;
        bool turnoValido = false;

        while (!turnoValido) {
            cout << "\n" << NEGRITA << CIAN << "Turno de operacion:\n" << RESET;
            cout << AMARILLO << "  [1]" << RESET << " Matutino  (6am - 2pm)\n";
            cout << AMARILLO << "  [2]" << RESET << " Vespertino (2pm - 10pm)\n";
            cout << AMARILLO << "  [3]" << RESET << " Nocturno  (10pm - 6am)\n";
            cout << AMARILLO << "  [4]" << RESET << " Tiempo completo (24h)\n";
            cout << NEGRITA << "Opcion: " << RESET;
            cin >> turno;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << ROJO << "  [!] Entrada invalida. Ingrese 1, 2, 3 o 4.\n" << RESET;
            } else if (turno < 1 || turno > 4) {
                cout << ROJO << "  [!] Opcion fuera de rango.\n" << RESET;
            } else {
                turnoValido = true;
            }
        }

        string nombreTurno;
        switch (turno) {
            case 1: nombreTurno = "Matutino";      break;
            case 2: nombreTurno = "Vespertino";    break;
            case 3: nombreTurno = "Nocturno";      break;
            case 4: nombreTurno = "Tiempo completo"; break;
        }

        // Captura diaria de PET
        double petUtilizadoSemana     = 0.0;
        double petDesperdiaciadoSemana = 0.0;
        double petMaxDia = 0.0;
        double petMinDia = -1.0;
        int    diaMayorDesperdicio = 0;
        double mayorDesperdicio    = 0.0;

        cout << "\n" << NEGRITA << MAGENTA << "Ingreso de datos diarios de PET\n" << RESET;

        for (int dia = 1; dia <= diasSemana; dia++) {

            cout << "\n" << AZUL << NEGRITA << "  Dia " << dia << ":\n" << RESET;

            // PET utilizado
            double petDiaUtilizado = -1.0;
            while (petDiaUtilizado < 0) {
                cout << CIAN << "    PET utilizado (unidades): " << RESET;
                cin >> petDiaUtilizado;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    petDiaUtilizado = -1.0;
                    cout << ROJO << "    [!] Ingrese un numero valido >= 0.\n" << RESET;
                } else if (petDiaUtilizado < 0) {
                    cout << ROJO << "    [!] El valor no puede ser negativo.\n" << RESET;
                }
            }

            // PET desperdiciado
            double petDiaDesperdiciado = -1.0;
            while (petDiaDesperdiciado < 0) {
                cout << CIAN << "    PET desperdiciado (unidades): " << RESET;
                cin >> petDiaDesperdiciado;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    petDiaDesperdiciado = -1.0;
                    cout << ROJO << "    [!] Ingrese un numero valido >= 0.\n" << RESET;
                } else if (petDiaDesperdiciado < 0) {
                    cout << ROJO << "    [!] El valor no puede ser negativo.\n" << RESET;
                } else if (petDiaDesperdiciado > petDiaUtilizado) {
                    cout << ROJO << "    [!] El desperdicio (" << petDiaDesperdiciado
                         << ") no puede superar lo utilizado (" << petDiaUtilizado << ").\n" << RESET;
                    petDiaDesperdiciado = -1.0;
                }
            }

            // Estadisticas por dia
            double petDiaAprovechado = petDiaUtilizado - petDiaDesperdiciado;
            double pctDia = (petDiaUtilizado > 0)
                            ? (petDiaDesperdiciado / petDiaUtilizado) * 100.0
                            : 0.0;

            // Barra visual de desperdicio del dia
            int barras = (int)(pctDia / 5);
            cout << "    Estado del dia: [";
            for (int b = 0; b < 20; b++) {
                if (b < barras)
                    cout << ROJO << "|" << RESET;
                else
                    cout << VERDE << "|" << RESET;
            }
            cout << "] " << AMARILLO << pctDia << "% desperdicio\n" << RESET;

            // Alerta si el desperdicio supera 50%
            if (pctDia > 50.0) {
                cout << ROJO << NEGRITA
                     << "    [ALERTA] Desperdicio critico este dia (>" << "50%)\n"
                     << RESET;
            }

            // Maximo y minimo de PET utilizado en la semana
            if (petDiaUtilizado > petMaxDia) petMaxDia = petDiaUtilizado;
            if (petMinDia < 0 || petDiaUtilizado < petMinDia) petMinDia = petDiaUtilizado;

            // Dia con mayor desperdicio
            if (petDiaDesperdiciado > mayorDesperdicio) {
                mayorDesperdicio    = petDiaDesperdiciado;
                diaMayorDesperdicio = dia;
            }

            petUtilizadoSemana      += petDiaUtilizado;
            petDesperdiaciadoSemana += petDiaDesperdiciado;
        }

        // Calculos semanales
        double petAprovechadoSemana    = petUtilizadoSemana - petDesperdiaciadoSemana;
        double porcentajeContaminacion = 0.0;
        double porcentajeAprovechamiento = 0.0;
        if (petUtilizadoSemana > 0) {
            porcentajeContaminacion  = (petDesperdiaciadoSemana / petUtilizadoSemana) * 100.0;
            porcentajeAprovechamiento = (petAprovechadoSemana   / petUtilizadoSemana) * 100.0;
        }

        // Promedio diario
        double promedioDiarioUtilizado    = petUtilizadoSemana    / diasSemana;
        double promedioDiarioDesperdiciado = petDesperdiaciadoSemana / diasSemana;

        // Clasificacion de nivel de contaminacion
        string nivelContaminacion;
        string colorNivel;
        if (porcentajeContaminacion < 20.0) {
            nivelContaminacion = "BAJO";
            colorNivel = VERDE;
        } else if (porcentajeContaminacion < 50.0) {
            nivelContaminacion = "MODERADO";
            colorNivel = AMARILLO;
        } else {
            nivelContaminacion = "CRITICO";
            colorNivel = ROJO;
        }

        totalReportes++;

        // Reporte del establecimiento
        cout << "\n" << BG_VERDE << BLANCO << NEGRITA;
        cout << "  REPORTE: " << nombreEstablecimiento << "  ";
        cout << RESET << "\n";

        cout << NEGRITA << BLANCO << "  Tipo          : " << RESET << nombreTipo      << "\n";
        cout << NEGRITA << BLANCO << "  Turno         : " << RESET << nombreTurno     << "\n";
        cout << NEGRITA << BLANCO << "  Dias operados : " << RESET << diasSemana << " dia(s)\n";

        cout << "\n" << NEGRITA << CIAN << "  Resumen semanal de PET:\n" << RESET;
        cout << "  PET utilizado total       : " << VERDE  << NEGRITA << petUtilizadoSemana      << " uds\n" << RESET;
        cout << "  PET desperdiciado total   : " << ROJO   << NEGRITA << petDesperdiaciadoSemana << " uds\n" << RESET;
        cout << "  PET aprovechado total     : " << VERDE  << petAprovechadoSemana               << " uds\n" << RESET;

        cout << "\n" << NEGRITA << CIAN << "  Promedios diarios:\n" << RESET;
        cout << "  Promedio utilizado/dia    : " << AZUL   << promedioDiarioUtilizado    << " uds\n" << RESET;
        cout << "  Promedio desperdiciado/dia: " << AMARILLO << promedioDiarioDesperdiciado << " uds\n" << RESET;

        cout << "\n" << NEGRITA << CIAN << "  Estadisticas:\n" << RESET;
        cout << "  Dia mayor desperdicio     : " << AMARILLO << "Dia " << diaMayorDesperdicio
             << " (" << mayorDesperdicio << " uds)\n" << RESET;
        cout << "  Max PET utilizado en dia  : " << VERDE  << petMaxDia << " uds\n" << RESET;
        cout << "  Min PET utilizado en dia  : " << AZUL   << petMinDia << " uds\n" << RESET;

        cout << "\n" << NEGRITA << CIAN << "  Indicadores:\n" << RESET;
        cout << "  % Contaminacion por semana: " << colorNivel << NEGRITA << porcentajeContaminacion << "%" << RESET << "\n";
        cout << "  % Aprovechamiento         : " << VERDE  << porcentajeAprovechamiento << "%\n" << RESET;
        cout << "  Nivel de contaminacion    : " << colorNivel << NEGRITA << nivelContaminacion << "\n" << RESET;

        // Barra global del establecimiento
        int barrasTotal = (int)(porcentajeContaminacion / 5);
        cout << "\n  Contaminacion semanal: [";
        for (int b = 0; b < 20; b++) {
            if (b < barrasTotal)
                cout << ROJO << "|" << RESET;
            else
                cout << VERDE << "|" << RESET;
        }
        cout << "] " << colorNivel << NEGRITA << porcentajeContaminacion << "%\n" << RESET;

        grandTotalPetUtilizado     += petUtilizadoSemana;
        grandTotalPetDesperdiciado += petDesperdiaciadoSemana;

        // Preguntar si registra otro
        bool respuestaValida = false;
        while (!respuestaValida) {
            cout << "\n" << NEGRITA << AMARILLO
                 << "Desea registrar otro establecimiento? (s/n): " << RESET;
            cin >> registrarOtro;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << ROJO << "  [!] Ingrese 's' o 'n'.\n" << RESET;
            } else if (registrarOtro != 's' && registrarOtro != 'S' &&
                       registrarOtro != 'n' && registrarOtro != 'N') {
                cout << ROJO << "  [!] Solo se acepta 's' o 'n'.\n" << RESET;
            } else {
                respuestaValida = true;
            }
        }

    } // fin while

    // Reporte final
    double porcentajeFinalContaminacion  = 0.0;
    double porcentajeFinalAprovechamiento = 0.0;
    double petRecuperableFinal = grandTotalPetUtilizado - grandTotalPetDesperdiciado;

    if (grandTotalPetUtilizado > 0) {
        porcentajeFinalContaminacion  = (grandTotalPetDesperdiciado / grandTotalPetUtilizado) * 100.0;
        porcentajeFinalAprovechamiento = (petRecuperableFinal       / grandTotalPetUtilizado) * 100.0;
    }

    string nivelFinal;
    string colorFinal;
    if (porcentajeFinalContaminacion < 20.0) {
        nivelFinal = "BAJO - Buen manejo de residuos";
        colorFinal = VERDE;
    } else if (porcentajeFinalContaminacion < 50.0) {
        nivelFinal = "MODERADO - Hay areas de mejora";
        colorFinal = AMARILLO;
    } else {
        nivelFinal = "CRITICO - Se requieren acciones urgentes";
        colorFinal = ROJO;
    }

    cout << "\n\n" << BG_ROJO << BLANCO << NEGRITA;
    cout << "   REPORTE FINAL DEL PROGRAMA   ";
    cout << RESET << "\n";

    cout << NEGRITA << BLANCO << "  Encargado     : " << RESET << nombreEncargado << "\n";
    cout << NEGRITA << BLANCO << "  Total reportes: " << RESET << totalReportes << "\n";

    cout << "\n" << NEGRITA << CIAN << "  Establecimientos registrados:\n" << RESET;
    cout << "  De comida   : " << AMARILLO << totalComida  << RESET << "\n";
    cout << "  Tiendas     : " << AMARILLO << totalTienda  << RESET << "\n";
    cout << "  Mercados    : " << AMARILLO << totalMercado << RESET << "\n";
    cout << "  TOTAL       : " << NEGRITA << BLANCO << totalEstablecimientos << RESET << "\n";

    cout << "\n" << NEGRITA << CIAN << "  Totales globales de PET:\n" << RESET;
    cout << "  Total utilizado      : " << VERDE  << NEGRITA << grandTotalPetUtilizado      << " uds\n" << RESET;
    cout << "  Total desperdiciado  : " << ROJO   << NEGRITA << grandTotalPetDesperdiciado   << " uds\n" << RESET;
    cout << "  Total aprovechado    : " << VERDE  << petRecuperableFinal                     << " uds\n" << RESET;

    cout << "\n" << NEGRITA << CIAN << "  Indicadores globales:\n" << RESET;
    cout << "  % Contaminacion global  : " << colorFinal << NEGRITA << porcentajeFinalContaminacion  << "%\n" << RESET;
    cout << "  % Aprovechamiento global: " << VERDE      << NEGRITA << porcentajeFinalAprovechamiento << "%\n" << RESET;

    // Barra final
    int barrasFinal = (int)(porcentajeFinalContaminacion / 5);
    cout << "\n  Indice global: [";
    for (int b = 0; b < 20; b++) {
        if (b < barrasFinal)
            cout << ROJO << "|" << RESET;
        else
            cout << VERDE << "|" << RESET;
    }
    cout << "]\n";

    cout << "\n  " << colorFinal << NEGRITA << "Nivel: " << nivelFinal << RESET << "\n";

    cout << "\n" << BG_AZUL << BLANCO << NEGRITA;
    cout << "   Fin del programa. Gracias, " << nombreEncargado << "!   ";
    cout << RESET << "\n\n";

    return 0;
}