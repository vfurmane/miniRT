# miniRT

This is my 5th project at @42Paris.

:timer_clock: : 1 month 24 days
:heavy_check_mark: : 102
:robot: : 1

## Usage

To compile the program:

```shell
make
```

To use bonus:

```shell
make bonus
```

And finally to run the program:

```shell
./miniRT scene [--save]
```

### The scene

The scene you have to pass to the program has to be formatted this way:

```
R   width:int               height:int
A   ratio:float[0.0,1.0]    color:RGB[0,255]

c   coordinates:XYZ         orientation:XYZ             fov:int[0,180]
l   coordinates:XYZ         ratio:float[0.0,1.0]        color:RGB[0,255]

sp  coordinates:XYZ         diameter:float              color:RGB[0,255]
pl  coordinates:XYZ         orientation:XYZ[-1.0,1.0]   color:RGB[0,255]
sq  coordinates:XYZ         orientation:XYZ[-1.0,1.0]   size:float          color:RGB[0,255]
cy  coordinates:XYZ         orientation:XYZ[-1.0,1.0]   diameter:float      height:float        color:RGB[0,255]
tr  point1:XYZ              point2:XYZ                  point3:XYZ          color:RGB[0,255]
```

Uppercase identifiers must be declared once. Lowercase identifiers can be declared any number of times.

| Identifier | Object                   |
| ---------- | ------------------------ |
| R          | Resolution of the window |
| A          | Ambiant light            |
| c          | Camera                   |
| l          | Light (bulb)             |
| sp         | Sphere                   |
| pl         | Plane                    |
| sq         | Square                   |
| cy         | Cylinder                 |
| tr         | Triangle                 |

## Personnal Notes

This project was really interesting on the one hand because it is our first graphics project at school and on the other hand because it uses high school mathematics such as vectors and matrices. It is not particularly complicated to make as long as you find the right resources on the Internet, and that you are not lost about the used mathematics.
