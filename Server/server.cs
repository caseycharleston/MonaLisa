using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

class Server
{
    private TcpListener tcpListener;
    private Dictionary<string, TcpClient> clients = new Dictionary<string, TcpClient>();

    public Server(string ipAddress, int port)
    {
        IPAddress localAddress = IPAddress.Parse(ipAddress);
        tcpListener = new TcpListener(localAddress, port);
    }

    public void Start()
    {
        tcpListener.Start();
        Console.WriteLine("Server is listening for incoming connections...");

        while (true)
        {
            TcpClient client = tcpListener.AcceptTcpClient();

            // Ask the client for their name
            string clientName = GetClientName(client);

            if (!string.IsNullOrEmpty(clientName) && !clients.ContainsKey(clientName))
            {
                clients.Add(clientName, client);
                Console.WriteLine("Client '{0}' connected.", clientName);

                // Start a new thread to handle this client
                Thread clientThread = new Thread(() => HandleClient(client, clientName));
                clientThread.Start();
            }
            else
            {
                Console.WriteLine("Client connection rejected. Name '{0}' is already in use.", clientName);
                client.Close();
            }
        }
    }

    private string GetClientName(TcpClient client)
    {
        NetworkStream clientStream = client.GetStream();
        StreamReader reader = new StreamReader(clientStream, Encoding.UTF8);

        string clientName = reader.ReadLine();
        return clientName;
    }

    private void HandleClient(TcpClient client, string clientName)
    {
        NetworkStream clientStream = client.GetStream();
        StreamReader reader = new StreamReader(clientStream, Encoding.UTF8);

        while (true)
        {
            try
            {
                string message = reader.ReadLine();

                if (string.IsNullOrEmpty(message))
                {
                    continue;
                }
                // Example client code. Shows the ability to write specific code for a client's name
                if (clientName.Equals("LisaDriver")) {
                    Console.WriteLine("Received from '{0}': {1}", clientName, message);
                    SendMessageToClient("head", message);
                }
            }
            catch (IOException)
            {
                break;
            }
        }

        clients.Remove(clientName);
        client.Close();
        Console.WriteLine("Client '{0}' disconnected.", clientName);
    }

    private void SendMessageToClient(string clientName, string message)
    {
        if (clients.TryGetValue(clientName, out TcpClient client))
        {
            NetworkStream clientStream = client.GetStream();
            StreamWriter writer = new StreamWriter(clientStream, Encoding.UTF8);

            writer.WriteLine(message + '\n');
            writer.Flush();
        } else {
            Console.WriteLine("Client {0} not found.", clientName);
        }
    }

    public static void Main(string[] args)
    {
        // Adjust the IP address and port as needed
        string ipAddress = "0.0.0.0";
        int port = 12345;

        Server server = new Server(ipAddress, port);
        server.Start();
    }
}
