# Chess-Ai

Initial idea is to create a simple chess 'ai' that can play at a very basic level. Choosing C++ for its object-oriented workflow, and to learn as well. Will be creating the game first and setting rules for potential ai/machine learning
## Features


### Prerequisites

- A C++ 64-bit compiler (ex. GCC, Clang, MSVC)
- Simple and Fast Multimedia Library (SMFL)
- Basic make and lib linking knowledge

### Building

```mingw32-make``` ```make```

## Roadmap
- Highlight squares on click
- Place pieces in a forward thinking manner 
- Make pieces movable

## Design Choices
- Originally made an array of 64 integers representing pieces(1-6) and 0 for empty squares, then looped through each piece and placed it based on the corresponding number

- But when I think about chess, I think of each piece being meaningful or unique in its own right. Not just something that is instanced onto a surface

- To solve this, Im currently trying a type based solution in combination with object id's to wrangle the objects

