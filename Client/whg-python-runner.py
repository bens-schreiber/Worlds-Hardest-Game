import socket
import threading

# Define server host and port
HOST = '127.0.0.1'
PORT = 8080

# Define a dictionary to store level names to coordinates mapping
# Has dummy data so there is always something to respond with
# TODO: NOSQL database
coordinates_map = {
    0: {
        "0000": (900,354),
    }
}

def prune_client(client_addr) -> None:
    # Delete the client's coordinates from dictionary if port matches
    for level in coordinates_map:
        if str(client_addr[1]) in coordinates_map[level]:
            del coordinates_map[level][str(client_addr[1])]

def handle_client_disconnect(data, client_addr) -> bool:
    if not data:
        # Break the loop if no data received
        print(f"Client disconnected: {client_addr[0]}:{client_addr[1]}")
        del coordinates_map[client_addr[1]]  # Remove client's coordinates from dictionary
    return not data

def handle_client_connection(client_socket, client_addr) -> None:
    while True:
        try:
            # Receive data from the client
            data = client_socket.recv(1024).decode('utf-8')

            # Break this connection if the client disconnects
            if (handle_client_disconnect(data, client_addr)):
                break

            # Log data recieved
            print(f"Received data from {client_addr[0]}:{client_addr[1]}: {data}")

            # Data comes in the form level (int), x (float), y (float)
            # Extract level name and coordinates from data
            level, x, y = map(float, data.split(','))
            level = int(level)

            # Update coordinates_map with the received coordinates
            if level not in coordinates_map:
                prune_client(client_addr)
                coordinates_map[level] = {client_addr[1] : (x,y)}

            # Log stored coordinates
            print(f"Stored coordinates for {client_addr[0]}: ({x}, {y})")

            # Build response with all coordinates except the client's coordinates
            # Limit the response to first 5 coordinates
            response = " ".join([f"{v[0]},{v[1]}" for k, v in coordinates_map[level].items() if k != client_addr[1]])
            if (not response):
                response = "NULL"

            # Send the response back to the client as a comma-separated list
            client_socket.send(response.encode('utf-8'))
            print(f"Sent response to {client_addr[0]}:{client_addr[1]}: {response}")

        except socket.error as e:
            print(f"Error occurred: {e}")
            client_socket.close()

            # Delete the client's coordinates from dictionary if port matches
            prune_client(client_addr)
            break


# Create a socket object
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the host and port
server_socket.bind((HOST, PORT))

# Listen for incoming connections
server_socket.listen(1)
print(f"Server is listening on {HOST}:{PORT}...")

while True:
    # Accept incoming connection
    client_socket, client_addr = server_socket.accept()
    print(f"Client connected from {client_addr[0]}:{client_addr[1]}")

    # Start a new thread to handle the client connection
    client_thread = threading.Thread(target=handle_client_connection, args=(client_socket, client_addr))
    client_thread.start()

# Close the server socket
server_socket.close()
