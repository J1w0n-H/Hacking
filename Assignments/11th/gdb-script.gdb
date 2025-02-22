set disassembly-flavor intel
set pagination off

# Break at key points
break strcmp
break main

# Run commands at strcmp
commands 1
  print (char*)$rdi
  print (char*)$rsi
  bt
  continue
end

# Start program
run wrongpass

