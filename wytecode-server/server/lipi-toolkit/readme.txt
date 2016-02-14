
Welcome to lipi-toolkit 4.0.0
-----------------------------

README for lipi-toolkit 4.0.0

Introduction
----------------
The lipi-tookit package comprises of three modules:

1) The toolkit provides core-toolkit which can be used for the creation and evaluation of recognizers for isolated shapes such as handwritten gestures and characters. 
2) lipiDesigner which is a part of toolkit, is a java based application which provides a GUI for creating, loading, training and packaging projects.
3) The toolkit also provides alphanumeric recognizer that can be readily integrated into client applications. 

The supported platforms
-----------------------------
Windows 7 (x86, x64)
Ubuntu 10.10 (x86, x64)

TABLE OF CONTENTS
----------------------------------
1. Installing lipi-toolkit 4.0.0
2. Executing binary
3. Building the source 
4. Manuals
5. Known Issues / Limitations

1. Installing lipi-toolkit 4.0.0
--------------------------------
a. lipi-toolkit 4.0.0 Packages : 

lipi-toolkit4.0.0-bin-x86.exe - Binary package for Windows 7 edition for VC2008
lipi-toolkit4.0.0-bin-x64.exe - Binary package for Windows 7 edition for VC2008
lipi-toolkit4.0.0-src-x86.exe - Source package for Windows 7 [VC2008] 
lipi-toolkit4.0.0-src-x64.exe - Source package for Windows 7 [VC2008]
lipi-toolkit4.0.0-linux-x64.tar.gz - Binary package for Linux
lipi-toolkit4.0.0-linux-x86.tar.gz - Binary package for Linux
lipi-toolkit4.0.0-src-linux.tar.gz - Source package for Linux

b. Unpacking / Extracting the package:
 
On Linux platform use the following command to extract
e.g.
     	tar -xzvf  lipi-toolkit4.0.0-src.linux.tar.gz

On Windows use installer
	Double click/execute the installable file
	e.g.
		lipi-toolkit4.0.0-src-win.exe
		
2. Executing binary
-------------------
1) lipi-core-toolkit

The user needs to set LIPI_ROOT environment variable before executing the binaries. On Windows, this variable is set automatically on installation of tool kit. On Linux, the user can either export LIPI_ROOT manually or can use build.sh/build-x64.sh with -s option.

For example (on Linux):
# export LIPI_ROOT=/opt/lipi
	where /opt/lipi is the installed location of lipi toolkit
OR
# sh build.sh -s (on 32 bit)

# sh build-x64.sh -s (on 64 bit)

2) lipiDesigner

Please refer the readme or user manual of lipiDesigner for executing the binary.

3. Building the source
----------------------
1) lipi-core-toolkit

For building source on Windows, please refer 'Building Source package' section of User Manual.

For building source on Linux, please refer the same section of User Manual. The source on Linux can also be build using build.sh or build-x64.sh script.

For example (On Linux):

# sh build.sh -b (To build source code on 32-bit)
# sh build.sh -c (To clean object code on 32-bit)

# sh build-x64.sh -b (To build source code on 64-bit)
# sh build-x64.sh -c (To clean object code on 64-bit)

2) lipiDesigner

Please refer the readme or user manual of lipiDesigner for building the source.

4. Manuals
----------
The detailed user manual of core-toolkit can be found at $LIPI_ROOT/doc/lipi-core-toolkit_4_0_User_Manual.pdf

The manual for lipiDesigner can be found at $LIPI_ROOT/lipiDesigner/doc/lipi-designer_4 0_user_manual.pdf

The user can also refer getting started manual at $LIPI_ROOT/doc/lipi-toolkit_4_0_getting_started.pdf to get started with lipi-core-toolkit and lipiDesigner.

5. Known Issues / Limitations
-----------------------------------------
1. Spaces in file paths in training/test list files

Issue:
In list files for training or testing, if the file path contains spaces, then runshaperec.exe reports an error, and training or testing fails. 

Workaround: 
Do not use directory or files names with spaces in them, or (for Windows platforms) use the DOS path instead (e.g. for C:\program files, use “C:\progra~1”).
