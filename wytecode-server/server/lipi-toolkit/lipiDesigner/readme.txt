                                 README

                         Lipi Designer Version 4.0

Contents

   * Introduction
   * System Requirements
   * Executing binary
   * Building the source
   * Manual
   * Bug Reports and Feedback   
   

Introduction

	Lipi Designer is a Java application which provides a GUI for creating, 
	loading & training and packaging shape recognizer projects. It can be 
	used for the rapid creation of recognizers for a set of characters or 
	gestures. Once the recognizer has been trained, and the accuracy of 
	recognition is found to be satisfactory, it may be packaged using the
	packaging feature provided by the application

System Requirements

	Windows 7 	               
	Microsoft Visual Studio 2008
	Java Development Kit (JDK) jdk 1.6.0_26 or above
	ActivePerl and Archive::Zip
	
	Ubuntu 10.10
	GNU C++ compiler 4.4
	Perl 5.10 or above and Archive::Zip
	Openjdk-6-jdk

Executing binary

	The user needs to set LIPI_ROOT environment variable before executing 
	the binary. On Windows, this variable is set automatically on installation
	of tool kit. On Linux, the user can either export LIPI_ROOT manually or can
	use build.sh/build-x64.sh script with -s option. This script can be found
	under $LIPI_ROOT/lipiDesigner directory.

	For example (on Linux):
	# export LIPI_ROOT=/opt/lipi
		where /opt/lipi is the installed location of lipi toolkit
	OR
	# sh build.sh -s (on 32 bit)
	
	# sh build-x64.sh -s (on 64 bit)

	Once LIPI_ROOT is set, lipiDesigner can be launched as shown below:
	
	# cd bin
	# sh lipiDesigner.sh

	(On windows)
	
	Under $LIPI_ROOT/lipiDesigner/bin directory, execute lipiDesigner.bat to start lipiDesigner.
	
Building the source

	For building source on Windows, please refer 'Building Lipi Designer source 
	code' section of Lipi Designer User Manual.

	For building source on Linux, please refer the same section of Lipi Designer 
	User Manual. The source on Linux can also be build using build.sh or
	build-x64.sh script.

	For example (on Linux):
	# sh build.sh -b (To build source code on Linux 32-bit)
	# sh build.sh -c (To clean object code on Linux 32-bit)
	
	# sh build-x64.sh -b (To build source code on Linux 64-bit)
	# sh build-x64.sh -c (To clean object code on Linux 64-bit)


Manual

	See the lipi-designer_4_0_user_manual.pdf document at $LIPI_ROOT/lipiDesigner/doc for information pertaining to lipiDesigner. 

