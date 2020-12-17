import socket
import sys


# Create a Socket ( connect two computers )
def create_socket():
    try:
        global host
        global port
        global s
        host = ""
        port = 9999
        s = socket.socket()

    except socket.error as msg:
        print("[SERVER CREATION ERROR]" + str(msg))

# Binding the socket and Listening for connection
def bind_socket():
    try:
        global host
        global port
        global s
        print("Binding the port", port)
        s.bind((host, port))
        s.listen(5)

    except socket.error as msg:
        print("[SERVER BINDING ERROR]" + str(msg) +"\n" + "Returning...")
        bind_socket()

# Establishing connection with a client ( socket must be listening )

def socket_accept():
    connection, address = s.accept()
    print("CONNECTION ESTABLISHED"," IP : ",address[0], " PORT : ",address[1])
    send_command(connection)
    connection.close()

# Send command to client
def send_command(connection : str):
    connect_high = True
    while connect_high:
        cmd = input()
        if cmd == 'q':
            connection.close()
            s.close()
            sys.exit()
        if len(str.encode(cmd)) > 0:
            connection.send(str.encode(cmd))
            client_response = str(connection.recv(1024),"utf-8")
            print(client_response, end="")


if __name__ == '__main__':
    create_socket()
    bind_socket()
    socket_accept()