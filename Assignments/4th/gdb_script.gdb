# Break at the start of main
break main

# Start the program and stop at the breakpoint
run

# Show memory layout for each variable after the program stops at the breakpoint
echo "Local Variables:\n"
info address local_var_1
info address local_var_2
info address local_var_3

echo "Heap-allocated Variables:\n"
info address ptr_1
info address ptr_2

echo "Global Variables (Uninitialized):\n"
info address global_uninit_var_1
info address global_uninit_var_2

echo "Static Local Variables:\n"
info address static_var_1
info address static_var_2

echo "Global Variables (Initialized):\n"
info address global_var_1
info address global_var_2

# Run a little bit further and break before the program exits
break *main+60  # Adjust this to where you want to pause before exiting main

# Continue execution until the new breakpoint
continue

# Display memory map and context information before the program exits
echo "Displaying memory map:\n"
vmmap

echo "Displaying context information:\n"
context

# Continue program execution until completion
continue

