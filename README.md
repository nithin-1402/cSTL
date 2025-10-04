# cSTL
**cSTL** is a **header-only Standard Template Library for C**, providing common data structures and algorithms with **type safety**, **static memory support (zero runtime allocation)**, and support for **dynamic allocation**.

## How to use
Simply copy the headers to your project :)  
Or, you can install the headers system wide to use it across all projects.

## Supported Data structures and Algorithms
Currently, the following data structures are supported:  
1. Array
2. Stack
3. Queue

And the following algorithms:  
1. Search
2. Sort
3. Min/Max (using sort)

And by extension, using array algorithms 
1. Sets
2. Dictionary
3. Map

Each of these data structures use user-provided buffers or statically allocated buffers (**no malloc**)

Support for both static and dynamic arrays is planned soon, along with Queues, Linked Lists, Heaps and heap based set, dictionary and map.

## Documentation
- Detailed API documentation is available in the `documentation/` folder.
- Example usage for each data structure is in the `examples/` folder.

## Issues and Contributions
**cSTL** is an **open-source** project. Feedback and Contributions of all kinds are highly appreciated - whether it's bug fixes, new features, examples, or documentation improvement.
