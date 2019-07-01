# Learning about graphics with OpenGL 

This project is a small OpenGL demo application that I built to learn graphics programming. Rather than a properly designed and abstracted rendering engine, it is a simple learning tool to help me work may way through the basics of rendering and graphics.

This is my first graphics project, so my emphasis is on understanding the rendering pipeline, organizing my classes around the API, and thinking about how the application should handle the management of windows, scenes, events, and other relatively low-level concerns.

Once I have a better handle on these details, I'll be adding more interesting demos and eventually switch my focus to more advanced shader code.

The UI is built with [Dear ImGui](https://github.com/ocornut/imgui.git).

## Getting started

For now this demo is only supported on Windows and must be built with Visual Studio 2017 Platform Toolset v141.

### Pre-requisites

- Visual Studio 2017 with Platform Toolset: Visual Studio 2017 v141
- Graphics support for OpenGL 4.6

### Build steps

1. Clone repository with **--recurse-submodules**
1. Run build script from **Developer Command Prompt for VS2017**

Example: clone with SSH and build
```git
git clone git@github.com:brockyates/learning-opengl.git --recurse-submodules
cd graphics
BuildVS2017.bat
```

## Credits and Learning Resources

### Online

- [docs.GL OpenGL API Documentation](http://docs.gl/)
- [OpenGL 4.6 Quick Reference Card](https://www.khronos.org/files/opengl46-quick-reference-card.pdf)
- [Anton's OpenGL 4 Tutorials](http://antongerdelan.net/opengl/)
- [Anton's 3d Maths Cheat Sheet](http://antongerdelan.net/teaching/3dprog1/maths_cheat_sheet.pdf)
- [Learn OpenGL](https://learnopengl.com/)
- [opengl-tutorial](http://www.opengl-tutorial.org/)
- [OpenGL 4.6 Specification](https://www.khronos.org/registry/OpenGL/specs/gl/glspec46.core.pdf)

### Youtube

- [TheChernoProject Game Engine Series](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT)
- [TheChernoProject OpenGL Series](https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)
- [ThinMatrix's OpenGL 3D Game Tutorials](https://www.youtube.com/playlist?list=PLRIWtICgwaX0u7Rf9zkZhLoLuZVfUksDP)
- [Jamie King's 3D Computer Graphics Using OpenGL Series](https://www.youtube.com/playlist?list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY)
- [thebennybox 3D Rendering and Game Engine Playlists](https://www.youtube.com/user/thebennybox/playlists)
- [3Blue1Brown Math Playlists](https://www.youtube.com/channel/UCYO_jab_esuFRV4b17AJtAw)

### Books

- Fundamentals of Computer Graphics Book by Steve Marschner and Peter Shirley
- OpenGL 4 Shading Language Cookbook Book by David Wolff
- Real-Time Rendering, Fourth Edition Book by Eric Haines, Naty Hoffman, and Tomas Möller
- Physically Based Rendering: From Theory to Implementation Book by Matt Pharr and Wenzel Jakob
- Mathematics for 3D Game Programming and Computer Graphics Book by Eric Lengyel

### Utilities

- [RenderDoc Graphics Debugger](https://renderdoc.org/)

## License

OpenGL Graphics Demo is licensed under the MIT License, see [LICENSE](https://github.com/brockyates/graphics/blob/master/LICENSE.txt) for more information.
