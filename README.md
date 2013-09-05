Dvos
====

A tiny operating system for the NXP Cortex M3 micro-controller.

The kernel has been tested on this micro-controller :
- LPC1311
- LPC1315
- LPC1343
- LPC1347
- LPC1769


Usage
-----

The Dvos is a Makefile project, you can use it directly from the command line :
make clean
make build

Open the file "Makefile.options" in the test project to customize your firmware.

The minimal source code to start the dvos system must be :

``` c
#include <libs-hardware.h>
#include <kernel-dvos.h>

void loop(void)
{
    while(1)
    {
    }
}

int usermain(void)
{
    
    newThread(loop,512,10,5);
   
    
    return 0;
}
```


NetBeans
--------

The project file of the dvos are created with NetBeans. If you want to use NetBeans IDE, follow the next step:

Install NetBeans :
- Install NetBeans 7.0.1 mini (C/C++ version)
- Update plugins (Tools->Plugins->Updates)
- Install plugin GdbServer (tools->plugins->Available Plugins->Gdbserver->Install)
- Add ARM toolchain in NetBeans config: (Netbeans->Preferences->C/C++->Tool Collection->Add)

Create a new project in NetBeans :
- File->New Project->C/C++->Existing sources
- Navigate to your new project repertory
- Select tool collection (arm)

License
-------

See LICENSE.txt for license of this code.

