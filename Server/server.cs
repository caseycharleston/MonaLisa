
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
    // represents the initial values for [camPos, headDist, targetDist, monitorSize, resolution]
    private string[] initialValues = new string[5];
    public Server(string ipAddress, int port)
    {
        IPAddress localAddress = IPAddress.Parse(ipAddress);
        tcpListener = new TcpListener(localAddress, port);
    }

    public void Start()
    {
        tcpListener.Start();
        Console.WriteLine("Server is listening for incoming connections!!...");

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
        Console.WriteLine("Now handling: '{0}'!", clientName);
        if (clientName.Equals("head")) {
            // for (int i = 0; i < 5; i++) {
            //     Console.WriteLine("Now sending message: '{0}'!", initialValues[i]);
            //     SendMessageToClient(clientName, initialValues[i]);
            // }
        }
        int initialValuesCount = 0;
        while (true) {
            try {
                string message = reader.ReadLine();
                if (string.IsNullOrEmpty(message)) {
                    continue;
                }
                Console.WriteLine("Received from '{0}': {1}", clientName, message);
                // Example client code. Shows the ability to write specific code for a client's name
                if (clientName.Equals("LisaDriver")) {
                    // initially, enter the desired values for [camPos, headDist, targetDist, monitorSize, resolution]
                    // ** LISA DRIVER MUST BE INITIALIZED FIRST FOR THE HEAD TO RECIEVE THE STARTING VALUES!**
                    // if (initialValuesCount < 5) {
                    //     Console.WriteLine("RECIEVED from '{0}': {1}", clientName, message);
                    //     initialValues[initialValuesCount] = message;
                    //     initialValuesCount++;
                    // }
                    // handle one trial
                    if (message.Equals("Sending grid number")) {
                        executeOneTrial(reader, clientName);
                    }
                }
            }
            catch (IOException) {
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

    private void getInitialParameters() {
    
    }

    public void executeOneTrial(StreamReader reader, string clientName) {
        // here take in the grid number and send it to the head client
        Console.WriteLine("got the first msg!");
        string secondMsg = reader.ReadLine();
        while (string.IsNullOrEmpty(secondMsg)) {
            Console.WriteLine("waiting!");
            secondMsg = reader.ReadLine();
        }
        Console.WriteLine("RECIEVED from '{0}': {1}", clientName, secondMsg);
        SendMessageToClient("head", "Sending grid number");
        SendMessageToClient("head", secondMsg);
        // here we will determine if its mona lisa head or regular head
        string thirdMsg = reader.ReadLine();
        while (string.IsNullOrEmpty(thirdMsg)) {
            Console.WriteLine("waiting!");
            thirdMsg = reader.ReadLine();
        }
        Console.WriteLine("RECIEVED from '{0}': {1}", clientName, thirdMsg);
        if (thirdMsg.Equals("Lisa")) {
            Console.WriteLine("will handle mona lisa");
            // send monaLisa z values and focal length computed from the 
            SendMessageToClient("head", "Lisa");
        } else {
                // send message to controller to display the regular head
            Console.WriteLine("will handle regular");
            SendMessageToClient("head", "Regular");
        }
        Console.WriteLine(""); 
    }
}
