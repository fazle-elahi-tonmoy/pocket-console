# pocket-console

### A handy device which can be used to control your presentation slide, scroll through windows, control media volume, play-pause the music, act as a clock or stopwatch, play simple video games and so much more! 


## Setup

- Clone the github repository first using git:
  ```
  git clone https://github.com/fazle-elahi-tonmoy/Pocket_Console.git
  ```
## Before Uploading Code:
  - Board : `ESP32 Dev Module`
  - Partition Scheme: `ESP Rainmaker`
  select these to increase your writtable flash size. otherwise there would be a program storage error. 

## Please note that:
  I have tried combining multiple games from multiple platform which utilizes various display libraries. So, combining them all would create a conflict using same integers or parameters. I have resolved the conflict in my display library and kept it here for your ease of usage. please replace your typical library with mine in your computer and then try compiling the code. 

## How to use:
  - up and down have used GPIO-00 and GPIO-19. use them to navigate. 
  - SW or select switch have used GPIO-26. 
  - Single press SW Button to enter menu. 
  - Single press to select anything
  - Press and hold for at least 500 milliseconds to change functionality in `BLE control`. This will indicate flashing up the LED light. 
  - Press and hold for at least 2 Seconds to return from any mode in `BLE control`. This will indicate by turning off the LED light which was lit up before.

## Circuit Diagram
  <img src="images/Pocket Console Circuit Diagram.png" width="auto">