# Matrix-Project-Snake-Game :snake:
This project is the final exam for the robotics introduction course. For more details check this [repo](https://github.com/alexion2001/IntroductionToRobotics)

<details>
<summary><h2>THE MENU :clipboard:</h2> </summary>
<br>

> <h4>Main Menu :bookmark_tabs:</h4>

      - Start game
      - Highscore (top 5 scores)
      - Settings
      - Game info (how to play)
      - About (details about creator) 
  
> <h4>Settings submenus: 🔧 </h4>
  
      - Level difficulty (Easy, Medium, Hard)
      - LCD contrast control
      - LCD brightness control
      - Matrix brightness control
      - Sounds ON or OFF
      - Exit to main menu


</details>

<details>
<summary><h2>GAME RULES :video_game:</h2> </summary>
<br>

# Game difficulty levels

> <h4>:one: Easy mode</h4>
> The speed of the snake is constant and the food blink at a regular interval. The score increases by 1 point for each food eaten.
  
> <h4>:two: Medium mode</h4>
> The speed of the snake is higher than in easy mode. The score increases by 2 points for each food eaten.
      
> <h4>:three: Hard mode</h4>
> The speed of the snake is higher than in easy mode ( same as in medium mode) and we have bombs :bomb:. The bombs blink faster than the food, and if the snake touches 
> them it dies. The score increases by 3 points for each food eaten.


</details>


<details>
<summary><h2>ELECTRONIC SETUP :electric_plug:</h2> </summary>
<br>
      
# Hardware components

* Arduino UNO
* 16x2 LCD
* 8x8 led matrix
* MAX7219 driver
* joystick
* active buzzer (not in use !)
* 10UF electrolytic capacitor
* 104pF ceramic capacitor
* resistors

## Connecting the driver to Arduino

> Connection Table

| Max7219 Driver Pins | Arduino Pins |
|  :----:             |    :----:   |
| 4 (GND)             | GND       |
| 9 (GND)             | GND       |
| 18 (ISET)           | 5V, resistor  |
| 19 (V+)             | 5V      |
| 1 (DIN)             | 13     |
| 12 (LOAD/CS)        | 10       |
| 13 (CLK)            | 12      |

> Connection Electronic Schema

![driverToarduino](https://user-images.githubusercontent.com/96074975/208295625-f6f6c6ea-b6d9-4b5f-a627-e9f9b456835b.jpg)


## Connecting the driver to matrix

> Connection Table

to be verify

> Matrix Pins - Common Cathode

![matrix_rowCol](https://user-images.githubusercontent.com/96074975/208294894-3928c9a4-a4b3-4ace-8714-aa14d82cea7e.PNG)




## Connecting the LCD to Arduino

> Connection Table
    
      
<table>
<tr><td>

|Display Pin | Arduino Pin|
|  :----:             |    :----:   |
| VSS (1)             | GND       |
| VDD (2)             | 5V       |
| V0 (3)              | 11 |
| RS (4)              | 9      |
| RW (5)              | GND    |
| E (6)               | 8     |
| D0 (7)              |  not in use     |
| D1 (8)              |  not in use     |

</td><td>

|Display Pin | Arduino Pin |
|  :----:             |    :----:   |
| D2 (9)              |   not in use     |
| D3 (10)            |   not in use    |
| D4 (11)            |    7  |
| D5 (12)            |    6   |
| D6 (13)            |   5    |
| D7 (14)            |    4   |
| A (15)            |    3  |
| K (16)            | GND      |

</td></tr> </table>
      
      
      

> LCD Pins

![lsc_schema](https://user-images.githubusercontent.com/96074975/208295069-41e320fe-13fc-4fad-8a7b-00968cb27004.PNG)


## Connecting the joystick and buzzer to Arduino

> Connection Table
      
<h6> :bangbang: The buzzer is not working due to technical problems ! </h6>

<table>
<tr><th> Joystick </th><th> Buzzer </th></tr>
<tr><td>

|Joystick Pin|Arduino Pin  |
|--|--|
|VRx| A5|
|VRy| A4|
|SW| 2|
|GND| GND|
|VCC| 5V|
      

</td><td>

|Buzzer Pin|Arduino Pin | 
|--|--|
|5V|not in use|
|GND|GND + 100 Ohm resistor|

</td></tr> </table>
 
      
> Joystick Schema      
      
![image](https://user-images.githubusercontent.com/96074975/208296958-ff794ba5-0350-40bf-bc90-1bfbba4a354f.png)


      
      
</details>

<details>
<summary><h2>CODE DETAILS :computer:</h2> </summary>
<br>
      
## Used libraries :books:
      
      - LiquidCrystal.h (for LCD control)
      - LedControl.h (for matrix control)
      - EEPROM.h (for memory)

## Memory addresses used for EEPROM :floppy_disk:



![WhatsApp Image 2022-12-17 at 20 41 41](https://user-images.githubusercontent.com/96074975/208257029-43b06598-6802-4778-8fac-8d28ef2cddfc.jpg)


## Matrix Animation :high_brightness:
      
> 1. Geeting Message Matrix Animation

![snake](https://user-images.githubusercontent.com/96074975/208298769-c5c10da5-62a4-4385-91e6-cd17472953f7.png)

      
> 2. Main Menu Matrix Animation
      
![image](https://user-images.githubusercontent.com/96074975/208298363-688ab317-6f7b-4267-ba4f-81242ada9b31.png)


      

</details>




