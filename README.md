# Chess-Ai

Initial idea is to create a simple chess 'ai' that can play at a very basic level. Choosing C++ for its object-oriented workflow, and to learn as well. The overlooked challenge of actually creating the game first will take some time
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
- Originally made an array of 64 integers representing pieces(1-6) and 0 for empty squares, then
chose  to loop through each piece and place based on their corresponding numbers

- But when I think about chess, I think of each piece as being meaningful in its own right. Not just 'something' that is instanced onto a surface.

- To solve this, Im currently trying a type based solution in combination with object id's to somehwat wrangle the objects.

