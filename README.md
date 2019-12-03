## General
____________

### Author
* Josh McIntyre

### Website
* jmcintyre.net

### Overview
* PkTime demonstrates the difficulty of brute-forcing cryptographic keys with a large enough keyspace

## Development
________________

### Git Workflow
* master for releases (merge development)
* development for bugfixes and new features

### Building
* make build
Build the utility
* make clean
Clean the build directory

### Features
* Calculate real brute force times for small keyspaces
* Calculate the average cryptographic op time for the device
* Estimate brute force times for large keyspaces

### Requirements
* Requires a terminal emulator

### Platforms
* Windows
* Linux
* MacOSX

## Usage
____________

### CLI Usage
* Run `pktime.exe` to show brute force times for various keyspace sizes
