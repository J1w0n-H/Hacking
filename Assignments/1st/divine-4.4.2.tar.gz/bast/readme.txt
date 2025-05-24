# BAST

You can either take ‹bast› to mean ‘bitvector algebra on a stack’ or the
Egyptian cat-goddess (because it is con«cat»enative and who doesn't love a bad
pun). In any case, ‹bast› is a simple, substitution-friendly intermediate
language with explicit control flow, clear data flow and a very simple static
type system.

A ‹bast› program is an explicit control-flow graph. Edges in the CFG are
unconditional: the only information they carry is where the computation
continues – if there is more than one successor, the program is simply
non-deterministic (it continues both ways). Conditional execution is
implemented via ‹assume› instructions, which abort the active branch (but
leave others free to continue). This way, all branching (conditional
statements, loops, switches, …) is implemented uniformly. Since both
non-determinism and ‹assume› are required anyway, this significantly improves
the orthogonality of the language.

Programs in ‹bast› are simply (and statically) typed: each program (or
subprogram) has a «stack signature», which lists the types of inputs (items
removed from the stack) and outputs (items placed on the stack). However,
unlike in many other languages, in ‹bast›, a subprogram is really just an
arbitrary continuous subgraph (if nodes are taken to each only contain one
instruction). This has a whole host of interesting consequences:

 • the stack signatures of all paths between any two points A and B of any
   program must be the same,
 • as a special consequence, the effect along a loop must be a type-level
   identity (taking the loop once or twice are both paths from A to A),
 • therefore, the depth of the stack of a given program is bounded.

Clearly, if we restrict ourselves to values from finite domains, an
intermediate language like this is not Turing-complete and hence, without
further extensions, cannot reasonably work as a target for compiling C or C++
programs. However, essentially the same thing holds for LLVM sans recursion,
where Turing-completeness is achieved through «memory» operations (like
‹alloca›, ‹load›, ‹store› and so on). However, we can one-up LLVM here,
because instead of baking in a bunch of memory access instructions, we can
model memory as a domain. From the point of view of ‹bast›, a «domain» is:

 1. a data representation (either built into the interpreter or compiler, or
    implemented in terms of other domains),
 2. a set of operations in that domain:
    a. homogeneous, where all operands and all results are from the same
       domain (most scalar operations – addition, multiplication,
       comparisons, etc. all fit in here),
    b. heterogeneous, which cross domain boundaries; due to the type system,
       these must still be «monomorphic» at the type level, but of course
       nothing in principle prevents constructing sum (and product) domains

From the point of view of ‹bast›, the main requirement is that values from a
domain can be pushed onto the stack. This is assured through the data
representation part of the domain, since all values are, eventually, built out
of values that come from built-in domains.

In addition to being simply typed, it is also «linear» in the sense that every
value is examined exactly once: by the operation that removed it from the
stack. Non-destructive stack reading is not possible. This might seem like a
very severe restriction on the expressiveness of the language – but for many
types, a ‹dup› operation can be implemented, restoring non-linearity for that
particular type.

The design of the language makes many common program checks and
transformations into special cases of evaluation. There are two caveats here:

 1. when an ‹assume› cannot be proved to be unsatisfiable, we must assume that
    the program may continue,
 2. we must be prepared to deal with infinite runs (i.e. we must treat the
    computation as a graph, not as a tree).
