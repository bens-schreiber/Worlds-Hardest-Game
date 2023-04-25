import socket
import threading
from itertools import islice

# Define server host and port
HOST = '127.0.0.1'
PORT = 8080

# Define a dictionary to store IP addresses to coordinates mapping
# Has dummy data so there is always something to respond with
# TODO: NOSQL database
coordinates_map = {
    "X": (900,354)
}

def handle_client_connection(client_socket, client_addr):
    while True:
        try:
            # Receive data from the client
            data = client_socket.recv(1024).decode('utf-8')
            if not data:
                # Break the loop if no data received
                print(f"Client disconnected: {client_addr[0]}:{client_addr[1]}")
                del coordinates_map[client_addr[1]] # Remove client's coordinates from dictionary
                break
            print(f"Received data from {client_addr[0]}:{client_addr[1]}: {data}")

            # Extract coordinates from data
            x, y = map(float, data.split(','))
            coordinates_map[client_addr[1]] = (x, y)
            print(f"Stored coordinates for {client_addr[0]}: ({x}, {y})")

            # Build response with all coordinates except the client's coordinates
            # First 5 only
            response = ' '.join(f"{coord[0]},{coord[1]}" for ip, coord in islice(coordinates_map.items(), 5) if ip != client_addr[1])

            # Send the response back to the client as a comma-separated list
            client_socket.send(response.encode('utf-8'))
            print(f"Sent response to {client_addr[0]}:{client_addr[1]}: {response}")

        except socket.error as e:
            print(f"Error occurred: {e}")
            client_socket.close()
            del coordinates_map[client_addr[1]] # Remove client's coordinates from dictionary
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