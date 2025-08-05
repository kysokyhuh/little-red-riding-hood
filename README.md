# Little Red Riding Hood Simulation

A console-based C program where Little Red Riding Hood (LRRH) automatically navigates an *n×n* grid, collects a flower, bread, and a woodsman, avoids pits and the wolf, then (if prepared) reaches Granny safely.

---

## Prerequisites

- **GCC** (or any C99-compatible compiler)  
- **Make** (optional, but recommended)  
- POSIX environment for `usleep()` (or you can use manual `waitForEnter()`)

---

## Getting Started

1. **Clone the repository**  
   ```bash
   git clone https://github.com/kysokyhuh/little-red-riding-hood.git
   cd little-red-riding-hood

## Build 

With Make (uses the provided Makefile):
make

Or compile manually:
gcc -Wall -Iheaders main.c agent.c grid.c elements.c utils.c -o main

## Run
./main

## Clean Up
make clean