# CaMykS

## What is CaMykS?

CaMykS is a CMS ("Content Management System"). More precisely, it's a tool used to build then manage and update a website. This is done online through a compatible web browser.

CaMykS is made to be the more flexible and ergonomic as possible into the two main steps of the lifetime of a website - building and managing.


## CaMykS features

CaMykS have several features that makes it powerful. It is multi-site, multilingual, collaborative and plugin-based to allow easy customisation. Management interface ergonomics has been a key-point during development. CaMykS is using the latest technologies such as Wysiwyg edition, RSS feeds, AJAX and many more.

[Read more, in french](http://www.camyks.net/benefits.htm)

## Requirements

CaMykS is working on LAMP (Linux/Apache/MySQL/PHP) or MAMP (Mac OS X/Apache/MySQL/PHP) systems.

We advise to suit the following versions:
* Apache 2.0+ (+ Module Rewrite)
* MySQL 5.5+
* PHP 5+ (version 5.6 advised, version 7 is currently untested)

## Getting started with CaMykS

Duplicate and rename the `skeleton_site` folder located in engine folder to the root base of your web server.

For a single-site installation, move CaMykS folder into the website folder.

Edit `site.php.inc` configuration file located in the etc folder.

Open `index.php` or `admin.php` from your web browser to finalise your website installation.

## Running CaMykS in docker
### Building the docker container

``
docker build -t camyks:latest .
``

### Running the container

``
docker run -h camyks --name camyks -p 8081:80 -it camyks:latest
``

And if you want to login to the container to look around

``
 docker exec -it camyks  /bin/bash
``

## License

CaMykS is available under [GNU GPL](http://www.gnu.org/licenses/licenses.en.html) licence.

## Contacts

CaMykS is now maintained and hosted by [Ideogram Design](http://www.ideogram-design.fr)

You can contact us using : 
* [Ideogram Design website](http://www.ideogram-design.fr)
* [Github](https://github.com/Dj1b/CaMykS)

## Acknowlegments

Thanks to Fanny, Frank and Ludo for their help and support.
