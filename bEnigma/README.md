# bEnigma

Enigma was a German invention, a monoalphabetic coder-decoder machine used during WW2. The bEnigma project's challenge is to create a code that simulates the operating principle of Enigma. 

**Warning:**  
I did not find all the information needed to perfectly duplicate the Enigma (e.g.: direction of the rotors' rotation). Because of that, only the method is the same, and the result could be different from the originals.

## Usage
While Enigma was a physical machine, bEnigma is a code that requires menus and modes to have setting features. bEnigma has the following states:
- ```MAIN_MENU``` (Default)
- ```CRYPTING```
- ```MAIN_SETTINGS```
- ```ROTOR_SETTINGS```
- ```SWITCHBOARD_SETTINGS```
- ```EXIT```

### Mode Switchers
For easier and faster navigation, there are built-in mode switchers, which can change the machine's state instantly.
- ```#1```: Start ```CRYPTING```
- ```#2```: Open ```MAIN_SETTINGS```
- ```#3```: ```EXIT```
- ```#4```: Return to ```MAIN_MENU```
These can be used in any state at any time.

### CRYPTING mode
Opens from ```MAIN_MENU``` or ```#1```. In this state, you can enter your message(s), and after leaving ```CRYPTING``` mode or ```EXIT```, the result will appear in the Enigma_result.txt file in the same folder where you execute the code.

### Settings
Opens from ```MAIN_MENU``` or ```#2```. All of the settings can be accessed from this menu. ```ROTOR_SETTINGS``` and ```SWITCHBOARD_SETTINGS``` menus open from here.

### EXIT options
To exit, you can navigate to the ```MAIN_MENU``` or use ```#3```. Both ways are correct and will not cause any errors.

## How did Enigma work?
The Enigma machines were based on a complex system of circuits, and the main parts included a keyboard, switchboard, rotors, reflector, and indicator lights. The (de)coding process is as follows:
```txt
keyboard (input) -> switchboard -> rotors (forward) -> relector -> rotors (backward) -> switchboard -> indicator lights (output)
```

### Input and Output
Keyboard is the input source, all path starts here and indicator lights are responsible for ouptut information. Each letter of the keyboard has their own indicator light. If you type in A (A button on keyboard) and the machine code it to H, then the light of H will flash up.

### Rotors
The rotors were the rotating components of the Enigma. With every key press, they moved forward one step, changing the signal's path and thus the output. However, while the path changes due to rotations, the order of connections or gates (as I referred to them in the code) between the two sides of the rotor did not change. There were five different rotors, but only three were used in the machine at once. 

Each rotor has a marking; when this marking is reached during rotation, not only does the rotor itself continue to turn at the next step, but it also advances the next rotor by one step. Thus, the first rotor rotates every letter, the second rotates after the first rotor completes a full rotation, and the third rotates after the second rotor completes a full rotation. I referred to these marks as "notches" in the code.

### Switchboard
The switchboard, much like rotors, was responsible for converting letters to others, but it provided a way to create your own set of gates without rotation. Both the switchboard and rotors can be represented by bijective functions, but while the rotors change with each use, the switchboard remains fixed.

### Reflector
Reflector was responsible for turn the signals path back. It can also be described by a bijective function, but it did not change regardless.
