# STL Mesh Analyser 
 
This repository contains a program that enables the analysis of STL (Standard Tessellation Language) files by extracting information from each individual triangle present in the mesh, including its normal vector, vertex coordinates, and the attribute byte count if provided.
In addition to the basic triangle information, the program calculates the area and contribution volume of each triangle, providing insight into the geometrical properties of the mesh.
Finally, the program calculates the total surface area by summing up the individual areas of all triangles in the mesh, and, it similarly determines the total volume of the 3D object. 

## Getting started

To run the program follow these steps:

### Compilation

To compile the code, make sure you have `make` installed, and run the following command in the source directory:

```
make
```

### Usage

After compiling the code, just run the `meshData` executable:  

```
./meshData [FILE]
```

#### Example

Because this program takes in the `.stl` file in the form a command-line argument, your input should look similar to this: 

```
./meshData test.stl
```

### Cleanup

To remove the generated file, you can simply use the following command:

```
make clean
```
