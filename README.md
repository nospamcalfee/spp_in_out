# Raspberry Pi Pico-w spp_counter standalone

I am trying to build a pico-w IOT device. One of the biggest problems is
initializing a IOT system in a random wifi environment. So my first thought
was to do a bluetooth interface to set my ssid/password/ip/ipmask and then
use my local wifi. If lwip supported mdns it would be easier, but doesn't
seem to just yet. Even if it did, the setting of the local wifi ssid/password
would be a problem in the field. I do assume the existence of a working wifi
environment.

The first step was to do a generic, small footprint, target somewhat
independent (easily ported?), flash file system handler. See
https://github.com/nospamcalfee/ringbuffer

The second step is this project, do a bluetooth initialization project.

## this project goal

I want to have a stand alone directory containing my project and its
configuration, but using the sdk for the big packages. I start with a
standalone bluetooth project. It merely extracts the spp_counter example and
adds a tiny bit of code to show how to add more code. This project uses
nothing from the pico-examples repo during its build.

In my last 25 years of embedded system contractor (retired! now), I have seen
many convoluted source trees and build systems. The pico-w sdk is such a
system. The design may be simple if you know everything about everything, but
some things I just want to use as a package and get on to my project. The
bluetooth stuff is such a package. The pico-examples build and run, great,
but I want an external project, where the big packages like btstack and lwip
are from the sdk, and my custom stuff is held in my project.

## Size of executable

If my goal of having a bluetooth configuration run first before my iot app,
everything must fit in the 2Mbytes of pico-w flash. I am amazed that the
current build of spp_counter requires 517K of flash - or about 1/4 the total
flash. That may make this approach to initialization unattainable, depending
on my app size needs.

In particular the .rodata required by the bluetooth stack seems huge. I may
need to investigate, but I prefer to use it as a black box. Maybe there is a
configuration option to reduce the requirements.  

```
Memory region         Used Size  Region Size  %age Used
           FLASH:      517168 B      2032 KB     24.85%
FLASH_PERSISTENT:          0 GB        16 KB      0.00%
             RAM:       35460 B       256 KB     13.53%
       SCRATCH_X:          0 GB         4 KB      0.00%
       SCRATCH_Y:          0 GB         4 KB      0.00%
```
## Warning

I have tested this code, but not every edge case. I use the android serial
bluetooth terminal app to connect, and receive and send text. I do not know
if Apple i-phones support this, I would like to be generic for
initialization. If i-phones do not support bluetooth serial, this is another
problem which might kill this bluetooth initialization approach.

This code works for me (so far) your code will need testing.

Your mileage may vary.


## Build and Install

This build assumes you have the pico-sdk installed and have defined in your
environment PICO_SDK_PATH. This package works as a native Linux shell build,
but should be easy to people who wish to further complicate the build using a
ide environment.

There is no requirement for any pico-examples source code (I hope)

```bash
cd yourprojectdirectory
mkdir build; cd build
cmake ..
make
```

Once built, the `spp_in_out.uf2` file can be dragged and dropped onto your
Raspberry Pi Pico to install and run the example.

