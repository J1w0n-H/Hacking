set disassembly-flavor intel
file exploit

break main
break malloc
break free
break *main+226

define analyze_heap
    echo "\nHeap Analysis:\n"
    heap
    echo "\nChunk Details:\n"
    x/32gx $arg0
end

document analyze_heap
Analyzes heap state and chunk contents
end

run
