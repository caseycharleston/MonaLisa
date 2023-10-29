using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Collections.Generic;
using System.Security.Permissions;
using System.Runtime.InteropServices;

// Socket Listener acts as a server and listens to the incoming
// messages on the specified port and protocol.
public class DemoServer
{
    static bool debug = true;
    static Dictionary<string, ClientInterface> clients;

    public static int Main(String[] args)
    {
        // change number to change # of clients that will connect to server
        // useful for debugging
        StartServer(2);
        return 0;
    }

    public static void StartServer(int numClients)
    {
        // Get Host IP Address that is used to establish a connection
        IPHostEntry host = Dns.GetHostEntry("localhost");
        IPAddress ipAddress = host.AddressList[0];
        IPEndPoint localEndPoint = new IPEndPoint(ipAddress, 10000);
        try {
            // Create a Socket that will use TCP protocol
            Socket server = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            server.Bind(localEndPoint);

            server.Listen(numClients);
            Console.WriteLine("Waiting for a connection...");

            clients = new Dictionary<string, ClientInterface>();

            // Load in dict of clients
            for (int i = 0; i < numClients; i++)
            {
                ClientInterface client = new ClientInterface(server.Accept());
                string name = client.ReceiveMessage();
                clients[name] = client;
                Console.WriteLine("Connected to " + name + " client");
            }

            // Main Client -> Server -> Client loop
            while (true)
            {
                // Contains unprocessed Vector3 Info
                if (debug) Console.WriteLine("receiving from calc...");
                string received = clients["calc"].ReceiveMessage();
                if (debug) Console.WriteLine("received from calc: " + received);
                // Send info to head
                clients["head"].SendMessage(received + "\0");
                if (debug) Console.WriteLine("sending to head...");

            }
        }
        catch (Exception e)
        {
            Console.WriteLine(e.ToString());
        }
        Console.WriteLine("\n Press any key to continue...");
        Console.ReadKey();
    }
}

class ClientInterface
{
    private Socket client;
    private string buffer;

    public ClientInterface(Socket client)
    {
        this.client = client;
        buffer = "";
    }
    public string ReceiveMessage()
    {
        byte[] bytes = null;
        int index = -1;
        while (index < 0)
        {
            bytes = new byte[100];
            int bytesRec = client.Receive(bytes);
            buffer += Encoding.ASCII.GetString(bytes, 0, bytesRec);
            index = buffer.IndexOf('\0');
        }
        string result = buffer.Substring(0, index);
        buffer = buffer.Substring(index + 1, buffer.Length - index - 1);
        return result;
    }

    public void SendMessage(string message)
    {
        client.Send(Encoding.ASCII.GetBytes(message));
    }
}