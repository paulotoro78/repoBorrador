/*Creacion de carpeta de log*/

public FrmAsistencia()
{
    InitializeComponent();
    this.Load += new EventHandler(FrmAsistencia_Load);
    CheckForIllegalCrossThreadCalls = false;

    /*JUSTO AQUI SE COPIA Y PEGA LO SIGUIENTE*/

    // =========================================
    // CREAR CARPETA LOGS EN BIN
    // =========================================
    try
    {
        string baseDir = AppDomain.CurrentDomain.BaseDirectory;
        string carpetaLogs = Path.Combine(baseDir, "logs");

        if (!Directory.Exists(carpetaLogs))
            Directory.CreateDirectory(carpetaLogs);
    }
    catch (Exception ex)
    {
        System.Diagnostics.Debug.WriteLine("Error creando carpeta logs: " + ex.Message);
    }

    /*Y AQUI TERMINA LO PEGADO*/

    ImprimirLog("Iniciando programa...");

//------------------------------------------------------//

/*SIGUIENTE PASO
BUSCA Y REEMPLAZA EL SIGUIENTE CODIGO
*/

private void ImprimirLog(string mensaje)
{
    string texto = $"{DateTime.Now:HH:mm:ss} [DEBUG] {mensaje}";
    System.Diagnostics.Debug.WriteLine(texto);
    Console.WriteLine(texto);
}

/*reemplazalo todo con lo siguiente*/
private readonly object _logFileLock = new object();

private void ImprimirLog(string mensaje)
{
    string linea = $"{DateTime.Now:yyyy-MM-dd HH:mm:ss.fff} [DEBUG] {mensaje}";

    // Mostrar en Output (como antes)
    System.Diagnostics.Debug.WriteLine(linea);
    Console.WriteLine(linea);

    try
    {
        string baseDir = AppDomain.CurrentDomain.BaseDirectory;
        string carpetaLogs = Path.Combine(baseDir, "logs");
        string archivo = Path.Combine(carpetaLogs, $"log_{DateTime.Now:yyyy-MM-dd}.txt");

        lock (_logFileLock)
        {
            using (StreamWriter sw = new StreamWriter(archivo, true))
            {
                sw.WriteLine(linea);
            }
        }
    }
    catch (Exception ex)
    {
        System.Diagnostics.Debug.WriteLine("Error escribiendo log: " + ex.Message);
    }
}

/*IMPORTANTE

Elimina si tienes arriba algo como:

---private static readonly object _lockLog = new object();

Porque ahora estamos usando:

---private readonly object _logFileLock = new object();

No necesitas los dos.*/

