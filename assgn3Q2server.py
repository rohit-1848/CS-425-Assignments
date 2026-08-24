'''
Run the code using the command: python assgn3Q2server.py
Make sure that the client code (assgn3Q2client.py) is running before executing the server code.
The server will wait for incoming datagrams from the client. When a datagram is received,
the server will decode the datagram, reverse the input string, and send the reversed string back to the client. 
The server will also print the client's address and the received datagram for logging purposes.
The server will continue to run indefinitely, waiting for new datagrams from the client.
Hence after closing the client, the server needs to be manually closed by killing the terminal.
'''

from socket import *
serverName = 'localhost'
serverPort = 42067

serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind((serverName, serverPort))
print("Server is online!")

while True:
    receivedDatagram, addr = serverSocket.recvfrom(1024)
    decodedDatagram = receivedDatagram.decode()
    print(f"Connected to the client {addr} and received {decodedDatagram}")
    reversedDatagram = decodedDatagram[::-1]
    serverSocket.sendto(reversedDatagram.encode(), addr)