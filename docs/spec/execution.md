# Execution

## Virtual Machine

While BraneScript is a Jit first, it is useful to think of it running within a virtualized context so we don't need to worry about the end machine and can focus purely on how it works conceptually.

The main goals of BraneScript are (in order of importance): 
1. Secure runtime code loading and linking
2. Easy multithreading by default 
3. Fast, *really fast*

Most coding languages start off designed for single threaded imperative execution, and then add features to extend that paradigm to pretend to still be imperative but it's it's running "async", or you have to manually mess with locks and mutexes. This makes the bar for creating multithreaded async code quite high as you need to learn what's happening cpu, even in higher level languages the abstraction usually get's worse instead of better!

I don't think it needs to be hard though, the reason it's hard to understand is because you're trying to use a paradigm that isn't meant to represent async things, to represent async things. If you start with your design taking async into account from the beginning then you can make it easy to understand and safe, rust almost does this, they make async safe, but they don't make it easy to use.

This leads to the first major difference between BraneScript and other programming frameworks. There are no "functions" only "pipelines". 
The idea is that the main thing that we need to do in most cases is take some input data, and transform it into some output data, and while functions represent that, generally a function is expected to perform some task to completion and then return control flow to where it was called from, whereas a pipeline takes in data, and then passes it on to the next stage. It creates the mental image of passing data along in a continuous way, rather then going off, doing something, and then returning. Pipelines have no return, they just call the next stage of processing.

They also have no stack frame, since a pipeline just continues and never returns, instead they may have a local heap allocated object that stores their local data if necessary. This makes jumping between threads while preserving values super easy. 


## Intermediate Representation 

BraneScript has two planned compiled formats:

1. Human readable (json ast)
2. Binary (custom format)

The human readable format is for debugging and quick dev, while the binary format is meant for release builds 



## Instructions



## Opcode reference 


| Opcode | _0 | _1 | _2 | _3 | _4 | _5 | _6 | _7 | _8 | _9 | _A | _B | _C | _D | _E | _F |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0_ | Unreachable | Return |
| 1_ |
| 2_ |
| 3_ |
| 4_ |
| 5_ |
| 6_ |
| 7_ |
| 8_ |
| 9_ |
| A_ |
| B_ |
| C_ |
| D_ |
| E_ |
| F_ |
