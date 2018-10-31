# RBE2002_template
Template code for the RBE 2002 final project

# Hardware

See: https://github.com/WPIRoboticsEngineering/RobotInterfaceBoard

# Development Computer Options  

## Option 1) A lab machine

Availible to all students. 

Note that Eclipse *should be installed by you* in your My Documents folder.  Each install of eclipse should be personal and not shared.

Note that the driver is installed on these computers

Note that Arduino with the ESP32 toolchain is already installed in C:\WPIAPPS\arduino-1.8.3\

##  Option 2) Personal Machine

### Supported for this class

Windows 10 Pro 

A user name with no " " in the file path. Generally it is safe to use your WPI username as the username on your computer.

Fresh install is genearlly reccomended every 6 months. Install disk are availible to students as a resource from the WPI Helpdesk.

OneDrive and Dropbox conflict with the install process and must be fully removed from the user file paths. 

Eclipse should be installed in C:\eclipse

Arduino should be installed in C:\RBE-arduino

After installation of both, ensure your user has write access to the directories. 

### Unsupported OS's

MacOS is unsupported and only intermittantly working. Drivers have been an issue with programming our board, and virtualization of Windows within OSX is tested non-working. If you have Mac OSX please install a fresh copy of Windows 10 nativly and dual boot. 

Ubuntu 16.04 is unsupported but works well.

Ubuntu 18.04 is unsupported but works well with some creative directions following. This will take more effort and would require pre-existing proficency in Linux. If you have 18.04 please install Windows 10 or 16.04. 

### How to get Windows 10 as a Student for free from WPI

To get your student copy of Windows go here: 

https://onlinestore.wpi.edu/

Select windows 10, and download it. For students you get one copy and it is free. 

You can follow this tutorial to install it:

https://www.youtube.com/watch?v=aTVOTY93XXU

# Arduino and the ESP32 Toolchain

## Driver

This is installed on the lab machines already. 

After extracting the Zip file, install the 64 bit version of the driver. 

https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers


## Personal Computer install Windows  (Supported)
download:

http://users.wpi.edu/~glipin/.uploads/RBE-arduino.zip

And extract it on your computer in 

```
C:/RBE-arduino
```
Run Arduino in the extracted folder.

## Personal Computer install Linux / Mac  (Unsupported)

Linux Instructions (16.04 works well, 18.04 is a bit fiddely and needs extra steps but can be made to work):

https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/debian_ubuntu.md


Mac instructions (NOT SUPPORTED BY THE LAB, HAS LOTS OF PROBLEMS):

https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/mac.md


# Arduino Libraries
## HOWTO
For detailed instructions on how libraries work, see: https://www.arduino.cc/en/Guide/Libraries

Open Arduino and select Sketch->Libraries -> Manage Libraries
## Which Libraries
Search for and install:

ESP32Servo

ESP32Encoder

Adafruit_BNO055

BNO055SimplePacketComs

Esp32SimplePacketComs

SimplePacketComs

WiiChuck

DFRobotIRPosition

PID

# Set up your project

Your privete Repository has been created for you here: https://github.com/RBE200x-lab

You and your team members should find your repository made with the template code in there. 


# Develop Code for your project

## Install Eclipse and the Sloeber plugin (If the computer doesn't already have it)

Download the eclipse installer from here:

[https://www.eclipse.org/downloads/](https://www.eclipse.org/downloads/)

![alt text](/doc/downloadEclipseForC.png)

Run the Eclipse installer

![alt text](/doc/runEclipesInstaller.png)

Install the C developemt version. 

![alt text](/doc/selectCversion.png)

Once the install is done, open eclipse and go to the workbench. 

![alt text](/doc/pickWorkspace.png)
![alt text](/doc/goToWorkspace.png)

Open

```
Help->Eclipse Marketplace...
```

Search for Sloeber 

![alt text](/doc/installSloeber.png)

Install "The Arduino Eclipse IDE named Sloeber" and restart eclipse. 

Set the workspace to Arduino mode. In the upper right hand corner there is a button with a little yellow plus sign, and when you hover over it is says "pen Perspective". Click that button. Select Arduino. 

Eclipse will restart to load the plugin.

#### Open the Arduino Preferences:

```
Arduino -> Preferences
```
And start by removing both of the default values for private Hardware and Private libraries:

![alt text](/doc/removePrivatePaths.png)

Under Private Hardware Path, select New.. and search for (where you extracted Arduino)/hardware/ 

Mine looks like:
```
C:\WPIAPPS\arduino-1.8.3\hardware\
```

Under Private Library path, select New.. and search for your user library directory. It is usually in (your users home)\Documents\Arduino\libraries for Windows, or (your users home)/Arduino/libraries for Unix systems. You know you have the right one if the folder contains ESP32Servo, Esp32SimplePacketComs, SimplePacketComs, EspWii and WiiChuck Directories from the library install step above. Remember the location of this folder, it will be where you clone your code in a coming step. 

Mine looks like:
```
C:\Users\harrington\Documents\Arduino\libraries
```

## Clone your project

In eclipse, open 
```
Window->Show View-> Other -> Git ->Git Repositories
```
![alt text](/doc/GitRepositories.png)

In the browser, Click the clone or download button in your new project and select clone (Be sure HTTPS not SSH is selected, unless you have set up your SSH keys).

 ![alt text](/doc/cloneFromGithub.png)

Copy the clone URL.

In Eclipse, click the clone button: 

 ![alt text](/doc/cloneNewRepo.png)

If your URL is still copied in the clip board, Eclipse will autofill most the clone information for the first step. Add your username and password.

 ![alt text](/doc/startCloning.png)

Hit next and get to the Branch Selection window, change nothing and hit next.

Use the default checkout location. 

Hit Finish

## Open your project and start working

In Eclipse, Right click in the Project View and select 
```
New->Arduino Sketch
```
Un-check the default location, and seclect where you just cloned your code. Mine looks like: 

```
C:\Users\harrington\git\RBE2002Code21
```

Give it the name:

```
RBE2002Main
```
![alt text](/doc/setNameAndSourceLocation.png)

and select the ESP32 toolchain. 
```
Board: ESP32 Dev Module
Upload Protocol: Default
Port (the port your device is on)
Core Debug Level: None
Flash Frequency 80mhz
Flash Mode: QIO
Flash Size: 4mb
Partition Scheme: Default
Upload Speed: 921600
```
![alt text](/doc/ESP32-setup.png)

Then hit next and select Default ino file

![alt text](/doc/defaultINO.png)

Hit finish. 

# Commit your changes

### Unfamiliar with Git?

run through this tutorial: https://resources.github.com/videos/github-best-practices/

Also check out this cheat sheet: http://overapi.com/git

### Familiar with Git?
When you make a change to any line of code, you should commit your changes. If you have worked for ~1 hour, then you should make a commit with a message describing your work. To do so, go back to 

Finally right click on your project
```
Team->Commit
```
Be sure to set the "Author" and "Committer" fields sould both contain the same data like this:
```
Kevin Harrington <harrington@wpi.edu>
```

Messages should consist of 60 charrectors of short description describing what changed, 2 new lines, then a t least one full sentance describing the justification for the change. If you have more than one file, only commit one at a time. using the "+" and "-" buttons in the Git Staging section. 

When you have chages to share with your team, first Right click on the repository and select "Pull". Merge any changes your team mates made and published to upstream. Then commit the merge (or commit nothing if the merge was clean) and push your changes to the upstream server.

Once you have pushed your changes, be sure to verify that they are on GitHub. On your repository, go to
```
Insights->Network
```
and verify your changes are there. 






