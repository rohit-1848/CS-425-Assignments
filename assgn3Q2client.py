'''
Run the code using the command: python assgn3Q2client.py
Make sure that the server code (assgn3Q2server.py) is running before executing the client code. 
The client will prompt the user to enter a datagram, which will be sent to the server. 
The server will reverse the input string and send it back to the client, which will then display the reversed string along with the server's address. 
The user can choose to continue sending datagrams or exit the program by typing 'y' or 'n' respectively.
'''

from socket import *
serverName = 'localhost'
serverPort = 42067

clientSocket = socket(AF_INET, SOCK_DGRAM)
clientSocket.connect((serverName, serverPort))
print("Client successfully connected!")

while True:
    userChoice = input('Type y to proceed and n to exit')
    if userChoice != 'y' and userChoice != 'n':
        print("Please enter a valid choice")
        continue
    elif userChoice == 'n':
        break
    inputDatagram = input('Enter the datagram to be sent : ')
    clientSocket.sendto(inputDatagram.encode(), (serverName, serverPort))
    receivedDatagram, addr = clientSocket.recvfrom(1024)
    print(f"Reversed input string from server address {addr} is : {receivedDatagram.decode()}")

clientSocket.close()