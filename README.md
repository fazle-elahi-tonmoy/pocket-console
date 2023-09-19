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
  - `up` and down have used GPIO-00 and GPIO-19. use them to navigate. 
  - `SW` or select switch have used GPIO-26.  
  - `BW` or back switch have used GPIO-18. 
  - Single press `SW` Button to enter menu. 
  - Single press `SW` Button to select anything
  - Single press `BW` Button to return to home screen

  ### When Using Presentation Mode:
  - Press and hold `SW` button for at least 500 milliseconds to trigger `home key` press. This will indicate flashing up the LED light. 
  - Press `up` button to go to next slide (key trigger - `right arrow`).
  - Press `down` button to go to previous slide (key trigger - `left arrow`).
  - Press `SW` button to trigger `page down` key press.
  - Press `BW` button to trigger `page up` key press.
  - Press and hold `BW` button for at least 500 milliseconds to return to home screen.
    
  ### When Using Media Mode:
  - Press and hold `SW` button for at least 500 milliseconds to trigger `mute sound` press. This will indicate flashing up the LED light. 
  - Press and hold `up` button for at least 500 milliseconds to trigger `next track` press. This will indicate flashing up the LED light. 
  - Press and hold `down` button for at least 500 milliseconds to trigger `previous track` press. This will indicate flashing up the LED light. 
  - Press `up` button to increase volume (key trigger - `volume increase`).
  - Press `down` button to decrease volume (key trigger - `volume decrease`).
  - Press `SW` button to trigger `play/pause` key press.
  - Press `BW` button to trigger `page down` key press. This is for scrolling through reels.
  - Press and hold `BW` button for at least 500 milliseconds to return to home screen.

## Circuit Diagram
  <img src="images/Circuit Diagram.png" width="auto">