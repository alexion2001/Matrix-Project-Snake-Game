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
* active buzzer
* 10UF electrolytic capacitor
* 104pF ceramic capacitor

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

to be verify

> LCD Pins

![lsc_schema](https://user-images.githubusercontent.com/96074975/208295069-41e320fe-13fc-4fad-8a7b-00968cb27004.PNG)


</details>

<details>
<summary><h2>CODE DETAILS :computer:</h2> </summary>
<br>

> Memory addresses used for EEPROM



![WhatsApp Image 2022-12-17 at 20 41 41](https://user-images.githubusercontent.com/96074975/208257029-43b06598-6802-4778-8fac-8d28ef2cddfc.jpg)



</details>




