*This project was created as part of the 42 cursus by wsilveir, mtakiyos.*

# cub3D

## Description

cub3D is a first-person maze renderer built with **raycasting**, inspired by
*Wolfenstein 3D*, the game that pioneered the genre. From a flat 2D grid it
draws a real-time 3D view: textured walls (one texture per cardinal direction)
over a solid floor and ceiling. It is written in C with the MiniLibX graphics
library and follows the 42 Norm.

Given a `.cub` scene file describing the textures, colors and map, the program
opens a window and lets you walk through the maze in first person.

Highlights:
- Raycasting with a **DDA** algorithm — exact wall hits, no fish-eye distortion
- Textured walls (N/S/E/W) and configurable floor/ceiling colors
- A live **minimap** that scrolls around the player
- Strict `.cub` parsing with clear error messages, and no memory leaks

## Instructions

Requirements: Linux, `cc`, `make`, and the X11 dev libraries MiniLibX needs
(`libxext-dev`, `libx11-dev`, `libbsd-dev`). MiniLibX and libft ship as git
submodules.

```sh
git clone --recurse-submodules <repo-url> cub3D
cd cub3D
make
./cub3D maps/valid/simple.cub
```

Controls:

| Key | Action |
| --- | --- |
| `W` / `S` | move forward / backward |
| `A` / `D` | strafe left / right |
| `←` / `→` | rotate the camera |
| `ESC` / close button | quit |

Extra make targets: `make leaks [MAP=path]` runs the program under valgrind with
the bundled suppressions; `make re`, `clean`, `fclean` behave as usual.

**Map format** (`.cub`): the header sets the four wall textures (`NO SO WE EA`)
and the floor/ceiling colors (`F` and `C`, as `R,G,B`). The map uses `1` (wall),
`0` (floor), `N/S/E/W` (player start and facing) and spaces, and must be fully
enclosed by walls. Ready-made examples live in `maps/valid/`; rejected cases (to
check error handling) live in `maps/invalid/`.

## Resources

- Lode Vandevenne — *Raycasting* tutorial, the reference for the DDA and wall
  texturing: <https://lodev.org/cgtutor/raycasting.html>
- MiniLibX documentation (42docs): <https://harm-smits.github.io/42docs/libs/minilibx>
- id Software — *Wolfenstein 3D*, the raycaster that inspired this project

### Use of AI

We used an AI assistant (Claude Code) as a pair-programming helper on specific
tasks: refactoring the raycaster to a DDA and adding wall texturing and the
floor/ceiling rendering; building the scrolling minimap; auditing and closing
memory leaks with valgrind; and bringing the parsing code up to the Norm. It was
also used to generate the test map suite in `maps/`. Every change was reviewed,
tested and committed by us.
