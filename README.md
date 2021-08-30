# Fundamentals of Virtual & Augmented Reality (UE19CS315)

This repo contains the course work related to the "Fundamentals of Virtual & Augmented Reality", taught at PES University during the Fall of 2021 (course code: UE19CS315) to 5th sem (3rd year) students.

As of now, it contains the code that was executed in the classroom.

## Getting Started

In order to run/execute code n this repo, you must have your Windows machine ready with the OpenGL software. You may find instructions to achieve that [Here at GeeksForGeeks](https://www.geeksforgeeks.org/how-to-setup-opengl-with-visual-studio-2019-on-windows-10/)

## Installation, Build, Usage & Development

Once, you have your machine ready, you will need to clone this repo locally using `git` or, you may just download it.

The solution consists of many projects, each of whose name is the month and date followed by what code that project contains.

You just need to right-click on the project you want to run as click `set as startup project` and then click the "play" (Local Windows Debugger) button to debug the code. 

> Note that this repo is being developed using `Platform Tooset: Visual Studio 2022 (v143)` applied on all projects. Visual Studio 2022 is still in preview as of this date. So, when running it on Visual Studio 2019, you may have to `retarget` the projects by either right-clicking on the solution or the project and clicking `retarget solution` or `retarget project` respectively (The deafult values to retarget will be chose for you).

> If you get an error while building, saying `cannot open file glut32.lib`, then make sure that the configuration you are using is set to `Debug|x86`. If you encounter any other `OpenGL` related problems make sure you installed the stuff properly.

## LICENSE

It has the MIT License (very permissive). Check the license file for details.
