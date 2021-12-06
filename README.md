# Liquid Growth
Members:
Ziyue Yang (ziyuey6) <br>
Yanzhen Shen (yanzhen4) <br>
Patrick Liu (pzl2) <br>

## Project Description: 
Liquid Growth is a text based productivity application that runs on the terminal. The user can interact with the application by typing commands listed in the menu. There will be a vase (in other words, a pretty container) every day for the user to manipulate (user can choose whichever vase that are available for each day). Each vase start off empty, and the user can add particles (unicoded characters) to the vase whenever the user believes he completed a task. The amount of particles will be determined by the user, based on some parameter that the user chooses. For example, if the user determined that he will work in a promodoro time table, he will add an entry after completing each 25 minutes study period. We do not limit how the user chooses to use this program (no time limit between entries). He can add 1 ~ 10 particles based on how hard he believed he worked, with 10 being the hardest and 1 the least hard. He can also choose which unicode to insert, or randomize it. However for each entry of 1 ~ 10 unicodes, the unicode will be the same; The user can also name his favorite particles and display it. The complete functionality can be seen in the menu below. 

### Algorithm:
The main algorithm-related part is the way the particles are added. We will try to make it as realistic as possible, where each particle seemingly dropped from a random place and spread across the existing particles from previous entries (see the visual demonstration below). A fun part of it is that the particles can overflow from the vase, which we believe will make the user feel proud.

### third-parties libraries: 
None besides the standard library.

### Our plan: 
Milestone 2: half done (the entire interface done) <br>
Milestone 3: fully done (finalize each detail, add documentation)

------------

### 
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
 + build m d y V >> add entry at specified day, V = vase type
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
 </pre>