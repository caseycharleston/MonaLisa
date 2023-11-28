using System;
using System.Net.Sockets;
using System.IO;

public class UnityClient
{
    private TcpClient client;
    private NetworkStream stream;
    private StreamReader reader;
    private StreamWriter writer;

    public string ServerIP { get; private set; }
    public int ServerPort { get; private set; }
    public string ClientName { get; private set; }

    public UnityClient(string clientName)
    {
        ClientName = clientName;
    }

    public bool ConnectToServer(string serverIP, int serverPort)
    {
        ServerIP = serverIP;
        ServerPort = serverPort;

        try
        {
            client = new TcpClient(ServerIP, ServerPort);
            stream = client.GetStream();
            reader = new StreamReader(stream);
            writer = new StreamWriter(stream);

            // Send the client name to the server upon connection
            SendMessage(ClientName);

            return true;
        }
        catch (Exception e)
        {
            Console.WriteLine("Failed to connect to the server: " + e.Message);
            return false;
        }
    }

    public void SendMessage(string message)
    {
        if (writer != null)
        {
            writer.WriteLine(message + '\n');
            writer.Flush();
        }
    }
        public string ReceiveMessage()
    {
        if (reader != null)
        {
            try
            {
                string receivedMessage = reader.ReadLine();
                return receivedMessage;
            }
            catch (IOException)
            {
                Console.WriteLine("Connection lost or error occurred.");
            }
        }

        return null;
    }
}
