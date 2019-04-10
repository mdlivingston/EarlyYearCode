using System;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Diagnostics;
using System.IO;
using WinSCP;
using System.Collections.Generic;


namespace SignalMetricsFTP
{
    class Program
    {
        public static class MoeConnection
        {
            public static SqlConnection GetConnection()
            {
                string connectionString = ConfigurationManager.ConnectionStrings["MOE"].ConnectionString;
                SqlConnection connection = new SqlConnection(connectionString);
                return connection;
            }
        }
        static void Main(string[] args)
        {
            // local path to which data files will be downloaded
            var localPath = ConfigurationManager.AppSettings["localPath"];
            // default extension of data files 
            var dataFileExtension = ConfigurationManager.AppSettings["dataFileExtension"];
            // if provided, downloaded this day's files from controller
            // if not provided, default to yesterday's date
            var overrideDate = ConfigurationManager.AppSettings["overrideDate"]; 
            // whether or not to skip the ftp process
            var skipFtp = Convert.ToBoolean(ConfigurationManager.AppSettings["skipFtp"]);
            // whether or not to skip the database insert process
            var skipDatabaseInserts = Convert.ToBoolean(ConfigurationManager.AppSettings["skipDatabaseInserts"]);
            // number of insert commands to bundle up before performing them in the database
            var bulkCommandCount = Convert.ToInt32(ConfigurationManager.AppSettings["bulkCommandCount"]);

            var now = DateTime.Now;
            var currentDateTimeForFileName = $"{now.Year}{now.Month:D2}{now.Day:D2}{now.Hour:D2}{now.Minute:D2}{now.Second:D2}{now.Millisecond}";
            using (var logFile = File.AppendText($"{localPath}\\logs\\ftpLog.{currentDateTimeForFileName}.txt"))
            {
                logFile.WriteLine($"Started FTP process at {DateTime.Now}");

                // Get the list of controller from which to FTP files
                var config = ControllerSection.GetConfig();

                if (!skipFtp)
                {
                    foreach (ControllerElement controller in config.Controllers)
                    {
                        Session session = new Session();
                        SessionOptions sessionOptions = new SessionOptions();

                        var pPath = $"{localPath}\\PrivateKeys.ppk";
                        var numberRetries = 0;
                        var connected = false;

                        // Will retry FTP'ing 3 times in case of connection issues
                        while ((++numberRetries <= 3) && !connected)
                        {                           
                            try
                            {
                                // Set up session options
                                if (controller.Protocol == "ftp")
                                {
                                    sessionOptions = new SessionOptions
                                    {
                                        Protocol = Protocol.Ftp,
                                        HostName = controller.IpAddress,
                                        PortNumber = 21,
                                        UserName = controller.User,
                                        Password = controller.Pwd,                                       
                                    };
                                }
                                else
                                {                                   
                                    sessionOptions = new SessionOptions
                                    {
                                        Protocol = Protocol.Sftp,
                                        HostName = controller.IpAddress,
                                        UserName = controller.User,
                                        Password = controller.Pwd,
                                        SshHostKeyFingerprint = controller.SshFingerPrint,
                                        SshPrivateKeyPath = pPath ,
                                    };

                                    sessionOptions.AddRawSettings("FSProtocol", "2");
                                }

                                // Connect
                                session.Open(sessionOptions);
                                connected = true;
                            }
                            catch (Exception ex)
                            {
                                logFile.WriteLine($"Error connecting to {controller.Name} on attempt {numberRetries}: {ex.Message}");
                            }

                            if (connected)
                            {
                                try
                                {
                                    using (session)
                                    {
                                        if (session.FileExists(controller.RemotePath))
                                        {
                                            // Enumerate files and directories to download
                                            IEnumerable<RemoteFileInfo> remoteFiles = session.EnumerateRemoteFiles(controller.RemotePath, null, EnumerationOptions.EnumerateDirectories | EnumerationOptions.AllDirectories);

                                            var yesterday = DateTime.Today.AddDays(-1);
                                            var fileDate = (string.IsNullOrEmpty(overrideDate))
                                                ? $"{yesterday.Year}_{yesterday.Month:D2}_{yesterday.Day:D2}"
                                                : overrideDate;

                                            foreach (RemoteFileInfo file in remoteFiles)
                                            {
                                                string localFilePath = session.TranslateRemotePathToLocal(file.FullName, controller.RemotePath, $"{localPath}\\");
                                                long fileLength = 0;
                                                var numberFileRetries = 0;
                                                var filePath = $"{localPath}\\{file.Name}";

                                                // Will retry to download each individual file if we get back a 0 byte file
                                                while (++numberFileRetries <= 3 && fileLength == 0)
                                                {
                                                    if (file.IsDirectory || !file.Name.StartsWith($"{controller.FilePrefix}{fileDate}") ||
                                                        !file.Name.EndsWith(dataFileExtension) ||
                                                        (File.Exists(filePath)))
                                                    {
                                                        if (!file.Name.StartsWith($"{controller.FilePrefix}{fileDate}"))
                                                            numberFileRetries = 3;
                                                        else
                                                            logFile.WriteLine($"Skipping {filePath}");
                                                        continue;
                                                    }

                                                    // Download file
                                                    TransferOperationResult transferResult = session.GetFiles(session.EscapeFileMask(file.FullName), localFilePath);

                                                    // Did the download succeeded?
                                                    if (!transferResult.IsSuccess)
                                                    {
                                                        // Print error (but continue with other files)
                                                        logFile.WriteLine("Error downloading file {0}: {1}", file.Name, transferResult.Failures[0].Message);
                                                    }
                                                    var localFile = new FileInfo(filePath);
                                                    fileLength = localFile.Length;
                                                    logFile.WriteLine($"Transferred {filePath} - length {fileLength}");

                                                    if (fileLength == 0)
                                                    {
                                                        logFile.WriteLine($"Deleting zero length file {filePath}");
                                                        localFile.Delete();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                catch (Exception ex)
                                {
                                    logFile.WriteLine($"Error on {controller.Name}: {ex.Message}");
                                    connected = false;
                                }
                            }
                        }
                        logFile.WriteLine("Finished with FTP process.");
                    }
                }
                else
                {
                    logFile.WriteLine("Skipping the FTP process.");
                }

                if (!skipDatabaseInserts)
                {
                    logFile.WriteLine($"Started database inserts at {DateTime.Now}");

                    // Execute the external perfLogTranslate.exe file to convert each .dat file to a .csv file
                    var perfLogTranslate = new Process
                    {
                        StartInfo =
                        {
                            FileName = $"{localPath}\\perfLogTranslate.exe",
                            Arguments = " -i *.dat",
                            WorkingDirectory = localPath
                        }
                    };
                    perfLogTranslate.Start();
                    perfLogTranslate.WaitForExit();

                    Directory.SetCurrentDirectory(localPath);
                    var datDir = new DirectoryInfo(localPath);
                    var datFiles = datDir.GetFiles("*.dat");

                    foreach (var file in datFiles)
                    {
                        // If .dat file exists in old folder, replace with this one
                        var filePath = $"{localPath}\\old\\{file.Name}";
                        if (File.Exists(filePath))
                            File.Delete(filePath);

                        file.MoveTo(filePath);
                    }

                    Directory.SetCurrentDirectory(localPath);
                    var csvDir = new DirectoryInfo(localPath);
                    var csvFiles = csvDir.GetFiles("*.csv");

                    foreach (var file in csvFiles)
                    {
                        DataTable table = new DataTable();
                        table.Columns.Add("SignalId");
                        table.Columns.Add("Timestamp");
                        table.Columns.Add("EventCode");
                        table.Columns.Add("EventParam");

                        try
                        {
                            var reader = new StreamReader(file.Name);

                            string line;
                            if ((line = reader.ReadLine()) != null)
                            {
                                var parms = line.Split(',');

                                var connectedToDb = true;
                                var conn = new SqlConnection
                                {
                                    ConnectionString = ConfigurationManager.ConnectionStrings["MOE"].ToString()
                                };

                                try
                                {
                                    conn.Open();
                                }
                                catch (Exception ex)
                                {
                                    logFile.WriteLine($"Error connecting to database: {ex.Message}");
                                    connectedToDb = false;
                                }

                                if (connectedToDb)
                                {
                                    var cmd = new SqlCommand
                                    {
                                        Connection = conn,
                                        CommandText = $"select SignalID from Signals where IPAddress = '{parms[0]}'",
                                        CommandType = CommandType.Text
                                    };
                                    var signalId = cmd.ExecuteScalar();
                                    cmd.Dispose();

                                    while ((line = reader.ReadLine()) != null)
                                    {
                                        parms = line.Split(',');

                                        DataRow row = table.NewRow();
                                        row.SetField(0, signalId);
                                        row.SetField(1, parms[0]);
                                        row.SetField(2, parms[1]);
                                        row.SetField(3, parms[2]);
                                        table.Rows.Add(row);
                                    }

                                    logFile.WriteLine($"Preparing to bulk copy {table.Rows.Count} rows for signal {signalId}");
                                    try
                                    {
                                        SqlBulkCopy bulkCopy = new SqlBulkCopy(conn, SqlBulkCopyOptions.Default, null);
                                        bulkCopy.DestinationTableName = "Controller_Event_Log";
                                        bulkCopy.WriteToServer(table);
                                        logFile.WriteLine($"Bulk copy for {signalId} successful");
                                    }
                                    catch (Exception e)
                                    {
                                        logFile.WriteLine($"Error while executing bulk copy for {signalId}");
                                    }
                                    
                                    table.Dispose();

                                    reader.Close();
                                    reader.Dispose();

                                    logFile.WriteLine($"Done with {file.Name} at {DateTime.Now}");
                                    // If .csv file exists in old folder, replace with this one
                                    var filePath = $"{localPath}\\old\\{file.Name}";
                                    if (File.Exists(filePath))
                                        File.Delete(filePath);
                                    file.MoveTo(filePath);
                                }
                                else
                                {
                                    logFile.WriteLine($"Leaving {file.Name} in folder unprocessed.");
                                }

                                try
                                {
                                    conn.Close();
                                    conn.Dispose();
                                }
                                catch (Exception ex)
                                {
                                    logFile.WriteLine($"Error closing or disposing connection.");
                                }
                            }
                        }
                        catch (Exception ex)
                        {
                            logFile.WriteLine($"Error: {ex.Message}");
                        }
                    }

                    logFile.WriteLine("Finished with database inserts.");
                }
                else
                {
                    logFile.WriteLine("Skipping database inserts.");
                }

                logFile.WriteLine($"Finished at {DateTime.Now}");
            }
           
        }
    }
}
