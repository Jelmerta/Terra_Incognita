Terra_Incognita
Surely the start of a big new MMORPG

This project requires CMake and Emscripten to build. We currently use VS Code with the CMake extension to build the project. Run emcmake cmake to build and then run make.

To run the project locally, we need to run it in a web server, to fully enable WebGL. For example through: "python -m http.server", and then go to your local directory where the built files are, I.E. http://localhost:8000/projects/Terra_Incognita/build/kloenk.html.

When deployed to the main branch, we deploy the game to a web service, such that it can be played online within minutes.