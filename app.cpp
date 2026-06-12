#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;
//reconecta app
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
const string BG_AMARILLO = "\033[43m";
const double LIMITE_SEMANAL_COMIDA  = 150.0;  // uds/semana (alta rotacion de empaques)
const double LIMITE_SEMANAL_TIENDA  = 200.0;  // uds/semana
const double LIMITE_SEMANAL_MERCADO = 300.0;  // uds/semana (mayor volumen)
const double LIMITE_DIARIO_COMIDA   = 22.0;   // uds/dia  (~150/7)
const double LIMITE_DIARIO_TIENDA   = 29.0;   // uds/dia  (~200/7)
const double LIMITE_DIARIO_MERCADO  = 43.0;   // uds/dia  (~300/7)
// Funcion: mostrar consejos segun nivel y tipo de establecimiento
void mostrarConsejos(int tipo, double porcentaje) {
    cout << "\n" << BG_AMARILLO << BLANCO << NEGRITA;
    cout << "  RECOMENDACIONES PARA TU ESTABLECIMIENTO  ";
    cout << RESET << "\n";
    //Consejos generales por nivel de contaminacion
    if (porcentaje < 20.0) {
        cout << VERDE << NEGRITA << "\n  [OK] Nivel BAJO - Sigue con estas buenas practicas:\n" << RESET;
        cout << VERDE << "  * Mantiene registros semanales para detectar cambios a tiempo.\n";
        cout << "  * Comparte tu metodo con otros establecimientos de la zona.\n";
        cout << "  * Considera un programa de reciclaje formal con empresas certificadas.\n" << RESET;
    } else if (porcentaje < 50.0) {
        cout << AMARILLO << NEGRITA << "\n  [ATENCION] Nivel MODERADO - Areas de mejora detectadas:\n" << RESET;
        cout << AMARILLO << "  * Revisa en cuales dias de la semana el desperdicio fue mayor.\n";
        cout << "  * Capacita al personal sobre separacion y manejo correcto de PET.\n";
        cout << "  * Establece una meta de reduccion del 10% para la proxima semana.\n";
        cout << "  * Considera sustituir empaques PET por alternativas reutilizables.\n" << RESET;
    } else {
        cout << ROJO << NEGRITA << "\n  [CRITICO] Nivel ALTO - Se requieren acciones urgentes:\n" << RESET;
        cout << ROJO << "  * Detener el uso excesivo de PET de forma inmediata.\n";
        cout << "  * Realizar una auditoria interna de residuos esta semana.\n";
        cout << "  * Contratar un gestor de residuos autorizado (SEMARNAT).\n";
        cout << "  * Elaborar un Plan de Manejo de Residuos (obligatorio si\n";
        cout << "    supera 10 toneladas/anio segun NOM-161-SEMARNAT-2011).\n" << RESET;
    }
    //Consejos especificos por tipo de establecimiento
    cout << "\n" << CIAN << NEGRITA << "  Consejos especificos para tu tipo de negocio:\n" << RESET;
    switch (tipo) {
        case 1: // Comida
            cout << CIAN;
            cout << "  [Comida] Usa dispensadores de salsas y condimentos en lugar\n";
            cout << "           de sachets individuales de PET.\n";
            cout << "  [Comida] Ofrece descuento a clientes que traigan su propio recipiente.\n";
            cout << "  [Comida] Sustituye botellas PET de agua por garrafones o filtros.\n";
            cout << "  [Comida] Separa envases limpios para venderlos a centros de acopio\n";
            cout << "           (precio aprox. $3-5 MXN/kg en mercado actual).\n";
            cout << RESET;
            break;
        case 2: // Tienda
            cout << CIAN;
            cout << "  [Tienda] Prefiere proveedores con empaques de PET reciclado (rPET).\n";
            cout << "  [Tienda] Coloca un contenedor de PET limpio para que clientes\n";
            cout << "           depositen sus envases al comprar.\n";
            cout << "  [Tienda] Negocia con tu proveedor la devolucion de empaques.\n";
            cout << "  [Tienda] Revisa productos con mayor desperdicio de empaque\n";
            cout << "           y busca alternativas con menos PET por unidad.\n";
            cout << RESET;
            break;
        case 3: // Mercado
            cout << CIAN;
            cout << "  [Mercado] Implementa un punto de acopio de PET centralizado\n";
            cout << "            para todos los locatarios del mercado.\n";
            cout << "  [Mercado] Organiza una cooperativa de venta de PET reciclado\n";
            cout << "            con otros locatarios para mejorar precio de venta.\n";
            cout << "  [Mercado] Solicita a la delegacion/municipio un programa de\n";
            cout << "            recoleccion diferenciada en tu mercado.\n";
            cout << "  [Mercado] Promueve bolsas reutilizables entre tus clientes.\n";
            cout << RESET;
            break;
    }
    // --- Informacion normativa ---
    cout << "\n" << MAGENTA << NEGRITA << "  Informacion normativa:\n" << RESET;
    cout << MAGENTA;
    cout << "  * NOM-161-SEMARNAT-2011: establecimientos comerciales que generen\n";
    cout << "    10 o mas toneladas/anio de residuos PET deben tener un Plan de\n";
    cout << "    Manejo registrado ante SEMARNAT (DOF, 01 Feb 2013).\n";
    cout << "  * Equivale aproximadamente a 192 envases de 500g por semana.\n";
    cout << "  * Incumplir puede derivar en multas de 20 a 50,000 dias de salario\n";
    cout << "    minimo (Art. 135 LGPGIR).\n";
    cout << RESET;
}
// Funcion: verificar y alertar limite de PET por tipo
void verificarLimitePET(int tipo, double petUtilizadoDia, double petDesperdiciado,
                        double petUtilizadoSemana, int diasOperados) {
    double limiteDiario, limiteSemanal;
    string nombreTipo;
    switch (tipo) {
        case 1:
            limiteDiario   = LIMITE_DIARIO_COMIDA;
            limiteSemanal  = LIMITE_SEMANAL_COMIDA;
            nombreTipo     = "comida";
            break;
        case 2:
            limiteDiario   = LIMITE_DIARIO_TIENDA;
            limiteSemanal  = LIMITE_SEMANAL_TIENDA;
            nombreTipo     = "tienda";
            break;
        default:
            limiteDiario   = LIMITE_DIARIO_MERCADO;
            limiteSemanal  = LIMITE_SEMANAL_MERCADO;
            nombreTipo     = "mercado";
            break;
    }
    // Alerta diaria
    if (petUtilizadoDia > limiteDiario) {
        cout << ROJO << NEGRITA
             << "    [LIMITE] PET utilizado hoy (" << petUtilizadoDia
             << " uds) supera el limite diario recomendado para "
             << nombreTipo << " (" << limiteDiario << " uds).\n"
             << RESET;
    }
    // Alerta desperdicio critico diario
    if (petDesperdiciado > (limiteDiario * 0.5)) {
        cout << AMARILLO << NEGRITA
             << "    [AVISO]  PET desperdiciado hoy es elevado. Revisa causas.\n"
             << RESET;
    }
    // Alerta semanal acumulada (solo si ya hay datos)
    if (petUtilizadoSemana > limiteSemanal) {
        cout << ROJO << NEGRITA
             << "    [LIMITE SEMANAL] Acumulado semanal (" << petUtilizadoSemana
             << " uds) ya supero el limite semanal para "
             << nombreTipo << " (" << limiteSemanal << " uds).\n"
             << RESET;
    }
}
int main() {
    cout << fixed << setprecision(2);
    // Pantalla de bienvenida
    cout << "\n" << BG_AZUL << BLANCO << NEGRITA;
    cout << "   SISTEMA DE CONTROL DE CONTAMINACION PET   ";
    cout << RESET << "\n";
    cout << CIAN << "  Registro de establecimientos y calculo de residuos\n" << RESET;
    cout << AMARILLO << "  Version 3.0 - Limites NOM-161 y consejos de mejora\n" << RESET;
    cout << "\n";
    // Variables globales
    int    totalEstablecimientos      = 0;
    int    totalReportes              = 0;
    double grandTotalPetUtilizado     = 0.0;
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
        // Tipo de establecimiento
        int  tipoEstablecimiento = 0;
        bool tipoValido = false;
        while (!tipoValido) {
            cout << "\n" << NEGRITA << CIAN << "Tipo de establecimiento:\n" << RESET;
            cout << AMARILLO << "  [1]" << RESET << " Establecimiento de comida"
                 << AZUL << " (limite: " << LIMITE_SEMANAL_COMIDA << " uds/sem)\n" << RESET;
            cout << AMARILLO << "  [2]" << RESET << " Tienda convencional     "
                 << AZUL << " (limite: " << LIMITE_SEMANAL_TIENDA << " uds/sem)\n" << RESET;
            cout << AMARILLO << "  [3]" << RESET << " Mercado                 "
                 << AZUL << " (limite: " << LIMITE_SEMANAL_MERCADO << " uds/sem)\n" << RESET;
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
        double limiteSemanalTipo, limiteDiarioTipo;
        switch (tipoEstablecimiento) {
            case 1:
                nombreTipo       = "Establecimiento de comida";
                limiteSemanalTipo = LIMITE_SEMANAL_COMIDA;
                limiteDiarioTipo  = LIMITE_DIARIO_COMIDA;
                totalComida++;
                break;
            case 2:
                nombreTipo       = "Tienda convencional";
                limiteSemanalTipo = LIMITE_SEMANAL_TIENDA;
                limiteDiarioTipo  = LIMITE_DIARIO_TIENDA;
                totalTienda++;
                break;
            case 3:
                nombreTipo       = "Mercado";
                limiteSemanalTipo = LIMITE_SEMANAL_MERCADO;
                limiteDiarioTipo  = LIMITE_DIARIO_MERCADO;
                totalMercado++;
                break;
        }
        cout << VERDE << "  Tipo registrado: " << NEGRITA << nombreTipo << RESET << "\n";
        cout << AZUL  << "  Limite semanal : " << limiteSemanalTipo << " uds  |  "
             << "Limite diario: " << limiteDiarioTipo << " uds\n" << RESET;
        cout << MAGENTA << "  (Referencia: NOM-161-SEMARNAT-2011)\n" << RESET;
        // Dias de operacion
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
        // Horario personalizado
        int horaInicio = 0;
        int horaFin = 0;
        bool horarioValido = false;
        cout << "\n" << NEGRITA << CIAN << "Horario personalizado del establecimiento:\n" << RESET;
        while (!horarioValido) {
            cout << AMARILLO << "  Hora de inicio (0-23): " << RESET;
            cin >> horaInicio;
            if (cin.fail() || horaInicio < 0 || horaInicio > 23) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << ROJO << "  [!] Ingrese una hora valida (0-23).\n" << RESET;
                horaInicio = -1;
                continue;
            }
            cout << AMARILLO << "  Hora de cierre (0-23): " << RESET;
            cin >> horaFin;
            if (cin.fail() || horaFin < 0 || horaFin > 23) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << ROJO << "  [!] Ingrese una hora valida (0-23).\n" << RESET;
                horaFin = -1;
                continue;
            }
            if (horaInicio == horaFin) {
                cout << ROJO << "  [!] La hora de cierre no puede ser igual a la de inicio.\n" << RESET;
                horaInicio = -1;
                horaFin = -1;
                continue;
            }
            horarioValido = true;
        }
        // Calcular turno basado en horario
        string nombreTurno;
        if (horaFin < horaInicio) {
            // Caso nocturno (ej: 22:00 - 06:00)
            nombreTurno = "Nocturno";
        } else if (horaInicio >= 6 && horaInicio < 12 && horaFin <= 14) {
            nombreTurno = "Matutino";
        } else if (horaInicio >= 12 && horaInicio < 17 && horaFin <= 22) {
            nombreTurno = "Vespertino";
        } else if ((horaFin - horaInicio) >= 16) {
            nombreTurno = "Tiempo completo";
        } else {
            nombreTurno = "Turno mixto";
        }
        cout << VERDE << "  Horario registrado: " << NEGRITA << horaInicio << ":00 - " 
             << horaFin << ":00" << RESET << "\n";
        cout << VERDE << "  Turno calculado: " << NEGRITA << nombreTurno << RESET << "\n";
        // Captura diaria de PET
        double petUtilizadoSemana      = 0.0;
        double petDesperdiaciadoSemana = 0.0;
        double petMaxDia    = 0.0;
        double petMinDia    = -1.0;
        vector<int> diasMayorDesperdicio;
        double mayorDesperdicio    = 0.0;
        int    diasSuperanLimite   = 0;
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
                } else if (petDiaUtilizado > limiteDiarioTipo) {
                    cout << ROJO << "    [!] La cantidad utilizada (" << petDiaUtilizado
                         << " uds) supera el limite diario permitido (" << limiteDiarioTipo
                         << " uds). La cantidad es incorrecta. Ingrese un valor valido.\n" << RESET;
                    petDiaUtilizado = -1.0;
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
                } else if (petDiaDesperdiciado > limiteDiarioTipo) {
                    cout << ROJO << "    [!] El desperdicio (" << petDiaDesperdiciado
                         << " uds) supera el limite diario permitido (" << limiteDiarioTipo
                         << " uds). La cantidad es incorrecta.\n" << RESET;
                    petDiaDesperdiciado = -1.0;
                }
            }
            // Acumulados antes de verificar limite semanal
            petUtilizadoSemana      += petDiaUtilizado;
            petDesperdiaciadoSemana += petDiaDesperdiciado;
            // --- VERIFICACION DE LIMITES ---
            verificarLimitePET(tipoEstablecimiento, petDiaUtilizado, petDiaDesperdiciado,
                               petUtilizadoSemana, dia);
            if (petDiaUtilizado > limiteDiarioTipo) diasSuperanLimite++;
            // Estadisticas del dia
            double pctDia = (petDiaUtilizado > 0)
                            ? (petDiaDesperdiciado / petDiaUtilizado) * 100.0
                            : 0.0;
            // Barra visual
            int barras = (int)(pctDia / 5);
            cout << "    Estado del dia: [";
            for (int b = 0; b < 20; b++) {
                if (b < barras)
                    cout << ROJO << "|" << RESET;
                else
                    cout << VERDE << "|" << RESET;
            }
            cout << "] " << AMARILLO << pctDia << "% desperdicio\n" << RESET;
            // Alerta desperdicio >50%
            if (pctDia > 50.0) {
                cout << ROJO << NEGRITA
                     << "    [ALERTA] Desperdicio critico este dia (>50%)\n"
                     << RESET;
            }
            // Max y min
            if (petDiaUtilizado > petMaxDia) petMaxDia = petDiaUtilizado;
            if (petMinDia < 0 || petDiaUtilizado < petMinDia) petMinDia = petDiaUtilizado;
            if (petDiaDesperdiciado > mayorDesperdicio) {
                mayorDesperdicio = petDiaDesperdiciado;
                diasMayorDesperdicio.clear();
                diasMayorDesperdicio.push_back(dia);
            } else if (petDiaDesperdiciado == mayorDesperdicio && mayorDesperdicio > 0) {
                diasMayorDesperdicio.push_back(dia);
            }
        }
        // Calculos semanales
        double petAprovechadoSemana      = petUtilizadoSemana - petDesperdiaciadoSemana;
        double porcentajeContaminacion   = 0.0;
        double porcentajeAprovechamiento = 0.0;
        if (petUtilizadoSemana > 0) {
            porcentajeContaminacion   = (petDesperdiaciadoSemana / petUtilizadoSemana) * 100.0;
            porcentajeAprovechamiento = (petAprovechadoSemana    / petUtilizadoSemana) * 100.0;
        }
        double promedioDiarioUtilizado    = petUtilizadoSemana    / diasSemana;
        double promedioDiarioDesperdiciado = petDesperdiaciadoSemana / diasSemana;
        // Clasificacion nivel
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
        // ===================== REPORTE =====================
        cout << "\n" << BG_VERDE << BLANCO << NEGRITA;
        cout << "  REPORTE: " << nombreEstablecimiento << "  ";
        cout << RESET << "\n";
        cout << NEGRITA << BLANCO << "  Tipo          : " << RESET << nombreTipo  << "\n";
        cout << NEGRITA << BLANCO << "  Turno         : " << RESET << nombreTurno << "\n";
        cout << NEGRITA << BLANCO << "  Dias operados : " << RESET << diasSemana << " dia(s)\n";
        cout << "\n" << NEGRITA << CIAN << "  Limites de uso (NOM-161-SEMARNAT-2011):\n" << RESET;
        cout << "  Limite semanal recomendado: " << AZUL  << limiteSemanalTipo << " uds\n" << RESET;
        cout << "  Limite diario recomendado : " << AZUL  << limiteDiarioTipo  << " uds\n" << RESET;
        cout << "  Dias que superaron limite : ";
        if (diasSuperanLimite == 0)
            cout << VERDE << "Ninguno\n" << RESET;
        else
            cout << ROJO << NEGRITA << diasSuperanLimite << " dia(s)\n" << RESET;
        // Estado semanal vs limite
        cout << "  Estado vs limite semanal  : ";
        if (petUtilizadoSemana <= limiteSemanalTipo)
            cout << VERDE << NEGRITA << "DENTRO DEL LIMITE (" << petUtilizadoSemana
                 << "/" << limiteSemanalTipo << ")\n" << RESET;
        else
            cout << ROJO << NEGRITA << "SUPERA EL LIMITE (" << petUtilizadoSemana
                 << "/" << limiteSemanalTipo << ")\n" << RESET;
        cout << "\n" << NEGRITA << CIAN << "  Resumen semanal de PET:\n" << RESET;
        cout << "  PET utilizado total       : " << VERDE  << NEGRITA << petUtilizadoSemana      << " uds\n" << RESET;
        cout << "  PET desperdiciado total   : " << ROJO   << NEGRITA << petDesperdiaciadoSemana << " uds\n" << RESET;
        cout << "  PET aprovechado total     : " << VERDE  << petAprovechadoSemana               << " uds\n" << RESET;
        cout << "\n" << NEGRITA << CIAN << "  Promedios diarios:\n" << RESET;
        cout << "  Promedio utilizado/dia    : " << AZUL    << promedioDiarioUtilizado    << " uds\n" << RESET;
        cout << "  Promedio desperdiciado/dia: " << AMARILLO << promedioDiarioDesperdiciado << " uds\n" << RESET;
        cout << "\n" << NEGRITA << CIAN << "  Estadisticas:\n" << RESET;
        cout << "  Dias mayor desperdicio    : " << AMARILLO;
        for (int i = 0; i < diasMayorDesperdicio.size(); i++) {
            if (i > 0) cout << ", ";
            cout << "Dia " << diasMayorDesperdicio[i];
        }
        cout << " (" << mayorDesperdicio << " uds)\n" << RESET;
        cout << "  Max PET utilizado en dia  : " << VERDE   << petMaxDia << " uds\n" << RESET;
        cout << "  Min PET utilizado en dia  : " << AZUL    << petMinDia << " uds\n" << RESET;
        cout << "\n" << NEGRITA << CIAN << "  Indicadores:\n" << RESET;
        cout << "  % Contaminacion por semana: " << colorNivel << NEGRITA << porcentajeContaminacion << "%" << RESET << "\n";
        cout << "  % Aprovechamiento         : " << VERDE  << porcentajeAprovechamiento << "%\n" << RESET;
        cout << "  Nivel de contaminacion    : " << colorNivel << NEGRITA << nivelContaminacion << "\n" << RESET;
        // Barra global
        int barrasTotal = (int)(porcentajeContaminacion / 5);
        cout << "\n  Contaminacion semanal: [";
        for (int b = 0; b < 20; b++) {
            if (b < barrasTotal)
                cout << ROJO << "|" << RESET;
            else
                cout << VERDE << "|" << RESET;
        }
        cout << "] " << colorNivel << NEGRITA << porcentajeContaminacion << "%\n" << RESET;
        // ===================== CONSEJOS =====================
        mostrarConsejos(tipoEstablecimiento, porcentajeContaminacion);
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
    // ===================== REPORTE FINAL =====================
    double porcentajeFinalContaminacion   = 0.0;
    double porcentajeFinalAprovechamiento = 0.0;
    double petRecuperableFinal = grandTotalPetUtilizado - grandTotalPetDesperdiciado;
    if (grandTotalPetUtilizado > 0) {
        porcentajeFinalContaminacion   = (grandTotalPetDesperdiciado / grandTotalPetUtilizado) * 100.0;
        porcentajeFinalAprovechamiento = (petRecuperableFinal        / grandTotalPetUtilizado) * 100.0;
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
    // Consejo final global
    if (porcentajeFinalContaminacion >= 20.0) {
        cout << "\n" << BG_AMARILLO << BLANCO << NEGRITA;
        cout << "  ACCION GLOBAL RECOMENDADA  ";
        cout << RESET << "\n";
        if (porcentajeFinalContaminacion < 50.0) {
            cout << AMARILLO << "  Implementa un programa de separacion de residuos en todos\n";
            cout << "  los establecimientos registrados para bajar al nivel BAJO.\n" << RESET;
        } else {
            cout << ROJO << "  Contacta a un gestor de residuos autorizado por SEMARNAT.\n";
            cout << "  La situacion actual puede generar obligaciones legales bajo\n";
            cout << "  la NOM-161-SEMARNAT-2011 y la LGPGIR.\n" << RESET;
        }
    }
    cout << "\n" << BG_AZUL << BLANCO << NEGRITA;
    cout << "   Fin del programa. Gracias, " << nombreEncargado << "!   ";
    cout << RESET << "\n\n";
    return 0;
}
