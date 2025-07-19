
# CPrime

CPrime is a robust and efficient prime number generator based on C, designed to compute primes up to enormous limits by utilizing advanced algorithms for optimal performance and scalability.

## Features

- Efficient prime number generation.
- Modular design with separate files for sieve logic and buffer management.
- Implemented using C and CMake for build configuration.

## Files Overview

- `main.c`: Entry point for the application.
- `Sieve.c` / `Sieve.h`: Contains the sieve algorithm for prime number generation.
- `buffer.c` / `buffer.h`: Handles data buffering operations.
- `chunk.c` / `chunk.h`: Manages chunking of data for efficient processing.
- `CMakeLists.txt`: Build configuration file for CMake.

## Getting Started

1. Clone the repository:

   ```bash
   git clone https://github.com/DataTrashHenri/CPrime.git
   ```

2. Navigate into the project directory:

   ```bash
   cd CPrime
   ```

3. Create a build directory and compile the project:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. Run the application:

   ```bash
   ./CPrime
   ```

## Usage

The application generates prime numbers up to a specified limit. Refer to the `main.c` file for configuration options. 
- `upperLimit` describes up to what numbers, primenumbers will be generated, and written to a file called `chunk.bin`.
- `bufferSize` defines how many primenumbers will be stored, before being flush to the file in one take.

## 	❗️Important Notes	❗️

### Input Number Format

The input numbers to the `sieve()` function must be displayable in the form of `4096 * k * k`, where `k` is a positive integer. This means that the upper limit of the sieve must be structured in such a way that it is divisible by 4096 and is a multiple of a square number.

### Buffer Size Requirement

The buffer size must be greater than the square root of the upper limit. This ensures the sieve algorithm has enough memory to efficiently handle the processing of large numbers.

## Contributing

Feel free to fork the repository, submit issues, and create pull requests. For major changes, please open an issue first to discuss what you would like to change.

## License

This project is licensed under the MIT License.
