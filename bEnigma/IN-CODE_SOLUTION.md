# In-Code solutions
## Rotor
Each letter has its own number, which is its index in the alphabet (starting from 0). During the process, the signal is represented by an index, which changes each time it passes through the reflector, switchboard, or a rotor. After modifications, this index will indicate the resulting letter.

According to the English alphabet, both sides of the rotors have 26 positions. The rotor gates are integer pairs, establishing a bidirectional connection between the two alphabets at the front and back positions. When the signal reaches the rotor, the gate (indexed by the signal) will add its own number to the index, resulting in the next index, which corresponds to the position connected on the opposite side of the rotor.

e.g.:
```txt
Letters:
    A    B    C    D    E    F    G    H    I    J    K    L    M    N    O    P    Q    R    S    T    U    V    W    X    Y    Z
Indexes:
    0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25
Gates:
{F  4,   9,  10,   2,   7,   1,  -3,   9,  13,  16,   3,   8,   2,   9,  10,  -8,   7,   3,   0,  -4, -20, -13, -21,  -6, -22, -16}
{B 20,  21,  22,   3,  -4,  -2,  -1,   8,  13,  16,  -9,  -7, -10,  -3,  -2,   4,  -9,   6,   0,  -8,  -3, -13,  -9,  -7, -10, -16}
    0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25
    A    B    C    D    E    F    G    H    I    J    K    L    M    N    O    P    Q    R    S    T    U    V    W    X    Y    Z
```
*Let the input letter be A, then the index will be 0. If the signal arrives from the front gate's number, and the position at index 0 is 4, (0 + 4 = 4), the resulting position is 4, which is equal to the index of letter E (Output is E). If the signal reaches this rotor at position 4 (letter E) from the backward direction (4 - 4 = 0), the result will be position 0 (letter A).*

## Rotation
To implement the rotation of the rotors, each one has a ```RInt rotation``` attribute. At start it is 0 and with every turn it changes. In the proccess this integer will be substracted from the index befor it reach the gates. After passing through the gatesfor correction will be added to after passing through the gates.

e.g.:
```txt
    A    B    C    D    E    F    G    H    I    J    K    L    M    N    O    P    Q    R    S    T    U    V    W    X    Y    Z
                                                    <--(rotation by 1)
   (B    C    D    E    F    G    H    I    J    K    L    M    N    O    P    Q    R    S    T    U    V    W    X    Y    Z    A)
    0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25

{   4,   9,  10,   2,   7,   1,  -3,   9,  13,  16,   3,   8,   2,   9,  10,  -8,   7,   3,   0,  -4, -20, -13, -21,  -6, -22, -16}
{  20,  21,  22,   3,  -4,  -2,  -1,   8,  13,  16,  -9,  -7, -10,  -3,  -2,   4,  -9,   6,   0,  -8,  -3, -13,  -9,  -7, -10, -16}

    0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25
   (B    C    D    E    F    G    H    I    J    K    L    M    N    O    P    Q    R    S    T    U    V    W    X    Y    Z    A)
                                                       (correction by 1)-->
    A    B    C    D    E    F    G    H    I    J    K    L    M    N    O    P    Q    R    S    T    U    V    W    X    Y    Z
```
*In this example, the rotation is 1, and let the input letter be Y (index is 24). After rotation, the index is (24-1=) 23. Next is passing through the gates at position 23 (23-6=17), then finishing with correction (17+1=18). The result is position 18 (letter S).*

### ResidueInt 

The RInt class is created to facilitate the implementation of rotor rotation by representing an element of the set of residues modulo n. The ```int modulus``` attribute is used to define the set of residues modulo ```modulus``` that the RInt number is an element of, and the ```RIntType type``` is used to specify the sign of the set.
| Type          | Interval (mod n) |
|---------------|------------------|
|```POSITIVE``` |[0, n-1]          |
|```NEGATIVE``` |[-n+1, 0]         |
|```FULLRANGE```|[-n+1, n-1]       |
