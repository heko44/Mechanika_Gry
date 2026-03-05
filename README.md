Console RPG Engine (Modern C++)
I built this text-based RPG project from scratch to get comfortable with modern C++, memory management, and object-oriented design. While it plays like a classic terminal game, the main focus was on building a clean, scalable backend architecture capable of handling complex game states, procedural generation, and data serialization.

Smart Memory Management: The entire project heavily relies on modern C++ memory semantics. I avoided raw pointers and manual memory management entirely, utilizing std::unique_ptr for entities/map grids and std::shared_ptr for items and inventory management to prevent memory leaks.

Deep OOP Architecture: The system uses a solid inheritance tree. Both Entity (Player, Goblin) and Item (Weapon, Armor, Consumable) act as abstract base classes. This allows for clean polymorphism, especially in the inventory system where different item types are handled through a unified interface.

Procedural Map Generation: Instead of hardcoding maps, the terrain is generated procedurally. It uses a cellular automaton approach (similar to Conway's Game of Life) – the map initializes randomly, and then a transform() function counts neighboring cell types to organically form fields, bushes, and trees.

Custom Serialization (Save/Load): I wrote a custom parser to save and load the game state. It serializes player stats, map coordinates, nested inventory stacks, and enemy locations into local .dat files using file streams and the <filesystem> library.

Complex Inventory Logic: The inventory isn't just a simple array. It handles stackable and unstackable items dynamically, calculates protection/damage multipliers, and updates entity stats on the fly when items are equipped or consumed.
