
## Monte Carlo Numerical Simulation of the 3-State Potts Model in D=2 Dimensions

This repository provides the source code for the numerical simulation of the **3-state Potts model** on a 2D square lattice, based on a **Markov Chain Monte Carlo (MCMC)** algorithm.

### Model Description
The system consists of a 2D square lattice of classical spins that can take three possible outcomes ($q = 0, 1, 2$). The spin values are updated at every step of the Markov Chain using a local **Metropolis algorithm** to simulate the thermal equilibrium of the system.

### Prerequisites
*   **Compiler:** A C compiler (e.g., `gcc`).
*   **Build Tool:** `make` (Linux/MacOS) or `mingw32-make` (Windows).
*   **Environment:** Windows users should use a **Git Bash** terminal with the **MinGW-w64** compiler suite for the best experience.

### Input Files
To run a simulation, the executable requires two files located in the `input/` directory:
1.  **`randomseed`**: Contains the seed for the random number generator (a negative integer or a small block of integers).
2.  **`params.dat`**: Defines the system configuration (lattice size, temperature, etc.) and Monte Carlo parameters (number of measures, decorrelation steps, etc.).

*Template examples are provided in the `input/` folder.*

### Compilation and Execution
This project includes a **Makefile** to automate the build process, organizing object files into `obj/` and the final executable into `bin/`.

### Output and Data Analysis
The outcome of the simulation are saved in a new folder called `output/`, which comprises of two files: a **`lattice.dat`** file, containing the spin configuration of the last step of the Markov Chain, and a **`measures.dat`** file, with the measures of the magnetization and energy density computed once every `i_decorrel` steps of the Markov Chain. Specifically, the latter file has four columns representing, respectively, the **real value**, the **imaginary value**, and the **absolute value** of the magnetization density, and **energy density** of the system evaluated at a given Markov Chain step.

#### Linux / Unix / MacOS / Git Bash:
To compile the code:
```bash
make

