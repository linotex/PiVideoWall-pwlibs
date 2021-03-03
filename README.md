# PiVideoWall (pwlibs)
## Pre-disclaimer
It is fork **piwall** from http://piwall.co.uk/ site

[pwomxplayer fork](https://github.com/linotex/PiVideoWall-pwomxplayer)

[Forum](https://groups.google.com/g/piwall-users)

[Create your own GPL movie PiWall](http://piwall.co.uk/information/installation)

[PiWall configuration file](http://piwall.co.uk/information/configuration-file)

[Features and Benefits](http://piwall.co.uk/information/6-features-and-benefits)

# Disclaimer of warranty

This software is provided on an "AS IS" BASIS and WITHOUT WARRANTY, either express or implied, including, without limitation, the warranties of non-infringement, merchantability or fitness for a particular purpose. THE ENTIRE RISK AS TO THE QUALITY OF THE WORK IS WITH YOU.

# Limitation of liability

Under no circumstances and under no legal theory, whether in tort (including negligence), contract, or otherwise, shall the we be liable to anyone for any direct, indirect, special, incidental, or consequential damages of any character arising as a result of the use of this software including, without limitation, damages for loss of goodwill, work stoppage, computer failure or malfunction, or any and all other commercial damages or losses.

# Overview

A master computer, which can be either a Raspberry Pi or a Linux PC, is in control of the wall and plays video files.  This communicates to all the Raspberry Pi 'tiles' of the wall via an ethernet network.  Each tile displays part of the picture on its screen, and the screens together form the 'wall'.

The combination of master and tiles together forms a PiWall video wall system.  The PiWall can be either fully stand-alone or the master can be connected to an external network via an additional wired or wireless network adapter, thus enabling the system to be controlled remotely.

**Please note that all Raspberry Pi computers used within a PiWall must be the model B version and not the cheaper model A that doesn't include an ethernet network interface.** (from me: now exists new PI 4, but I down know if it works now)
 
# Hardware required

You will need:

- a master computer, which can be a Raspberry Pi or a Linux PC;
- at least one Raspberry Pi "tile" computer for each screen in your PiWall;
- an ethernet switch with at least as many ports as you have Pis - this can be omitted if you are only going to test with a single tile/screen;
- a suitable screen and HDMI lead for each tile;
- associated network cables and power supplies;
- for each tile, an SD card with a capacity of at least 2GB - check http://elinux.org/RPi_SD_cards for compatible SD cards;
- if the master is a Raspberry Pi you will also need;
  - another SD card with a capacity of at least 2GB - but you may well need a considerably larger card, depending on the number and size of video files you want to play;
  - (optional) a screen and keyboard;
  - (optional) a USB-ethernet adapter - check http://elinux.org/RPi_USB_Ethernet_adapters for compatible devices;
  - (optional) a USB sound card - check http://elinux.org/RPi_VerifiedPeripherals#USB_Sound_Cards for compatible devices;
  - (optional) a powered USB hub - check http://elinux.org/RPi_Powered_USB_Hubs for compatibility.

Note that it is possible to try out the system without the full number of tiles that you eventually intend to have - for example, you may just want to test with a single tile before committing to purchasing a full 4-screen system.  (With a single tile, it is possible to dispense with the ethernet switch and use a crossover ethernet cable instead, but that is outside the scope of this guide.)

# Installing the software

If the master is not a Raspberry Pi then just install [ffmpeg](http://ffmpeg.org/download.html) or [avconv](https://libav.org/avconv.html) on your machine.

Note: you may wish to perform the relevant network configuration steps from the next section for each master and tile Raspberry Pi as you install the software otherwise you will have to reconnect screens and keyboards.

If the **master is** a Raspberry Pi then perform the following actions:

1. Download the latest [Raspbian](https://www.raspberrypi.org/software/) image and follow the associated instructions to write the image to the SD card.
2. Insert the SD card into the master, connect a keyboard and screen and boot the computer.
3. Follow the standard instructions and connect to your home network so you can browse the Internet.
4. From a terminal window enter the command `sudo apt-get install libav-tools`.
5. Now perform the network configuration for the master from the network configuration section.

For each Raspberry Pi tile follow the first three actions from the above Raspberry Pi master list then do the following actions:

1. Use the Midori browser to navigate to this page and continue following these instructions
2. [Click here to download the pwlibs](https://github.com/linotex/PiVideoWall-pwlibs/raw/main/build/pwlibs1_1.1_armhf.deb) package and just "save" it. [Original link](http://dl.piwall.co.uk/pwlibs1_1.1_armhf.deb)
3. From a terminal window type `sudo dpkg -i /home/pi/pwlibs1_1.1_armhf.deb`
4. [Click here to download the pwomxplayer](https://github.com/linotex/PiVideoWall-pwomxplayer/raw/main/build/pwomxplayer_20130815_armhf.deb) package and just "save" it. [Original link](http://dl.piwall.co.uk/pwomxplayer_20130815_armhf.deb)
5. From a terminal window type `sudo dpkg -i /home/pi/pwomxplayer_20130815_armhf.deb`
6. Now perform the network configuration for the tile from the network configuration section.

# Network configuration

Each Pi needs to have a different IP address (obviously!) and you almost certainly want these to be statically assigned.  For this Guide we'll assume a private address range of **192.168.0.*** if you need to use another set of addresses, then adjust accordingly.

In a production environment, you may want to connect the master Pi to an existing network - this is best achieved by adding a USB ethernet or WiFi adapter as a second interface to the master. Configuring this second network interface is beyond the scope of this document.

In order for the master to communicate efficiently with the tiles, it uses multicast addressing (where each packet sent by the master is received by all the tiles).  The rules and guidelines for using multicast addresses are complex; if the network is completely private then it doesn't really matter, but in this Guide we'll use one of the "administratively scoped" addresses, 239.0.1.23.  If you plan to use a real, shared network, then speak to your network administrator to agree an address.

If you are using a Linux PC as your master and don’t want to permanently alter your network configuration then execute the following commands after you have connected to the private PiWall network.

`sudo ifconfig eth0 192.168.0.??? netmask 255.255.255.0 up`

`sudo route add -net 224.0.0.0 netmask 240.0.0.0 eth0`
 
Note that this enables the full multicast address range, even though we'll only be using a single address within that range.

To make this routing permanent on a Raspberry Pi master or tile, edit the network interface stanza in "**/etc/network/interfaces**", e.g.

```
iface eth0 inet static
  address 192.168.0.???   
  netmask 255.255.255.0   
  up route add -net 224.0.0.0 netmask 240.0.0.0 eth0
```

We usually use an address of 100 for the master and number the tiles from 1, upwards.

# Testing the software

First test a tile to ensure that it is working correctly. Start by connecting a keyboard to the tile and attaching a USB pen drive that contains a movie that the standard omxplayer can display. Find the path of the USB pen drive, from the command line type `df` this will list all the file systems on your Pi. In the right hand column, look for the entry that has a path that starts with "**/media/**", on my system it is "**/media/18DA-7CE4**". Prepend this path to the "movie.avi" argument in the following commands. Confirm that the movie can be played by the standard omxplayer provided with the Raspbian image by typing `omxplayer movie.avi` at the command prompt. Next verify that pwomxplayer can play the movie by typing `pwomxplayer movie.avi`. Finally check that pwomxplayer can show a section of the video by typing `pwomxplayer --tile-code=42 movie.avi` which should display just the top right corner of the original movie, but magnified to fill the whole screen.

Now you're ready to test the master in conjunction with one or more tiles. On each Raspberry Pi tile type `pwomxplayer --tile-code=$n udp://239.0.1.23:1234?buffer_size=1200000B` (where $n=41 is the top left, 42 is the top right, 43 is the bottom left and 44 is the bottom right for a 4 screen PiWall). On the master type `avconv -re -i movie.avi -vcodec copy -f avi -an udp://239.0.1.23:1234`

The "**--tile-code**" configuration doesn't provide bezel compensation, for that you will need to provide a detailed PiWall configuration file. That will be the subject of a further guide to be published later this week.

# Limitations

1. If you want to play consecutive movies that have different resolution settings then you will either have to
  - stop & start all the pwomxplayers between movies with different resolutions or
  - re-encode all your movies to use the same resolution settings.
2. Sound is not transmitted to the screens so you will have to redirect the sound output from the avconv command on the master and play it through the master's local hardware.
3. You cannot connect (or re-connect) a pwomxplayer to a movie that is already transmitting. You must stop the master avconv, start your pwomxplayer(s) then re-start the master avconv command.

# Support

The first port of call for support for this GPL software is the [Forum](https://groups.google.com/g/piwall-users). We will regularly monitor the Forum and encourage other knowledgeable members to help out where possible.

We will make new versions of the software available whenever there are fixes or updates.

-----

# PiWall configuration file

[Original link](http://piwall.co.uk/information/configuration-file)

Although there are several command-line options which allow definition of the picture geometry, it is usually easier to write a configuration file. This file contains information that describes the overall size of the wall and the position and size of each tile in the wall. The units used are arbitrary so it is easy to define the layout using millimetres.

Each tile within a PiWall requires a copy of the same configuration file named "**.piwall**" to be stored in the "**/home/pi**" directory.  The format of the file is a familiar style with each section name in square brackets followed by several _name=value_ property definitions.  Comment lines beginning with a “#” character are also allowed.

Start by measuring the overall width and height of the wall, measure from the inside of the bezel on the top left of the wall to the inside of the bezel on the top right of the wall and then do the same for the height, remembering to measure from the inside of the bezels.  This defines the usable area in which the complete video picture will be displayed.

Add the “wall definition” information to the .piwall file by typing

 
```
[my_wall]
width=????
height=????
x=0
y=0
```
 
(In this example we use the top left of the wall area as the origin of the cooordinate system; you could choose another point so long as the coordinates of the tiles (below) are consistent.)

Each screen is connected to a Raspberry Pi, each of which requires a unique name; the PiWall software reads this from a separate configuration file called "**/home/pi/.pitile**", which should look like the following:

```
[tile]
id=???
```

Where ??? is the chosen tile name.

We find the easiest way of organising things is to set the name of each tile to "pi?" where "?" is the last part of the tile's IP network address, and to use a simple numbering of tiles in rows from left to right, top to bottom, So, for a 3x3 system we would have

1 | 2 | 3
-|-|-
4 | 5 | 6
7 | 8 | 9

with the corresponding Raspberry Pi computers having hostnames pi1, pi2, … pi9 and IP addresses 192.168.01, 192.168.0.2, … 192.168.0.9

Now, for each tile we will create a “tile definition” section in the .piwall file to define the geometry of the tile screen in relation to the wall.  Measure the displayable area of the screen (between the bezels) and the distance from the top left of the wall (or wherever you have defined the origin of your coordinates)..

```
[my_tile1]
wall=my_wall
width=???
height=???
x=???
y=???
```

Repeat for each of the remaining tiles.

Finally, we create a “config” section to tie it all together.  This maps each tile identity to a tile definition.

```
[my_config]
pi1=my_tile1
pi2=my_tile2
…
piN=my_tileN
```
 
Having created the .piwall file, we can now use a single option to use the configuration:

`pwomxplayer --config=my_config …`

Note that this allows us to use the same command on every tile to show the appropriate portion of the video picture.

For illustration, here is a complete example .piwall file

```
# wall definition for 2x2 screens with bezel compensation
[4bez_wall]
width=1067
height=613
x=0
y=0

# corresponding tile definitions
[4bez_1]
wall=4bez_wall
width=522
height=293
x=0
y=0
 
[4bez_2]
wall=4bez_wall
width=522
height=293
x=545
y=0

[4bez_3]
wall=4bez_wall
width=522
height=293
x=0
y=320
```

```
[4bez_4]
wall=4bez_wall
width=522
height=293
x=545
y=320

# config
[4bez]
pi1=4bez_1
pi2=4bez_2
pi3=4bez_3
pi4=4bez_4
 ```

Note that the section names for the wall definition and tile definitions are arbitrary; they are used only as labels referenced from other sections.  You are free to use whatever naming scheme you choose.

The .piwall file can contain multiple configurations, thus avoiding the need to push different .piwall files e.g. when changing between bezel and no-bezel modes.
