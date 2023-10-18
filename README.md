<a name="readme-top"></a>


<!-- PROJECT SHIELDS -->
<img src="https://github.com/ahmed-alllam/AlphaLogos/actions/workflows/tests.yml/badge.svg" alt="Tests Status" height="28"></img>
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">

  <a href="https://github.com/ahmed-alllam/AlphaLogos">
    <img src="assets/project-image.jpeg" alt="AlphaLogos!" width="350">
  </a>

<h3 align="center">AlphaLogos: Logic Synthesis Optimization</h3>

  <p align="center">
    <a href="http://alphalogos2-516469619.eu-west-3.elb.amazonaws.com/">View Demo</a>
    ·
    <a href="https://github.com/ahmed-alllam/AlphaLogos/issues">Report Bug</a>
    ·
    <a href="https://github.com/ahmed-alllam/AlphaLogos/issues">Request Feature</a>
  </p>
</div>


<!-- ABOUT THE PROJECT -->


## About The Project

AlphaLogos is a logic synthesis optimization tool that takes a logic circuit and optimizes it using the Quinn-McCluskey algorithm. You can access the project demo using this [link](http://alphalogos2-516469619.eu-west-3.elb.amazonaws.com/).

> **Note**
> This project is still under development and is not yet ready for deployment!


## Tech Stack

The project utilizes the following technologies and libraries:

* [![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
* [![Docker](https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white)](https://www.docker.com/)
* [![Crow](https://img.shields.io/badge/Crow-800000?style=for-the-badge)](https://github.com/CrowCpp/Crow)
* [![Boost](https://img.shields.io/badge/Boost-FF6F61?style=for-the-badge&logo=boost&logoColor=white)](https://www.boost.org/)
* [![Jinja2](https://img.shields.io/badge/Jinja2CppLight-B41717?style=for-the-badge)](https://github.com/hughperkins/Jinja2CppLight)
* [![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)](https://cmake.org/)
* [![Catch2](https://img.shields.io/badge/Catch2-B5177B?style=for-the-badge)](https://github.com/catchorg/Catch2)


## Building and Running the Project

To build and run the AlphaLogos project using Docker, follow the steps below:

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/ahmed-alllam/alphalogos.git
   cd alphalogos
   ```

2. **Build the Docker Image**:
   ```bash
   docker build -t alphalogos:latest .
   ```

3. **Run the Docker Container**:
   ```bash
   docker run -p 8000:8000 alphalogos
   ```

4. **Access the Application**:
   After executing the commands above, open your browser and navigate to `http://localhost:8000` to access the application.


<!-- CONTACT -->
## Created By

Ahmed Allam - [LinkedIn](https://linkedin.com/in/ahmed-e-allam) - ahmedeallam@aucegypt.edu - 900214493

Mohamed Mansour - Hamdy47@aucegypt.edu - 900222990

Mohamed Abdelmagid - [LinkedIn](https://www.linkedin.com/in/mohamed-abdelmagid-3aab51195/) - mabdelmagid@aucegypt.edu - 900223215


<!-- MARKDOWN LINKS & IMAGES -->
[contributors-shield]: https://img.shields.io/github/contributors/ahmed-alllam/AlphaLogos.svg?style=for-the-badge
[contributors-url]: https://github.com/ahmed-alllam/AlphaLogos/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/ahmed-alllam/AlphaLogos.svg?style=for-the-badge
[forks-url]: https://github.com/ahmed-alllam/AlphaLogos/network/members
[stars-shield]: https://img.shields.io/github/stars/ahmed-alllam/AlphaLogos.svg?style=for-the-badge
[stars-url]: https://github.com/ahmed-alllam/AlphaLogos/stargazers
[issues-shield]: https://img.shields.io/github/issues/ahmed-alllam/AlphaLogos.svg?style=for-the-badge
[issues-url]: https://github.com/ahmed-alllam/AlphaLogos/issues
[license-shield]: https://img.shields.io/github/license/ahmed-alllam/AlphaLogos.svg?style=for-the-badge
[license-url]: https://github.com/ahmed-alllam/AlphaLogos/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[product-screenshot]: images/screenshot.png
