

Gulshan Kumar -20161082
=================

3D Game Legend of Zelda in Opengl(GLFW)
=================

### How to compile:

```
cmake CMakeLists.txt
make
```

### How to run the game:

```
./boat-race
```

### Rules of the game:

* Move the boat and kill the enemies
* Obhects are purely 3-D like barrels is in proper barrel shape, cannon ball is sphere and cannon is cylinder , ocean is 3-D cylinder.
* After scoring some points, a boss will appear who is difficult to kill
* There are rocks on the sea. Colliding with them leads to loss of health.
* You can shoot torpedos at the rocks/enemies/monsters to destroy them
* A wind may appear at certain intervals of time and it can move the boat along the wind direction
* There are barrels floating on the sea with gifts/powerups available.
* On killing a boss, you get a booster which increases your speed for some amount of time
* The game can be viewed through different camera views such as HELICOPTER, FOLLOW, BOAT , TOWER,TOP...

### Controls :
* The user can play by keyboard.
* Helicopter view can be accessed using mouse

##### Keyboard Controls

|         KEY |     ACTION |
| ----------: | ---------: |
|           f | Fire torpedo/Cannon |
|           Space |  Jump |
|    esc or q |       Quit |
|    up arrow |       Move Forward |
|  down arrow |     Move Backward |
|  left arrow |  Rotate left |
| right arrow | Rotate Right |
| V | View /Camera change |
| r | Weather change /Rain occurs |
| a | Weapon change |
| w | rotating up the cannnon |
| s | rotating  down the cannon |

### Additional Features:
* The game has audio as background sound.
* Score & Life features were implemented.
* Life bar is implemented
* Moving/Rotating canon is implemented
* Weather change is implemented.
* compass is implemented that locate the boat.
