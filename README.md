# Liquid Growth
Members:
Ziyue Yang (ziyuey6) <br>
Yanzhen Shen (yanzhen4) <br>
Patrick Liu (pzl2) <br>

## Project Description: 
Liquid Growth is a text based productivity application that runs on the terminal. The user can interact with the application by typing commands listed in the menu. There will be a vase (in other words, a pretty container) every day for the user to manipulate (user can choose whichever vase that are available for each day). Each vase start off empty, and the user can add particles (unicoded characters) to the vase whenever the user believes he completed a task. The amount of particles will be determined by the user, based on some parameter that the user chooses. For example, if the user determined that he will work in a promodoro time table, he will add an entry after completing each 25 minutes study period. We do not limit how the user chooses to use this program (no time limit between entries). He can add 1 ~ X particles based on how hard he believed he worked, with X being the hardest and 1 the least hard. He can also choose which unicode to insert, or randomize it. However for each entry of 1 ~ X unicodes, the unicode will be the same; The user can also name his favorite particles and display it. One important feature is automatic save and load between each launches, so the vases and all unicodes will not be lost after each session. The complete functionality can be seen in the menu below.

### Algorithm:
The main algorithm-related part is the way the particles are added. We will try to make it as realistic as possible, where each particle seemingly dropped from a random place and spread across the existing particles from previous entries (see the visual demonstration below). A fun part of it is that the particles can overflow from the vase, which we believe will make the user feel proud.

### third-parties libraries: 
None besides the standard library.

### Our plan: 
Milestone 2: half done (the entire interface done) <br>
SUCCEED <br>
Milestone 3: fully done (finalize each detail, add documentation) <br>
SUCCEED <br>

### How we built the project: (timeline)
We first finished the basic framework of individual vases: vase.hpp, vase.cc, main.cc, etc.
We then added the shiny.hpp and shiny.cc to store and add the unicodes. 
We then implemented all the important functions of the vase class, including the Save and Load functionalities. 
We then created the collection.hpp and collection.cc classes to enable "next vase" and "prev vase" operations.
We then added user input functionality and mapped them into our functions. 
Finally we debugged all of them and finished README.md and the test suite. 


### Test cases
To use our test suite, type in the terminal: <br>
```make tests```

## Showcase
<pre>
+----------------------------------------+
|                                        |
|                                        |
|                     ߶                  |
|                    ߶߶߶                 |
|                    ߶߶߶                 |
|                   ߶߶Ӂ߶߶                |
|                   ߶ӁӁ߶߶                |
|                  ߶߶ӁӁӁӁ߶               |
|                  ߶ϾӁӁӁӁ߶               |
|                 ߶ϾϾӁӁӁӁӁ߶߶             |
|            ⎛   ߶ϾϾϾϾӁӁӁӁ߶߶ ⎞           |
|            ‾‾|߶߶ϾϾϾϾϾӁӁӁӁ|‾‾           |
|            __|߶ϾϾϢϾϾϾϾӁӁӁ|__           |
|           ⎛   ϾϾϾϢϾϾϾϾӁӁϢ   ⎞          |
|        ⎛‾‾    ϢϢϢϢϢϾϾϾϢϢϢ    ‾‾⎞       |
|         ‾‾⎝  ϾϢϢϢϢϢϢϢϾϢƢƢϢ  ⎠‾‾        |
|            \ ϢϢƢƢƢƢƢϢϢƢƢƢƢ /           |
|             \ƢƢƢƢƢƢƢƢϢƢƢƢƢ/            |
|              ‾‾⎛ƢƢƢƢƢƢƢ⎞‾‾             |
|                 ‾‾‾‾‾‾‾                |
[Sunday] [Mood: Awesome!] [Weather: Sunny]
+--------------[12/06/2021]--------------+
| 30 Ƣ << worked on lab
| 25 Ϣ << finished lab!
| 30 Ͼ << trying out Obsidian
| 29 Ӂ << studying for CS 173 quiz
| 28 ߶ << finished studying
+----------------------------------------+
Type "help" to get a list of commands available

[Commands Available]
 + build m d y V >> add vase at specified day, V = vase type
 +                    Ex: build 12 31 2021 0
 + cd m d y      >> check vase of the day
 +                    Ex: cd 12 31 2002
 + add n # T     >> add num unicode log_text
 +                    Ex: add 10 $ Completed HW!
 + next          >> check vase of the next day
 + prev          >> check vase of the previous day
 + log @         >> add text to log.
 + mood @        >> change mood
 + weath @       >> change weather
 + undo          >> undo last entry
 + quit          >> quit the program
 </pre>

## Detailed Documentation of the Commands Available
**To start the program**, type <br>
```make```
<br><br>

**To get a help deck of all the commands available**, type <br>
```help``` or ```h```<br><br>

**To add a vase at a specified day**, type <br>
```build [month] [date] [year] [vase_type]``` <br>
We currently support two vase types, coded 0 and 1. <br>
For example, ```build 12 5 2021 0``` or ```build 9 7 2022 1``` <br><br>

**To switch to a date where a vase has already been created**, type <br>
```cd [month] [date] [year]``` <br><br>

**To add an entry (unicodes) to the vase currently showing on screen**: type <br>
```add [num_of_unicodes] [unicode] [log_text]``` <br>
For example, ```add 3 Ӂ Finished TRA! ``` <br><br>

**To check the next vase available**, type <br>
```next``` <br><br>

**To check the previous vase available**, type <br>
```prev``` <br><br>

**To change the log of the current vase**, type <br>
```log [log_text]``` <br><br>

**To change the mood of the current vase**, type <br>
```mood [mood_text]``` <br><br>

**To change the weather of the current vase**, type <br>
```weath [weather_text]``` <br><br>

**To undo last entry**, type <br>
```undo``` <br><br>

**To quit the program**, type <br>
```quit``` <br><br>


