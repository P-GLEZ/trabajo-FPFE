# My first Geant4 application
This contains the code of the lab sessions of FPFE.

To get the code of the first session:  
`git clone --branch day1 git@github.com:folguera/FPFE-Geant4.git MyFirstApplication`

To get the code of the second session:  
`git clone --branch day2 git@github.com:folguera/FPFE-Geant4.git MyFirstApplication`


# How to build this application (reminder)

1. You need to generate the Makefile by using cmake from the 
   build directory as (on the virtual machine)

`cmake ../` 

  and if you have your Geant4 installation on your system, you need to specify 
  the location of the Geant4Config.cmake file (which is in your Geant4 installation
  location in the /lib/Geant4-10.6.0 directory) by setting the path to it in the 
  -DGeant4_DIR Geant4 cmake variable as


`cmake ../ -DGeant4_DIR=/Where/Your/Geant4/installation/is/lib/Geant4-10.6.0/`

2. After the Makefile is generated by the above cmake command you need to invoke 
   the make command to build (compile and link) your application with Geant4 
   toolkit as 
   
`make`    

  If everything is compiled and linked successfully, the 'yourMainApplication'
  executable of the application is available under this build directory. 

-------

Para usar esta aplicación (y simular los datos mostrados en la figura 8 del paper de Meroli), ejecuta el siguiente comando

`./ourmain ../MacroMeroni`

y para mostrar los datos

`python macro.py`
