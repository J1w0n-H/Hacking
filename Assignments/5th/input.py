from pwn import *

# Define the offset and payload
offset = 2
payload = b'A' * offset  # Fill buffer with 'A's
payload += b'B' * (desired_length - offset)  # Adjust this as needed to reach the target size

print(payload)
