<h1 align="center">Welcome to Efficient Study Planner 👋</h1>
<p align="center">
  
  <a aria-label="GitHub issues" href="https://github.com/ausaf007/efficient-study-planner/issues" target="_blank">
    <img src="https://img.shields.io/github/issues/ausaf007/efficient-study-planner?style=for-the-badge" />
  </a>
  <a aria-label="GitHub license" href="https://github.com/ausaf007/efficient-study-planner/blob/master/LICENSE" target="_blank">
    <img src="https://img.shields.io/badge/LICENSE-MIT-brightgreen?style=for-the-badge" />
  </a>
  <a aria-label="Build Status" target="_blank">
    <img src="https://img.shields.io/badge/build-passing-brightgreen?style=for-the-badge" />
  </a>
  <a aria-label="GitHub contributors" href="https://github.com/ausaf007/efficient-study-planner/graphs/contributors" target="_blank">
    <img src="https://img.shields.io/badge/Contributors-3-brightgreen?style=for-the-badge" />
  </a>
  <a aria-label="linkedin-shield" href="https://www.linkedin.com/in/md-ausaf-rashid/" target="_blank">
    <img src="https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555" />
  </a>
</p>

<h3 align="center">Optimize your study plan with ESP!</h3>

<!-- TABLE OF CONTENTS -->
<details open>
  <summary>Table of Contents</summary>
  <ul>
    <li><a href="#about-the-project">About The Project</a></li>
    <li><a href="#tech-stack">Tech Stack</a></li>
    <li><a href="#prerequisites">Prerequisites</a></li>
    <li><a href="#how-to-use">How To Use?</a></li>
    <li><a href="#license">License</a></li>
  </ul>
</details>

## About The Project

The Efficient Study Planner (ESP) is a CLI app that gives a detailed and optimized plan to study for an upcoming exam. It takes into consideration each student's strengths & weaknesses, syllabus and exam schedule to decide the most optimum study plan. 

## Tech Stack

[![](https://img.shields.io/badge/Built_with-C-blue?style=for-the-badge&logo=C)](https://en.cppreference.com/w/c/language)
[![](https://img.shields.io/badge/Built_with-ESP_Lib-red?style=for-the-badge)](https://github.com/ausaf007/efficient-study-planner/blob/master/esp_lib.h)
[![](https://img.shields.io/badge/Built_with-Code_Blocks-red?style=for-the-badge)](https://www.codeblocks.org/)

## Prerequisites

Download and install GCC compiler and CodeBlocks IDE for [Windows](http://www.codeblocks.org/downloads/binaries/#imagesoswindows48pnglogo-microsoft-windows), [Mac OS X](http://www.codeblocks.org/downloads/binaries/#imagesosapple48pnglogo-mac-os-x) or [Linux](http://www.codeblocks.org/downloads/binaries/#imagesoslinux48pnglogo-linux-32-and-64-bit). You can use any IDE of your choice.  

## How to use?

You can fork or download/clone the repo, once you have all three files "Student.c", "University.c" and "esp_lib.h" downloaded, make sure to keep them in the same directory. Then you need to compile both the C files. You should get University.exe and Student.exe files from GCC. 

* After that run University.exe and enter the number of topics included in each subject and their names. Then, you need to enter the examination schedule. This application will be used mainly by the university admin.

* Then, you can run Student.exe. All students have to enter their Name and Roll Number for using this application for the first time. Every individual student’s detail is stored in the Student Database for them to access later.

* Then the student needs to mention their past scores in 12th and 10th grade. Strengths and weaknesses will be decided based on this. 

* Then, the student can see their strengths and weaknesses, create a "Personalized Time Table", see the exam syllabus & schedule decided by the university admin. The personalized timetable is generated in such a way that it gives high priority to students' weaknesses and gives a low priority to students' strengths so that the student can improve themselves at their weak points.

All the best for your exams!

## License
Code released under [MIT License.](https://choosealicense.com/licenses/mit/)

