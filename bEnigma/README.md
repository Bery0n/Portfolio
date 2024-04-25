# bEnigma

Enigma was a German invention, a monoalphabetic coder-decoder machine used during WW2. The bEnigma project's challenge is to create a code that simulates the operating principle of Enigma. 

**Warning:**  
I did not find all the information needed to perfectly duplicate the Enigma (e.g.: direction of the rotors' rotation). Because of that, only the method is the same, and the result could be different from the originals.

## Usage
While Enigma was a physical machine, bEnigma is a code that requires menus and modes to have setting features. bEnigma has the following states:
- **MAIN_MENU** (Default)
- **CRYPTING**
- **MAIN_SETTINGS**
- **ROTOR_SETTINGS**
- **SWITCHBOARD_SETTINGS**
- **EXIT**

### Mode Swithcers
For easier and faster navigation, there are built-in mode switchers, which can change the machine's state instantly.
- **#1**: Start CRYPTING
- **#2**: Open MAIN_SETTINGS
- **#3**: EXIT
- **#4**: Return to MAIN_MENU
These can be used in any state at any time.

### CRYPTING mode
Opens from MAIN_MENU or #1. In this state, you can enter your message(s), and after leaving Crypting mode or EXIT, the result will appear in the Enigma_result.txt file in the same folder where you execute the code.

### Settings
Opens from MAIN_MENU or #2. All of the settings can be accessed from this menu. ROTOR_SETTINGS and SWITCHBOARD_SETTINGS menus open from here.

### EXIT options
To exit, you can navigate to the MAIN_MENU or use #3. Both ways are correct and will not cause any errors.


