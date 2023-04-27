import socket
import threading
import os

# Define server host and port
HOST = os.environ.get("HOST", "10.217.45.170")
PORT = int(os.environ.get("PORT", "8080"))

# Define a dictionary to store level names -> client -> coordinates
# TODO: NOSQL database
level_client_coordinates_map = {}

"""
Deletes the client from the level port coordinates map
"""
def prune_client(client_addr) -> None:

    # Check every level for the players previous coordinates
    for level in level_client_coordinates_map:
        if client_addr in level_client_coordinates_map[level]:
            del level_client_coordinates_map[level][client_addr]
            break

"""
When the client disconnects, (denoted by no value returned in data) prune them from the map
"""
def handle_client_disconnect(data, client_addr) -> bool:
    if not data:
        # Break the loop if no data received
        print(f"Client disconnected: {client_addr[0]}:{client_addr[1]}")
        prune_client(client_addr)
    return not data

"""
Recieve data in the form:   level, xPos, yPos
Store this data in a map filterable by level, and then by the client
Respond with all coordinate pairs (x,y) in the level
"""
def handle_client_connection(client_socket, client_addr) -> None:
    while True:
        try:
            # Receive data from the client
            data = client_socket.recv(1024).decode('utf-8')

            # Break this connection if the client disconnects
            if (handle_client_disconnect(data, client_addr)):
                break

            # Data comes in the form level (int), x (float), y (float)
            # Extract level name and coordinates from data
            level, x, y = map(float, data.split(','))
            level = int(level)

            # Add new level if not already in map
            if level not in level_client_coordinates_map:
                prune_client(client_addr)
                level_client_coordinates_map[level] = {client_addr : (x,y)}

            # Remove the clients previous level entries on a new level
            elif client_addr not in level_client_coordinates_map[level]:
                prune_client(client_addr)
            
            # Update with new coordinates
            level_client_coordinates_map[level][client_addr] = (x,y)

            # Build response with all coordinates except the client's coordinates
            # Limit the response to first 5 coordinates
            response = " ".join([f"{v[0]},{v[1]}" for k, v in level_client_coordinates_map[level].items() if k != client_addr])
            if (len(response) == 0):

                # Return an N if there is nothing in the level. Why N? Why not
                response = "N"

            # Send the response back to the client as a comma-separated list
            client_socket.send(response.encode('utf-8'))

        except socket.error as e:
            print(f"Error occurred with {client_addr[0]}:{client_addr[1]} - {e}")
            client_socket.close()

            # Delete the client's coordinates from dictionary if port matches
            prune_client(client_addr)
            break
        except:
            client_socket.send("N".encode('utf-8'))
            client_socket.close()
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
