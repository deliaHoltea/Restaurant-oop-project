# Restaurant OOP Project

This project was developed as part of the Object-Oriented Programming (OOP) course at university. The application simulates the functionality of a restaurant using object-oriented principles in C++.

## Overview

The application allows for:

- managing the inventory of raw ingredients;
- defining recipes (ingredients and quantities);
- building a menu of available products;
- placing and validating customer orders;
- generating reports based on orders;
- reading and writing data using text and binary files.

## Features

- Load raw ingredients from a text file and save them to a binary file.
- Create recipes based on existing ingredients.
- Define menu products using recipes.
- Display an interactive menu and allow user input for placing orders.
- Check stock availability before accepting an order.
- Generate client reports in the console and save them to `Rapoarte.txt`.
- Use of STL containers (`vector`, `list`, `set`) and file operations.

## Core Classes

- **MateriePrima**: Represents a raw ingredient with name and quantity.
- **Retetar**: Represents a recipe with multiple ingredients and quantities.
- **Produs**: A menu item with name, price, nutritional values, and associated recipe.
- **Meniu**: A collection of products and logic for handling customer orders.
- **Comanda**: Represents a customer order and calculates total price and preparation time.
- **Client**: Stores the customer's name and order history and generates reports.

## Input Files

### `TextFile1.txt` – Ingredients file

Each line contains the name of an ingredient and the quantity in stock, separated by a space.  
This file is read into a `set<MateriePrima>` for uniqueness and is used to initialize the central stock of ingredients.

**Example:**
```
tomatoes 100
cheese 50
ham 80
```

- `tomatoes` – ingredient name (string)
- `100` – quantity in stock (double)

### `TextFile2.txt` – Products file

Each product is defined across 6 consecutive lines:

1. Product name (string)
2. Recipe: number of ingredients followed by pairs of (ingredient_name quantity) (e.g., `2 tomatoes 50 cheese 30`)
3. Preparation time in minutes (float)
4. Product price (float)
5. Product weight in grams (float)
6. Nutritional values: calories, proteins, carbohydrates (floats)

**Example:**
```
PizzaMargherita
2 tomatoes 50 cheese 30
10
25.0
500.0
200.0 15.0 30.0
```

## How to Run

1. Compile `main.cpp` using a C++17+ compiler.
2. Place `TextFile1.txt` and `TextFile2.txt` in the working directory.
3. Run the application.
4. Enter your name when prompted and follow the console instructions to place orders.
5. Final reports will be printed in the console and saved to `Rapoarte.txt`.

## Binary File Output

The application also saves data to binary files:
- `Stoc.bin` – stores available ingredients.
- `Meniu.bin` – stores the full menu configuration.

## Requirements

- C++17 or newer
- Recommended IDE: Code::Blocks / Visual Studio / CLion
- Correctly formatted input text files

## Author

Project developed by me as part of the Object-Oriented Programming course.
