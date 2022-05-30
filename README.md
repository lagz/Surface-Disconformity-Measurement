# Surface-Disconformity-Measurement

## Purpose
- This project was created for a freelance client that needed a custom device to measure the surface disconformity of various rock formations in a way that could be graphed for visual interpretation. 

## Mechanical Design
- Accommodating for rough terrain, lawnmower wheels were chosen for their practicality and low cost. Based on this design choice, the wheel brackets were modeled to attach four rubber lawnmower wheels to a surplus wooden plank from a local hardware store. The lawnmower wheel bolts also function as independant axels for each wheel.
- For maneuverability, two screw eyes were fastened to the rear of the cart for a hook connected to an extension arm to attach. This allows the user to carefully pull the cart across the surface rock for measurement. 
- The device was also designed to be assembled and disassembled without any tools needed so it could be shipped via UPS. 

## Electrical Design
- The microcontroller chosen for this project was the Elegoo Uno R3. While this is certainly not the best microcontroller for this project, it did the job just fine. 
- The CQRobot Ocean VL53L1X time of flight sensor was chosen for the one dimensional distance data needed to make measurements.
- An Arduino compatible MicroSD card reader was used to store the collected data. 
- The user interface of the device consists of a button, a red LED, and a green LED.
- Since this is an very low power device, a simple 5V output phone battery charger was used to power the electronics. 

## Software Design
- The program for this project was written in the arduino programming language in a rather unsophistaicated manner. As I was in a bit of a time cruch when making this, the current iteration of the code is not elegant by any stretch of the imagination. 
- A simple polling algorithm is used to gather data for the sensor and store it on the MicroSD card as a comma delineated text file.
- There is a simple error checking loop to ensure that the MicroSD card is initalized. 

## Future Additions 
- While I can live with the mechanical design being quite crude, there is certainly room for importavement within the programming. I would like to add some more error checking loops and organize the code better. I also think a more elegant algorithm can be implemented. Message me if you have any ideas. 

(Note: to keep costs low, off-the-shelf components were used for the majority of the project)
