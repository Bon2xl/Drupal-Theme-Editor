Prerequisite
Please install the following 
----------------------
- XCode [https://developer.apple.com/xcode/download/]
- Homebrew [http://brew.sh/] 
- NVM [https://github.com/creationix/nvm]



Installation
****** To make all this work, install and run modules inside assets/ folder. *******
----------------------

Package.json ******
- Please make sure the line of code below is include in your /assets/package.json. If not please manually add it.
  "scripts": {
    "postinstall": "find node_modules/ -name '*.info' -type f -delete"
  },
- The script above prevents npm not to download files that has .info extension.

Node
- nvm install 0.10.40
- nvm use 0.10.40
- nvm alias default 0.10

Bower
- sudo npm install -g bower
- bower install

Grunt  
- sudo npm install -g grunt-cli
- sudo npm install --unsafe-perm

Then run 'grunt'....


REQUIREMENTS
----------------------
NVM : latest version
Node : v0.10.40
Npm : 1.4.28


Notes
----------------------
Development CSS/JS: 
  - 'grunt' will compile scss and js files.
  - 'grunt watch' will watch all the changes you do in SCSS and JS and compile it.
  - 'grunt build' will build all the palettes inside the current theme and will also create a separate CSS for IE9
  
Javascript 
  - Make sure 'grunt watch' is running.
  - To add new script or function go inside js/modules and add a new file. Grunt will take care of compiling them into one file 'js/app.js'."

    - cd assets/
    - 'grunt watch'

    - /assets/js/modules/
        - newJSFunction.js

    compiled to.

    - /assets/js
        - app.js
