# Flight Controller
This module uses an open source flight controller code called MultiWii.
# MultiWii steps with Windows 11
1. Download Multiwii 2.3 from this link, https://code.google.com/archive/p/multiwii/
2. Open up the MultiWii.ino file and configure it to your liking.
3. Download this version of Java in order to run the java application, https://www.oracle.com/java/technologies/javase/javase8-archive-downloads.html
4. Select the com port that the arduino is on and then click calibrate.
# ESC Calibration
1. Hook up 12v to the ESC.
2. Connect PWM pin from the ESC's BEC connector (yellow or orange wire) to digital pin 9 of an arduino uno and upload the code from the ESC calibration arduino file.
